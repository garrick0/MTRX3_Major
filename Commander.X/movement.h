/**
 *  @file movement.h
 *  @brief Header file for source file movement.
 *
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

void movement(int location, int gains);
int rotation(int pidInput, int gains);
void encoderMovement(char *buffer);

#endif
