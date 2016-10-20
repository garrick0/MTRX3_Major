/*
 * @file    servo.h
 * @author  Monadil
 * @date    20/10/16
 * @brief   Header file for the servoTest
 * @todo    Implement middle position at the start - might need to use timer
 * 
 */

#ifndef SERVO_H
#define	SERVO_H

#define HIGH 1
#define LOW 0

unsigned char turnFLAG = 0; /*!< Flag used to know whether to go to HIGH time or LOW time */
// unsigned char initialFLAG = 0; /*!< Initialise to middle at the beginning */
unsigned char angle = 175; /*!< Test degree for servo movement*/

void servoSetup(void);
void servoTurn(void);
void initialiseCCP2(void);

//! Functions for degrees to servo movement
void degrees2pulse_HIGH(unsigned char degrees);
void degrees2pulse_LOW(unsigned char degrees);

//! Functions for HIGH time control
void move0_HIGH(void);
void move45_HIGH(void);
void move90_HIGH(void);
void move135_HIGH(void);
void move180_HIGH(void);

//! Functions for LOW time control
void move0_LOW(void);
void move45_LOW(void);
void move90_LOW(void);
void move135_LOW(void);
void move180_LOW(void);

#endif	/* SERVO_H */

