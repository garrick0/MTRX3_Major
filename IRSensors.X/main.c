//**********************************************************
//*  IR Sensor Module
//**********************************************************
//*  Samuel Gleeson    
//*  
//*  
//**********************************************************
#include <stdio.h>
#include <stdlib.h>
#include <p18f4520.h>
//#include "IRSensors.c"
#include <usart.h>
#include "ConfigRegs_18F4520.h"
//#include "IRSensor.c"
#include "IRSensors.h"
//#include "sw_spi.h"
//#include "spi.h"
//#include "math.h"



//number used for testing
int testnum = 0;

//Array containing detected object thresholds
int detectVals[3];

void high_interupt(void);
void highPriorityISR(void);




void main() {
    
    IRSetup();
    timerSetup();
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

    INTCON   = 0b10000000;  // Enable all high priority interrupts

    while(1) {
        
        //Read IR sensor buffer and return result
        IRDetect(2,detectVals);
        if (detectVals[0] == 1) {
            testnum++;
        }
        
        if (detectVals[1] == 1) {
            testnum++;
        }
        
        if (detectVals[2] == 1) {
            testnum++;
        }

        
    }
}























#pragma code highPriorityInterruptAddress = 0x0008
void high_interupt(void){
    _asm GOTO highPriorityISR _endasm
}



#pragma interrupt highPriorityISR
void highPriorityISR(void){
    //you need to use async PL to switch modes
    //(for the input chip)
    //you want to use PL input, clock once to get 8 values parallel in, then set PL high, then use SPI to shift the 8 bits through serially

    //while(!INTCONbits.TMR0IF);     // Wait for Time 0 to time out
    
    //Sample IR sensor and store in buffer
    sampleIR();
    ADCON0bits.GO = 1;
    
    PIR1 = 0;
    PIR2 = 0;
    

    return;

}














void timerSetup() {
    
    T1CON = 0b10000001;
    T3CON = 0b00000000;
            
    CCP1CON = 0b00000010;
    PIE1bits.CCP1IE = 1;     // Enables CCP1 interrupts
    IPR1bits.CCP1IP = 1;     // Sets CCP1 interrupt to high priority
    PIR1bits.CCP1IF = 0;
    
    
    //PIE1 = 0b00000100;      

    //IPR1 = 0b00000100;     

    RCON = 0b10000000;      // Enables priority levels on interrupts 

    CCPR1L = 0x82;         // Set period to 30Hz  
    //CCPR1H = 0x35;
    
    //slower value
    CCPR1H = 0xF5;
}




void IRDetect( int numAverage,int* detectArray) {
    int IRVals[3];
    // Return the sum of 
        IRDistances(numAverage,IRVals);
     
        IRThresholds(IRVals,detectArray);
        
}
















void IRThresholds(int* IRVals, int* detectArray) {
    int i;
    for (i = 0; i < 3; i++) {
            if (IRVals[i] > 150) {
                //Detection on 1
               
                IRVals[i] = 0;
                detectArray[i] = 1;
                    
            }
            else {
                detectArray[i] = 0;
            }
    }
        
}


void IRDistances(int numAverage, int* vals) {
    
    // used as generic index
    int i;
    
    //Stores buffer index being read from
    int readIndex;
    
    
    //Index of last buffer input
    int index0 = IRIndex0-1;
    int index1 = IRIndex1-1;
    int index2 = IRIndex2-1;
    
    //stores sum of buffers
    int IRSum0 = 0;
    int IRSum1 = 0;
    int IRSum2 = 0;
    
    int holder;

    
            /////////// Loops through buffer
    for (i = 0; i < numAverage; i++) {
        
        readIndex =  (MAXIMUM_IR+IRIndex0-1-i)%MAXIMUM_IR ;
        
        holder = IRBuffer0[readIndex];
        
        IRSum0 += IRBuffer0[readIndex];
        
        
    }
    vals[0]= IRSum0;
    
    
    for (i = 0; i < numAverage; i++) {
        
        readIndex =  (MAXIMUM_IR+IRIndex1-1-i)%MAXIMUM_IR ;
        
        IRSum1 += IRBuffer1[readIndex];
        
        
    }
    vals[1]= IRSum1;
    

    
    for (i = 0; i < numAverage; i++) {
        
        readIndex =  (MAXIMUM_IR+IRIndex2-1-i)%MAXIMUM_IR ;
        
        IRSum2 += IRBuffer2[readIndex];
    
        
    }
    
    vals[2]= IRSum2;
    
    //reset sums
    //IRSum0 = 0; 
    //IRSum1 = 0;
    //IRSum2 = 0;
    return vals;
}














//From lecture slides


void sampleIR() {
    int rawVal;
    //Read value
    rawVal = readIR();
    //Store in buffer
    storeBuffer(rawVal);
    
    //Change sensor
    changeSensor();

    //PIR1bits.CCP1IF = 0; //turn off interrupt flag
}




int readIR() {
    int sensorVal;
    
    //wait until conversion complete
    while (PIR1bits.ADIF == 0) {}

    //return high byte
    return ADRESH;
    
}


void changeSensor() {
    if (counter == 0) {
 
    //Sensor 2 
        ADCON0bits.CHS = 0b0001;
        //
        counter = 1;
    }
    
    //Second Sensor
    else if (counter == 1) {
        //Sensor 3
        ADCON0bits.CHS = 0b0010;
        counter = 2;
        
    }
    
    //Third Sensor
    else if (counter == 2) {
        
            //Sensor 1
        ADCON0bits.CHS = 0b0000;
        //reset timer
        counter = 0;

    }
}

void storeBuffer(int high) {
    //check sensor number
    //store in buffer
    if (counter == 0) {
        //reset buffer index if reached max
        if (IRIndex0 == MAXIMUM_IR) {
            IRIndex0 = 0;
        }
        
        //store in buffer
        
        IRBuffer0[IRIndex0] = high;
        IRIndex0++;
        
    }
    
    else if (counter == 1) {
        if (IRIndex1 == MAXIMUM_IR) {
            IRIndex1 = 0;
        }
        
        //store in buffer
        IRBuffer1[IRIndex1] = high;
        IRIndex1++;
        
    }
    
    
    
    else if (counter == 2) {
        if (IRIndex2 == MAXIMUM_IR) {
            IRIndex2 = 0;
        }
        
        //store in buffer
        IRBuffer2[IRIndex2] = high;
        IRIndex2++;
        
    }
    
    
}



