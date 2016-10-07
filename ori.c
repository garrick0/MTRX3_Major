/* receives and tests strength */
// method 2: RSSI PWM 64us, 24-100% duty
// method 1: get the 7th byte in api mode
#include "p18f452.h"
#include <stdio.h>
#include <stdlib.h>
#include "pconfig.h"
#include "spi.h"
#include "ConfigRegs.h"
#include "delays.h"
#include "usart.h"
#define BIT0 0x01
void initUSART(void);
void read_ISR(void);
void sendCommand(char *ptr0);
 void delay(void);

#pragma interrupt chk_isr // used for high only
void chk_isr (void){
    read_ISR();
}
#pragma code highPrior = 0x0008 // high priority
void highPrior (void){
    _asm
    goto    chk_isr 
    _endasm
}
#pragma code
// method 1
char ATCommand0[] = "+++"; //Initialize AT Command Mode.
//char ATCommand1[] = "ATAP0\r"; // API mode for coordinator 
//char ATCommand2[] = "ATBD3\r"; // Set up Baud Rate: 9600
char ATCommand3[] = "ATCE1\r"; // Coordinator Enabled.
char ATCommand4[] = "ATCN\r"; // End AT Command Mode.
//char startByte = 0x7E;
int counter;
unsigned char cycles = 256;
char *ptr0;
// method 1

// method 2
int delayPeriod = 8;
// method 2

// Variable definitions.
char r;
char chirp = 'z';
 
main(void)
 {
    // configure USART
    initUSART();
    
    // method 2
    //TRISAbits.RA0=1; // input on RA0 for RSSI pin
    //LATAbits.LATA0=1;
    // method 2
    
    while (1);
 }
 
 void initUSART(void)
 {
    TRISBbits.RB0=0; // output on RB0
    LATBbits.LATB0=0;
    PORTBbits.RB0=0; // test for wave
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
             USART_CONT_RX     &
             USART_BRGH_HIGH, 25 );
    //Short Pause
    // method 1
//	  Delay10KTCYx(250);
    sendCommand(ATCommand0); 
//    Delay10KTCYx(250);
  //  sendCommand(ATCommand1); 
//    Delay10KTCYx(250);
//    sendCommand(ATCommand2); 
//    Delay10KTCYx(250);
   // sendCommand(ATCommand3); 
//    Delay10KTCYx(250);
   // sendCommand(ATCommand4); 
//    Delay10KTCYx(250);
    //method 1
    
    INTCONbits.GIEH=1;      /* Enable interrupt globally*/
    INTCONbits.GIEL=1; 
    return 0;
 }
 
void read_ISR(void){

    PIR1bits.RCIF=0;//clear flag
    PORTB = PORTB^BIT0; // toggle for debug
    r = ReadUSART();
    if (TXSTAbits.TRMT == 1)
    {
        putcUSART(r); // disp read letter
    }

    return 0;
}

void sendCommand(char *ptr0){
    while (*ptr0)
    {
        if (TXSTAbits.TRMT == 1)
        {
            putcUSART(*ptr0);
            ptr0++;
        }
    }
    delay(); //Wait for an OK answer from XBee.
}
 void delay(void)
 {
     counter = 2;
     while (counter != 0)
         {
         Delay10KTCYx(+cycles);
         counter = (counter - 1);
         }    
 } 