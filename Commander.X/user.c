/**
  * @file user.c
  * @author Will
  * @date 24/9/16
  * @brief  Read user input from command controller.
  *
  * Reads a user inputted buffer and returns appropriate output
  *
  */

#include    <p18f452.h>
#include    "globalVars.h"
#include    "user.h"
#include    "define.h"

//! Start up initialization - specifically to put mode into MANUAL.
void initialSetup(void){
     CURRENT_STATE = MANUAL;
    
}

//! Maybe implement an interrupt where all the user inputs are stored into a buffer.
void getInputs(unsigned char PARROT_FOUND, unsigned char INTERFACE_MODE){
    
}

//! Take inputs from the command controller and output appropriate state.
char userOutput(void){
 
}


