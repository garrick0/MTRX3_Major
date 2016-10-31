
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
void low_interrupt( void );
//void goto_high_ISR(void);
//void goto_low_ISR(void);
// UI
void UISetup(void);
void inputUI(char* UIbuffer,struct UserInterfaceInput* UIInput);
//void inputUI(char* UIBuffer,char* State,char* commandInput);
void outputUI(struct UserInterfaceOutput *UIOutput);
//char storeUI(char* UIBuffer);

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
#pragma code high_interrupt_vector = 0x0008
void goto_high_ISR(void) {
    _asm goto high_interrupt _endasm
}
#pragma code

#pragma code low_interrupt_vector=0x0018
void goto_low_ISR( void ){
    _asm goto low_interrupt _endasm       
}
#pragma code

//Global Variables
//flag set on serial receive
char receiveFlag;
//Receive Buffer used for storage         
char recBuffer[30];

char	UIbuffer[1];			//stores user inputs
int UIdelay=0;

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
    struct UserInterfaceInput *ptrUIInput=&UIInput;
    
    //Holds values output to the user
    struct UserInterfaceOutput UIOutput;
    struct UserInterfaceOutput *ptrUIOutput=&UIOutput;
    
    //Holds values transmitted by robot comms
    struct communicationsInput RobotReceiveComms;
    
    struct communicationsOutput RobotTransmitComms;
    
    
    //Triggered in interrupt
    char UIFlag;
    
    
    
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
    
    //disable interrupts
    INTCONbits.GIE_GIEH = 0;    //global interrupt disable
	INTCONbits.PEIE_GIEL = 0;   //peripheral interrupt disable    
         
         
    //UI
    UISetup();


    // Comms
    //commSetup();



    //Nav
    //navSetup();
    
   
     //code for testing
    (ptrUIInput->stateRequest)=INITIALISE;
    (ptrUIInput->max_robot_speed)=10;
    (ptrUIInput->max_yaw_rate)=10;		
    (ptrUIInput->ir_samples)=10;
    (ptrUIInput->ir_rate)=10;
    (ptrUIInput->rf_samples)=10;
    (ptrUIInput->p_gain)=10;
    (ptrUIInput->i_gain)=10;
    (ptrUIInput->d_gain)=10;			
    (ptrUIInput->motors)=0;
    (ptrUIInput->find_parrot)=0;
    (ptrUIOutput->parrotDirection)=90;
    (ptrUIOutput->parrotDistance)=10;
    (ptrUIOutput->ir_left)=30;
    (ptrUIOutput->ir_front)=20;
    (ptrUIOutput->ir_right)=10;
    (ptrUIOutput->parrot_moving)=1;
    (ptrUIOutput->parrot_found)=1;
    (ptrUIOutput->instMag)=0;
    (ptrUIOutput->instDir)=0;
    (ptrUIOutput->instructionFlag)=1;
    (ptrUIOutput->half_scan)=0;			//1 when scanning, 0 when not scanning
	(ptrUIOutput->full_scan)=0;
    //end test code
    
  
       //Enable Interrupts
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 1;
    INTCONbits.GIE = 1;
    
    /* Loop */
    while(1){
        

              
            //Process user interface input if interrupt triggered
        //if (UIFlag ==1) {
            //UI Should receive(Change of system state, Direction Inputs and parameter changes(not yet implemented)
            
            //Parses the UI buffer (contains interrupt info) and modifies the UIInput struct
        inputUI(UIbuffer,ptrUIInput);
            
            //UIFlag = 0;
        //}
        
        if (ptrUIInput->stateRequest != 0) {
            int test = ptrUIInput->commandInput;
            test++;
        }
         
        
        
        //Receive Comms from ground (array)
            //array [IRVals,signalStrength,instructionFlag]
        if (receiveFlag == 1) {
            
            //Get sensor data from robot
            //chirpStrength = processReceived(recBuffer,IRVals,&instructionFlag);
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
        
        
        //robotMove(&UIOutput,&RobotTransmitComms,UIInput,RobotReceiveComms,State);
        //outputs - instMag,instDir
        //        - parrotPosition,IRVals,parrot_moving,parrot_found
        //inputs  - chirpStrength,IRVals,instructionFlag,State
        
        
        
        
        //instMag = 100;
        //instDir = 'f';
        //transmit to ground to move robot
        //transmitComms(RobotTransmitComms);
                
        //test code
        (ptrUIOutput->State)=(ptrUIInput->stateRequest);
        (ptrUIOutput->max_robot_speed)=(ptrUIInput->max_robot_speed);	//return values of all parameters
        (ptrUIOutput->max_yaw_rate)=(ptrUIInput->max_yaw_rate);
        (ptrUIOutput->ir_samples)=(ptrUIInput->ir_samples);
        (ptrUIOutput->ir_rate)=(ptrUIInput->ir_rate);
        (ptrUIOutput->p_gain)=(ptrUIInput->p_gain);
        (ptrUIOutput->i_gain)=(ptrUIInput->i_gain);
        (ptrUIOutput->d_gain)=(ptrUIInput->d_gain);
        (ptrUIOutput->rf_samples)=(ptrUIInput->rf_samples);
        //end test code
        
        
            
                
                
        //State,parrotDirection,parrotDistance,IRVals,parrot_moving,parrot_found
        outputUI(ptrUIOutput);

    }
}
#pragma interrupt low_interrupt
void low_interrupt(void){
 
    
	if(INTCONbits.TMR0IF){          //check if delay timer triggered interrupt
        INTCONbits.TMR0IF=0;
        INTCONbits.TMR0IE =0;       //disable interrupt
        T0CONbits.TMR0ON =0;        //turn timer off       
        UIdelay=1;
    }else if(PIR1bits.RCIF){        //check if serial receive triggered interrupt
        CheckPCInput(UIbuffer);
    }else if(PIR2bits.CCP2IF){      //check is servo delay triggered interrupt
        PIR2bits.CCP2IF = 0;
        servoToggle();
    }
  
}
#pragma interrupt high_interrupt
void high_interrupt(void) {
    // Disable Interrupts
    INTCONbits.GIE = 0;
     
        /*Serial Receive Interrupt*/
    if (PIR1bits.RCIF == 1) {

        //receiveFlag = receiveComms(recBuffer);
        PIR1bits.RCIF = 0;

    }	
	else if(EmergencyStop){              //check if user input triggered interrupt
        INTCONbits.INT0IF = 0;      //clear PORTB0 interrupt flag
		Emergency_Stop(UIbuffer);
	}else if(ORInput){				//check if user input triggered interrupt
        INTCON3bits.INT1IF = 0;	//clear PORTB1 interrupt flag
		CheckUserInput(UIbuffer);
        
	}
    
    

    //Enable Interrupts
    INTCONbits.GIE = 1;
    

    
}


char stateControl(char State,char stateRequest) {
    return stateRequest;
}

