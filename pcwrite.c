#include    <stdio.h>
#include    <p18f4520.h>
#include    "ConfigRegs_18F4520.h"
#include    <usart.h>
#include    <delays.h>

void initialiseComs(void);
void waitTransmit(void);
void PCWrite(char *Data);

unsigned char hello[] = "Testing\r\n";
unsigned char *string = hello;

void main(void)
{
	initialiseComs();
	PCWrite(string);
	
}

void initialiseComs(void)
{
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 1;
    
    Delay10KTCYx(250);
    
    OpenUSART( USART_TX_INT_OFF  &
             USART_RX_INT_ON  &
             USART_ASYNCH_MODE &
             USART_EIGHT_BIT   &
             USART_CONT_RX &
             USART_BRGH_HIGH, 64 );
}

void  PCWrite(char *Data)
{
	while(*Data){

        while(TXSTAbits.TRMT !=1);
        
        putcUSART(*Data);
        
        Data++;
    }
}
    
