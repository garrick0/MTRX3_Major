#include "p18f4520.h"
#include <stdio.h>
#include <stdlib.h>
#include "pconfig.h"
#include "spi.h"
#include "ConfigRegs_18F4520.h"
#include "delays.h"
#include "usart.h"
//#include "ASCII.h"
#include "sw_uart.h"
#include "portb.h"

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

// set UART to RB1
// set write routine same 
// read and save to circular buffer 
// do not do anything within that time frame 
void readXBee(void);
void readSerial(void);
void initUSART(void);
void DelayTXBitUART(void);
void DelayRXHalfBitUART(void);
void DelayRXBitUART(void);
void high_interrupt(void);
void low_interrupt(void);
void xBeeSetup(void);

#pragma code highPriorityInterruptAddress=0x0008
void high_interrupt(void){
 
    _asm 
    GOTO readXBee
    _endasm   
    }
#pragma code
#pragma code lowPriorityInterruptAddress=0x0018
void low_interrupt(void){
 
    _asm 
    GOTO readSerial
    _endasm   
    }
#pragma code

char buffer[50], length = 50, *rcPtr, read;

void main( void ){

    rcPtr = buffer; // point to beginning of buffer
    initUSART();
    xBeeSetup();
    putcUART(0x00);
    Delay10KTCYx(250);
    
    while(1){
        putcUART(0x16);
        Delay10KTCYx(250);
    }; 
}

#pragma interrupt readXBee
void readXBee(void) {
  	
    rcPtr++; // save RCREG in circular buffer
    if(*rcPtr == endBuf){
        rcPtr = buffer;
    }
    *rcPtr = ReadUART();
    INTCON3bits.INT1IF = 0;	//clear PORTB1 interrupt flag

}
#pragma interruptlow readSerial
void readSerial(void) {
  	
    *rcPtr = ReadUSART();
    while(TXSTAbits.TRMT != 1);
    putcUSART(*rcPtr); // print onto serial
    PIR1bits.RCIF = 0;	//clear PORTB1 interrupt flag

}
void xBeeSetup(void){
    INTCONbits.GIE_GIEH = 0;    //global interrupt disable
	INTCONbits.PEIE_GIEL = 0;   //peripheral interrupt disable
    RCONbits.IPEN = 1;		//enable priority on interrupts
    
    OpenUART(); // set up UART 
    // TX - pin default - B4
    // RX - pin B1
         
    INTCON2bits.RBPU = 0;	//PORTB internal pullups enabled
    
   // PORTA=0x00;             // set PORTA as outputs
    PORTB=0x00;             //set PORTB as outputs
    TRISB = 0x0F;       //set PORTB 0:3 pins to inputs and 4:7 pins as outputs
  //  TRISA = 0x3F;       //set PORTA 0:5 pins to inputs and 5:7 pins as outputs
    ADCON1=0x0F;        //set all PORTS as digital I/O (may have to change for f452)

    //interrupt setup for xBee signal capture
    INTCON3bits.INT1IE = 1;	//enable PORTB1 interrupt
    INTCON3bits.INT1IP = 1;	//set PORTB1 interrupt to high priority
    INTCON3bits.INT1IF = 0;	//clear PORTB1 interrupt flag
    INTCON2bits.INTEDG1 = 0;	//PORTB1 interrupt on falling edge
    
    INTCONbits.GIE_GIEH = 1;    //global interrupt enable
	INTCONbits.PEIE_GIEL = 1;   //peripheral interrupt enable
    return 0;
}

void DelayTXBitUART(void){ //249
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

void DelayRXHalfBitUART(void){ //121
    Delay100TCYx(1);
    Delay10TCYx(2);
    Nop();

}
void DelayRXBitUART(void){//247
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
void initUSART(void)
{
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
    
    IPR1bits.RCIP = 0; // low priority for serial
    
    return 0;
}   	



