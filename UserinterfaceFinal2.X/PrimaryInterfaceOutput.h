/* 
 * File:   PrimaryInterfaceOutput.h
 * Author: W
 *
 * Created on 11 October 2016, 20:09
 */

#ifndef PRIMARYINTERFACEOUTPUT_H
#define	PRIMARYINTERFACEOUTPUT_H

void LEDSetup(void);
void  LEDOutput(int parrot_found,int parrot_moving)
void    PrimaryInterfaceOutput(struct UserInterfaceOutput *UIOutput,int interface_mode,int state_variable,int menu_position);

#endif	/* PRIMARYINTERFACEOUTPUT_H */

