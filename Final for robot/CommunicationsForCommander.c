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
#define BIT4 0x10
#define startChar 'K'
#define endChar 'O'
#define sep '*'
#define comma ','
#define endBuf 0xFF
#define valMask 0x0F

/**
 * @brief Initiate the USART communications on the Commander
 * @usage allows the 2 RF modules to communicate to each other 
 */
void commsSetupCommander(void) {
    
    OpenUART(); // set up UART 
    // TX - pin default - B4
    // RX - pin B1     
    INTCON2bits.RBPU = 0; //PORTB internal pull-ups enabled
    PORTB=PORTB&(~(BIT1|BIT4)); //set PORTB pin 1 & 4 as 0
    TRISB = (TRISB|BIT1)&(~BIT4); //set PORTB 0:3 pins to inputs and 4:7 pins as outputs
    ADCON1=0x0F; //set all PORTS as digital I/O 

    //interrupt setup for xBee signal capture
    INTCON3bits.INT1IE = 1;	//enable PORTB1 interrupt
    INTCON3bits.INT1IP = 1;	//set PORTB1 interrupt to high priority
    INTCON3bits.INT1IF = 0;	//clear PORTB1 interrupt flag
    INTCON2bits.INTEDG1 = 0; //PORTB1 interrupt on falling edge

    return 0;
}
/**
 * @brief send the data package from commander to robot 
 * @param which area is the instruction directed at (IR,RSSI,...)
 * @param the message/instruction (eg value to write to wheels);
 */
char startString[] = {startChar,NULL};
char endString[] = {endChar,NULL};
// system: 
// + : to read 
// - : to write 
char IR[] = "+1";
char RSSI[] = "+2";
char ENC[] = "+3";
char PWM[] = "-1";
char MOVE[] = "-2";
void transmitDataCommander(char* identifier, char* instruction, char *checkSum) {
    
    putsUART(startString); // send the package that indicates the start
    putsUART(identifier); // sends the identifier for which instruction
    putsUART(instruction); // sends the instruction
    WriteUART(checkSum); // send security check measure for instruction
    putsUART(endString); // send the package that indicates the end 
    
    return 0;
}

/**
 * @brief interrupt routine for receive 
 * @usage directly saves received data into a circular buffer due to the time constraints of SW serial
 */
void receiveDataCommander(void){
    
    INTCON3bits.INT1IF = 0;	//clear PORTB1 interrupt flag
    rcPtr++; // save RCREG in circular buffer
    if(*rcPtr == endBuf){
        RSSIPtr = buf;
    }
    *rcPtr = ReadUART();
    return 0;
}
/**
 * @brief creates a check sum security measure 
 * @param string of values to be sent 
 * @return sum of individual values stored 
 */
char createCheckSum( char * string){
    char checkSum = 0;
    while (*string) // while not end of string 
    {
        checkSum = checkSum + *string; 
    } 
    return checkSum;
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