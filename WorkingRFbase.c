
#include "p18f452.h"
#include <stdio.h>
#include <stdlib.h>
#include "pconfig.h"
#include "spi.h"
#include "ConfigRegs.h"
#include "delays.h"
#include "usart.h"
//#include "RFmodule.h"
//#include "ASCII.h"
#define BIT0 0x01
//#define CR 0x0D

void initUSART(void);
void read_ISR(void);

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

int i,j,k;
char pwIR[] = "*1", pwEN[] = "*2", pwW[] = "*3", pwRSSI[] = "*4";
//char *pwSetting[] = {&pwIR[0],&pwEN[0],&pwW[0],&pwRSSI[0]}, pwOption;
char instruct[] = "hi\r\n";
char buf[50], response[50], sendBuf[50];
int length = 50;
char *rcPtr, *txPtr, *rtPtr, *fillPtr;
int stage = 1; // default for testing
int idle = 0, pwfill = 1, instSend = 2, wait =  3, done = 4;

main(void)
 {
    // both buffers are null terminated
//    buf[(sizeof(buf)/sizeof(char)) - 1] = 0x00;
//    buf[(sizeof(buf)/sizeof(char)) - 1] = 0x00;

    buf[length - 1] = 0xFF;
    response[length - 1] = 0xFF;
    rcPtr = buf; // set initial save in buffer
    rtPtr = buf; // point to saved location
    PORTBbits.RB0 = 0;
    // poll for what instruction
    //pwOption = 1; // default for testing
    // also set stage here
    // configure USART
    initUSART();
    while (1){
        if(PORTBbits.RB0 == 1){ // flag check
            PORTBbits.RB0 = 0;
            stage++;
        }
        
        if(stage == pwfill){
            fillPtr = &pwIR[0];
            j = 0;
            while(*fillPtr){
                sendBuf[j] = *fillPtr;
                j++;
                fillPtr++;
            }
            stage++; // enter sending stage
        }else if(stage == instSend){
            fillPtr = instruct;
            while(*fillPtr){
                sendBuf[j] = *fillPtr;
                j++;
                fillPtr++;
            }
            sendBuf[j] = 0x00;
            txPtr = sendBuf;
            while (*txPtr)
            {
                while (TXSTAbits.TRMT != 1); // wait till transmit buffer is empty
                putcUSART(*txPtr); // write command 
                txPtr++;  
            }
            // debug debug
            Delay10KTCYx(250);
            Delay10KTCYx(250);
            Delay10KTCYx(250);
            stage = 1;
            // debug
            //stage++; // done send
            
        }else if(stage == wait){
            stage++;
            PORTBbits.RB1=1;
        }else if(stage == done){
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
            PORTBbits.RB2=1;
            stage = idle; // return to idle
        }
    }
 }
 
void initUSART(void)
{
   TRISBbits.RB0=0; // output on RB0 as flag
   LATBbits.LATB0=0;
   PORTBbits.RB0=0; // 
   TRISBbits.RB1=0; // test
   LATBbits.LATB1=0;
   PORTBbits.RB1=0; // 
   TRISBbits.RB2=0; // test
   LATBbits.LATB2=0;
   PORTBbits.RB2=0; // 
   //PORTC Bit 6 Is TX (PIN 25)
   TRISCbits.TRISC6 = 0;
   //PORTC Bit 7 Is RX (PIN 26)
   TRISCbits.TRISC7 = 1;
   //Short Pause
   Delay10KTCYx(250);
   //no prior
   RCONbits.IPEN = 0;
   //Configure USART - 9600 Baud
    OpenUSART( USART_TX_INT_OFF  &
             USART_RX_INT_ON  &
             USART_ASYNCH_MODE &
             USART_EIGHT_BIT   &
             USART_CONT_RX     &
             USART_BRGH_HIGH, 25 );

    //Short Pause
  
   INTCONbits.GIEH=1;      /* Enable interrupt globally*/
   INTCONbits.GIEL=1; 
   return 0;
}
 
void read_ISR(void){

    PIR1bits.RCIF=0; // clear flag   
    rcPtr++;
    if(*rcPtr == 0xFF){ // circular buffer
        rcPtr = buf;
    }
    *rcPtr = ReadUSART();
    if(*rcPtr == 0x0D){
        PORTBbits.RB0 = 1;
    }
    return 0;
}

 