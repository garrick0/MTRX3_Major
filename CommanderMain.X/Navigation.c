#include <p18f4520.h>            
#include <math.h>
//#include "ConfigRegs.h"
#include "main.h"
#include "Communications.h"
#include "UserInterface.h"







#define IDLE 1
#define MOVING 2
#define SCANNING 3

#define MAX_SCANS 12

#define INCS30DEGREES 500
#define FORWARDINCS 500

#define DETECTION_THRESHOLD 50
void parseUIDirection(struct UserInterfaceInput* UIInput, struct communicationsOutput* CommsOutput);
char checkScan(char* chirpBuffer,struct UserInterfaceOutput* UIOutput);

char chirpBuffer[12] = {0x00};
char robotState = SCANNING;
char scanCounter = 0;






void navSetup(void) {
    
}


void robotMove(struct UserInterfaceOutput* UIOutput,struct communicationsOutput* CommsOutput,struct UserInterfaceInput* UIInput,struct communicationsInput* CommsInput,char State){
    
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
                //Set instruction flag to high
                CommsInput->instructionFlag = 1;
                
                
                //Increment scan counter
                scanCounter++;
                
                //Change robot state
                robotState = SCANNING;
                //Generate instruction (30 degree rotation clockwise)
                CommsOutput->instDir = 'R';
                CommsOutput->instMag = INCS30DEGREES;
            }
            
            //If full scan is complete
            else {
                //Calculate direction of highest chirp
                char maxMagnitude = checkScan(chirpBuffer,UIOutput);
                
                //Check if value exceeds detection threshold
                    if (maxMagnitude > DETECTION_THRESHOLD) {
                        UIOutput->parrot_found = 1;
                    }
                
                //Change robot state
                robotState = IDLE;
            }
            
            
        }
        
        
        
        //Check if movement has just finished
        else if (robotState == IDLE) {
            //Generate command
            if (State == MANUAL_MODE) {
                //Set commands to user input
                parseUIDirection(UIInput,CommsOutput);
                //Set Instruction flag high
                
            }
            
            else if (State == AUTOMATIC_MODE) {
                //Automatic Algorithm
            }
            
            CommsInput->instructionFlag = 1;
        }
        
        //If command finished
        else if (robotState == MOVING) {
            robotState = IDLE;
        }
        
    }
    
    //If completing action
    else {
        //Do nothing
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
    
    UIOutput->current_direction = maxDir;
    

    return maxVal;
    
}

void parseUIDirection(struct UserInterfaceInput* UIInput, struct communicationsOutput* CommsOutput) {
    
    //Move Forward
    if (UIInput->commandInput == 'U') {
        CommsOutput->instMag = FORWARDINCS;
        CommsOutput->instDir = UIInput->commandInput;
        robotState = MOVING;
    }
    
    
        //Move Back
    else if (UIInput->commandInput == 'B') {
        CommsOutput->instMag = FORWARDINCS;
        CommsOutput->instDir = UIInput->commandInput;
        robotState = MOVING;
    }
    
            //Move Right
    else if (UIInput->commandInput == 'R') {
        CommsOutput->instMag = INCS30DEGREES;
        CommsOutput->instDir = UIInput->commandInput;
        robotState = MOVING;
    }
    
                //Move Left
    else if (UIInput->commandInput == 'L') {
        CommsOutput->instMag = INCS30DEGREES;
        CommsOutput->instDir = UIInput->commandInput;
        robotState = MOVING;
    }
    
                    //Move Left
    else if (UIInput->commandInput == 'F') {
        robotState = SCANNING;
    }
    
    else if (UIInput->commandInput == 'H') {
        robotState = SCANNING;
    }
    
}
    
    