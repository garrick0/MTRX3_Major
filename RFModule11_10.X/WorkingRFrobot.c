// receives instructions
#include "p18f452.h"
#include <stdio.h>
#include <stdlib.h>
#include "pconfig.h"
#include "spi.h"
#include "ConfigRegs.h"
#include "delays.h"
#include "usart.h"
#include "ASCII.h"
#define BIT0 0x01
#define NULL 0x00
#define CR 0x0D

void initUSART(void);
void read_ISR(void);
void sendMsg(char *txPtr);
void saveMsg(char *msg, char* savedMsg);
void prepMsg(char *msgToSend, char* package);

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
char instruct[20], pw[20], got[] = "*g\r", buf[100], sendBuf[100];
int length = 100;
char *rcPtr, *rtPtr;
int stage = 0;
int i,j,k;
const int idle = 0, msgReceived = 1, respondSend = 2, done = 3;

main(void)
 {
    buf[length - 1] = 0xFF;
    rcPtr = buf;
    rtPtr = rcPtr;
    PORTBbits.RB0 = 0;
    // configure USART
    initUSART();
    while (1){
        if(PORTBbits.RB0 == 1){ // flag check
            PORTBbits.RB0 = 0;
            stage++;
        }
        if(stage == msgReceived){
            stage++; 
            saveMsg(rtPtr,instruct);
            rtPtr = rcPtr;  
        }else if(stage == respondSend){
            prepMsg(got,sendBuf)
            sendMsg(sendBuf);
            stage++; // done send
            
        }else if(stage == done){
            stage = idle;

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
   RCONbits.IPEN = 0;

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
// ISR that constantly saves in circular buffer 
void read_ISR(void){

    PIR1bits.RCIF=0; // clear flag   
    rcPtr++;
    if(*rcPtr == 0xFF){
        rcPtr = buf;
    }
    *rcPtr = ReadUSART();
    if(*rcPtr == 0x0D){
        PORTBbits.RB0 = 1;
    }
    return 0;
}
// input address of msg, sends the msg
void sendMsg(char *txPtr){
    
    while (*txPtr)
    {
        while (TXSTAbits.TRMT != 1); // wait till transmit buffer is empty
        putcUSART(*txPtr); // write command 
        txPtr++;  
    } 
}
// save the msg inside a buffer
void saveMsg(char *msg, char* savedMsg){
    while(*msg != CR){
        *savedMsg = *msg;
        savedMsg ++;
        msg++;
        if(*rtPtr == 0xFF){
            rtPtr = buf;
        }
    }
    return 0;
}
// save the msg inside a buffer
void prepMsg(char *msgToSend, char *package){
    while(*msgToSend){
        *package = *msgToSend;
        package ++;
        msgToSend++;
    }
    *package = NULL;
    return 0;
}