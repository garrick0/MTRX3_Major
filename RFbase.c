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
#define NULL 0x00
#define CR 0x0D

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
int i,j,k;
char pwIR = "*1", pwEN = "*2", pwW = "*3", pwRSSI = "*4";
char pwSetting[] = [&pwIR[0],&pwEN[0],&pwW[0],&pwRSSI[0]], pwOption;
char instruct[] = "eg\r";
char buf[100] = {0x01}, response[20] = {0x01}, sendBuf[100];
char *rcPtr, *txPtr, *rtPtr, *fillPtr;
int stage = 1; // default for testing
const int idle = 0, pwfill = 1, instSend = 2, instSending = 3, wait =  4, done = 5;

main(void)
 {
    // both buffers are null terminated
    buf[(sizeof(buf)/sizeof(char)) - 1] = NULL;
    buf[(sizeof(buf)/sizeof(char)) - 1] = NULL;
    rcPtr = &buf[0]; // set initial save in buffer
    rcPtr = &buf[0]; // point to saved location
    PORTBbits.RB0 = 0;
    // poll for what instruction
    pwOption = 1; // default for testing
    // also set stage here
    // configure USART
    initUSART();
    while (1){
        if(PORTBbits.RB0 == 1){ // flag check
            PORTBbits.RB0 = 0;
            stage++;
        }
        switch(stage){
            case pwfill: // send password
                fillPtr = pwSetting[pwOption];
                j = 0;
                while(*fillPtr){
                    sendBuf[j] = *fillPtr;
                    j++;
                    fillPtr++;
                }
                stage++; // enter sending stage
                break;
            case instSend: // sending instruction
                fillPtr = &instruct[0];
                while(*fillPtr){
                    sendBuf[j] = *fillPtr;
                    j++;
                    fillPtr++;
                }
                txPtr = &sendBuf[0];
                PIE1bits.TXIE = 1;
                putcUSART(*txPtr);
                stage++; // enter sending stage
                break;
            case wait: // start waiting for response
                stage++;
                break;
            case done:
                // check if received
                i = 0;
                while(*rtPtr){ // save in circular buffer
                    response[i] = *rtPtr;
                    i++;
                    rtPtr++;
                    if(*rtPtr == 0x00){
                        rtPtr = &buf[0];
                    }
                }
                stage = idle; // return to idle
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
    if(*rcPtr == 0x00){ // circular buffer
        rcPtr = &buf[0];
    }
    *rcPtr = ReadUSART();
    if(*rcPtr == CR){
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

 