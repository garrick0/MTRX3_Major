/* 
 * File:   UserInterface.h
 * Author: msye1207
 *
 * Created on 20 October 2016, 4:54 PM
 */

#ifndef USERINTERFACE_H
#define	USERINTERFACE_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif


//UserinterfaceOutput returns requests for robot movements, change of state,
//and parameter changes.
//#pragma udata large_udata

struct UserInterfaceInput {
    /*VALUES NEEDED TO OUTPUT TO MAIN*/
    char stateRequest;
    char commandInput;
    /////////////////////////////////////
    /*
    
	char userinput;			//movement command or NULL

	int current_state;		//request new state

	int max_robot_speed;	//request new values of all parameters
	int max_yaw_rate;		//note values can only be adjusted by integer increments
	int ir_samples;
	int ir_rate;
	int rf_samples;
	int p_gain;
	int i_gain;
	int d_gain;				//also need: motors=On/Off and find_parrot=on/off requests

	int motors;
	int find_parrot;*/
};

struct UserInterfaceOutput {
    
    /*VALUES THAT WILL BE INPUT BY MAIN*/
    
    char State;
    char parrotDirection;
    char parrotDistance;
    char IR1;
    char IR2;
    char IR3;
    char parrot_moving;
    char parrot_found;
    int instMag;
    char instDir;
    char instructionFlag;
    
    ////////////////////////////////
    
    /*
	int current_state;		//return current state

	int initialising;		//0 when initialisation of new state not complete, 1 when complete
							//initialisation of each new state is required for a few seconds
							//at least for UI

	int half_scan;			//1 when scanning, 0 when not scanning
	int full_scan;

	int max_robot_speed;	//return values of all parameters
	int max_yaw_rate;
	int ir_samples;
	int ir_rate;	int rf_samples;
	int p_gain;
	int i_gain;
	int d_gain;

	//int parrot_moving;		//1 when moving/found, else 0
	//int	parrot_found;
	int current_direction;	//angle between 0 and 360
	int ir_left;			//distance in cm
	int ir_right;
	int ir_front;
*/
};

#endif	/* USERINTERFACE_H */












