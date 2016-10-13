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
unsigned char stateControl(unsigned char CURRENT_STATE) {
  if (CURRENT_STATE == MANUAL){
      PORTB = ONELED; 
      return CURRENT_STATE;
  }
  
  else if (CURRENT_STATE == AUTOMATIC){
      PORTB = TWOLED;
      return CURRENT_STATE;
  }
  
  else if (CURRENT_STATE == FACTORY){
      PORTB = THREELED;
      return CURRENT_STATE;
  }
  
  else if (CURRENT_STATE == LOST){
      PORTB = FOURLED;
      return CURRENT_STATE;
  }
}
      

