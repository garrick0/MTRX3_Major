#include <p18f4520.h>            
#include <math.h>
//#include "ConfigRegs.h"
#include "main.h"







#define IDLE 1
#define MOVING 2
#define SCAN 3
#define RECALIBRATE 4


#define SCAN_NUMBER 3

//#define SWATHSIZE 30
//#define MAX_SCANS 360/SWATHSIZE
#define MAX_SCANS 12

#define ENCODERTICKSPERREVOLUTION 1000



char robotState = RECALIBRATE;

void getRobotState(char State,int* targetEncoder,int* currentEncoder,int* chirpStrength,int* parrotLoc,char* distance);

void scan(int* currentEncoder,int* targetEncoder,int* chirpStrength,int totalScans,int* parrotLoc,char* distance);

//Calculates encoder array positions
void calcScanPositions(int* currentEncoder,int totalScans,int* scanEncoderValsLeft,int* scanEncoderValsRight);






void navSetup(void) {
    
}

void robotMove(char State,int* targetEncoder,int* currentEncoder,int* chirpStrength,int* parrotLoc,char* distance) {
    
    //check if in state
    //generate next function
    
    
    
    
    //getRobotState(State,targetEncoder,currentEncoder,chirpStrength,parrotLoc,distance);
    
}





void getRobotState(char State,int* targetEncoder,int* currentEncoder,int* chirpStrength,int* parrotLoc,char* distance) {
    
    //Test values
    int currEncoder[2];
    int scanEncValsLeft[10];
    int scanEncValsRight[10];
    currEncoder[0] = 100;
    currEncoder[1] = 100;
    //int totalScans = 3;

    
    
    calcScanPositions(currEncoder,12, scanEncValsLeft, scanEncValsRight);
    
    
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
       if ((currentEncoder[0] == targetEncoder[0]) && (currentEncoder[1] == targetEncoder[1])) {
           //perform scan
           robotState = IDLE;
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
    }
}




void scan(int* currentEncoder,int* targetEncoder,int* chirpStrength,int totalScans,int* parrotLoc,char* parrotDistance) {
    //generic index
    int i;
    
    //Initialise scan at -1
    int scanNum = -1;
    
    //Stores encoder start and end value for each scan
    int scanEncoderValsLeft[(MAX_SCANS)];
    int scanEncoderValsRight[MAX_SCANS];
    
    //calcScanPositions(currentEncoder,totalScans);
    
    
    
    //Stores chirp strength at each movement
    char scanChirpVals[MAX_SCANS];
    
    
    calcScanPositions(currentEncoder,totalScans,scanEncoderValsLeft,scanEncoderValsRight);
    
    //initScan
    if (scanNum == -1) {
        //calculateSwathThresholds(currentValues);
            
        //calculateEncoder Positions
            
        //Turn robot to first scan position
        targetEncoder[0] = scanEncoderValsLeft[0];
        targetEncoder[1] = scanEncoderValsRight[0];
            
        
            
            scanNum = 0;
        }
        
        
        //If robot in position and chirp detected
        if ((currentEncoder[0] == scanEncoderValsLeft[scanNum]) && (currentEncoder[1] == scanEncoderValsRight[scanNum]) && (*chirpStrength > 0)) {
            //MOVEROBOT
            //Store chirp strength for this scan
            scanChirpVals[scanNum] = *chirpStrength;
            
            //clear chirp
            *chirpStrength = 0;
            
            //Increment scan
            scanNum++;
            
            
            
            //if final scan, analyse data
            if (scanNum == totalScans) {
                char maxChirpLoc=0;
                for (i = 0; i < totalScans; i++) {
                    
                    //Get scan location where chirp strength is highest
                    if (scanChirpVals[i] > scanChirpVals[maxChirpLoc]) {
                        maxChirpLoc = i;
                        

                    } 
                    

                }
                                    
                
                   //Parrot direction is at max chirp location
                parrotLoc[0] = scanEncoderValsLeft[maxChirpLoc];
                parrotLoc[1] = scanEncoderValsRight[maxChirpLoc];
                    
                    //calculate parrot distance
                *parrotDistance = scanChirpVals[maxChirpLoc];
                
                    

            } 
            
            
            // If more scans required
            else {
                //Update Target encoder values
                targetEncoder[0] = scanEncoderValsLeft[scanNum];
                targetEncoder[1] = scanEncoderValsRight[scanNum];
                 
            }
        }
                    
            
    }
        
        
        
        
    //
    void calcScanPositions(int* currentEncoder,int totalScans,int* scanEncoderValsLeft,int* scanEncoderValsRight) {
        int i;
        int test;
        int x;
        
        
        int Incs15Degrees = ENCODERTICKSPERREVOLUTION/24;
        currentEncoder[0]=100;
        currentEncoder[1]=100;
        

        
        if (totalScans%2 == 1) {
                    //get value of middle index
            
            int centreIndex = (totalScans+1)/2-1;
            
            //store current encoder values at center index
            test = currentEncoder[0];
            x = centreIndex;
            scanEncoderValsLeft[centreIndex] = currentEncoder[0];
            test = currentEncoder[1];
            scanEncoderValsRight[centreIndex] = currentEncoder[1];
            
            
            //add current position as centre value
            //scanEncoderVals[(totalScans-1)] = currentEncoder[0];
            //scanEncoderVals[totalScans] = currentEncoder[1];
            
            for (i=0;i< centreIndex;i++) {

                //Store centre + ith value
                test = currentEncoder[0]+2*(i+1)*Incs15Degrees;
                x = centreIndex+i+1;
                scanEncoderValsLeft[centreIndex+i+1] = currentEncoder[0]+2*(i+1)*Incs15Degrees;
                test = currentEncoder[1]-Incs15Degrees;
                scanEncoderValsRight[centreIndex+i+1] = currentEncoder[1]-2*(i+1)*Incs15Degrees;
                
                //Store centre - ith value (signs swapped)
                test = currentEncoder[0]-Incs15Degrees;
                x = centreIndex-(i+1);
                scanEncoderValsLeft[centreIndex-(i+1)] = currentEncoder[0]-2*(i+1)*Incs15Degrees;
                test = currentEncoder[0]-Incs15Degrees;
                scanEncoderValsRight[centreIndex-(i+1)] = currentEncoder[1]+2*(i+1)*Incs15Degrees;
                
                
            }
            
            for (i = 0; i < MAX_SCANS; i++) {
                x++;
                test = scanEncoderValsLeft[i];
                x++;
                test = scanEncoderValsRight[i];
                x++;
            }
            
            
        }
        
        
        //if index is odd
        else {
            int i;
            int x;
            int test;
            //centre index + .5
            int centreIndexHigh = totalScans/2;
            
            
                        //store current encoder values at center index
            test =currentEncoder[0] + Incs15Degrees;
            scanEncoderValsLeft[centreIndexHigh] = currentEncoder[0] + Incs15Degrees;
            test = currentEncoder[1] - Incs15Degrees;
            scanEncoderValsRight[centreIndexHigh] = currentEncoder[1] - Incs15Degrees;
            
            //centre - 1
            x = centreIndexHigh-1;
            test =currentEncoder[0] - Incs15Degrees;
            scanEncoderValsLeft[centreIndexHigh-1] = currentEncoder[0] - Incs15Degrees;
            test =currentEncoder[0] + Incs15Degrees;
            scanEncoderValsRight[centreIndexHigh-1] = currentEncoder[1] + Incs15Degrees;
            
            //Cycle through and add for those not in middle
            for (i = 0; i < centreIndexHigh-1; i++) {
                //values right of centre
                x =centreIndexHigh+(i+1);
                test = currentEncoder[0] + Incs15Degrees +2*(i+1)*Incs15Degrees;
                scanEncoderValsLeft[centreIndexHigh+(i+1)] = currentEncoder[0] + Incs15Degrees +2*(i+1)*Incs15Degrees;
                test= currentEncoder[1] - Incs15Degrees - 2*(i+1)*Incs15Degrees;
                scanEncoderValsRight[centreIndexHigh+(i+1)] = currentEncoder[1] - Incs15Degrees - 2*(i+1)*Incs15Degrees;
                x =centreIndexHigh-(i+1);
                //values left of centre
                test = currentEncoder[0] - Incs15Degrees-2*(i+1)*Incs15Degrees;
                scanEncoderValsLeft[centreIndexHigh-(i+2)] = currentEncoder[0] - Incs15Degrees-2*(i+1)*Incs15Degrees;
                test=currentEncoder[1] + Incs15Degrees+2*(i+1)*Incs15Degrees;
                scanEncoderValsRight[centreIndexHigh-(i+2)] = currentEncoder[1] + Incs15Degrees+2*(i+1)*Incs15Degrees;
                
            }
            
            
            
            
            
            
        }
        
       
    }
