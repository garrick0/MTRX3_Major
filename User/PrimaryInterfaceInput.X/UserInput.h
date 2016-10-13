/* 
 * File:   UserInptSetup.h
 * Author: W
 *
 * Created on 11 October 2016, 13:28
 */

#ifndef USERINPUTSETUP_H
#define	USERINPUTSETUP_H

void UserInputSetup(void);
void CheckUserInput(char *UserInputBuffer);
void WriteUserInputBuffer(const rom char *letter,char *UserInputBuffer);
void ReadUserInputBuffer(char *UserInputBuffer);
void ClearUserInputBuffer(char *UserInputBuffer);
void ON_OFF(void);
void Emergency_Stop(char *UserInputBuffer);

#endif	/* USERINPUTSETUP_H */

