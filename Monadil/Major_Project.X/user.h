/**
 *  @file user.h
 *  @brief Header file for source file user.
 *
 */

#ifndef USER_H_
#define USER_H_

void getInputs(void);

int userOutput(int directionInput, int scan, int changeState, int secondayInterface);

void displayLCD(unsigned char CURRENT_STATE);

#endif
