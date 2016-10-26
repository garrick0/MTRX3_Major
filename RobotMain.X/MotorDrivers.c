#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <p18f4520.h>
#include <string.h>
//#include "ConfigRegs_18F4520.h"


unsigned char timerH; 
unsigned char timerL;
unsigned int counts;
int timer;
int j = 0;
unsigned int currentEncoderValue;
unsigned int nextEncoderValue;
char currentFlag;
char Flag;
unsigned int currentMagnitude;
    unsigned int wheel1_counterl;
    unsigned int wheel1_counterh ;


void setInitalSpeed(void);
void set_speed(unsigned int);
void resetEncoders(void);
void directionalMovement(char);
void getEncoderValues();


void directionalMovement(char direction){
    //Left Turn
    if(direction == 'L' || direction == 'l'){
        PORTDbits.RD4 = 1;
        PORTDbits.RD6 = 0;
        PORTDbits.RD0 = 1;
        PORTDbits.RD1 = 0;
    //Right Turn    
    } else if (direction == 'R' || direction == 'r') {
        PORTDbits.RD4 = 0;
        PORTDbits.RD6 = 1;
        PORTDbits.RD0 = 0;
        PORTDbits.RD1 = 1;
    //Backwards
    } else if (direction == 'd' || direction == 'D') {
        PORTDbits.RD4 = 0;
        PORTDbits.RD6 = 1;
        PORTDbits.RD0 = 1;
        PORTDbits.RD1 = 0;
    //Forwards
    } else if (direction == 'u' || direction == 'U') {
        PORTDbits.RD4 = 1;
        PORTDbits.RD6 = 0;
        PORTDbits.RD0 = 0;
        PORTDbits.RD1 = 1;  
    //Stop
    } else if (direction == 's' || direction == 'S') {
        PORTDbits.RD4 = 0;
        PORTDbits.RD6 = 0;
        PORTDbits.RD0 = 0;
        PORTDbits.RD1 = 0;
    } else {
        currentFlag = 0;
    }
    
}

void getEncoderValues(){
    currentEncoderValue = 0;
    wheel1_counterl = TMR0L;
    wheel1_counterh = TMR0H;

    currentEncoderValue = (wheel1_counterh*256) + wheel1_counterl;
}

void resetEncoders(void){
    TMR0L = 0;
    TMR0H = 0;
    TMR1L = 0;
    TMR1H = 0;
}

void motorSetup(void){
    currentFlag = 0;
    
    TRISD = 0;
    PORTD = 0;
    PORTC = 0;
    TRISB = 0;
    PORTB = 0;
    
    TRISCbits.RC0 = 1;
    PORTCbits.RC0 = 1;
    RCONbits.IPEN = 1; // turn priority levels on
    IPR1bits.RCIP = 0;
    
    
    //16-bit counter wheel 1
    T0CONbits.TMR0ON = 1;
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 1;
    T0CONbits.T0SE = 0;
    T0CONbits.PSA = 1;

    //CCP Setup
    PR2 = 0xFF;   //initialize PR2 registers for the set frequency 2.44Khz 
    CCP1CONbits.DC1B1 = 0;
    CCP1CONbits.DC1B0 = 0;
    CCPR1L = 0x00; //Set duty cycle to 100% (aka zero movement)
    T2CON = 0b00000100; //Initialize Timer2 
    CCP1CON = 0b10001100;   //Initialize CCP1 module to PWM mode with two pins generating PWMs (RC2, [RD5 ??])
    TRISCbits.RC2 = 0;
    PORTCbits.RC2 = 0;
    
    
    directionalMovement('s');
    resetEncoders();
    getEncoderValues();
    set_speed(0);
    currentFlag = 0;
    currentMagnitude  = 0;
}


void set_speed(unsigned int duty)
{
    unsigned int duty_input = 0; 
    duty_input = (255*duty)/100; //convert to scaled 8 bit input 
    //duty_input = (2*duty);
    CCPR1L = duty_input;
}

//Drive the motors with a pwm

/*Inputs an instruction maginitude and type (F,B,L,R), instruction flag(1 == instruction in process, 0 == hold or emergency stop)*/
char DriveMotors(unsigned int magnitude,char direction,char mainFlag, unsigned int speed, char * detailedFlagName) {
    if ((currentFlag == 0 && mainFlag == 0) ) {
        set_speed(0);
        directionalMovement('s');
        currentEncoderValue = 0;
        
    } else if (currentFlag == 1 && mainFlag == 0) {
        set_speed(0);
        currentFlag = 0;
        directionalMovement('s');
        currentEncoderValue =0;
        
    } else if (currentFlag == 0 && mainFlag == 1) {
        currentEncoderValue =0;
        resetEncoders();
        getEncoderValues();
        currentMagnitude = 0; 
                currentFlag = 1;
        directionalMovement(direction);
        set_speed(speed);
        currentMagnitude = magnitude; 
    }
    else if (currentFlag == 1 && mainFlag == 1) {
        getEncoderValues();
    
        if (currentEncoderValue >= currentMagnitude) {
            set_speed(0);
            currentFlag = 0;
            *detailedFlagName = 1;
            directionalMovement('s');
            currentMagnitude = 0; 
        }
   
    }
    return currentFlag;
}