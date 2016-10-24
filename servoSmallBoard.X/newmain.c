/*
 * @file    servoTest.c
 * @author  Monadil
 * @date    20/10/16
 * @brief   Servo control for the user interface
 * 
 */

#include    <p18f4520.h>
#include    "ConfigRegs_18F4520.h"
#include    "servo.h"

#pragma code lowPriorityInterruptAddress=0x0018

void low_interrupt(void){
    _asm GOTO servoTurn
    _endasm
}
#pragma code

void main(void){
    
    servoSetup();
    initialiseCCP2();
    
    while(1){
        
    }
}

#pragma interrupt servoTurn

void servoTurn(void){
    PIR2bits.CCP2IF = 0;
    turnFLAG ^= HIGH;  
    
        if (turnFLAG == HIGH){
            PORTCbits.RC1 = 0;
            degrees2pulse_LOW(angle);
        }
        
        if (turnFLAG == LOW){
            PORTCbits.RC1 = 1;
            degrees2pulse_HIGH(angle); 
        }
}

         
void servoSetup(void){
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;
    CCPR2L = 0;
    T3CON = 0b10001001; 

    PORTC = 0x00;
    TRISCbits.RC1 = 0x00;
    
    CCP2CON = 0b00001011;
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
  
    RCONbits.IPEN = 1;
    PIE2bits.CCP2IE = 1;
    IPR2bits.CCP2IP = 0;
  
}

void initialiseCCP2(void){
    PORTCbits.RC1 = 1;
    move90_HIGH();
}

void degrees2pulse_LOW(unsigned char degrees){
    if ((degrees >= 0) && (degrees < 23)){
        move0_LOW(); 
    }
    
    if ((degrees >= 23) && (degrees <= 68)){
        move45_LOW(); 
    }
    
    if((degrees > 68) && (degrees <= 113)){
        move90_LOW();
    }
    
    if((degrees > 113) && (degrees <= 158)){
        move135_LOW();
    }
    
    if((degrees > 158) && (degrees <= 180)){
        move180_LOW();
    }
}


void degrees2pulse_HIGH(unsigned char degrees){
    if ((degrees >= 0) && (degrees < 23)){
        move0_HIGH(); 
    }
    
    if ((degrees >= 23) && (degrees <= 68)){
        move45_HIGH(); 
    }
    
    if((degrees > 68) && (degrees <= 113)){
        move90_HIGH();
    }
    
    if((degrees > 113) && (degrees <= 158)){
        move135_HIGH();
    }
    
    if((degrees > 158) && (degrees <= 180)){
        move180_HIGH();
    }
}

void move0_HIGH(void){
    CCPR2H = 0x09;
    CCPR2L = 0xC4;
}

void move45_HIGH(void){
    CCPR2H = 0x0E;
    CCPR2L = 0xA6;
}

void move90_HIGH(void){
    CCPR2H = 0x11;
    CCPR2L = 0x17;
}

void move135_HIGH(void){
    CCPR2H = 0x13; 
    CCPR2L = 0x88; 
}

void move180_HIGH(void){
    CCPR2H = 0x1A;
    CCPR2L = 0xDB;
}

void move0_LOW(void){     
    CCPR2H = 0xB9;
    CCPR2L = 0x8C;
}

void move45_LOW(void){
    CCPR2H = 0xB4;
    CCPR2L = 0xAA;
}

void move90_LOW(void){
    CCPR2H = 0xB2;
    CCPR2L = 0x39;
}

void move135_LOW(void){
    CCPR2H = 0xAF; 
    CCPR2L = 0xC8;   
}

void move180_LOW(void){
    CCPR2H = 0xA8;
    CCPR2L = 0x75;  
}



