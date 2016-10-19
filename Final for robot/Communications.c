#include "usart.h"
#include "p18f4520.h"
#include <stdio.h>
#include <stdlib.h>
#include "pconfig.h"
#include "ConfigRegs_18F4520.h"
#define CR 0x0D
#define FULL 0xFF
#define chirpSound 'z'
#define BIT0 0x01
#define startChar 'K'
#define endChar 'O'
#define sep '*'
#define comma ','
#define endBuf 0xFF
#define valMask 0x0F
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

    return 0;
}
/**
 * @brief send the data package from robot to commander 
 * @param values for IR in char form (Null terminated)
 * @param values for signal strength in char form(Null terminated)
 * @param valuse for encoder values in char form (Null terminated)
 */
char startString[] = {FULL,startChar,FULL,NULL};
char endString[] = {FULL,endChar,FULL,NULL};
char separatorString[] = {sep,FULL,NULL};
void transmitData(char* IRValsPackage, char* signalStrengthPackage, char* currentEncoderValsPackage, char checkSum) {
    char checkSumPackage[] = {checkSum,FULL};
    //while(RCREG != chirpSound); // wait till chirp is done then take chance to send data avoid confusion 
    sendMsg(startString); // send the package that indicates the start
    sendMsg(IRValsPackage); // send IR
    sendMsg(seperatorString); // separator 
    sendMsg(signalStrengthPackage); // send RSSI
    sendMsg(seperatorString); // separator 
    sendMsg(currentEncoderValsPackage); // send encoder 
    sendMsg(seperatorString); // separator 
    sendMsg(checkSumPackage); // security
    sendMsg(endString); // send the package that indicates the end 
    
    return 0;
}
/**
 * @brief converts string of int values into string of char in package separated by comma
 * @param string of int data
 * @param string of char data thats been converted 
 */
void intToPackage(int* data, char* dataInChar){
    int alg, algDiv; // algebra to convert int to char
    while(*data){
        alg = *data;
        while(alg){
            algDiv = alg/10; // get rid of smallest 1 places 
            *dataInChar = alg - algDiv*10; // save smallest 1 places
            alg = algDiv;
            dataInChar++; // increment buffer place 
            *dataInChar = FULL; // allow for falling edge resistor to detect
            dataInChar++;
        }
        data++;
        *dataInChar = comma;
        dataInChar++; // increment buffer place 
        *dataInChar = FULL; // allow for falling edge resistor to detect
        dataInChar++;
    }  
    *dataInChar = NULL; // null terminated
    return 0;
}
/**
 * @brief converts string of char values into string in package
 * @param string of char ASCII data
 * @param string of char data thats been converted and separated 
 */
void RSSIToPackage(char* RSSIval, char* dataInPack){

    while(*RSSIval){
        *dataInPack = *RSSIval&valMask; // get rid of first byte 
        dataInPack++; // increment buffer place 
        *dataInPack = FULL; // allow for falling edge resistor to detect
        dataInPack++;
    }   
    *dataInPack = NULL; // null terminated 
    return 0;
}
/**
 * @brief interrupt routine for receive 
 * @usage when it detects the end bytes of the message ie the start and end
 * it toggles the flag which allows it to save
 * which means that it 1 instance of flag will cause it to save, the second will 
 * cause it to stop saving. The buffer ends with 0xFF
 */
char flag = 0x00; // for indication of save on/off
void receiveData(void){
    
    PIR1bits.RCIF=0; // clear receive flag
    
    if(RCREG == startChar){ // turn on save text flag
        flag = 1; // turn on 
        rcPtr = buf; // point to beginning of buffer 
    }else if (RCREG == endChar){ // turn on save text flag
        flag = 0; // turn off
    }
    if(flag && RCREG != chirpSound){ // when flag is turned on discard all chirps
        rcPtr++; // save RCREG in circular buffer
        if(*rcPtr == endBuf){
            RSSIPtr = buf;
        }
        *rcPtr = ReadUSART();
    }
    return 0;
}
/**
 * @brief requests the value of RSSI
 * @usage it waits for the most recent chirp, then sends command get into command mode
 * sends ATDB request
 * ends command mode, the RSSI is saved by the receive ISR
 */
const char ATCommandStart[] = "+++"; //Initialize AT Command Mode.
const char ATCommandRSSI[] = "ATDB\r"; // read signal strength
const char ATCommandEnd[] = "ATCN\r"; // end command
void getRSSI(void){
    
    while(RCREG != chirpSound); //wait till chirp received
    sendMsg(ATCommandStart); // start command mode
    while(RCREG != CR);
    sendMsg(ATCommandRSSI); // request RSSI
    while(RCREG != CR);
    sendMsg(ATCommandEnd); // end AT mode

    return 0;
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
        txPtr++;  
    } 
    return 0;
}
/**
 * @brief creates a check sum security measure 
 * @param string of values to be sent 
 * @return sum of individual values stored 
 */
// note , the max of the values is EF for sending to commander because first bit cannot be set
char createCheckSum( char * string){
    char checkSum = 0;
    while (*string) // while not end of string 
    {
        checkSum = checkSum + *string; 
    } 
    if (checkSum>0xEF){
        checkSum = 0xEF;
    }
    return checkSum;
}