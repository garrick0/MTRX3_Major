#include <p18f452.h>            
//#include "ConfigRegs.h"
#include "main.h"






#define IDLE 1
#define MOVING 2
#define SCAN 3
#define RECALIBRATE 4


#define SCAN_NUMBER 3


char robotState = RECALIBRATE;

void getRobotState(char State,int* encoderVals,int* currentEncoder,int chirpStrength);


void navSetup(void) {
    
}

void robotMove(char State,int* encoderVals,int* currentEncoder,int chirpStrength) {
    
    getRobotState(State,encoderVals,currentEncoder,chirpStrength);
    
}


void getRobotState(char State,int* encoderVals,int* currentEncoder,int chirpStrength) {
    
    //if new command required
    if (robotState == IDLE) {
        if (State == MANUAL_MODE) {
            //get from UI
        }
        else if (State == AUTOMATIC_MODE) {
            //generate with algorithm
        }
        else if (State == FACTORY_MODE) {
            //do nothing
        }
    
    }
    
    
    
    //if  moving
    else if (robotState == MOVING) {
        //check if finished moving
       if ((currentEncoder[0] == encoderVals[0]) && (currentEncoder[1] == encoderVals[1])) {
           //perform scan
           robotState = SCAN;
       }
           
           //continue if still moving
    }
    
    
    //if short scan
    else if (robotState == SCAN) {
        char scanNum = 20;
        int scanEdgeValues[20];
        //calculate scanning encoder values for each swath
        //move to first scan position
        //wait until in position
        //record chirp strength
        //increment counter and move to next scan position
        //when all scans finished compare max value to threshold
        //if exceeds threshold begin moving
        
        //Calculate scanning encoder values for each swath if first time
        if (scanNum == 20) {
        //calculateSwathThresholds(currentValues);
            
        //calculateEncoder Positions
            
        //Turn robot to first scan position
            
            
        
            
            scanNum = 0;
        }
        
        
        //If robot in position and 
        if ((currentEncoder[0] == scanEdgeValues[scanNum*2]) && (currentEncoder[1] == encoderVals[scanNum*2+1]) && (chirpStrength > 0)) {
            //MOVEROBOT
        }
        
        
        //Perform 3 scans
        for (scanNum = 0; scanNum < SCAN_NUMBER; scanNum++) {
            
        }
    }
}




