/* 
 * File:   Tut7a.c
 * Author: Riley Green
 *         Martin Abeleda
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <p18f4520.h>
#include <string.h>
#include "ConfigRegs_18F4520.h"
#include <usart.h>

#define BUFSIZE 7

char string[] = "\r\nYou said: ";
char message[BUFSIZE];
int transmit;
int receiveCounter;
char* rxPtr;
char* txPtr;
char result; 
int i;
unsigned char timerH; 
unsigned char timerL;
unsigned int counts;
unsigned int timer;
int setting;

void setInitalSpeed(void);
void setup2(void);
void setup(void);
void waitTransmit(void);
void tx232(void);
void rx232(void);
void highPriorityISR(void);
void setSpeed(void);

/* Interrupt Declarations */
#pragma code lowPriorityInterruptAddress = 0x0018
void low_ISR(void) {
    _asm goto rx232 _endasm
}
#pragma code

#pragma code highPriorityInterruptAddress = 0x0008
void high_ISR(void){
    _asm GOTO highPriorityISR _endasm
}
#pragma code

void main(void) {
    setup();
    setup2();
    setInitalSpeed();
    /* Loop */
    PORTDbits.RD4 = 1;
    PORTDbits.RD6 = 1;
    PORTDbits.RD0 = 1;
    PORTDbits.RD1 = 1;
    
    while(1) {
        
        if(transmit) {
            // send the message
            tx232();
        }
        setSpeed();
    }
}

/* Interrupt Service Routine */
#pragma interrupt rx232
void rx232(void) {
    
    *rxPtr = RCREG;             // Read Data
    
    if(*rxPtr== 'a'){
        PORTDbits.RD4 = 1;
        PORTDbits.RD6 = 0;
        PORTDbits.RD0 = 1;
        PORTDbits.RD1 = 0;
    } else if (*rxPtr== 'd') {
        PORTDbits.RD4 = 0;
        PORTDbits.RD6 = 1;
        PORTDbits.RD0 = 0;
        PORTDbits.RD1 = 1;
    } else if (*rxPtr== 's') {
        PORTDbits.RD4 = 0;
        PORTDbits.RD6 = 1;
        PORTDbits.RD0 = 1;
        PORTDbits.RD1 = 0;
    } else if (*rxPtr== 'w') {
        PORTDbits.RD4 = 1;
        PORTDbits.RD6 = 0;
        PORTDbits.RD0 = 0;
        PORTDbits.RD1 = 1;
    } else if (*rxPtr== 'z') {
        PORTDbits.RD4 = 1;
        PORTDbits.RD6 = 1;
        PORTDbits.RD0 = 1;
        PORTDbits.RD1 = 1;
    } else if (*rxPtr== '1') {
        setting = 1;
    } else if (*rxPtr== '2') {
        setting = 2;
    } else if (*rxPtr== '3') {
        setting = 3;
    } else if (*rxPtr== '4') {
        setting = 4;
    } 
    
    /* When <cr> has been received, transmit*/
    if (*rxPtr == '\r'){
        transmit = 1;
        *rxPtr = '\0';          // Replace with NULL
    }

    /* Implement Circular Buffer*/
    if (rxPtr >= &message[BUFSIZE-1]){
        int j = 0;
        for (j = 0;j < BUFSIZE; j++) {
            message[j] = message[j+1];
        }
    } else {
       *rxPtr++;
    }
    PIR1 = 0;                   // Clear interrupt flags
}

void setInitalSpeed(void){
    INTCONbits.TMR0IF = 0;
    CCPR1L = 0xFF;
    CCP1CON |= 0b00110000;
    PWM1CON = 0b00000000;
}


/* Setup Function */
void setup(void) {

    /* Interrupt Enable*/
    INTCON = 0b11000000;        // Global interrupt enable
    PIE1 = 0b00100000;          // Enable USART receive
    IPR1 = 0b00100000;          // Receive High priority
    RCON = 0b10000000;          // Priority enable

    /* Serial Enable */
    TRISC |= 0b10000000;         //
    TXSTA = 0b00100110;         // Transmit enable, high baud
    SPBRG = 64;                 // Baud = 9600
    RCSTA = 0b10010000;         // serial enable, 8 bit receive, enable reception

    txPtr = &message[0];
    rxPtr = &message[0];
    transmit = 0;
}

void setup2(void){
    PORTC = 0; 
    TRISD = 0;
    PORTD = 0;
    TRISB = 0;
    PORTB = 0;
    
    //PWM Setup
    //set PORTC 3 to output
    TRISCbits.TRISC3 = 0;
    PORTCbits.RC3 = 0;
    PIE1bits.TMR1IE = 1;
    //Configure Timer 1 interrupt
    
    IPR1bits.TMR1IP = 1;
   
    PIR1bits.TMR1IF = 0;
    
    setting = 1;
    setSpeed();
    
    TMR1H = timerH;
    TMR1L = timerL;  
    T1CONbits.TMR1ON = 1;
    INTCONbits.GIEH = 1; //enable interrupts
    INTCONbits.GIEL = 1; 
    RCONbits.IPEN = 1; // turn priority levels on
    IPR1bits.RCIP = 0;
}

void waitTransmit(void) {
    while(!TXSTAbits.TRMT);         // Wait for TSR to be ready
    return;
}

void tx232(void) {
    int i;
    /* Print string */
    for (i = 0; i < sizeof(string); i++){
        waitTransmit();             // Wait for TSR to be ready
        TXREG = string[i];
    }

    /* Print the message until we hit null */
    while(*txPtr != '\0') {
        waitTransmit();
        TXREG = *txPtr++;
    }

    /* At end of message send <cr> then <lf>*/
    waitTransmit();
    TXREG = '\r';
    waitTransmit();
    TXREG = '\n';

    transmit = 0;                   // Clear transmit flag
    txPtr = &message[0];            // Reset Pointer
    rxPtr = &message[0];
}

void setSpeed(void) {
    if(setting == 1) {
        counts = 65535;
    } else if(setting == 2){
        counts = 64000;
    } else if(setting == 3){
        counts = 63000;
    } else if(setting == 4){
        counts = 60000;
    }
    
    timerH = ((counts >> 8) & 0xff);
    timerL = ((counts >> 0) & 0xff);
}

#pragma interrupt highPriorityISR
void highPriorityISR(void){
    PORTCbits.RC3 ^= 1; 
    
    TMR1L = timerL;      //clear timers
    TMR1H = timerH;      //clear timers 
    PIR1 = 0;	    //clear interrupt
}