/* receives and tests strength */

#include "p18f452.h"
#include <stdio.h>
#include <stdlib.h>
#include "pconfig.h"
#include "spi.h"
#include "ConfigRegs.h"
#include "delays.h"
#include "usart.h"
#include "RFmodule.h"
#include "ASCII.h"
#define BIT0 0x01

void initUSART(void);
void read_ISR(void);
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

char ATCommandStart[] = "+++"; //Initialize AT Command Mode.
char ATCommandRSSI[] = "ATDB\r"; // read signal strength
char ATCommandEnd[] = "ATCN\r"; // end command
char buffer[20];
int bufferL = 20, counter1 = 20, counter2 = 20;
int counter;
unsigned char cycles = 256;
char *ptr0;
char r;
char chirp = 'z';
char *recPtr, *writePtr;

main(void)
 {
    buffer[19] = 0x00;
    recPtr = &buffer[0];
    writePtr = &buffer[0];
    // configure USART
    initUSART();
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

   INTCONbits.GIEH=1;      /* Enable interrupt globally*/
   INTCONbits.GIEL=1; 
   return 0;
}
 
void read_ISR(void){

    PIR1bits.RCIF=0; // clear flag
    *recPtr = ReadUSART();
    recPtr++;
    if(*recPtr == 0x00){
        recPtr = &buffer[0];
    }
    return 0;
}

void delay(void)
{
   Delay10KTCYx(+cycles);
   return 0;
} 
 