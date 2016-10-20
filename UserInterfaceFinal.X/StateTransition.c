//UserinterfaceOutput returns requests for robot movements, change of state,
//and parameter changes.
//#pragma udata large_udata

struct UserinterfaceOutput {
	char userinput;			//movement command or NULL

	int current_state;		//request new state

	int max_robot_speed;	//request new values of all parameters
	int max_yaw_rate;		//note values can only be adjusted by integer increments
	int ir_samples;
	int ir_rate;
	int rf_samples;
	int p_gain;
	int i_gain;
	int d_gain;

	int motors;
	int find_parrot;
};

struct UserinterfaceInput {
	int current_state;		//return current state

	int initialising;		//0 when initialisation of new state not complete, 1 when complete
							//initialisation of each new state is required for a few seconds
							//at least for UI

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

	int parrot_moving;		//1 when moving/found, else 0
	int	parrot_found;
	int current_direction;	//angle between 0 and 360
	int ir_left;			//distance in cm
	int ir_right;
	int ir_front;

};
//#pragma udata
#include "SecondaryInterfaceOutput.h"
#include <stdlib.h>

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
//secondary output *flag *flag;

//void    PCWrite(char *Data);


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
//flag is set upon variable change or successful state change
void StateTransition(struct UserinterfaceInput *ptrInput,struct UserinterfaceOutput *ptrOutput,int *interface_mode,int *state_variable,int *menu_position,char *userinput,int *flag){
//struct UserinterfaceOutput *
	//struct UserinterfaceOutput *ptrOutput;
	//ptrOutput = (struct UserinterfaceOutput *) malloc(sizeof(struct UserinterfaceOutput));

	//initialise the output struct to the input values:
	(ptrOutput->current_state)=(ptrInput->current_state);
	(ptrOutput->max_robot_speed)=(ptrInput->max_robot_speed);
	(ptrOutput->max_yaw_rate)=(ptrInput->max_yaw_rate);
	(ptrOutput->ir_samples)=(ptrInput->ir_samples);
	(ptrOutput->ir_rate)=(ptrInput->ir_rate);
	(ptrOutput->rf_samples)=(ptrInput->rf_samples);
	(ptrOutput->p_gain)=(ptrInput->p_gain);
	(ptrOutput->i_gain)=(ptrInput->i_gain);
	(ptrOutput->d_gain)=(ptrInput->d_gain);

	if(*interface_mode==PRIMARY_INTERFACE_MODE){

        switch((ptrInput->current_state)){

            case INITIALISE:
                switch(*state_variable){
                    case ENTRY:
                        if((ptrInput->initialising)){
                            *state_variable=NORMAL;
                            *flag=1;
                        }
                        break;
                    case NORMAL:
                        if((ptrInput->initialising)){
                            (ptrOutput->current_state)=USER_MANUAL_MODE;     //request state change
                            *state_variable=ENTRY;
                        }
                        break;
                }
                break;

            case USER_MANUAL_MODE:
                switch(*state_variable){
                    case ENTRY:
                        if((ptrInput->initialising)){
                            *state_variable=NORMAL;

                        }
                        break;
                    case NORMAL:
                        if(*userinput==Abutton){
                            //(ptrOutput->current_state)=USER_MANUAL_MODE;
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
                        if((ptrInput->initialising)){
                            *state_variable=NORMAL;

                        }
                        break;
                    case NORMAL:
                        if(*userinput==Abutton){
                            //(ptrOutput->current_state)=USER_MANUAL_MODE;
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
                        if((ptrInput->initialising)){
                            *state_variable=NORMAL;

                        }
                        break;
                    case NORMAL:
                        if(*userinput==Abutton){
                            //(ptrOutput->current_state)=USER_MANUAL_MODE;
                            *interface_mode=SECONDARY_INTERFACE_MODE;
                            *state_variable=ENTRY;
                            *menu_position=0;

                        }
                        break;
                }
                break;

        }
        if(*userinput==Abutton || *userinput==BButton){ 	//if A or B button pressed
			(ptrOutput->userinput)='\0';
			if(*userinput==Abutton){
				*flag=1;
			}
		}else{
			(ptrOutput->userinput)=*userinput;
		}
    }

    else if(*interface_mode==SECONDARY_INTERFACE_MODE){

        switch((ptrInput->current_state)){

            case USER_MANUAL_MODE:
                switch(*state_variable){
                    case ENTRY:
                        if((ptrInput->initialising)){
                            *state_variable=NORMAL;

                        }
                        break;
                    case NORMAL:
                        if(*userinput==Abutton){
                            if((*menu_position)!=3){
                                *state_variable=PARAMETER;

                            }else if((*menu_position)==3){
                                (ptrOutput->current_state)=USER_AUTO_MODE;   //request
                                *state_variable=ENTRY;
                                *menu_position=0;
                                (ptrOutput->find_parrot)=0;
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
                            	(ptrOutput->motors)=1;           //request
                                //*menu_position=0;
                                *state_variable=NORMAL;

                                break;
                            case 1:
                            	(ptrOutput->motors)=0;         //request
                                //*menu_position=0;
                                *state_variable=NORMAL;

                                break;
                            case 2:
                                if(*userinput==LEFT){
                                    (ptrOutput->max_robot_speed)=(ptrInput->max_robot_speed)-1;

                                }
                                if(*userinput==RIGHT){
                                    (ptrOutput->max_robot_speed)=(ptrInput->max_robot_speed)+1;

                                }
                                if(*userinput==BButton){
                                    *state_variable=NORMAL;

                                }
                                break;
                            case 4:
//                                if(*userinput==UP){
//                                    (ptrOutput->current_state)=FACTORY_MODE;
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
                                        (ptrOutput->current_state)=FACTORY_MODE;
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
                        if((ptrInput->initialising)){
                            *state_variable=NORMAL;

                        }
                        break;
                    case NORMAL:
                        if(*userinput==Abutton){
                            switch(*menu_position){
                                case 0:
                                	*state_variable=PARAMETER;
                                    break;
                                case 1:
                                    (ptrOutput->current_state)=USER_MANUAL_MODE; //request
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
                    	(ptrOutput->find_parrot)=1;         //request
						//*menu_position=0;
						*state_variable=NORMAL;

						break;
                }
                break;

            case FACTORY_MODE:  ////////////////////////////
                switch(*state_variable){
                    case ENTRY:
                        if((ptrInput->initialising)){
                            *state_variable=NORMAL;

                        }
                        break;
                    case NORMAL:
                        if(*userinput==Abutton){
                            if((*menu_position)!=6){
                                *state_variable=PARAMETER;

                            }else if((*menu_position)==6){
                                (ptrOutput->current_state)=USER_MANUAL_MODE;   //request
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
                                    (ptrOutput->max_robot_speed)=(ptrInput->max_robot_speed)-1;       //request
                                }
                                if(*userinput==RIGHT){
                                    (ptrOutput->max_robot_speed)=(ptrInput->max_robot_speed)+1;
                                }
                                if(*userinput==BButton){
                                    *state_variable=NORMAL;
                                }
                                break;
                            case 2:
                                if(*userinput==LEFT){
                                    (ptrOutput->max_yaw_rate)=(ptrInput->max_yaw_rate)-1;       //request
                                }
                                if(*userinput==RIGHT){
                                    (ptrOutput->max_yaw_rate)=(ptrInput->max_yaw_rate)+1;
                                }
                                if(*userinput==BButton){
                                    *state_variable=NORMAL;
                                }
                                break;
                            case 3:
                                if(*userinput==LEFT){
                                    (ptrOutput->ir_samples)=(ptrInput->ir_samples)-1;       //request
                                }
                                if(*userinput==RIGHT){
                                    (ptrOutput->ir_samples)=(ptrInput->ir_samples)+1;
                                }
                                if(*userinput==BButton){
                                    *state_variable=NORMAL;
                                }
                                break;
                            case 4:
                                if(*userinput==LEFT){
                                    (ptrOutput->ir_rate)=(ptrInput->ir_rate)-1;       //request
                                }
                                if(*userinput==RIGHT){
                                    (ptrOutput->ir_rate)=(ptrInput->ir_rate)+1;
                                }
                                if(*userinput==BButton){
                                    *state_variable=NORMAL;
                                }
                                break;
                            case 5:
                                if(*userinput==LEFT){
                                    (ptrOutput->rf_samples)=(ptrInput->rf_samples)-1;       //request
                                }
                                if(*userinput==RIGHT){
                                    (ptrOutput->rf_samples)=(ptrInput->rf_samples)+1;
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
									(ptrOutput->p_gain)=(ptrInput->p_gain)-1;       //request
								}
								if(*userinput==RIGHT){
									(ptrOutput->p_gain)=(ptrInput->p_gain)+1;
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
                                    (ptrOutput->i_gain)=(ptrInput->i_gain)-1;       //request
                                }
                                if(*userinput==RIGHT){
                                    (ptrOutput->i_gain)=(ptrInput->i_gain)+1;
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
                                    (ptrOutput->d_gain)=(ptrInput->d_gain)-1;       //request
                                }
                                if(*userinput==RIGHT){
                                    (ptrOutput->d_gain)=(ptrInput->d_gain)+1;
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
        	(ptrOutput->userinput)=*userinput;
        }else{
        	(ptrOutput->userinput)='\0';
        	*flag=1;
        }
    }

    //return ptrOutput;
}
