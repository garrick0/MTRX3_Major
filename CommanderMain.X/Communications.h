/* 
 * File:   Communications.h
 * Author: msye1207
 *
 * Created on 20 October 2016, 5:50 PM
 */

#ifndef COMMUNICATIONS_H
#define	COMMUNICATIONS_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif
struct communicationsInput {
    
    /*VALUES THAT WILL BE INPUT BY MAIN*/
    
    char IR1;
    char IR2;
    char IR3;
    char chirpStrength;
    char instructionFlag;
    char max_robot_speed;	//return values of all parameters
	char max_yaw_rate;
	char ir_samples;
	char ir_rate;	
    char rf_samples;
	char p_gain;
	char i_gain;
	char d_gain;


};


struct communicationsOutput {
    
    int instMag;
    char instDir;
    
    
};
#endif	/* COMMUNICATIONS_H */

