   
/**
 * @file robotmain.c
 * @date 15 Oct 2016
 * @brief Implements control of the robot
 * 
 * Utilises timers, interrupts and function calls to implement control of the robot
 * 
 * @author Samuel Gleeson
 *
 * @bugs Still Writing
 */


/* -- Includes -- */
#include <p18f4520.h>            
//#include "ConfigRegs.h"
#include "ConfigRegs_18F4520.h"
#include "IRSensors.h"
#include "Communications.h"






/* -- Function Prototypes -- */
void high_interrupt(void);


// Encoders
void SetupEncoders(void);
void sampleEncoders(int* encoderValues);

//Motors
void motorSetup(void);
char DriveMotors(int magnitude,char direction,char mainFlag);






/* -- Global Variables -- */

//Target number of encoder increments (transmitted from main)
int targetEncoders[2] = {10,10};

//signal strength is modified by the receive interrupt
char signalStrength[5];

//The current encoder values, modified in the readEncoders function
int currentEncoderVals[2];


//Array containing detected object thresholds
int detectVals[3];

//Buffer to store receive data
char receiveBuffer[50] = {0x00};

//Chirp Strength
char chirpStr;

//ReceiveFlag triggered when receive entered
char receiveFlag=0;
char crflag = 0;

//MotorInstructionFlag
char instructionFlag;






/* Interrupt Declarations */
#pragma code high_interrupt_vector = 0x000008
void goto_high_ISR(void) {
    _asm goto high_interrupt _endasm
}
#pragma code




/** 
 * @brief Main Function
 *  
 * Implements Robot Control
 * 
 *  
 * @return 
 */



void main(void) {
    int i;
    char detectVals[3] = {0x00,0x00,0x00};

    
    int instMag=100;
    char instDir = 'F';

    //timerSetup();
    //SetupIR();
    
    //Set up Encoders
    //SetupEncoders();
    //SetupIR();
    //SetupEncoders();
    commsSetup();
    //motorSetup();
    
    //Set up IR sensors
    IRSetup();
    
    //debugSetup();
    
    //Timer 1 Setup
    //IPR1bits.TMR1IP = 1; // timer 1 overflow
    //PIE1bits.TMR1IE = 1;
    //T1CON = 0b10110001;
    
    //Timer 3 Setup
    IPR2bits.TMR3IP = 1;
    PIE2bits.TMR3IE = 1;
    T3CON = 0b10110001;
    ADCON0bits.GO = 1;
    
    //Turn on timer 3

    
    
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 0;
    INTCONbits.GIE = 1;
    
    
    

    
    /* Loop */
    while(1){
        
        //Process Receive Function
            //add inputs global variables
        if (receiveFlag) {
            processReceived(receiveBuffer, &instMag,&instDir,&instructionFlag);
            receiveFlag=0;
        }
        //Perform PID or similar and drive motors
        //instructionFlag = DriveMotors(instMag,instDir,instructionFlag);

        //Read IR sensor buffer and return result
        IRDetect(2,detectVals);
        
        if (detectVals[0] > 0) {
            i++;
        }
        if (detectVals[1] > 0) {
            i++;
        }
        if (detectVals[2] > 0) {
            i++;
        }
        
        //Testing Values for comms
        signalStrength[0] = 0x36;
        signalStrength[1] = 0x35;
        signalStrength[2] = 0x00;
        instructionFlag = 0;
        
        

         //transmit to commander
        //transmitData(detectVals,signalStrength,instructionFlag);
    }
}

void high_interrupt(void) {

    
    // Disable Interrupts
    INTCONbits.GIE = 0;
    
 
    
        /* IRSensors Timer Interrupt */
    //if ((PIR1bits.TMR1IF == 1)&&(PIE1bits.TMR1IE == 1)) {
    //reset clock
        //TMR1H = 0;
        //TMR1L = 0;
        
        

        //sampleIR();
        //Begin new IR conversion
        //ADCON0bits.GO = 1;
    
        //Clear timer flag
        //PIR1bits.TMR1IF = 0;
        
        //PIR1 = 0;
       // PIR2 = 0;
        
        
    

    //}
    
    
    
    
        /* IRSensors Timer Interrupt */
    if ((PIR2bits.TMR3IF == 1)&&(PIE2bits.TMR3IE == 1)) {
    //reset clock
        TMR3H = 0;
        TMR3L = 0;
        
        
        
        sampleIR();
        //Begin new IR conversion
        ADCON0bits.GO = 1;
    
        //Clear timer flag
 
        PIR2bits.TMR3IF = 0;
        
        PIR1 = 0;
        PIR2 = 0;
        
            IPR2bits.TMR3IP = 1;
    PIE2bits.TMR3IE = 1;
    T3CON = 0b10110001;
    ADCON0bits.GO = 1;
        
        
        
        
    sampleEncoders(currentEncoderVals);
        //sampleIR();
        //ADCON0bits.GO = 1;
   
    
        //Clear timer flag
        

    }
    
    
    
    
    
        /*Serial Receive Interrupt*/
    if (PIR1bits.RCIF == 1) {
        receiveData(receiveBuffer, &crflag, &receiveFlag);

        PIR1bits.RCIF = 0;

    }
    
    

    //Enable Interrupts
    INTCONbits.GIE = 1;
    return;

    
}

