#include "usart.h"
#include "p18f4520.h"
#include <stdio.h>
#include <stdlib.h>
#include "delays.h"
#define CR 0x0D
#define FULL 0xFF
#define chirpSound 'z'
#define BIT0 0x01
#define startChar 'K'
#define endChar 'O'
#define sep 0x16
#define comma ','
#define endBuf 0xFF
#define valMask 0x0F
#define numMask 0x30
#define processing 0
#define sum 2

void getRSSI(char * buffer, char * signalStrength, char * rFlag, char *CRflag);
void sendMsg(char *tx);
char createCheckSum(char * string);
void intToPackage(int* data, char* dataInChar);
void RSSIToPackage(char* RSSIval, char* dataInPack);

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
 */
char startString[] = {FULL,FULL,startChar,FULL,NULL}; // ensure it is pulled high to trigger falling edge interrupt
char endString[] = {endChar,NULL}; // return to falling edge trigger 
char separatorString[] = {sep,FULL,NULL}; // indicate the different values
void transmitData(int* IRVals,char* signalStrength,char processComplete) {
    char IRValsPackage[20]; // data in mode that can be received
    char signalStrengthPackage[20];
    char checkPackage[] = {0x30,FULL,NULL}; // process complete 
    
    intToPackage(IRVals, IRValsPackage);
    RSSIToPackage(signalStrength, signalStrengthPackage);
    checkPackage[0] = checkPackage[0]|processComplete; // process complete is sent in ASCII 1/0
    
    sendMsg(startString); // send the package that indicates the start
    sendMsg(IRValsPackage); // send IR
    sendMsg(separatorString); // separator 
    sendMsg(signalStrengthPackage); // send RSSI
    sendMsg(separatorString); // separator 
    sendMsg(checkPackage); // process complete
    sendMsg(endString); // send the package that indicates the end 
    
    return;
    
}
/**
 * @brief interrupt routine for receive 
 * @param buffer that stores all values except for chirps
 * @param flag that indicates CR
 * @usage when it detects the end bytes of the message ie the start and end
 * it toggles the flag which allows it to save
 * which means that it 1 instance of flag will cause it to save, the second will 
 * cause it to stop saving. The buffer ends with 0xFF
 */
char flag = 0x00; // for indication of save on/off
char* rcPtr;
char receiveData(char* buffer, char *CRflag){
    int gotInsFlag = 0;
    PIR1bits.RCIF=0; // clear receive flag
    
    if(RCREG == startChar){ // turn on save text flag
        flag = 1; // turn on 
        rcPtr = buffer; // point to beginning of buffer 
    }else if (RCREG == endChar){ // turn on save text flag
        flag = 0; // turn off
        rcPtr++;
        *rcPtr = endChar;
        gotInsFlag = 1; // indicate that there is ins
        return gotInsFlag; // return is instruction received
    }
     if(RCREG == CR){ // turn on save cr flag
        *CRflag = 1; // turn on 
     }
    if(flag && RCREG != chirpSound){ // when flag is turned on discard all chirps
        rcPtr++; // save RCREG in circular buffer
        if(*rcPtr == endBuf){
            rcPtr = buffer;
        }
        *rcPtr = ReadUSART();
    }
    return gotInsFlag;
}

/**
 * @brief process the received data to get instruction
 * @param main buffer that stores all received letters 
 * @param instMag pointer to store of magnitude 
 * @param store of indication of direction 
 * @param indication of command received 
 * @return 
 */
void processReceived(char* buffer, int* instMag,char* instDir,char* commandFlag) {
    //remove RSSI receive flag
    int multiplier = 1;
    buffer++; // skip the start buffer 
    buffer++;
    *instMag = 0;
    // calculate magnitude
    // the buffer is high byte then low byte
    while(*buffer != sep){
        *instMag = *instMag + (*buffer)*multiplier;
        buffer++;
        multiplier = multiplier*256; // 8 bytes
    }
    buffer++;
    *instDir = *buffer;
    *commandFlag = 1; // got command 
    return; 
}


/**
 * @brief converts string of int values into string of char in package separated by comma
 * @param string of int data
 * @param string of char data thats been converted 
 */
void intToPackage(int* data, char* dataInChar){
    while(*data){
        *dataInChar = (*data) >> 8;
        dataInChar++; // increment buffer place 
        *dataInChar = FULL; // allow for falling edge resistor to detect
        dataInChar++; // increment buffer place 
        *dataInChar = (*data) & 0xFF;
        dataInChar++; // increment buffer place 
        *dataInChar = FULL; // allow for falling edge resistor to detect
        dataInChar++;
        
        data++; // go to next 
        
        *dataInChar = comma;
        dataInChar++; // increment buffer place 
        *dataInChar = FULL; // allow for falling edge resistor to detect
        dataInChar++;
    }  
    *dataInChar = NULL; // null terminated
}

/**
 * @brief converts string of char values into string in package
 * @param string of char ASCII data terminated by CR
 * @param string of char data thats been converted and separated 
 */
void RSSIToPackage(char* RSSIval, char* dataInPack){
    RSSIval++;
    while(*RSSIval != CR){
        *dataInPack = (*RSSIval)-numMask; // get rid of type identifier
        dataInPack++; // increment buffer place 
        *dataInPack = FULL; // allow for falling edge resistor to detect
        dataInPack++;
        RSSIval++;
    }   
    *dataInPack = NULL; // null terminated 

}

/**
 * @brief requests the value of RSSI
 * @param main buffer that stores received values
 * @param buffer that stores signal strength
 * @param receive flag when instruction is received
 * @param CR flag when receive interrupt receives CR
 * @usage it waits for the most recent chirp, then sends command get into command mode
 * sends ATDB request
 * ends command mode, the RSSI is saved by the receive ISR
 */
char ATCommandStart[] = "+++"; //Initialize AT Command Mode.
char ATCommandRSSI[] = "ATDB\r"; // read signal strength
char ATCommandEnd[] = "ATCN\r"; // end command

void getRSSI(char * buffer, char * signalStrength, char * rFlag, char *CRflag){
    
    while(RCREG != chirpSound); //wait till chirp received
    sendMsg(ATCommandStart); // start command mode
    while(*CRflag != 1); // wait for CR
    *CRflag = 0; // reset
    sendMsg(ATCommandRSSI); // request RSSI
    while(*CRflag != 1); // wait for CR
    *CRflag = 0; // reset
    sendMsg(ATCommandEnd); // end AT mode
    while(*CRflag != 1); // wait for CR
    *CRflag = 0; // reset
    // reset the received flag
    *rFlag = 0;
    buffer ++; // originally pointing to the start byte
    buffer ++; // skip start byte 
    while(*buffer != endChar){
        *signalStrength = *buffer; // save the signal strength
        signalStrength++;
        buffer++;
    }
    *signalStrength = NULL; 
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
        tx++;  
    } 

}
/**
 * @brief creates a check sum security measure 
 * @param string of values to be sent 
 * @return sum of individual values stored 
 */
// note , the max of the values is EF for sending to commander because first bit cannot be set
char createCheckSum(char * string){
    char checkSum = 0;
    while (*string) // while not end of string 
    {
        if(*string != FULL){ // when it is not the FF
            checkSum = checkSum + *string; 
        }      
    } 
    if (checkSum>0xEF){ // cap at EF 
        checkSum = 0xEF;
    }
    return checkSum;
}