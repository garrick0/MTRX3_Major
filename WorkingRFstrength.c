/* receives and tests strength */

#include "p18f452.h"
#include <stdio.h>
#include <stdlib.h>
#include "pconfig.h"
#include "spi.h"
#include "ConfigRegs.h"
#include "delays.h"
#include "usart.h"
//#include "RFmodule.h"
#include "ASCII.h"
#define BIT0 0x01

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
char ATCommandStart[] = "+++"; //Initialize AT Command Mode.
char ATCommandRSSI[] = "ATDB\r"; // read signal strength
char ATCommandEnd[] = "ATCN\r"; // end command
char RSSI[20], stat[20], buf[100];
char *rcPtr, *txPtr, *rtPtr;
int stage = 1;
const int idle = 0, startSend = 1, rssiReq = 3, done =  5;
int i,j,k;

main(void)
 {
    rcPtr = buf;
    PORTBbits.RB0 = 0;
    // configure USART
    initUSART();
    while (1){
        if(PORTBbits.RB0 == 1){ // flag check
            PORTBbits.RB0 = 0;
            stage++;
        }
        if(stage == startSend){
            txPtr = ATCommandStart;
            while (*txPtr)
            {
                while (TXSTAbits.TRMT != 1); // wait till transmit buffer is empty
                putcUSART(*txPtr); // write command 
                txPtr++;  
            }
            stage++; // done send
        }else if(stage == rssiReq){
            txPtr = ATCommandRSSI;
            while (*txPtr)
            {
                while (TXSTAbits.TRMT != 1); // wait till transmit buffer is empty
                putcUSART(*txPtr); // write command 
                txPtr++;  
            }
            stage++; // done send
            PORTBbits.RB1=1;
        }else if(stage == done){
            // check if received
            PIE1bits.RCIE = 0;
            i = 0;
            while(*rtPtr){ // save in circular buffer
                RSSI[i] = *rtPtr;
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
           USART_CONT_RX &
            USART_BRGH_HIGH, 25 );

   INTCONbits.GIEH=1;      /* Enable interrupt globally*/
   INTCONbits.GIEL=1; 
   return 0;
}
 
void read_ISR(void){

    PIR1bits.RCIF=0; // clear flag   
    rcPtr++;
//    if(*rcPtr == 0x00){
//        rcPtr = &buf[0];
//    }
    *rcPtr = ReadUSART();
    if(*rcPtr == CR){
        PORTBbits.RB0 = 1;
    }
    return 0;
}
