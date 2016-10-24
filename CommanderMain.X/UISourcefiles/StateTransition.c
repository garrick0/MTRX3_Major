#include "UserInterface.h"
#include <stdlib.h>
#include <p18f4520.h>

#define INITIALISE          0
#define USER_MANUAL_MODE 	1
#define USER_AUTO_MODE 		2
#define	FACTORY_MODE		3

#define	PRIMARY_INTERFACE_MODE	0
#define	SECONDARY_INTERFACE_MODE	1

#define ENTRY               0
#define NORMAL              1
#define PARAMETER           2
#define	PID					3

#define LEFT                'L'
#define RIGHT               'R'
#define UP                  'U'
#define DOWN                'D'
#define Abutton             'A'
#define BButton             'B'
#define HALFSCAN            'H'       
#define FULLSCAN            'F'


char passcode[]= "UU";
int i=0;
int success;
int GetPasscode(char *input){
	if(*input==passcode[i]){
		i++;
		if(i==(sizeof(passcode)-1)){
			return 2;		//if whole passcode correct, return 2
		}else{
			return 1;		//while typing passcode correct, return 1
		}
	}else{
		i=0;
		return 0;			//if passcode wrong, return 0
	}
}
int setup=0;
int initialising_state(int *setup){
    if(*setup==0){
        T0CON=0x96;             //set up delay of 1.5 seconds
        INTCONbits.TMR0IE=1;
        INTCONbits.TMR0IF=0;
        INTCON2bits.TMR0IP=0; //set to low priority
        *setup=1;
    }
    if(UIdelay){ 
        UIdelay=0;
        *setup=0;
        return 1;  
    }else{
        return 0;
    }
}

//flag is set upon variable change or successful state change
void StateTransition(struct UserInterfaceInput *UIInput,int *interface_mode,int *state_variable,int *menu_position,char *userinput,int *flag){
//struct UserinterfaceOutput *
	//struct UserinterfaceOutput *UIInput;
	//UIInput = (struct UserinterfaceOutput *) malloc(sizeof(struct UserinterfaceOutput));

	if(*interface_mode==PRIMARY_INTERFACE_MODE){

        switch((UIInput->stateRequest)){

            case INITIALISE:
                switch(*state_variable){
                    case ENTRY:
                        if((initialising_state(&setup))){
                            *state_variable=NORMAL;
                            *flag=1;
                        }
                        break;
                    case NORMAL:
                        if((initialising_state(&setup))){
                            (UIInput->stateRequest)=USER_MANUAL_MODE;     //request state change
                            *state_variable=ENTRY;
                            *flag=1;
                        }
                        break;
                }
                break;

            case USER_MANUAL_MODE:
                switch(*state_variable){
                    case ENTRY:
                        if((initialising_state(&setup))){
                            *state_variable=NORMAL;
                            *flag=1;
                        }
                        break;
                    case NORMAL:
                        if(*userinput==Abutton){
                            //(UIInput->stateRequest)=USER_MANUAL_MODE;
                            *interface_mode=SECONDARY_INTERFACE_MODE;
                            *state_variable=ENTRY;
                            *menu_position=0;

                        }
                        break;
                }
                break;

            case USER_AUTO_MODE:
                switch(*state_variable){
                    case ENTRY:
                        if((initialising_state(&setup))){
                            *state_variable=NORMAL;
                            *flag=1;

                        }
                        break;
                    case NORMAL:
                        if(*userinput==Abutton){
                            //(UIInput->stateRequest)=USER_MANUAL_MODE;
                            *interface_mode=SECONDARY_INTERFACE_MODE;
                            *state_variable=ENTRY;
                            *menu_position=0;

                        }
                        break;
                }
                break;

            case FACTORY_MODE:
                switch(*state_variable){
                    case ENTRY:
                        if((initialising_state(&setup))){
                            *state_variable=NORMAL;
                            *flag=1;
                        }
                        break;
                    case NORMAL:
                        if(*userinput==Abutton){
                            //(UIInput->stateRequest)=USER_MANUAL_MODE;
                            *interface_mode=SECONDARY_INTERFACE_MODE;
                            *state_variable=ENTRY;
                            *menu_position=0;

                        }
                        break;
                }
                break;

        }
        if(*userinput==Abutton || *userinput==BButton){ 	//if A or B button pressed
			(UIInput->commandInput)='\0';
			if(*userinput==Abutton){
				*flag=1;
			}
		}else{
			(UIInput->commandInput)=*userinput;
		}
    }

    else if(*interface_mode==SECONDARY_INTERFACE_MODE){

        switch((UIInput->stateRequest)){

            case USER_MANUAL_MODE:
                switch(*state_variable){
                    case ENTRY:
                        if((initialising_state(&setup))){
                            *state_variable=NORMAL;
                            *flag=1;
                        }
                        break;
                    case NORMAL:
                        if(*userinput==Abutton){
                            if((*menu_position)!=3){
                                *state_variable=PARAMETER;

                            }else if((*menu_position)==3){
                                (UIInput->stateRequest)=USER_AUTO_MODE;   //request
                                *state_variable=ENTRY;
                                *menu_position=0;
                                (UIInput->find_parrot)=0;
                            }

                        }
                        if(*userinput==BButton){
                            *interface_mode=PRIMARY_INTERFACE_MODE;
                            *state_variable=ENTRY;
                            *menu_position=0;

                        }
                        if(*userinput==UP){
                            if((*menu_position)>0){
                                *menu_position=*menu_position-1;

                            }
                        }
                        if(*userinput==DOWN){
                            if((*menu_position)<4){
                            	 *menu_position=*menu_position+1;

                            }
                        }
                        break;
                    case PARAMETER:
                        switch(*menu_position){
                            case 0:
                            	(UIInput->motors)=1;           //request
                                //*menu_position=0;
                                *state_variable=NORMAL;
                                *flag=1;
                                break;
                            case 1:
                            	(UIInput->motors)=0;         //request
                                //*menu_position=0;
                                *state_variable=NORMAL;
                                *flag=1;
                                break;
                            case 2:
                                if(*userinput==LEFT){
                                    (UIInput->max_robot_speed)=(UIInput->max_robot_speed)-1;

                                }
                                if(*userinput==RIGHT){
                                    (UIInput->max_robot_speed)=(UIInput->max_robot_speed)+1;

                                }
                                if(*userinput==BButton){
                                    *state_variable=NORMAL;

                                }
                                break;
                            case 4:
//                                if(*userinput==UP){
//                                    (UIInput->stateRequest)=FACTORY_MODE;
//                                    *state_variable=ENTRY;
//                                    *menu_position=0;
//                                }
//                                else if(*userinput!=UP){
//                                    *state_variable=NORMAL;
//                                    PCWrite("Wrong Passcode");
//
//                                }
                                if(*userinput){ // == 1
                                    success=GetPasscode(userinput);
                                    if(success==0){
                                        *state_variable=NORMAL;

                                        PCROMWrite("Wrong Passcode");
                                    }else if(success==1){
                                        //no action
                                    }else if(success==2){
                                        (UIInput->stateRequest)=FACTORY_MODE;
                                        *state_variable=ENTRY;
                                        *menu_position=0;
                                    }
                                }
                                break;

                        }
                        break;
                }
                break;

            case USER_AUTO_MODE:
                switch(*state_variable){
                    case ENTRY:
                        if((initialising_state(&setup))){
                            *state_variable=NORMAL;
                            *flag=1;
                        }
                        break;
                    case NORMAL:
                        if(*userinput==Abutton){
                            switch(*menu_position){
                                case 0:
                                	*state_variable=PARAMETER;
                                    break;
                                case 1:
                                    (UIInput->stateRequest)=USER_MANUAL_MODE; //request
                                    *menu_position=0;
                                    *state_variable=ENTRY;
                                    break;
                            }
                        }
                        if(*userinput==BButton){
                            *interface_mode=PRIMARY_INTERFACE_MODE;
                            *state_variable=ENTRY;
                            *menu_position=0;

                        }
                        if(*userinput==UP){
                            if((*menu_position)>0){
                            	*menu_position=*menu_position-1;

                            }
                        }
                        if(*userinput==DOWN){
                            if((*menu_position)<1){
                            	*menu_position=*menu_position+1;

                            }
                        }
                        break;
                    case PARAMETER:
                    	(UIInput->find_parrot)=1;         //request
						//*menu_position=0;
						*state_variable=NORMAL;

						break;
                }
                break;

            case FACTORY_MODE:  ////////////////////////////
                switch(*state_variable){
                    case ENTRY:
                        if((initialising_state(&setup))){
                            *state_variable=NORMAL;
                            *flag=1;
                        }
                        break;
                    case NORMAL:
                        if(*userinput==Abutton){
                            if((*menu_position)!=6){
                                *state_variable=PARAMETER;

                            }else if((*menu_position)==6){
                                (UIInput->stateRequest)=USER_MANUAL_MODE;   //request
                                *state_variable=ENTRY;
                                *menu_position=0;
                            }
                        }
                        if(*userinput==BButton){
                            *interface_mode=PRIMARY_INTERFACE_MODE;
                            *state_variable=ENTRY;
                            *menu_position=0;
                        }
                        if(*userinput==UP){
                            if((*menu_position)>0){
                            	 *menu_position=*menu_position-1;
                            }
                        }
                        if(*userinput==DOWN){
                            if((*menu_position)<6){
                            	 *menu_position=*menu_position+1;
                            }
                        }
                        break;
                    case PARAMETER:
                        switch(*menu_position){
                            case 0:
								*state_variable=PID;
                                break;
                            case 1:
                                if(*userinput==LEFT){
                                    (UIInput->max_robot_speed)=(UIInput->max_robot_speed)-1;       //request
                                }
                                if(*userinput==RIGHT){
                                    (UIInput->max_robot_speed)=(UIInput->max_robot_speed)+1;
                                }
                                if(*userinput==BButton){
                                    *state_variable=NORMAL;
                                }
                                break;
                            case 2:
                                if(*userinput==LEFT){
                                    (UIInput->max_yaw_rate)=(UIInput->max_yaw_rate)-1;       //request
                                }
                                if(*userinput==RIGHT){
                                    (UIInput->max_yaw_rate)=(UIInput->max_yaw_rate)+1;
                                }
                                if(*userinput==BButton){
                                    *state_variable=NORMAL;
                                }
                                break;
                            case 3:
                                if(*userinput==LEFT){
                                    (UIInput->ir_samples)=(UIInput->ir_samples)-1;       //request
                                }
                                if(*userinput==RIGHT){
                                    (UIInput->ir_samples)=(UIInput->ir_samples)+1;
                                }
                                if(*userinput==BButton){
                                    *state_variable=NORMAL;
                                }
                                break;
                            case 4:
                                if(*userinput==LEFT){
                                    (UIInput->ir_rate)=(UIInput->ir_rate)-1;       //request
                                }
                                if(*userinput==RIGHT){
                                    (UIInput->ir_rate)=(UIInput->ir_rate)+1;
                                }
                                if(*userinput==BButton){
                                    *state_variable=NORMAL;
                                }
                                break;
                            case 5:
                                if(*userinput==LEFT){
                                    (UIInput->rf_samples)=(UIInput->rf_samples)-1;       //request
                                }
                                if(*userinput==RIGHT){
                                    (UIInput->rf_samples)=(UIInput->rf_samples)+1;
                                }
                                if(*userinput==BButton){
                                    *state_variable=NORMAL;
                                }
                                break;

                        }
                        break;
					case PID:
						switch(*menu_position){
							case 0:
								if(*userinput==LEFT){
									(UIInput->p_gain)=(UIInput->p_gain)-1;       //request
								}
								if(*userinput==RIGHT){
									(UIInput->p_gain)=(UIInput->p_gain)+1;
								}
								if(*userinput==BButton){
									*state_variable=NORMAL;
									*menu_position=0;
								}
								if(*userinput==UP){
									if((*menu_position)>0){
										 *menu_position=*menu_position-1;
									}
								}
								if(*userinput==DOWN){
									if((*menu_position)<2){
										*menu_position=*menu_position+1;
									}
								}
								break;
							case 1:
                                if(*userinput==LEFT){
                                    (UIInput->i_gain)=(UIInput->i_gain)-1;       //request
                                }
                                if(*userinput==RIGHT){
                                    (UIInput->i_gain)=(UIInput->i_gain)+1;
                                }
								if(*userinput==BButton){
									*state_variable=NORMAL;
									*menu_position=0;
								}
								if(*userinput==UP){
									if((*menu_position)>0){
										 *menu_position=*menu_position-1;
									}
								}
								if(*userinput==DOWN){
									if((*menu_position)<2){
										*menu_position=*menu_position+1;
									}
								}
                                break;
							case 2:
                                if(*userinput==LEFT){
                                    (UIInput->d_gain)=(UIInput->d_gain)-1;       //request
                                }
                                if(*userinput==RIGHT){
                                    (UIInput->d_gain)=(UIInput->d_gain)+1;
                                }
								if(*userinput==BButton){
									*state_variable=NORMAL;
									*menu_position=0;
								}
								if(*userinput==UP){
									if((*menu_position)>0){
										 *menu_position=*menu_position-1;
									}
								}
								if(*userinput==DOWN){
									if((*menu_position)<2){
										*menu_position=*menu_position+1;
									}
                                }
                                break;
						}
						break;



                }
                break;

        }
        if(*userinput==FULLSCAN || *userinput==HALFSCAN){ 	//if full scan or half scan button pressed
        	(UIInput->commandInput)=*userinput;
        }else{
        	(UIInput->commandInput)='\0';
            if(*userinput!='\0'){
                *flag=1;
            }
        }
    }

    //return UIInput;
}
