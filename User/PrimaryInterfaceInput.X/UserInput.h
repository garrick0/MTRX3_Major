/* 
 * File:   UserInptSetup.h
 * Author: W
 *
 * Created on 11 October 2016, 13:28
 */

#ifndef USERINPUTSETUP_H
#define	USERINPUTSETUP_H

void UserInputSetup(void);
void CheckUserInput(void);
void WriteUserInputBuffer(const rom char *letter, int idx,char *UserInputBuffer);
void ReadUserInputBuffer(char *UserInputBuffer,int idx);
void ClearUserInputBuffer(void);
void ON_OFF(void);
void Emergency_Stop(void);

#endif	/* USERINPUTSETUP_H */

