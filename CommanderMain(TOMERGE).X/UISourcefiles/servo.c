#include    <p18f4520.h>
#include    "UserInterface.h"

//char turnFLAG = 0;

int hightime_highbit;
int hightime_lowbit;

int lowtime_highbit;
int lowtime_lowbit;



void servoToggle(void){
    //turnFLAG ^= HIGH;  
    
        if (PORTCbits.RC2 == HIGH){
            PORTCbits.RC2 = 0;
            CCPR2H = lowtime_highbit;
            CCPR2L = lowtime_lowbit; 
        }
        
        else if (PORTCbits.RC2 == LOW){
            PORTCbits.RC2 = 1;
            CCPR2H = hightime_highbit;
            CCPR2L = hightime_lowbit; 
        }
}
void servoSetup(void){

    CCPR2L = 0;
    T3CON = 0b10001001; 

    PORTCbits.RC2 = 0;
    TRISCbits.RC2 = 0;
    
    CCP2CON = 0b00001011;
    
    PIR2bits.CCP2IF = 0;
    PIE2bits.CCP2IE = 1;
    IPR2bits.CCP2IP = 0;
  
}

void initialiseCCP2(void){
    PORTCbits.RC2 = 1;
    CCPR2H = 0x11;
    CCPR2L = 0x17;
}
void servoOutput(int degrees){
    degrees2pulse_LOW(degrees);
    degrees2pulse_HIGH(degrees);
}
void degrees2pulse_LOW(int degrees){
    if ((degrees >= 0) && (degrees < 23)){
        move0_LOW(); 
    }
    
    else if ((degrees >= 23) && (degrees <= 68)){
        move45_LOW(); 
    }
    
    else if((degrees > 68) && (degrees <= 113)){
        move90_LOW();
    }
    
    else if((degrees > 113) && (degrees <= 158)){
        move135_LOW();
    }
    
    else if((degrees > 158) && (degrees <= 180)){
        move180_LOW();
    }
}

void degrees2pulse_HIGH(int degrees){
    if ((degrees >= 0) && (degrees < 23)){
        move0_HIGH(); 
    }
    
    else if ((degrees >= 23) && (degrees <= 68)){
        move45_HIGH(); 
    }
    
    else if((degrees > 68) && (degrees <= 113)){
        move90_HIGH();
    }
    
    else if((degrees > 113) && (degrees <= 158)){
        move135_HIGH();
    }
    
    else if((degrees > 158) && (degrees <= 180)){
        move180_HIGH();
    }
}

void move0_HIGH(void){
    hightime_highbit = 0x09;
    hightime_lowbit = 0xC4;
}

void move45_HIGH(void){
    hightime_highbit = 0x0E;
    hightime_lowbit = 0xA6;
}

void move90_HIGH(void){
    hightime_highbit = 0x11;
    hightime_lowbit = 0x17;
}

void move135_HIGH(void){
    hightime_highbit = 0x13; 
    hightime_lowbit = 0x88; 
}

void move180_HIGH(void){
    hightime_highbit = 0x1A;
    hightime_lowbit = 0xDB;
}

void move0_LOW(void){     
    lowtime_highbit = 0xB9;
    lowtime_lowbit = 0x8C;
}

void move45_LOW(void){
    lowtime_highbit = 0xB4;
    lowtime_lowbit = 0xAA;
}

void move90_LOW(void){
    lowtime_highbit = 0xB2;
    lowtime_lowbit = 0x39;
}

void move135_LOW(void){
    lowtime_highbit = 0xAF; 
    lowtime_lowbit = 0xC8;   
}

void move180_LOW(void){
    lowtime_highbit = 0xA8;
    lowtime_lowbit = 0x75;  
}
