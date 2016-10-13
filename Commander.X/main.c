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
#include    "define.h"
#include    "globalVars.h"
#include	"movement.h"
#include	"navigation.h"
#include    "setup.h"
#include	"state.h"
#include	"user.h"

void main(void){
        // All setups here
        initialSetup();
        setupLEDs(); // Set-up and calibrate

        // Asynchronous scheduling method 
        while(1){
            stateControl(CURRENT_STATE);
        }    
}