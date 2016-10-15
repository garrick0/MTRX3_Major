
/**
 * @file main.c
 * @date 15 Oct 2016
 * @brief Implements control of the commander
 * 
 * Utilises timers, interrupts and function calls to implement control of the commander
 * 
 * @author Samuel Gleeson
 *
 * @bugs Still Writing
 */


/* -- Includes -- */
#include <p18f452.h>            
#include "ConfigRegs.h"







/* -- Function Prototypes -- */
void high_interrupt(void);

// UI
void UISetup(void);
void receiveUI(int* UIVals);
void outputUI(char state,char* parrotPosition, char* IRVals);


// Comms
void commSetup(void);
void receiveComms(int* recVals);
void transmitComms(int* encoderVals);


//Nav
void navSetup(void);



// misc





/* -- Global Variables -- */
#define MANUAL_MODE 0
#define AUTOMATIC_MODE 1
#define FACTORY_MODE 2






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

    
        //packet received from robot
        int recVals[6];
        //packet received from UI
        int UIVals[1];
        
        //Hold the encoder (L/R) values
        int encoderVals[2];
        
        //System State
        char state = MANUAL_MODE;
        
        //Relative x,y value of parrot to robot
        char parrotPosition[2];
        
        //IR Value Thresholds
        char IRVals[3];
    


    
    
    //UI
    UISetup();


    // Comms
    commSetup();



    //Nav
    navSetup();
    
    
  
    //Enable Interrupts
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 0;
    INTCONbits.GIE = 1;
    
    
    
    
    
    

    
    /* Loop */
    while(1){
        

        
        
        
        //Receive Comms from ground (array)
            //array [IRVal1,IRVal2,IRVal3,signalStrength,EncoderLeft,EncoderRight]
        receiveComms(recVals);
        
        //Receive user interface input
            //array[state change, moveforward,moveback,turnright,turnleft]
        receiveUI(UIVals);
        
        
 
        
        //perform calculations
        
        
            // Find where parrot is
                //Use chirps and spins
            
            //Find how to get there
                //Manual = inputs
                //Auto = algorithm
        
        
        
        
        if (state == MANUAL_MODE) {
            
        }
        
        
        
        
        //transmit to ground to move robot
        transmitComms(encoderVals);
                
        //write to UI
        outputUI(state,parrotPosition,IRVals);

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
        

    
        //Clear timer flag
        PIR1bits.TMR1IF = 0;
    

    }
    
    
    
        /* Encoder Timer Interrupt */
    if ((PIR2bits.TMR3IF == 1)&&(PIE2bits.TMR3IE == 1)) {
    //reset clock
        TMR3H = 0;
        TMR3L = 0;

   
    
        //Clear timer flag
        PIR2bits.TMR3IF = 0;

    }
    
    
    
    
    
        /*Serial Receive Interrupt*/
    if (PIR1bits.RCIF == 1) {

        
        PIR1bits.RCIF = 0;

    }
    
    

    //Enable Interrupts
    INTCONbits.GIE = 1;
    

    
}

