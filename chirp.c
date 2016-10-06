/* acts as test bird and transmits chirp 'Z' at 15Hz */
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
void initTimer(void);
void PWM2Hz(void);

#pragma interrupt chk_isr // used for high only
void chk_isr (void){
    if(PIR2bits.CCP2IF == 1){
        PWM2Hz();
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

main(void)
 {
    // configure Timer
    initTimer();
    // configure USART
    initUSART();
    // Send chirp @ 2Hz
    INTCONbits.GIEH=1;      // Enable interrupt globally
    INTCONbits.GIEL=1; 
    
    while (1);
 }
void initTimer(void){
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
    
    PIE2bits.CCP2IE=1;//allow interrupt for CCP2
    PIR2bits.CCP2IF=0;//clear flag
    // timer setup end
    return 0;
}
void initUSART(void){
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
}
 
void PWM2Hz(void){
    TMR3H=0;//start at 0 start counting up
    TMR3L=0;
    PIR2bits.CCP2IF=0;//clear flag
    PORTB = PORTB^BIT0; // toggle for debug
    if (TXSTAbits.TRMT == 1)
    {
        putcUSART('z'); // chirp
    }
    return 0;
}
 