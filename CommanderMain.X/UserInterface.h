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
#define HIGH 1
#define LOW 0

struct UserInterfaceInput {
    /*VALUES NEEDED TO OUTPUT TO MAIN*/
    char stateRequest;
    char commandInput;
 
	char max_robot_speed;	//request new values of all parameters
	char max_yaw_rate;		//note values can only be adjusted by integer increments
	char ir_samples;
	char ir_rate;
	char rf_samples;
	char p_gain;
	char i_gain;
	char d_gain;				//also need: motors=On/Off and find_parrot=on/off requests
	char motors;
	char find_parrot;
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
    char instMag;
    char instDir;
    char instructionFlag;

	char half_scan;			//1 when scanning, 0 when not scanning
	char full_scan;
	char max_robot_speed;	//return values of all parameters
	char max_yaw_rate;
	char ir_samples;
	char ir_rate;	
    char rf_samples;
	char p_gain;
	char i_gain;
	char d_gain;
	
	

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
void  LEDOutput(int parrot_found,int parrot_moving,char instructionFlag);
void    PrimaryInterfaceOutput(struct UserInterfaceOutput *UIOutput,int interface_mode,int state_variable,int menu_position);

//LCD functions
void LCDInitialise(void);
void LCDLine1ROMWrite(char buff[]);
void LCDLine1RAMWrite(char *buff);
void LCDLine2ROMWrite(char buff[]);
void LCDLine2RAMWrite(char *buff);
void LCDClear(void);

 /*!< Flag used to know whether to go to HIGH time or LOW time */
// unsigned char initialFLAG = 0; /*!< Initialise to middle at the beginning */

void servoToggle(void);
void servoSetup(void);
void servoTurn(void);
void initialiseCCP2(void);

//! Functions for degrees to servo movement
void degrees2pulse_HIGH(int degrees);
void degrees2pulse_LOW(int degrees);

//! Functions for HIGH time control
void move0_HIGH(void);
void move45_HIGH(void);
void move68_HIGH(void);
void move90_HIGH(void);
void move135_HIGH(void);
void move180_HIGH(void);

//! Functions for LOW time control
void move0_LOW(void);
void move45_LOW(void);
void move68_LOW(void);
void move90_LOW(void);
void move135_LOW(void);
void move180_LOW(void);

void servoOutput(int degrees);

#endif	/* USERINTERFACE_H */