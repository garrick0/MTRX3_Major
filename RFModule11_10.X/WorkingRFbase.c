// send instructions
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

int i,j,k;
char pwIR[] = "*1", pwEN[] = "*2", pwW[] = "*3", pwRSSI[] = "*4";
char instruct[] = "hi\r\n";
char buf[50], response[50], sendBuf[50];
int length = 50;
char *rcPtr, *rtPtr;
int stage = 1; // default for testing
int idle = 0, pwfill = 1, instSend = 2, wait =  3, done = 4;

main(void)
 {
    buf[length - 1] = 0xFF;
    response[length - 1] = 0xFF;
    rcPtr = buf; // set initial save in buffer
    rtPtr = rcPtr; // point to saved location
    PORTBbits.RB0 = 0;
    // configure USART
    initUSART();
    while (1){
        if(PORTBbits.RB0 == 1){ // flag check
            PORTBbits.RB0 = 0;
            stage++;
        }
        if(stage == pwfill){
            prepMsg(pwIR,sendBuf);
            stage++; // enter sending stage
        }else if(stage == instSend){
            prepMsg(instruct,sendBuf);
            sendMsg(sendBuf);
            stage ++;
        }else if(stage == wait){
            stage++;
        }else if(stage == done){
            saveMsg(rtPtr,response); // save the response
            rtPtr = rcPtr;
            stage = idle; // return to idle
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
 