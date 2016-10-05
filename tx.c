/* acts as test bird and transmits chirp 'Z' at 15Hz */
#include "p18f452.h"
#include <stdio.h>
#include <stdlib.h>
#include "pconfig.h"
#include "spi.h"
#include "ConfigRegs.h"
#include "delays.h"
#include "usart.h"
#define ON 1
#define OFF 0 
#define BIT0 0x01

void init(void);
void delay(void);
void wave_30(void);
void sendCommand(char *ptr0);

#pragma interrupt chk_isr // used for high only
void chk_isr (void){
    if(PIR2bits.CCP2IF == 1){
        wave_30();
    }
}
#pragma code highPrior = 0x0008 // high priority
void highPrior (void){
    _asm
    goto    chk_isr
    _endasm
}
#pragma code

 // Variable definitions.
 int counter, i, j;
 
 char ATCommand0[] = "+++\r"; //Initialize AT Command Mode.
 char ATCommand1[] = "ATID000A\r"; //Set up the PAN ID.
 char ATCommand2[] = "ATAP0\r"; // API mode for coordinator // changed
 char ATCommand3[] = "ATBD3\r"; //Set up Baud Rate: 9600
 char ATCommand4[] = "ATCE1\r"; //Coordinator Enabled.
 char ATCommand5[] = "ATCN\r"; //End AT Command Mode.
 char chirp[] = "Z"; //transmit mode chirp
 
main(void)
 {
    // timer setup
    TRISBbits.RB0=0; // output on RB0
    LATBbits.LATB0=0;
    PORTBbits.RB0=0; // test for wave
    
    T3CON=0x39; // 8 bit R/W mode, CCP2 = timer3 CCP1 = timer 1,pre-scale of 8, internal clock
    CCP2CON=0x0A; // Compare mode, interrupt on match and manually,interrupt on match
    
    CCPR2H=0xF4; // 2Hz
    CCPR2L=0x24;
    
    TMR3H=0; // start at 0 start counting up
    TMR3L=0;
    
    PIE2bits.CCP2IE=ON;//allow interrupt for CCP2
    PIR2bits.CCP2IF=OFF;//clear flag
    
    
//PORTC Bit 6 Is TX (PIN 25)
	TRISCbits.TRISC6 = 0;
//PORTC Bit 7 Is RX (PIN 26)
	TRISCbits.TRISC7 = 1;

//Short Pause
	Delay10KTCYx(250);

//Configure USART - 9600 Baud
  OpenUSART( USART_TX_INT_OFF  &
             USART_RX_INT_OFF  &
             USART_ASYNCH_MODE &
             USART_EIGHT_BIT   &
             USART_CONT_RX     &
             USART_BRGH_HIGH, 25 );

//Short Pause
	Delay10KTCYx(250);
    
    // timer set up end
//    
//    // RF set up 
//     init(); //Initialize ports and set up status.
//     delay(); //Wait for the XBee to initialize.
//     sendCommand(ATCommand0); 
//     sendCommand(ATCommand1); 
//     sendCommand(ATCommand2); 
//     sendCommand(ATCommand3); 
//     sendCommand(ATCommand4); 
//     sendCommand(ATCommand5); 
//     // RF set up end
//     
     // Send chirp @ 2Hz
    INTCONbits.GIEH=1;      /* Enable interrupt globally*/
    INTCONbits.GIEL=1; 
    
    while (1);
 }
 
 void init(void)
 {
     // Port Directions: 1=input, 0=output
     // RC7Out - Din in XBee, RC6In - Dout in XBee
     TRISC = 0x01; //Set up the port C, RC6-Out, RC7-In.
     // Set up the USART
     PIE1 = 0x00; //Interruptions disabled.
     PIR1 = 0x10; //Binary of 0001 0000, verify if transmit buffer is empty.
     INTCON = 0x00; //Disable global interruptions.
     
    TXSTAbits.BRGH=1;        /* Set baud rate to high*/
    SPBRG=25;                /* 9600 baud*/
    TXSTAbits.SYNC=0;	     /* Enable asynchronous transmit*/
    RCSTAbits.SPEN=1;	     /* Serial port enable*/
    TXSTAbits.TXEN=1;	     /* Enable transmit*/
    RCSTAbits.CREN=1;	     /* Enables continuous receive */
 }
 
 void delay(void)
 {
     counter = 5;
     while (counter != 0)
         {
         Delay10KTCYx(+cycles);
         counter = (counter - 1);
         }    
 } 
 
 void wave_30(void){
    TMR3H=0;//start at 0 start counting up
    TMR3L=0;
    PIR2bits.CCP2IF=0;//clear flag
    PORTB = PORTB^BIT0; // toggle
    ptr0 = chirp;
//    if (TXSTAbits.TRMT == 1)
//    {
//        TXREG = *ptr0; //Write data in the TXREG to be sent            
//        *ptr0++; //Increment value of pointer
//    }
    putcUSART('z');
}
 
 void sendCommand(char *ptr0){
    while (*ptr0)
    {
        if (TXSTAbits.TRMT == 1)
        {
            TXREG = *ptr0; //Write data in the TXREG to be sent            
            *ptr0++; //Increment value of pointer
        }
    }
    delay(); //Wait for an OK answer from XBee.
 }