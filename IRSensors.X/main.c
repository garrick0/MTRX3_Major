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












