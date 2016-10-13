/* 
 * File:   SecondaryInterfaceOutput.h
 * Author: W
 *
 * Created on 12 October 2016, 23:03
 */

#ifndef SECONDARYINTERFACEOUTPUT_H
#define	SECONDARYINTERFACEOUTPU;T_H

void    PCWrite(char *Data);
void    PCLineClear(void);
void    SecondaryInterfaceOutput(int CURRENT_STATE,int INTERFACE_MODE,int STATE_VARIABLE,int MENU_POSITION,int PARROT_FOUND,char *MAX_ROBOT_SPEED,char *MAX_YAW_RATE,char *IR_SAMPLES,char *IR_RATE,char *RF_SAMPLES);

#endif	/* SECONDARYINTERFACEOUTPUT_H */

