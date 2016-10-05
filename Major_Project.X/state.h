/**
 *  @file   state.h
 *  @brief  Header file for source file state.
 * 
 *  @remarks    Removed enum for state definitions to defines.  
 *
 */

#ifndef STATE_H_
#define STATE_H_

#define MANUAL      0
#define AUTOMATIC   1
#define FACTORY     2
#define LOST        3

#define ONELED      0xF1
#define TWOLED      0xF2
#define THREELED    0xF4
#define FOURLED     0xF8

int stateControl(unsigned char CURRENT_STATE);

#endif
