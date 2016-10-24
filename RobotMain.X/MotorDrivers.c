#include <p18f4520.h>         
void getEncoderValues(int*);
char currentFlag;



void motorSetup(void) {
    TRISCbits.RC2 = 1;
    TRISD = 0;
    PORTD = 0;
    //CCP Setup
    PR2 = 0xFF;   //initialize PR2 registers for the set frequency 2.44Khz 
    CCP1CONbits.DC1B1 = 0;
    CCP1CONbits.DC1B0 = 0;
    CCPR1L = 0x3F; //Set duty cycle to 100% (aka zero movement)
    T2CON = 0b00000100; //Initialize Timer2 
    CCP1CON = 0b10001100;   //Initialize CCP1 module to PWM mode with two pins generating PWMs (RC2, [RD5 ??])
    TRISCbits.RC2 = 0;
    PORTCbits.RC2 = 0;
    
    PORTDbits.RD4 = 1;
    PORTDbits.RD6 = 0;
    PORTDbits.RD0 = 0;
    PORTDbits.RD1 = 1;  
    TMR0L = 0;
    TMR0H = 0;
}

//Drive the motors with a pwm

/*Inputs an instruction maginitude and type (F,B,L,R), instruction flag(1 == instruction in process, 0 == hold or emergency stop)*/
char DriveMotors(int magnitude,char direction,char mainFlag) {
    unsigned int currentEncoderValues[2];
    //unsigned int test;
    
//    getEncoderValues(currentEncoderValues);
    /*test = 0;
    test = currentEncoderValues[0];
    test = currentEncoderValues[1];
    test++;
    
    */
    return 0;
}


void getEncoderValues(int* currentEncoderValues){
    //To com function
            
    int wheel1_counterl = TMR0L;
    int wheel1_counterh = TMR0H;
    int wheel2_counterl= TMR1L;
    int wheel2_counterh = TMR1H;
    /*
        unsigned int test;

    test = 0;
    test = (wheel1_counterh*256) + wheel1_counterl;
    test = (wheel2_counterh*256) + wheel2_counterl;
    test++;
    */
    //For on-board processing
    currentEncoderValues[0] = (wheel1_counterh*256) + wheel1_counterl;
    currentEncoderValues[1] = (wheel2_counterh*256) + wheel2_counterl;
}