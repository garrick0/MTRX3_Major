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
void receiveComms(char* receiveBuffer,char *flag);
void transmitComms(struct communicationsOutput CommsOutput);
void processReceived(char* Buffer,char* IRVals, char* instructionFlag, char * chirpStr, char *connection);
void handShake(void);
//Nav
void navSetup(void);
//void robotMove(char State,int* encoderVals,int* currentEncoder,int* chirpStrength,int* parrotLoc,char* distance);
char robotMove(struct UserInterfaceOutput* UIOutput,struct communicationsOutput* CommsOutput,struct UserInterfaceInput* UIInput,struct communicationsInput* CommsInput,char State);
    
    
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



    
    //Input and output structs
    
    //Holds values input by the user
    struct UserInterfaceInput UIInput;
    struct UserInterfaceInput *ptrUIInput=&UIInput;
    
    //Holds values output to the user
    struct UserInterfaceOutput UIOutput;
    struct UserInterfaceOutput *ptrUIOutput=&UIOutput;
    
    //Holds values transmitted by robot comms
    struct communicationsInput RobotReceiveComms;
    
    //Variables transmitted to robot
    struct communicationsOutput RobotTransmitComms;








    //flag set on serial receive
char receiveFlag;

    //Receive Buffer used for storage         
char recBuffer[30];

    //Store user inputs
char UIbuffer[1];			

        
    //System State
char State = INITIALISE;
        
    //IR Value Thresholds
char IRVals[3];
   
    //Is robot idle
char instructionFlag = 0;

    //Chirp Strength
char chirpStrength;

    //Comms status to robot
char connection;

    //Robot Instruction Magnitude
int instMag;
    
    //Robot Instruction Type
char instDir;

    //Test variable
int test;

int UIdelay = 0;
char deBounce=0;
char deBounceThreshold=10;

char newInstruction = 0;













/** 
 * @brief Main Function
 *  
 * Implements Robot Control
 * 
 *  
 * @return 
 */



void main(void) {

  
    
    //disable interrupts
    INTCONbits.GIE_GIEH = 0;    //global interrupt disable
	INTCONbits.PEIE_GIEL = 0;   //peripheral interrupt disable    
         
         
    //UI
    UISetup();
    
    (UIInput.stateRequest)=INITIALISE;
    (UIInput.max_robot_speed)=10;
    (UIInput.max_yaw_rate)=10;		
    (UIInput.ir_samples)=10;
    (UIInput.ir_rate)=10;
    (UIInput.rf_samples)=10;
    (UIInput.p_gain)=10;
    (UIInput.i_gain)=10;
    (UIInput.d_gain)=10;			
    (UIInput.motors)=0;
    (UIInput.find_parrot)=0;
    (UIOutput.parrotDirection)=90;
    (UIOutput.parrotDistance)=10;
    (UIOutput.ir_left)=30;
    (UIOutput.ir_front)=20;
    (UIOutput.ir_right)=10;
    (UIOutput.parrot_moving)=0;
    (UIOutput.parrot_found)=0;
    (UIOutput.instMag)=0;
    (UIOutput.instDir)=0;
    (UIOutput.instructionFlag)=0;
    (UIOutput.half_scan)=0;			//1 when scanning, 0 when not scanning
	(UIOutput.full_scan)=0;
    
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 1;
    INTCONbits.GIE = 1;
    while((UIInput.stateRequest)==INITIALISE){
        inputUI(UIbuffer,&UIInput);
        (UIOutput.State)=(UIInput.stateRequest);
        outputUI(&UIOutput);
    }
    INTCONbits.PEIE = 0;
    RCONbits.IPEN = 0;
    // Comms
    commSetup();

    /////////////////////////// TEST CODE BEGIN ////////////////////////////////
    


    
    
    

    
    
        
        //State = AUTOMATIC_MODE;
    State = USER_MANUAL_MODE;
        UIInput.commandInput='U';
        RobotReceiveComms.instructionFlag=0;
        test = RobotTransmitComms.instDir;
        test = RobotTransmitComms.instMag;
        

    RobotTransmitComms.instMag = 1000;
    RobotTransmitComms.instDir = 'b';
    
    
    
    
	
    /////////////////////////// TEST CODE END ////////////////////////////////
    
  
       //Enable Interrupts
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 1;
    INTCONbits.GIE = 1;
    
    
    
    
    
    
    

    
    //transmitComms(RobotTransmitComms);   
    
    /* Loop */
    while(1){
        int test1;
 
            //Parses the UI buffer (contains interrupt info) and modifies the UIInput struct
        inputUI(UIbuffer,&UIInput);
            

        

        
        
                (UIOutput.State)=(UIInput.stateRequest);
        (UIOutput.max_robot_speed)=(UIInput.max_robot_speed);	//return values of all parameters
        (UIOutput.max_yaw_rate)=(UIInput.max_yaw_rate);
        (UIOutput.ir_samples)=(UIInput.ir_samples);
        (UIOutput.ir_rate)=(UIInput.ir_rate);
        (UIOutput.p_gain)=(UIInput.p_gain);
        (UIOutput.i_gain)=(UIInput.i_gain);
        (UIOutput.d_gain)=(UIInput.d_gain);
        (UIOutput.rf_samples)=(UIInput.rf_samples);
        //end test code
        
        
        
        
        
        
        
  
        //Receive Comms from ground (array)
        if (receiveFlag == 1) {
            
            
            //Return values from robot
            processReceived(recBuffer,IRVals, &instructionFlag, &chirpStrength,&connection);
            
            //Store in struct
            RobotReceiveComms.IR1 = IRVals[0];
            RobotReceiveComms.IR2 = IRVals[1];
            RobotReceiveComms.IR3 = IRVals[2];
            RobotReceiveComms.instructionFlag = instructionFlag;
            RobotReceiveComms.chirpStrength=chirpStrength;
            UIOutput.parrotDistance = chirpStrength;
            //Reset flag
            if (chirpStrength <=0x25){
                UIOutput.parrot_found=1;
            }else{
                UIOutput.parrot_found=0;
            }
        
            if (chirpStrength > 0) {
                test = 0;
            }
            receiveFlag = 0;
        }
        
        //State Control
        State = stateControl(State,UIInput.stateRequest);
        
        if (State == USER_MANUAL_MODE) {
            test++;
        }
        
        else if (State == USER_AUTO_MODE) {
            test++;
        }
        
        
        if (UIInput.commandInput == 'D') {
            test++;
        }
        else if (UIInput.commandInput=='U') {
            test++;
        }
        
        if (RobotReceiveComms.instructionFlag == 1) {
            test = 0;
        }

        //Generate system outputs from inputs
        newInstruction = robotMove(&UIOutput,&RobotTransmitComms,&UIInput,&RobotReceiveComms,State);
        //RobotReceiveComms.instructionFlag = 0;
         
        
        //Output UI values to user
        outputUI(&UIOutput);
        

        
        
       //Transmit Instruction to robot if new one is generated (only transmit when in the correct menu   )
        if (newInstruction & (State != INITIALISE)) {
            
            //while(connection == 0){
                //handShake();
                //if(receiveFlag == 1){
                //    processReceived(recBuffer,IRVals, &instructionFlag, &chirpStrength,&connection);
                //}
            //}
            test++;
            transmitComms(RobotTransmitComms);
            newInstruction = 0;
        }

    }
}
#pragma interrupt low_interrupt
void low_interrupt(void){
    //INTCONbits.GIE = 0;
    if(ORInput /*&& deBounce>=deBounceThreshold*/){				//check if user input triggered interrupt
        INTCON3bits.INT1IF = 0;	//clear PORTB1 interrupt flag
        deBounce=0;
		CheckUserInput(UIbuffer);     
	}
    if(INTCONbits.TMR0IF){          //delay interrupt  
        INTCONbits.TMR0IF=0;
        INTCONbits.TMR0IE =0;       //disable interrupt
        T0CONbits.TMR0ON =0;        //turn timer off       
        UIdelay=1;
        
    }
    if(PIR1bits.RCIF){        //check PC input flag
        CheckPCInput(UIbuffer);
        
    }
    if(PIR2bits.CCP2IF){      //check is servo delay triggered interrupt
        PIR2bits.CCP2IF = 0;
        servoToggle();
        if(deBounce<deBounceThreshold){
            deBounce++;
        }
    }
    //INTCONbits.GIE = 1;

}
#pragma interrupt high_interrupt
void high_interrupt(void) {
/*Serial Receive Interrupt*/
    if (INTCON3bits.INT2IF == 1) {
        
        receiveComms(recBuffer,&receiveFlag);
        INTCON3bits.INT2IF = 0;

    }

    
    // Disable Interrupts
    INTCONbits.GIE = 0;
    
        
	if(EmergencyStop){              //check if user input triggered interrupt
        INTCONbits.INT0IF = 0;      //clear PORTB0 interrupt flag
		Emergency_Stop(UIbuffer);
        
	}
    

    //Enable Interrupts
    INTCONbits.GIE = 1;
    

    
}


char stateControl(char State,char stateRequest) {
    return stateRequest;
}