/* 
 * File:   StateTransition.h
 * Author: W
 *
 * Created on 15 October 2016, 12:17
 */

#ifndef STATETRANSITION_H
#define	STATETRANSITION_H

struct UserinterfaceOutput *StateTransition(struct UserinterfaceInput *ptrInput,int *interface_mode,int *state_variable,int *menu_position,char *userinput,int *flag);
void GetPasscode(char *userinput);


#endif	/* STATETRANSITION_H */

