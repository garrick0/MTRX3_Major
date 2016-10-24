#include    <p18f4520.h>
#include    "UserInterface.h"

char turnFLAG = 0;

void servoOutput(char turnFLAG, int angle){
    //turnFLAG ^= HIGH;  
    
        if (turnFLAG == HIGH){
            PORTCbits.RC2 = 0;
            degrees2pulse_LOW(angle);
        }
        
        if (turnFLAG == LOW){
            PORTCbits.RC2 = 1;
            degrees2pulse_HIGH(angle); 
        }
}
void servoSetup(void){
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;
    CCPR2L = 0;
    T3CON = 0b10001001; 

    PORTCbits.RC2 = 0;
    TRISCbits.RC2 = 0;
    
    CCP2CON = 0b00001011;
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
  
    RCONbits.IPEN = 1;
    PIE2bits.CCP2IE = 1;
    IPR2bits.CCP2IP = 0;
  
}

void initialiseCCP2(void){
    PORTCbits.RC2 = 1;
    move90_HIGH();
}

void degrees2pulse_LOW(int degrees){
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

void degrees2pulse_HIGH(int degrees){
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
