
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
#include <p18f4520.h>            

#include "ConfigRegs_18F4520.h"
#include "main.h"




/* -- Function Prototypes -- */
void high_interrupt(void);

// UI
void UISetup(void);
void receiveUI(int* UIVals);
void outputUI(char state,char* parrotPosition, char* IRVals);


// Comms
void commSetup(void);
char receiveComms(char* receiveBuffer);
void transmitComms(int instMag,char instDir);
char processReceived(char* recBuffer,char* IRVals,char* instructionFlag);


//Nav
void navSetup(void);
void robotMove(char State,int* encoderVals,int* currentEncoder,int* chirpStrength,int* parrotLoc,char* distance);



// misc



/* Interrupt Declarations */
#pragma code high_interrupt_vector = 0x000008
void goto_high_ISR(void) {
    _asm goto high_interrupt _endasm
}
#pragma code


//Global Variables
//flag set on serial receive
char receiveFlag;
//Receive Buffer used for storage         
char recBuffer[30];




/** 
 * @brief Main Function
 *  
 * Implements Robot Control
 * 
 *  
 * @return 
 */



void main(void) {
    
        //Chirp Strength
    char chirpStrength;
        // Is robot ready for new command
    char instructionFlag;

        //Robot Instruction Magnitude
    int instMag;
    
        //Robot Instruction Type
    char instDir;

        //packet received from UI
        int UIVals[1];
        
        //Hold the encoder (L/R) values
        int targetEncoder[2];
        
        //System State
        char State = MANUAL_MODE;
        
        //Relative x,y value of parrot to robot
        char parrotPosition[2];
        
        //IR Value Thresholds
        char IRVals[3];
        
          //hold current encoder values
         int currentEncoder[2];
         
         //Parrot Location
         int parrotLoc[2];
         
         //Parrot Distance
         char parrotDistance;
         



    
    
    //UI
    //UISetup();


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
        //receiveUI(UIVals);
         
        
        
        //Receive Comms from ground (array)
            //array [IRVals,signalStrength,instructionFlag]
        if (receiveFlag == 1) {
            
            //Get sensor data from robot
            //chirpStrength = processReceived(recBuffer,IRVals,&instructionFlag);
            
            //Reset flag
            receiveFlag = 0;
        }
        
        
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
        
        
        
        
        
        
        //robotMove(State,targetEncoder,currentEncoder,&recVals[3],parrotLoc,&parrotDistance);
        
        
        
        instMag = 100;
        instDir = 'f';
        //transmit to ground to move robot
        transmitComms(instMag,instDir);
                
        //write to UI
        //outputUI(State,parrotPosition,IRVals);

    }
}

void high_interrupt(void) {

    
    // Disable Interrupts
    INTCONbits.GIE = 0;
    
    
    
    
    
    
    
        /*Serial Receive Interrupt*/
    //if (PIR1bits.RCIF == 1) {

        receiveFlag = receiveComms(recBuffer);
        //PIR1bits.RCIF = 0;

    //}
    
    

    //Enable Interrupts
    INTCONbits.GIE = 1;
    

    
}

