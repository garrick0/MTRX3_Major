/* 
 * File:   StateTransition.h
 * Author: W
 *
 * Created on 15 October 2016, 12:17
 */

#ifndef STATETRANSITION_H
#define	STATETRANSITION_H

int initialising_state(int *delay,int *setup);
void StateTransition(struct UserInterfaceInput *UIInput,int *interface_mode,int *state_variable,int *menu_position,char *userinput,int *flag);
int GetPasscode(char *input);


#endif	/* STATETRANSITION_H */

