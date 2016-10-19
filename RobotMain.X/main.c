
/**
 * @file robotmain.c
 * @date 15 Oct 2016
 * @brief Implements control of the robot
 * 
 * Utilises timers, interrupts and function calls to implement control of the robot
 * 
 * @author Kelly Lynch
 *
 * @bugs Still Writing
 */


/* -- Includes -- */
#include <p18f4520.h>            
//#include "ConfigRegs.h"
#include "ConfigRegs_18F4520.h"
#include "IRSensors.h"






/* -- Function Prototypes -- */
void high_interrupt(void);

// IRs
void SetupIR(void);
void IRProcess(int* IRVals);
void sampleIR(void);

// Encoders
void SetupEncoders(void);
void sampleEncoders(void);

//Motors
void motorSetup(void);
void DriveMotors(int* encoderIncs,int* currentEncoderVals);

//Communications
void commsSetup(void);
char transmitData(int* IRVals,char signalStrength,int* currentEncoderVals);
void receiveData(void);

// misc
void debugSetup(void);




/* -- Global Variables -- */

//number of encoder increments
int* encoderIncs[2] = {10,10};

//signal strength is modified by the receive interrupt
char* signalStrength = "";

//The current encoder values, modified in the readEncoders function
int* currentEncoderVals[2] = {0,0};


//Array containing detected object thresholds
int detectVals[3];






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
    int* IRVals[3];
    int i;
    
    //Set up IR sensors
    IRSetup();
    //timerSetup();
    //SetupIR();
    
    //Set up Encoders
    //SetupEncoders();
    //SetupIR();
    SetupEncoders();
    commsSetup();
    motorSetup();
    
    
    debugSetup();
    
    //Timer 1 Setup
    IPR1bits.TMR1IP = 1; // timer 1 overflow
    PIE1bits.TMR1IE = 1;
    T1CON = 0b10110001;
    
    //Timer 3 Setup
    IPR2bits.TMR3IP = 1;
    PIE2bits.TMR3IE = 1;
    T3CON = 0b10110001;

    
    
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 0;
    INTCONbits.GIE = 1;
    
    
    

    
    /* Loop */
    while(1){
        
        //Perform PID or similar and drive motors
        DriveMotors(encoderIncs,currentEncoderVals);

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
              
               

         //transmit to commander
        transmitData(IRVals,signalStrength,currentEncoderVals);
    }
}

void high_interrupt(void) {

    
    // Disable Interrupts
    INTCONbits.GIE = 0;
    
    
    /* IRSensors Timer Interrupt */
    if ((PIR1bits.TMR1IF == 1)&&(PIE1bits.TMR1IE == 1)) {
    //reset clock
        TMR1H = 0;
        TMR1L = 0;
        
        
        sampleIR();
        
        //Begin new IR conversion
        ADCON0bits.GO = 1;
    
        //Clear timer flag
        PIR1bits.TMR1IF = 0;
        
        PIR1 = 0;
        PIR2 = 0;
        
        
    

    }
    
    
    
        /* Encoder Timer Interrupt */
    if ((PIR2bits.TMR3IF == 1)&&(PIE2bits.TMR3IE == 1)) {
    //reset clock
        TMR3H = 0;
        TMR3L = 0;
        sampleEncoders();
   
    
        //Clear timer flag
        PIR2bits.TMR3IF = 0;

    }
    
    
    
    
    
        /*Serial Receive Interrupt*/
    if (PIR1bits.RCIF == 1) {
        receiveData();
        
        PIR1bits.RCIF = 0;

    }
    
    

    //Enable Interrupts
    INTCONbits.GIE = 1;
    

    
}

