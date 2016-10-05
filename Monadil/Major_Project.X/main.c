/**
 *  @file main.c
 *  @author Monadil
 *  @date 24/9/16
 *  @breif Main file
 *
 *  The main program for the Robot Commander.
 * 
 *  @todo       Add scheduler - looking at cooperative scheduling.
 *  @remarks    Current method involves using a super loop.
 */

#include    <p18f452.h>
#include    "ConfigRegs.h"
#include	"communication.h"
#include    "globalVars.h"
#include	"movement.h"
#include	"navigation.h"
#include	"serial.h"
#include    "setup.h"
#include	"state.h"
#include	"user.h"

void main(void){
    while(1){
        setupLEDs(); // Set-up and calibrate
        CURRENT_STATE = MANUAL;
        stateControl(LOST);  
    }
}

// Proposed workflow
// 1. PowerOn - Calibrate initial settings
// 2. Manual mode on default
// 3. GetUserInput from commander (full scan)
// 4. Communication module transmit user commands
// 5. Communication module received from robot
// 6. Movement module - encoders positioned to move
// 7. 
