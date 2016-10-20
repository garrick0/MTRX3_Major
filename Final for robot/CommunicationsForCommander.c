#include "sw_uart.h"
#include "p18f4520.h"
#include <stdio.h>
#include <stdlib.h>
#include "pconfig.h"
#include "ConfigRegs_18F4520.h"
#include "delays.h"
#define CR 0x0D
#define FULL 0xFF
#define chirpSound 'z'
#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT4 0x10
#define startChar 'K'
#define endChar 'O'
#define sep 0x16
#define comma ','
#define endBuf 0xFF
#define valMask 0x0F

/**
 * @brief Initiate the USART communications on the Commander
 * @usage allows the 2 RF modules to communicate to each other 
 */
void commsSetupCommander(void) {
    
    OpenUART(); // set up UART 
    // TX - pin C4
    // RX - pin B1     
    INTCON2bits.RBPU = 0; //PORTB internal pull-ups enabled
    PORTBbits.RB2 = 0; //set PORTB pin 2
    TRISBbits.TRISB2 = 1; //set PORTB 2 to input
    ADCON1=0x0F; //set all PORTB as digital I/O 
    
    PORTCbits.RC4 = 0; // set RC4 to 0
    TRISCbits.TRISC4 = 0; // RC4 is output

    //interrupt setup for xBee signal capture
    INTCON3bits.INT2IE = 1;	//enable PORTB2 interrupt
    INTCON3bits.INT2IP = 1;	//set PORTB2 interrupt to high priority
    INTCON3bits.INT2IF = 0;	//clear PORTB2 interrupt flag
    INTCON2bits.INTEDG2 = 0; //PORTB2 interrupt on falling edge

    return 0;
}
/**
 * @brief send the data package from commander to robot 
 * @param magnitude upper lower null
 * @param direction null
 */
char startString[] = {startChar,NULL};
char separatorString[] = {sep,NULL}; // indicate the different values
char endString[] = {endChar,NULL};
void transmitDataCommander(int instMag, char instDir) {
    char magPack[10];
    char dirPack[10] = {instDir,NULL};
    intToPackage(instMag,magPack); // convert to deliverable form
    
    putsUART(startString); // send the package that indicates the start
    putsUART(magPack); // sends the identifier for which instruction
    putsUARTseparatorString); // send the separators
    putsUART(dirPack); // sends the instruction
    putsUART(endString); // send the package that indicates the end 
    
    return 0;
}
/**
 * @brief converts string of int values into string of char in package separated by comma
 * @param string of int data
 * @param string of char data thats been converted 
 */
void intToPackage(int data, char* dataInChar){
    
    *dataInChar = (*data) >> 8;
    dataInChar++; // increment buffer place 
    *dataInChar = (*data) & 0xFF;
    dataInChar++;

    *dataInChar = NULL; // null terminated
}

/**
 * @brief interrupt routine for receive 
 * @usage directly saves received data into a circular buffer due to the time constraints of SW serial
 */
char *rcPtr;
void receiveDataCommander(char* buffer){
    
    INTCON3bits.INT2IF = 0;	//clear PORTB2 interrupt flag
    rcPtr++; // save RCREG in circular buffer
    if(*rcPtr == endBuf){
        rcPtr = buffer;
    }
    *rcPtr = ReadUART();
    return 0;
}

/**
 * @brief the delay functions for UART, written for minimal board only
 * @usage written for serial read, stated number of Tosc
 */
void DelayTXBitUART(void){ //249 cycles
    Delay100TCYx(2);
    Delay10TCYx(4);
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();

}

void DelayRXHalfBitUART(void){ //121 cycles
    Delay100TCYx(1);
    Delay10TCYx(2);
    Nop();

}
void DelayRXBitUART(void){//247 cycles
    Delay100TCYx(2);
    Delay10TCYx(4);
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
  
}