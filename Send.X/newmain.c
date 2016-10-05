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

void setInitalSpeed(void);
void setup2(void);
void setup(void);
void waitTransmit(void);
void tx232(void);
void rx232(void);

/* Interrupt Declarations */
#pragma code high_interrupt_vector = 0x000008
void goto_high_ISR(void) {
    _asm goto rx232 _endasm
}
#pragma code

void main(void) {
    setup();
    setup2();
    setInitalSpeed();
    /* Loop */
    PORTDbits.RD4 = 1;
    PORTDbits.RD2 = 0;
    PORTDbits.RD0 = 1;
    PORTDbits.RD1 = 0;
    
    while(1) {
        
        if(transmit) {
            // send the message
            tx232();
        }
    }
}

/* Interrupt Service Routine */
#pragma interrupt rx232
void rx232(void) {
    
    *rxPtr = RCREG;             // Read Data
    
    if(*rxPtr == 'w') {
        CCPR1L = CCPR1L + 5;
    } else if(*rxPtr== 's'){
        CCPR1L = CCPR1L - 5;
    } else if(*rxPtr == 'd'){
        if(PWM1CON == 128) {
          PWM1CON = 0; 
        } else {
        PWM1CON = PWM1CON +4;
        }
    } else if(*rxPtr == 'a'){
        if(PWM1CON == 0) {
          PWM1CON = 128; 
        } else {
        PWM1CON = PWM1CON - 4;
        }
    } else if(*rxPtr== 'o'){
        PORTDbits.RD4 ^= 1;
        PORTDbits.RD6 ^= 1;
        PORTDbits.RD0 ^= 1;
        PORTDbits.RD1 ^= 1;
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
    TRISC = 0b10000000;         //
    TXSTA = 0b00100110;         // Transmit enable, high baud
    SPBRG = 64;                 // Baud = 9600
    RCSTA = 0b10010000;         // serial enable, 8 bit receive, enable reception

    txPtr = &message[0];
    rxPtr = &message[0];
    transmit = 0;

}

void setup2(void){
    PR2 = 0xFF;
    CCPR1L = 0b00000000;
    PORTC = 0; 
    TRISD = 0;
    PORTD = 0;
    TRISB = 0;
    PORTB = 0;
    T2CON = 0b00000100;
    CCP1CON = 0b10001110;
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
