
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
#include "UserInterface.h"
#include "Communications.h"




/* -- Function Prototypes -- */
void high_interrupt(void);

// UI
void UISetup(void);
void inputUI(char* UIbuffer,struct UserInterfaceInput* UIInput);
//void inputUI(char* UIBuffer,char* State,char* commandInput);
void outputUI(struct UserInterfaceOutput UIOutput);
char storeUI(char* UIBuffer);

// Comms
void commSetup(void);
char receiveComms(char* receiveBuffer);
void transmitComms(struct communicationsOutput CommsOutput);
char processReceived(char* recBuffer,char* IRVals,char* instructionFlag);


//Nav
void navSetup(void);
//void robotMove(char State,int* encoderVals,int* currentEncoder,int* chirpStrength,int* parrotLoc,char* distance);
void robotMove(struct UserInterfaceOutput* UIOutput,struct communicationsOutput* CommsOutput,struct UserInterfaceInput UIInput,struct communicationsInput CommsInput,char State);
    
    
    //Holds values output to the user
    

// misc
char stateControl(char State,char stateRequest);


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
    
    
    
    
    
    
    
    //USERINTERFACE
    
    //Input and output structs
    
    //Holds values input by the user
    struct UserInterfaceInput UIInput;
    
    //Holds values output to the user
    struct UserInterfaceOutput UIOutput;
    
    //Holds values transmitted by robot comms
    struct communicationsInput RobotReceiveComms;
    
    struct communicationsOutput RobotTransmitComms;
    
    
    //Triggered in interrupt
    char UIFlag;
    
    char* UIBuffer;
    
    char commandInput;
    
    char parrot_moving;
    
    char parrot_found;
    
    char stateRequest;
    
    
    

        //packet received from UI
        int UIVals[1];
        
        //Hold the encoder (L/R) values
        int targetEncoder[2];
        
        //System State
        char State = MANUAL_MODE;
        
        //Relative x,y value of parrot to robot
        char parrotPosition;
        
        //IR Value Thresholds
        char IRVals[3];
        
          //hold current encoder values
         int currentEncoder[2];
         
         //Parrot Location
         int parrotLoc[2];
         
         //Parrot Distance
         char parrotDistance;
         

         //Initiate flags at 0
         UIFlag = 0;
         instructionFlag = 0;
    
    
         
         
         
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
        

              
            //Process user interface input if interrupt triggered
        if (UIFlag ==1) {
            //UI Should receive(Change of system state, Direction Inputs and parameter changes(not yet implemented)
            
            //Parses the UI buffer (contains interrupt info) and modifies the UIInput struct
            inputUI(UIBuffer,&UIInput);
            
            UIFlag = 0;
        }
         
        
        
        //Receive Comms from ground (array)
            //array [IRVals,signalStrength,instructionFlag]
        if (receiveFlag == 1) {
            
            //Get sensor data from robot
            chirpStrength = processReceived(recBuffer,IRVals,&instructionFlag);
            RobotReceiveComms.IR1 = IRVals[0];
            RobotReceiveComms.IR2 = IRVals[1];
            RobotReceiveComms.IR3 = IRVals[2];
            RobotReceiveComms.instructionFlag = instructionFlag;
            

            //UIOutput.
            
            //Reset flag
            receiveFlag = 0;
        }
        
        //State Control
        State = stateControl(State,UIInput.stateRequest);
        
        
        robotMove(&UIOutput,&RobotTransmitComms,UIInput,RobotReceiveComms,State);
        //outputs - instMag,instDir
        //        - parrotPosition,IRVals,parrot_moving,parrot_found
        //inputs  - chirpStrength,IRVals,instructionFlag,State
        
        
        
        
        //instMag = 100;
        //instDir = 'f';
        //transmit to ground to move robot
        transmitComms(RobotTransmitComms);
                

        
        
            
                
                
        //State,parrotDirection,parrotDistance,IRVals,parrot_moving,parrot_found
        //outputUI(UIOutput);

    }
}

void high_interrupt(void) {

    
    // Disable Interrupts
    INTCONbits.GIE = 0;
    
    
    
    
    
    
    
        /*Serial Receive Interrupt*/
    //if (PIR1bits.RCIF == 1) {

        //receiveFlag = receiveComms(recBuffer);
        //PIR1bits.RCIF = 0;

    //}
    
    

    //Enable Interrupts
    INTCONbits.GIE = 1;
    

    
}


char stateControl(char State,char stateRequest) {
    return stateRequest;
}
