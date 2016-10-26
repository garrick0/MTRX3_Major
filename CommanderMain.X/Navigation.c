#include <p18f4520.h>            
#include <math.h>
//#include "ConfigRegs.h"
#include "main.h"
#include "Communications.h"
#include "UserInterface.h"







#define IDLE 1
#define MOVING 2
#define SCANNING 3
#define TURNING 4

#define MAX_SCANS 12

#define INCS30DEGREES 744
#define FORWARDINCS 744

#define DETECTION_THRESHOLD 50
char parseUIDirection(struct UserInterfaceInput* UIInput, struct communicationsOutput* CommsOutput,struct communicationsInput* CommsInput);
char checkScan(char* chirpBuffer,struct UserInterfaceOutput* UIOutput);
void autoAlgorithm(struct communicationsOutput* CommsOutput);

char chirpBuffer[12] = {0x00};
char robotState = IDLE;
char scanCounter = 0;

char prevAutoInstr = IDLE;
char parrot_Direction = 0;
char parrotDistance = 0;






void navSetup(void) {
    
}


char robotMove(struct UserInterfaceOutput* UIOutput,struct communicationsOutput* CommsOutput,struct UserInterfaceInput* UIInput,struct communicationsInput* CommsInput,char State){
    
    //If ready for new command
    if (CommsInput->instructionFlag == 0) {
        //Check if scan has just finished
        if (robotState == SCANNING) {
            //Wait until chirp is detected and stored
            
            //TESTING
            CommsInput->chirpStrength = 1;
            
            while (CommsInput->chirpStrength == 0) {
                //wait
            }
            //Store chirp
            chirpBuffer[scanCounter] = CommsInput->chirpStrength;
            
            
            
            //Check if more scans required
            if (scanCounter < MAX_SCANS) {
                //SETSCAN(30DEGREES)

                
                
                //Increment scan counter
                scanCounter++;
                
                //Change robot state
                robotState = SCANNING;
                //Generate instruction (30 degree rotation clockwise)
                CommsOutput->instDir = 'R';
                CommsOutput->instMag = INCS30DEGREES;
                
                //Set instruction flag to high
                CommsInput->instructionFlag = 1;
                return 1;
            }
            
            //If full scan is complete
            else {
                //Calculate direction of highest chirp
                char maxMagnitude = checkScan(chirpBuffer,UIOutput);
                scanCounter = 0;
                
                //Check if value exceeds detection threshold
                    if (maxMagnitude > DETECTION_THRESHOLD) {
                        UIOutput->parrot_found = 1;
                    }
                
                //Change robot state
                robotState = IDLE;
                return 0;
            }
            
            
        }
        
        
        
        //Check if movement has just finished
        else if (robotState == IDLE) {
            //Generate command
            if (State == USER_MANUAL_MODE) {
                //Set commands to user input
                if (parseUIDirection(UIInput,CommsOutput,CommsInput)) {
                    return 1;
                }
                //Set Instruction flag high
                return 0;
            }
            
            else if (State == USER_AUTO_MODE) {
                //Automatic Algorithm
                //Inputs are - last command used, 
                autoAlgorithm(CommsOutput);
                return 1;
                
                //autoAlgorithm(UIOutput)
            }
            

        }
        
        //If command finished
        else if (robotState == MOVING) {
            robotState = IDLE;
            return 0;
        }
        
    }
    
    //If completing action
    else {
        //Do nothing
        return 0;
    }
}




//Return direction of highest value chirp
char checkScan(char* chirpBuffer,struct UserInterfaceOutput* UIOutput)  {
    char i;
    char maxDir = 0;
    char maxVal = 0;
    //Rotate through buffer and get highest value
    for (i = 0; i < 12; i++) {
        if (chirpBuffer[i] > maxVal) {
            maxDir = i;
            maxVal = chirpBuffer[i];
        }
    }
    
    UIOutput->parrotDirection = maxDir;
    
    parrotDistance = maxVal;
    parrot_Direction = maxDir;
    return maxVal;
    
}

char parseUIDirection(struct UserInterfaceInput* UIInput, struct communicationsOutput* CommsOutput,struct communicationsInput* CommsInput) {
    
    //Move Forward
    if (UIInput->commandInput == 'U') {
        CommsOutput->instMag = FORWARDINCS;
        CommsOutput->instDir = UIInput->commandInput;
        robotState = MOVING;
        CommsInput->instructionFlag = 1;
        return 1;
    }
    
    
        //Move Back
    else if (UIInput->commandInput == 'D') {
        CommsOutput->instMag = FORWARDINCS;
        CommsOutput->instDir = UIInput->commandInput;
        robotState = MOVING;
        CommsInput->instructionFlag = 1;
        return 1;
    }
    
            //Move Right
    else if (UIInput->commandInput == 'R') {
        CommsOutput->instMag = INCS30DEGREES;
        CommsOutput->instDir = UIInput->commandInput;
        robotState = MOVING;
        CommsInput->instructionFlag = 1;
        return 1;
    }
    
                //Move Left
    else if (UIInput->commandInput == 'L') {
        CommsOutput->instMag = INCS30DEGREES;
        CommsOutput->instDir = UIInput->commandInput;
        robotState = MOVING;
        CommsInput->instructionFlag = 1;
        return 1;
    }
    
                    //Move Left
    else if (UIInput->commandInput == 'F') {
        robotState = SCANNING;
        CommsInput->instructionFlag = 1;
        return 1;
    }
    
    else if (UIInput->commandInput == 'H') {
        robotState = SCANNING;
        CommsInput->instructionFlag = 1;
        return 1;
    }
    return 0;
    
}
    


void autoAlgorithm(struct communicationsOutput* CommsOutput) {
    
    //Initiate with rotation to get robot position
    if ((prevAutoInstr == IDLE)) {
        
        //This will set the robot to perform a full scan
        robotState = SCANNING;
        prevAutoInstr = SCANNING;
        
    }
    
    //Assumption you have parrot position at this state
    else if (prevAutoInstr == SCANNING) {
        //Generate command yourself from chirps
        CommsOutput->instDir = 'R';
        CommsOutput->instMag = parrot_Direction*INCS30DEGREES;
        
        //Change to moving
        robotState = MOVING;
        //Move to parrot direction
        prevAutoInstr = TURNING;
    }
    else if (prevAutoInstr == TURNING) {
        //Needs to be generated from calibration data
        int distLookup[6] = {100,200,300,400,500,600};
                
        //Set to move forward
        CommsOutput->instDir = 'F';
        //look up increments in table
        CommsOutput->instMag = distLookup[parrotDistance/10];
        
        //Change to moving
        robotState = MOVING;
        //Update auto mode
        prevAutoInstr = MOVING;
    }
    
        //Go back to idle state to check if still in auto mode
    else if (prevAutoInstr == MOVING) {
          //Change to Idle state
        robotState = IDLE;
        //Update auto mode
        prevAutoInstr = IDLE;
    }
    
    
}