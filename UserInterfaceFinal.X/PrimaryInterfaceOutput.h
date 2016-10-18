/* 
 * File:   PrimaryInterfaceOutput.h
 * Author: W
 *
 * Created on 11 October 2016, 20:09
 */

#ifndef PRIMARYINTERFACEOUTPUT_H
#define	PRIMARYINTERFACEOUTPUT_H


int  LEDOutput(int PARROT_FOUND,int PARROT_MOVING);
void    PrimaryInterfaceOutput(struct UserinterfaceInput *ptrInput,int interface_mode,int state_variable,int menu_position);


#endif	/* PRIMARYINTERFACEOUTPUT_H */

