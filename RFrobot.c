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
void write_ISR(void);

#pragma interrupt chk_isr1 // used for high only
void chk_isr (void){
    read_ISR();
}
#pragma code highPrior = 0x0008 // high priority
void highPrior (void){
    _asm
    goto    chk_isr1 
    _endasm
}
#pragma code
#pragma interrupt chk_isr2 // used for low only
void chk_isr (void){
    write_ISR();
}
#pragma code lowPrior = 0x0018 // low priority
void highPrior (void){
    _asm
    goto    chk_isr2 
    _endasm
}
#pragma code
char instruct[20], pw = [20], got[] = "*g\r", buf[100], sendBuf[100];
char *rcPtr, *txPtr, *fillPtr;
int stage = 0;
int i,j,k;
const int idle = 0, msgRec = 1, msgReceived = 2, respondSend = 5, responding = 6,  done = 7;

main(void)
 {
    rcPtr = &buf[0];
    PORTBbits.RB0 = 0;
    // configure USART
    initUSART();
    while (1){
        if(PORTBbits.RB0 == 1){
            PORTBbits.RB0 = 0;
            stage++;
        }
        switch(stage){
            case msgReceived:
                // check password discard all chirps
                stage++;
                break;
            case respondSend:
                // send response
                fillPtr = &got[0];
                j = 0;
                while(*fillPtr){
                    sendBuf[j] = *fillPtr;
                    j++;
                    fillPtr++;
                }
                txPtr = &sendBuf[0];
                PIE1bits.TXIE = 1;
                putcUSART(*txPtr);
                stage ++;
                break;
            case done:
                stage = 0;
                break;
        }
    }
 }
 
void initUSART(void)
{
   TRISBbits.RB0=0; // output on RB0 as flag
   LATBbits.LATB0=0;
   PORTBbits.RB0=0; // 
   //PORTC Bit 6 Is TX (PIN 25)
   TRISCbits.TRISC6 = 0;
   //PORTC Bit 7 Is RX (PIN 26)
   TRISCbits.TRISC7 = 1;
   //Short Pause
   Delay10KTCYx(250);
   //allow for priority, read - high write - low
   RCONbits.IPEN = 1;
   IPR1bits.RCIP = 1;
   IPR1bits.TXIP = 0;
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
    rcPtr++;
    if(*rcPtr == 0x00){
        rcPtr = &response[0];
    }
    *rcPtr = ReadUSART();
    if(*rcPtr == CR || *rcPtr == '*'){
        PORTBbits.RB0 = 1;
    }
    return 0;
}
void write_ISR(void){

    PIR1bits.TXIF=0; // clear flag
    txPtr++;
    if(*txPtr == 0x00){
        PORTBbits.RB0 = 1;
        PIE1bits.TXIE = 0;
    }
    putcUSART(*txPtr);
    return 0;
}

 