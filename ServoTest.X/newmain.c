/*
 * File:   newmain.c
 * Author: Monadil
 *
 * Created on 19 October 2016, 12:38 PM
 */

#include    <p18f452.h>
#include    "ConfigReg.h"

#define HIGH 1
#define LOW 0

unsigned char turnFLAG = 0;
//int degrees = 90;

void servoSetup(void);
void servoTurn(void);
//void degrees2pulse(void);

void moveRight_LOW(void);
void moveLeft_LOW(void);
void moveMiddle_LOW(void);

void moveRight_HIGH(void);
void moveLeft_HIGH(void);
void moveMiddle_HIGH(void);

#pragma code highPriorityInterruptAddress=0x0008

void high_interrupt(void){
    _asm GOTO servoTurn
    _endasm
}
#pragma code

void main(void){
    
    servoSetup();
    
    while(1){
         
     }
}

#pragma interrupt servoTurn

void servoTurn(void){
    PIR2bits.CCP2IF = 0;
    turnFLAG ^= HIGH;
    
    if (turnFLAG == HIGH){
        PORTCbits.RC1 = 0;
        
        //moveLeft_LOW(); //Right
         
        moveMiddle_LOW();
        
        //moveRight_LOW(); // Left
    }
        
    if (turnFLAG == LOW){
        PORTCbits.RC1 = 1;
        
        //moveLeft_HIGH();
                
         moveMiddle_HIGH();
        
        //moveRight_HIGH();

    }
}

void servoSetup(void){
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;
    CCPR2L = 0;
    T3CON = 0b10001001; 

    PORTC = 0x00;
    TRISCbits.RC1 = 0x00;
    //LATCbits.LATC1 = 0x00;
    
    CCP2CON = 0b00001011;
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    
    RCONbits.IPEN = 1;
    PIE2bits.CCP2IE = 1;
    IPR2bits.CCP2IP = 1;
    
    PORTCbits.RC1 = 1;
   
    // Set CCPR2.
    //moveLeft_HIGH();
    moveMiddle_HIGH();
    //moveRight_HIGH();
    
}

void moveLeft_HIGH(void){
        //LEFT
        CCPR2H = 0x03;
        CCPR2L = 0xE8;
        
    // 180 attempt - LEFT
        //CCPR2H = 0x0F;
        //CCPR2L = 0xA0;
    
}

void moveMiddle_HIGH(void){
// MIDDLE
//
        //CCPR2H = 0x05;
        //CCPR2L = 0xDC;
        
        // 180 attempt
        CCPR2H = 0x06;
        CCPR2L = 0xD6;
        
//    
    
}

void moveRight_HIGH(void){
//    RIGHT
    
       CCPR2H = 0x07; //90 degress -  0x13 for small
       CCPR2L = 0xD0; 
    
    // 180 Attempt
       //CCPR2H = 0x03; //90 degress -  0x13 for small
       //CCPR2L = 0xE8; 

    
}

void moveLeft_LOW(void){
    ////      LEFT - 90 degrees       
        CCPR2H = 0x4A;
        CCPR2L = 0x38;
        
        // 180 attempt
        //CCPR2H = 0x3E;
        //CCPR2L = 0x80;
}

void moveMiddle_LOW(void){
    //        // MIDDLE
        //CCPR2H = 0x48;
        //CCPR2L = 0x44;
        
        //180 Attempt
        CCPR2H = 0x47;
        CCPR2L = 0x4A;
    
}

void moveRight_LOW(void){
//        RIGHT
        CCPR2H = 0x46; //90 degress -  0x13 for small
        CCPR2L = 0x50; 
        
        // 180 Attempt
    
        //CCPR2H = 0x4A;
        //CCPR2L = 0x38;
}



