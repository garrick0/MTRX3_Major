/* 
 * File:   SecondaryInterfaceOutput.h
 * Author: W
 *
 * Created on 12 October 2016, 23:03
 */

#ifndef SECONDARYINTERFACEOUTPUT_H
#define	SECONDARYINTERFACEOUTPUT_H

void    PCWrite(char *Data);
void    PCLineClear(void);
void    SecondaryInterfaceOutput(struct UserinterfaceInput *ptrInput,int interface_mode,int state_variable,int menu_position);

#endif	/* SECONDARYINTERFACEOUTPUT_H */

