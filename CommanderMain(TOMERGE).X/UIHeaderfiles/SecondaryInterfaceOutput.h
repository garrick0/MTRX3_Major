/* 
 * File:   SecondaryInterfaceOutput.h
 * Author: W
 *
 * Created on 12 October 2016, 23:03
 */

#ifndef SECONDARYINTERFACEOUTPUT_H
#define	SECONDARYINTERFACEOUTPUT_H

void    PCROMWrite(rom char *Data);
void    PCRAMWrite(char *Data);
void    PCLineClear(void);
void    initialiseComs(void);
void    SecondaryInterfaceOutput(struct UserInterfaceOutput *UIOutput,int interface_mode,int state_variable,int menu_position);
#endif	/* SECONDARYINTERFACEOUTPUT_H */