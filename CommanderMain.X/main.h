/* 
 * File:   main.h
 * Author: sgle6040
 *
 * Created on 17 October 2016, 6:35 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif





/* -- Function Prototypes -- */
void high_interrupt(void);

// UI
void UISetup(void);
void receiveUI(int* UIVals);
void outputUI(char state,char* parrotPosition, char* IRVals);


// Comms
void commSetup(void);
void receiveComms(int* recVals);
void transmitComms(int* encoderVals);


//Nav
void navSetup(void);
void robotMove(char State,int* encoderVals,int* currentEncoder,int chirpStrength);



// misc





/* -- Global Variables -- */
#define MANUAL_MODE 0
#define AUTOMATIC_MODE 1
#define FACTORY_MODE 2



#endif	/* MAIN_H */

