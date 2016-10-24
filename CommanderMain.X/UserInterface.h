/* 
 * File:   UserInterface.h
 * Author: W
 *
 * Created on 21 October 2016, 13:52
 */

#ifndef USERINTERFACE_H
#define	USERINTERFACE_H

#define  EmergencyStop	PORTBbits.RB0
#define  ORInput        PORTBbits.RB1
#define  On_Off_Switch	PORTBbits.RB4
#define INITIALISE 0

struct UserInterfaceInput {
    /*VALUES NEEDED TO OUTPUT TO MAIN*/
    char stateRequest;
    char commandInput;
 
	int max_robot_speed;	//request new values of all parameters
	int max_yaw_rate;		//note values can only be adjusted by integer increments
	int ir_samples;
	int ir_rate;
	int rf_samples;
	int p_gain;
	int i_gain;
	int d_gain;				//also need: motors=On/Off and find_parrot=on/off requests
	int motors;
	int find_parrot;
};
struct UserInterfaceOutput {
    
    /*VALUES THAT WILL BE INPUT BY MAIN*/
    
    char State;
    char parrotDirection;
    char parrotDistance;
    char ir_left;
    char ir_front;
    char ir_right;
    char parrot_moving;
    char parrot_found;
    int instMag;
    char instDir;
    char instructionFlag;

	int half_scan;			//1 when scanning, 0 when not scanning
	int full_scan;
	int max_robot_speed;	//return values of all parameters
	int max_yaw_rate;
	int ir_samples;
	int ir_rate;	
    int rf_samples;
	int p_gain;
	int i_gain;
	int d_gain;
	int current_direction;	//angle between 0 and 360
	

};

extern int UIdelay;

//setup functions
void UISetup(void);
char storeUI(char* UIBuffer);
void inputUI(char* UIbuffer,struct UserInterfaceInput* UIInput);
void outputUI(struct UserInterfaceOutput *UIOutput);

//LCD delay functions
void DelayFor18TCY(void);
void DelayPORXLCD(void);
void DelayXLCD(void);

//User input functions
void UserInputSetup(void);
void CheckUserInput(char *UserInputBuffer);
void CheckPCInput(char *UserInputBuffer);
void WriteUserInputBuffer(const rom char *letter,char *UserInputBuffer);
char ReadUserInputBuffer(char *UserInputBuffer);
void ClearUserInputBuffer(char *UserInputBuffer);
void ON_OFF(void);
void Emergency_Stop(char *UserInputBuffer);

//state transition functions
int initialising_state(int *setup);
void StateTransition(struct UserInterfaceInput *UIInput,int *interface_mode,int *state_variable,int *menu_position,char *userinput,int *flag);
int GetPasscode(char *input);

//secondary interface functions
void    PCROMWrite(rom char *Data);
void    PCRAMWrite(char *Data);
void    PCLineClear(void);
void    initialiseComs(void);
void    SecondaryInterfaceOutput(struct UserInterfaceOutput *UIOutput,int interface_mode,int state_variable,int menu_position);

//primary interface functions
void LEDSetup(void);
void  LEDOutput(int parrot_found,int parrot_moving);
void    PrimaryInterfaceOutput(struct UserInterfaceOutput *UIOutput,int interface_mode,int state_variable,int menu_position);

//LCD functions
void LCDInitialise(void);
void LCDLine1ROMWrite(char buff[]);
void LCDLine1RAMWrite(char *buff);
void LCDLine2ROMWrite(char buff[]);
void LCDLine2RAMWrite(char *buff);
void LCDClear(void);

//#include    "servo.h"

#endif	/* USERINTERFACE_H */