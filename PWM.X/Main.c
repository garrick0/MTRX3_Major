#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <p18f4520.h>
#include <string.h>
#include "ConfigRegs_18F4520.h"

int i;
unsigned char timerH; 
unsigned char timerL;
unsigned int counts;
int timer;
int j = 0;

int wheel1_counterh,wheel1_counterl;
int wheel2_counterh,wheel2_counterl;

int wheel1_currentValue,wheel2_currentValue;
int wheel1_nextValue,wheel2_nextValue;

void setInitalSpeed(void);
void setup(void);
void set_speed(unsigned int);
int calcEncoder1(char, int);
void resetEncoders(void);
void directionalMovement(int);
void getEncoderValues(void);


void main(void) {
    setup();
    
    directionalMovement(4);
    resetEncoders();
    getEncoderValues();
    
    wheel1_nextValue = calcEncoder1('f',30) + wheel1_currentValue;
    wheel2_nextValue = calcEncoder1('f',30) + wheel2_currentValue;
    
    while(1){      
        set_speed(100);
        
        getEncoderValues();
        
        if (wheel1_currentValue >= wheel1_nextValue || wheel2_currentValue >= wheel2_nextValue) {
            set_speed(0);
            resetEncoders();
            directionalMovement(0);
            while(1);
        }

    }
}

void directionalMovement(int direction){
    //Left Turn
    if(direction == 1){
        PORTDbits.RD4 = 1;
        PORTDbits.RD6 = 0;
        PORTDbits.RD0 = 1;
        PORTDbits.RD1 = 0;
    //Right Turn    
    } else if (direction == 2) {
        PORTDbits.RD4 = 0;
        PORTDbits.RD6 = 1;
        PORTDbits.RD0 = 0;
        PORTDbits.RD1 = 1;
    //Backwards
    } else if (direction == 3) {
        PORTDbits.RD4 = 0;
        PORTDbits.RD6 = 1;
        PORTDbits.RD0 = 1;
        PORTDbits.RD1 = 0;
    //Forwards
    } else if (direction == 4) {
        PORTDbits.RD4 = 1;
        PORTDbits.RD6 = 0;
        PORTDbits.RD0 = 0;
        PORTDbits.RD1 = 1;  
    //Stop
    } else if (direction == 0) {
        PORTDbits.RD4 = 1;
        PORTDbits.RD6 = 1;
        PORTDbits.RD0 = 1;
        PORTDbits.RD1 = 1;
    }
}


void getEncoderValues(void){
    wheel1_counterl= TMR0L;
    wheel1_counterh = TMR0H;
    wheel2_counterl= TMR1L;
    wheel2_counterh = TMR1H;
    
    wheel1_currentValue = (wheel1_counterh*256) + wheel1_counterl;
    wheel2_currentValue = (wheel2_counterh*256) + wheel2_counterl;
}


void resetEncoders(void){
    TMR0L = 0;
    TMR0H = 0;
    TMR1L = 0;
    TMR1H = 0;
}

void setup(void){
    TRISD = 0;
    PORTD = 0;
    PORTC = 0;
    TRISB = 0;
    PORTB = 0;
    
    INTCONbits.GIEH = 1; //enable interrupts
    INTCONbits.GIEL = 1; 
    RCONbits.IPEN = 1; // turn priority levels on
    IPR1bits.RCIP = 0;
    
    //16-bit counter wheel 1
    T0CONbits.TMR0ON = 1;
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 1;
    T0CONbits.T0SE = 0;
    T0CONbits.PSA = 1;
    
  //  PORTAbits.AN4 = 0;
    ADCON1bits.PCFG0 = 1;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG2 = 0;
    ADCON1bits.PCFG3 = 1;
    TRISAbits.RA4 = 1;
      
      
    //16-bit counter wheel 2
    T1CONbits.RD16 = 0;
    T1CONbits.T1RUN = 0;
    T1CONbits.T1CKPS0= 0;
    T1CONbits.T1CKPS1= 0;
    T1CONbits.T1OSCEN = 0;
    T1CONbits.T1SYNC = 1;
    T1CONbits.TMR1CS = 1;
    T1CONbits.TMR1ON = 1;
    
    //CCP Setup
    PR2 = 0xFF;   //initialize PR2 registers for the set frequency 2.44Khz 
    CCP1CONbits.DC1B1 = 0;
    CCP1CONbits.DC1B0 = 0;
    CCPR1L = 0x00; //Set duty cycle to 100% (aka zero movement)
    T2CON = 0b00000100; //Initialize Timer2 
    CCP1CON = 0b10001100;   //Initialize CCP1 module to PWM mode with two pins generating PWMs (RC2, [RD5 ??])
    TRISCbits.RC2 = 0;
    PORTCbits.RC2 = 0;
}


void set_speed(unsigned int duty)
{
    unsigned int duty_input; 
    duty_input = (255*duty)/100; //convert to scaled 8 bit input 
    CCPR1L = duty_input;
}

int calcEncoder1(char MovType, int Val) {
    int  TargetEncod;
    float PI = 3.1415;
    int wheel2cent_R = 10;
    int wheel_r = 4.5;
    int EncodErr;
    float rads;
    if(MovType == 'f') {
        TargetEncod =  131*64*(Val/(2*PI*wheel_r)); //Calculate number of encoder clicks
        return TargetEncod;
    }     
    else if(MovType == 'r') {
        float rads = Val/180;
        TargetEncod = 64*((wheel2cent_R*rads)/(2*PI*wheel_r)); //Calculate number of encoders 
        return TargetEncod;
    }
    return 0;
    }