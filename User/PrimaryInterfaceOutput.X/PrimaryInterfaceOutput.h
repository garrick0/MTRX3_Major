/* 
 * File:   PrimaryInterfaceOutput.h
 * Author: W
 *
 * Created on 11 October 2016, 20:09
 */

#ifndef PRIMARYINTERFACEOUTPUT_H
#define	PRIMARYINTERFACEOUTPUT_H

LEDOutput(int PARROT_FOUND,int PARROT_MOVING);
InitialiseServo(void);
ServoDelayms(int Delay);
ServoDelay10us(int Delay);
ServoOutput(int CURRENT_DIRECTION);
PrimaryInterfaceOutput(int CURRENT_STATE,int INTERFACE_MODE,int PARROT_FOUND,int PARROT_MOVING,int CURRENT_DIRECTION);


#endif	/* PRIMARYINTERFACEOUTPUT_H */

