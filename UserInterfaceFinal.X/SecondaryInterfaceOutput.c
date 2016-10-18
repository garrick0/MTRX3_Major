//UserinterfaceOutput returns requests for robot movements, change of state,
//and parameter changes.
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

#include <stdio.h>

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
//unsigned char   *(ptrInput->max_robot_speed);


void    PCWrite(char *Data){
    printf("%s",Data);
}
void    PCLineClear(void){
    printf("\r                                          \r");
}

char str[80];

void    SecondaryInterfaceOutput(struct UserinterfaceInput *ptrInput,int interface_mode,int state_variable,int menu_position){

    //////////////////////////////////////////////////////////////
    if((ptrInput->current_state)==INITIALISE){
        //............................
        switch(state_variable){
            case ENTRY:
                PCWrite("Welcome to...\nPress A to enter commands and UP/DOWN arrows to scroll\nInitialising...\n");
                break;
            case NORMAL:
                PCWrite("USER_MANUAL_MODE\nPress A to enter command\n");
                break;
        }
    }

    if(interface_mode==SECONDARY_INTERFACE_MODE){

        //////////////////////////////////////////////////////////////
        if((ptrInput->current_state)==USER_MANUAL_MODE){
            //............................
            if(state_variable==ENTRY){
                PCWrite("USER_MANUAL_MODE\n0-SET_MOTORS_ON\n1-SET_MOTORS_OFF\n2-SET_SPEED_MAX\n3-SET_MODE_USER_AUTO\n4-SET_MODE_FACTORY\n");
                PCWrite("Use UP/DOWN arrows to scroll\nPress A to select\nPress B to exit\n\n");
            }
            //...............................
            if(state_variable==NORMAL){

                switch(menu_position){
                    case 0:
                        PCLineClear();
                        PCWrite("0-SET_MOTORS_ON");
                        break;
                    case 1:
                        PCLineClear();
                        PCWrite("1-SET_MOTORS_OFF");
                        break;
                    case 2:
                        PCLineClear();
                        PCWrite("2-SET_SPEED_MAX");
                        break;
                    case 3:
                        PCLineClear();
                        PCWrite("3-SET_MODE_USER_AUTO");
                        break;
                    case 4:
                        PCLineClear();
                        PCWrite("4-SET_MODE_FACTORY");
                        break;
                }

            }
            //..............................
            if(state_variable==PARAMETER){

                switch(menu_position){
                    case 0:
                        PCWrite("\nMOTORS_ON\n");
                        break;
                    case 1:
                        PCWrite("\nMOTORS_OFF\n");
                        break;

                    case 2:
                        //PCWrite("\nMAX SPEED=\n");           //////////////////change
                        PCLineClear();

                        sprintf(str,"MAX SPEED= %d",(ptrInput->max_robot_speed));
                        PCWrite(str);
                        break;
                    case 4:
                    	PCLineClear();
                        PCWrite("Enter Passcode:");
                        break;
                }
            }

        }

        ////////////////////////////////////////////////////////
        if((ptrInput->current_state)==USER_AUTO_MODE){
            //............................
            if(state_variable==ENTRY){
                PCWrite("USER_AUTO_MODE\n0-SET_FIND_PARROT\n1-SET_MODE_USER_MANUAL\n");
                PCWrite("Use UP/DOWN arrows to scroll\nPress A to select\nPress B to exit\n\n");
            }
            //...............................
            if(state_variable==NORMAL){
                switch(menu_position){
                    case 0:
                        PCLineClear();
                        PCWrite("0-SET_FIND_PARROT");
                        break;
                    case 1:
                        PCLineClear();
                        PCWrite("1-SET_MODE_USER_MANUAL");
                        break;
                }
            }
            if(state_variable==PARAMETER){
            	PCWrite("\nFinding Parrot\n");
            }
        }

        ////////////////////////////////////////////////////////
        if((ptrInput->current_state)==FACTORY_MODE){
            //............................
            if(state_variable==ENTRY){
                PCWrite("\nFACTORY_MODE\n0-SET_PID_GAINS\n1-SET_SPEED_MAX\n2-SET_YAW_RATE_MAX\n3-SET_IR_SAMPLES_PER_ESTIMATE\n4-SET_IR_SAMPLE_RATE\n5-SET_RF_SAMPLES_PER_ESTIMATE\n6-SET_MODE_USER_MANUAL\n");
                PCWrite("Use UP/DOWN arrows to scroll\nPress A to select\nPress B to exit\n\n");
            }
            //...............................
            if(state_variable==NORMAL){
                switch(menu_position){
                    case 0:
                        PCLineClear();
                        PCWrite("0-SET_PID_GAINS");
                        break;
                    case 1:
                        PCLineClear();
                        PCWrite("1-SET_SPEED_MAX");
                        break;
                    case 2:
                        PCLineClear();
                        PCWrite("2-SET_YAW_RATE_MAX");
                        break;
                    case 3:
                        PCLineClear();
                        PCWrite("3-SET_IR_SAMPLES_PER_ESTIMATE");
                        break;
                    case 4:
                        PCLineClear();
                        PCWrite("4-SET_IR_SAMPLE_RATE");
                        break;
                    case 5:
                        PCLineClear();
                        PCWrite("5-SET_RF_SAMPLES_PER_ESTIMATE");
                        break;
                    case 6:
                        PCLineClear();
                        PCWrite("6-SET_MODE_USER_MANUAL");
                        break;
                }
            }
            //..............................
            if(state_variable==PARAMETER){
                switch(menu_position){
                    case 0:
                        break;
                    case 1:
                    	PCLineClear();

						sprintf(str,"MAX SPEED= %d",(ptrInput->max_robot_speed));
						PCWrite(str);
						break;
                    case 2:
                    	PCLineClear();

						sprintf(str,"MAX YAW RATE= %d",(ptrInput->max_yaw_rate));
						PCWrite(str);
                        break;
                    case 3:
                    	PCLineClear();

						sprintf(str,"IR SAMPLES PER ESTIMATE= %d",(ptrInput->ir_samples));
						PCWrite(str);
                        break;
                    case 4:
                    	PCLineClear();

						sprintf(str,"IR SAMPLE RATE= %d",(ptrInput->ir_rate));
						PCWrite(str);
                        break;
                    case 5:
                    	PCLineClear();

						sprintf(str,"RF SAMPLES PER ESTIMATE= %d",(ptrInput->rf_samples));
						PCWrite(str);
                        break;
                }
            }
            if(state_variable==PID){
            	switch(menu_position){
            		case 0:
                    	PCLineClear();
						sprintf(str,"Proportional Gain= %d",(ptrInput->p_gain));
						PCWrite(str);
                        break;
            		case 1:
                    	PCLineClear();
						sprintf(str,"Integral Gain= %d",(ptrInput->i_gain));
						PCWrite(str);
                        break;
            		case 2:
                    	PCLineClear();
						sprintf(str,"Derivative Gain= %d",(ptrInput->d_gain));
						PCWrite(str);
                        break;
            	}
            }
        }
    }
    else if(interface_mode==PRIMARY_INTERFACE_MODE){
        if((ptrInput->parrot_found)){
           // PCWrite("\n PARROT FOUND!!!!\n");
        }
    }
}












