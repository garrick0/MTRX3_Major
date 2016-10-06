//**********************************************************
//*  Tute8.C
//**********************************************************
//*  Martin Abeleda  440264259
//*  Riley Green	    440275152    
//*  
//*  
//**********************************************************
#include <stdio.h>
#include <stdlib.h>
#include <p18f452.h>
#include <usart.h>
#include "ConfigRegs.h"
#include "sw_spi.h"
#include "spi.h"

void high_interupt(void);
void highPriorityISR(void);
unsigned char SerialData;

int counter = 0;
void main(void) {
    
    //TRISB = 0;
    TRISA = 0xFF;
    
    //Clear port B
    //PORTB = 0;
    
    T1CON = 0b10000001;
    T3CON = 0b00000000;
            
    CCP1CON = 0b00000010;

    PIE1 = 0b00000100;      // Enables CCP1 interrupts

    IPR1 = 0b00000100;      // Sets CCP1 interrupt to high priority

    RCON = 0b10000000;      // Enables priority levels on interrupts 
    
  
    
    CCPR1L = 0x82;         // Set period to 30Hz  
    CCPR1H = 0x35;
    
    
    TRISCbits.RC2 = 0; 
    
    


    
    //Set timer to Fosc/8,A/D enabled
    ADCON0 = 65;
    
    //Set VDD and VSS reference 
    ADCON1 = 14;
    ADCON1 = 0b00001110;
    //RAO
    //ADCO 00001110
    
    
    
    ADCON0bits.ADON = 1;
    
    
    ///////////// AD INTERRUPT
    
    PIE1bits.ADIE = 1;      // Enables CCP1 interrupts
    PIR1bits.ADIF = 0;
    IPR1bits.ADIP = 0;      // Sets CCP1 interrupt to high priority

 //   RCON
 //   Clear ADIF bit
//? Set ADIE bit
//? Set GIE bit
//? Set PEIE bit
    
    
    
    
    
    
      INTCON   = 0b10000000;  // Enable all high priority interrupts

    while(1);
}


//From lecture slides
#pragma code highPriorityInterruptAddress = 0x0008
void high_interupt(void){
    _asm GOTO highPriorityISR _endasm
}


//#pragma code highPriorityInterruptAddress = 0x0018
//void low_interupt(void){
//    _asm GOTO lowPriorityISR _endasm
//}


#pragma interrupt highPriorityISR
void highPriorityISR(void){
    //you need to use async PL to switch modes
    //(for the input chip)
    //you want to use PL input, clock once to get 8 values parallel in, then set PL high, then use SPI to shift the 8 bits through serially

    //while(!INTCONbits.TMR0IF);     // Wait for Time 0 to time out
        
    ADCON0bits.GO = 1;
        //wait until conversion complete
    while (PIR1bits.ADIF == 0) {}
        
        //get adc conversion result
    PORTB = ADRESH;
    
    
    
    
    
    
    
    PIR1 = 0;	    //clear interrupt
    TMR1L = 0;      //clear timers
    TMR1H = 0;      //clear timers
}