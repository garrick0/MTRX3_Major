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
    
}

//! Maybe implement an interrupt where all the user inputs are stored into a buffer.
void getInputs(void){
    
}

//! Take inputs from the command controller and output appropriate state.
int userOutput(int directionInput, int scan, int changeState, int secondayInterface){

}

void displayLCD(unsigned char CURRENT_STATE){
    
}


