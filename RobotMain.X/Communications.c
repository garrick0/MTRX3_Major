#include "usart.h"
#include "p18f4520.h"

#include <stdio.h>
#include <stdlib.h>
#include "delays.h"
#define CR 0x0D
#define FULL 0xFF
#define chirpSound 'z'
#define BIT0 0x01
#define startCh 'K' //4B
#define safety '^' // 5E
#define shake '~' // 7F
#define endChar 'O' //4F
#define endBuf 0xFF
#define valMask 0x0F
#define lowMask 0xF0
#define numMask 0x30
#define processing 0
#define sum 2

void sendMsg(char *tx);
void sendAT(char *tx);
/**
 * @brief Initiate the USART communications on the robot 
 * @usage allows the 2 RF modules to communicate to each other 
 */
void commsSetup(void) {
     //PORTC Bit 6 Is TX (PIN 25)
    TRISCbits.TRISC6 = 0;
    //PORTC Bit 7 Is RX (PIN 26)
    TRISCbits.TRISC7 = 1;
    //Short Pause
    Delay10KTCYx(250);
    //Configure USART - 9600 Baud
    OpenUSART( USART_TX_INT_OFF  &
             USART_RX_INT_ON  &
             USART_ASYNCH_MODE &
             USART_EIGHT_BIT   &
             USART_CONT_RX &
             USART_BRGH_HIGH, 64 );
    
}
/**
 * @brief send the data package from robot to commander 
 * @param values for IR in int form (Null terminated)
 * @param values for signal strength in char form (Null terminated)
 * @param the indication if the process is complete
 * @return done 
 */
char startString[] = {startCh,safety,NULL};
char endString[] = {endChar,NULL}; // extra to ensure
void transmitData(char* IRVals,char* signalStrength,char processComplete) {
    char i = 0;
    char checkPackage[] = {0x10,NULL}; // process complete and check sum    
    char IRpack[] = {0x20,0x20,0x20,0x00}; // process IRvalues 
    checkPackage[0] = checkPackage[0]|processComplete;
    while(i<3){ // package IR 
        IRpack[i] = IRpack[i]|(*IRVals);
        IRVals++;
        i++;
    }
    sendMsg(startString); // send the package that indicates the start
    sendMsg(IRpack); // send IR
    sendMsg(signalStrength); // send RSSI
    sendMsg(checkPackage); // process complete flag
    sendMsg(endString); // send the package that indicates the end 
    return;
}
/**
 * @brief interrupt routine for receive 
 * @param buffer to save the string 
 * @param the flag to indicate carriage return
 * @return instruction received
 * @usage when it detects the end bytes of the message ie the start and end
 * it toggles the flag which allows it to save
 * which means that it 1 instance of flag will cause it to save, the second will 
 * cause it to stop saving. The buffer ends with 0xFF
 */

char* rcPtr;
char read;
void receiveData(char* buffer, char *CRflag, char *recFlag, char *saveF){
    PIR1bits.RCIF=0; // clear receive flag
    read = ReadUSART();
    *recFlag = 0;
    if(read == startCh){ // turn on save text flag
        *saveF = 1; // turn on 
        rcPtr = buffer; // point to beginning of buffer 
    }else if (read == endChar){ // turn on save text flag
        *saveF = 0; // turn off
        *recFlag = 1; // indicate that there is ins
    }
    if(read == CR){ // turn on save CR flag
        *CRflag = 1; // turn on 
     }
    if(*saveF && read != chirpSound){ // when flag is turned on discard all chirps
        *rcPtr = read; // save
        rcPtr++; // save RCREG in circular buffer
        if(*rcPtr == endBuf){
            rcPtr = buffer;
        }
    }
    return;
}
/**
 * @brief process the received data
 * @param the buffer that saves received data
 * @param the magnitude
 * @param the direction 
 * @param the flag that indicates command is received
 * @return done 
 */
char gotIt[] = "K^~O";
char test;
char processReceived(char* buffer, int* instMag,char* instDir,char* commandFlag) {

    int i = 0, j = 0;
    while(*buffer != startCh){
        buffer++;
    }
    buffer++;
    if(*buffer != safety){ // failed read
        return;
    }
    buffer++;
    if (*buffer == shake){ // check if hand shaking 
        sendMsg(gotIt);
    }
    *instMag = 0;
    test = (*buffer)&0x0F0;
    if(test == 0x010){

        while(j<4){
            *instMag = *instMag << 4;
            *instMag = (*instMag) | (*buffer)&valMask;
            buffer++; 
            j++;
        }          
    }else{
        return;
    }

    *instDir = (*buffer)&0x0F;
    
    *commandFlag = 1; // got command time for action
    return 0; // reset the instruction received flag
}
/**
 * @brief requests the value of RSSI
 * @usage it waits for the most recent chirp, then sends command get into command mode
 * sends ATDB request
 * ends command mode, the RSSI is saved by the receive ISR
 */
char ATCommandStart[] = "+++"; //Initialize AT Command Mode.
char ATCommandRSSI[] = "ATDB\r"; // read signal strength
char ATCommandEnd[] = "ATCN\r"; // end command


void getRSSI(char * buffer, char * signalStrength, char * rFlag, char *CRflag, char *saveF){
    int count = 5000000;
    while(RCREG != chirpSound && count > 0){
        count --;
    }
    if (count == 0){
        *signalStrength = 0x30;
        signalStrength++;
        *signalStrength = NULL; // null terminated
        return;
    }
    sendAT(ATCommandStart); // start command mode
    while(*CRflag != 1); // wait for CR
    *CRflag = 0; // reset
    sendAT(ATCommandRSSI); // request RSSI
    while(*CRflag != 1); // wait for CR
    *CRflag = 0; // reset
    sendAT(ATCommandEnd); // end AT mode
    while(*CRflag != 1); // wait for CR
    *CRflag = 0; // reset
    // reset the received flag 
    *saveF = 0; //since it ends with K disable flag
    *rFlag = 0;
    while(*buffer != CR){
        buffer ++;
    }
    buffer++;
    while(*buffer != CR){
        *signalStrength = *buffer;
        signalStrength++;
        buffer++;
    }
    *signalStrength = NULL; // null terminated
    return;
}

/**
 * @brief transmits string to other RF module on robot 
 * @param pointer to the string to be sent (NULL terminated)
 * @param pointer to the password representing type of instruction/response (NULL terminated)
 */
void sendMsg(char *tx){
    
    while (*tx) // send string
    {
        while (TXSTAbits.TRMT != 1); // wait till transmit buffer is empty
        putcUSART(*tx); // write  
        while (TXSTAbits.TRMT != 1); // wait till transmit buffer is empty
        putcUSART(FULL); // write FF to ensure that the falling edge is reset
        tx++;  
    } 

}

void sendAT(char *tx){
    
    while (*tx) // send string
    {
        while (TXSTAbits.TRMT != 1); // wait till transmit buffer is empty
        putcUSART(*tx); // write  
        tx++;  
    } 

}