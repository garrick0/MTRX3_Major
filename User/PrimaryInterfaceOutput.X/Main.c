/* 
 * File:   Main.c
 * Author: W
 *
 * Created on 11 October 2016, 14:28
 */

#include <stdio.h>
#include <stdlib.h>
#include "ConfigRegs_18F4520.h"
#include "PrimaryInterfaceOutput.h"
#include "LCDWrite.h"
#include "xlcd.h"
#include "xlcddelays.h"
/*
 * 
 */
int CURRENT_DIRECTION=30;

void main(void) {
    InitialiseServo();
}

void lowPriorityIsr(void){
    if(PIR1bits.CCP1IF){            //if compare of timer1
        PIR1bits.CCP1IF=0;          //reset flag
        ServoOutput(CURRENT_DIRECTION);
    }
     
    
}
