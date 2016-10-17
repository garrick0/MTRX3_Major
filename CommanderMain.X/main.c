
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
#include "main.h"






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
        char State = MANUAL_MODE;
        
        //Relative x,y value of parrot to robot
        char parrotPosition[2];
        
        //IR Value Thresholds
        char IRVals[3];
        
          //hold current encoder values
         int currentEncoder[2];
    


    
    
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
        

               //Receive user interface input
            //array[state change, moveforward,moveback,turnright,turnleft]
        receiveUI(UIVals);
         
        
        
        //Receive Comms from ground (array)
            //array [IRVal1,IRVal2,IRVal3,signalStrength,EncoderLeft,EncoderRight]
        receiveComms(recVals);
        currentEncoder[0] = recVals[4];
        currentEncoder[1] = recVals[5];
        
        
        //Process chirps,encoders -> angle -> strength
        
        //check signal strength is in acceptable range
              //if not, spin
        
        //inputs - chirp/encoder buffer, state
        //outputs - encoder values
        
 
        
        //perform calculations
        
        
            // Find where parrot is
                //Use chirps and spins
        //locateParrot()    
        
        
            //Find how to get there
                //Manual = inputs
                //Auto = algorithm
        
        
        
        
        
        
        robotMove(State,encoderVals,currentEncoder,recVals[3]);
        
        
        
        
        //transmit to ground to move robot
        transmitComms(encoderVals);
                
        //write to UI
        outputUI(State,parrotPosition,IRVals);

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

