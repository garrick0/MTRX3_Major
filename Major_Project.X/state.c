/**
 * @file state.c
 * @author Monadil
 * @date 24/9/16
 * @brief  State control
 *
 * @remarks Initially testing states by turning LED on and off. 
 * 
 */

#include    <p18f452.h>
#include    "state.h"
#include    "define.h"
#include    "globalVars.h"

//! State control - check whether change state has been found
void stateControl(unsigned char CURRENT_STATE) {
  if (CURRENT_STATE == MANUAL){
      PORTB = ONELED; 
  }
  
  else if (CURRENT_STATE == AUTOMATIC){
      PORTB = TWOLED;
  }
  
  else if (CURRENT_STATE == FACTORY){
      PORTB = THREELED;
  }
  
  else if (CURRENT_STATE == LOST){
      PORTB = FOURLED;
  }
}
      

