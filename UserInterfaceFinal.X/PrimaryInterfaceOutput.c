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


#include   "LCDWrite.h"
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

//#define BirdMoving      PORTCbits.RC0
//#define BirdFound       PORTCbits.RC1
//#define ServoControl    PORTCbits.RC2
//#define PiezoControl    PORTCbits.RC3

int  LEDOutput(int parrot_found,int parrot_moving){
    if(parrot_found){
       // int BirdFound=1;
    }else{
       // int BirdFound=0;
    }
    if(parrot_moving){
       // int BirdMoving=1;
    }else{
       // int BirdMoving=0;
    }
    return 0;
}

//assuming global variable CURRENT_DIRECTION is relative orientation
//servo requires compare interrupts to generate control PWM
/*void    InitialiseServo(void){

    INTCONbits.GIE_GIEH=0;
    INTCONbits.PEIE_GIEL=0;

    CCP1CON=0x0B;    //setup CCP1 for compare and special event

    T1CON=0x81;       //setup timer 1, 16 bit operation, 1:1 prescale

    PORTBbits.RB2=0;    //set as output
    TRISBbits.RB2=0;

    PIR1bits.CCP1IF	=0;	    //clear interrupt flag
    PIE1bits.CCP1IE=1;		//enable CCP1 interrupt
    IPR1bits.CCP1IP=0;		//set CCP1 interrupt to low priority

    T3CONbits.T3CCP2=0;     //timer1 is clock source for CCP1 module
    T3CONbits.T3CCP1=1;     //timer3 is clock source for CCP2 module

    INTCONbits.GIE_GIEH=1;  //enable interrupts
    INTCONbits.PEIE_GIEL=1;
}

void    ServoDelayms(int Delay){
    //clock cycles between toggles = delay(ms)*2.5MHz
    CCPR1L=	(2500*Delay)&0x00FF;	  //store lower byte
    CCPR1H= (2500*Delay)&0xFF00;    //store upper byte
}
void    ServoDelay10us(int Delay){
    //clock cycles between toggles = delay(10us)*2.5MHz
    CCPR1L=	(25*Delay)&0x00FF;	  //store lower byte
    CCPR1H= (25*Delay)&0xFF00;    //store upper byte
}

//check: delays of 1ms is 0deg, 1.5ms is 90deg, 2ms is 180deg
void    ServoOutput(int CURRENT_DIRECTION){
    if(ServoControl==0){
        ServoControl=1;
        ServoDelay10us(int(CURRENT_DIRECTION*0.38+80)); //set 20ms low time
    }else{
        ServoControl=0;
        ServoDelayms(int(CURRENT_DIRECTION*0.38+80));     //change
    }
}*/
//void LCDLine1Write(char *input){
//	printf("LCDLINE1:%s\n",input);
//}
//void LCDLine2Write(char *input){
//	printf("LCDLINE2:%s\n",input);
//}
//void LCDClear(void){
//
//}

char string[80];

void    PrimaryInterfaceOutput(struct UserinterfaceInput *ptrInput,int interface_mode,int state_variable,int menu_position){

    LEDOutput((ptrInput->parrot_found),(ptrInput->parrot_moving));
    //ServoOutput(CURRENT_DIRECTION);

    if((ptrInput->current_state)==INITIALISE){
            //............................
        switch(state_variable){
            case ENTRY:
                LCDClear();
                LCDLine1Write("Welcome to...");
                LCDLine2Write("Initialising..");
                break;
            case NORMAL:
                LCDClear();
                LCDLine1Write("USER_MANUAL_MODE");
                break;
        }
    }
    if(interface_mode==SECONDARY_INTERFACE_MODE){

        //////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////
        if((ptrInput->current_state)==USER_MANUAL_MODE){
            //............................
            if(state_variable==ENTRY){
                LCDClear();
                LCDLine1Write("USER_MANUAL_MODE");
            }
            //...............................
            if(state_variable==NORMAL){
                switch(menu_position){
                    case 0:
                        LCDClear();
                        LCDLine1Write("0-SET_MOTORS_ON");
                        break;
                    case 1:
                        LCDClear();
                        LCDLine1Write("1-SET_MOTORS_OFF");
                        break;
                    case 2:
                        LCDClear();
                        LCDLine1Write("2-SET_SPEED_MAX");
                        break;
                    case 3:
                        LCDClear();
                        LCDLine1Write("3-SET_MODE_USER_AUTO");
                        break;
                    case 4:
                        LCDClear();
                        LCDLine1Write("4-SET_MODE_FACTORY");
                        break;
                }

            }
            //..............................
            if(state_variable==PARAMETER){
                switch(menu_position){
                    case 0:
                        LCDClear();
                        LCDLine1Write("MOTORS_ON");				/////////////////////////////////////////////////////////
                        break;
                    case 1:
                        LCDClear();
                        LCDLine1Write("MOTORS_OFF");			/////////////////////////////////////////////////////////
                        break;
                    case 2:
                        LCDClear();

                        sprintf(string,"%d",(ptrInput->max_robot_speed));
                        LCDLine1Write("MAX SPEED=");
                        LCDLine2Write(string);
                        break;
                    case 4:
                        LCDClear();
                        LCDLine1Write("Enter Passcode:");
                        break;
                }
            }

        }

        ////////////////////////////////////////////////////////
        if((ptrInput->current_state)==USER_AUTO_MODE){
            //............................
            if(state_variable==ENTRY){
                LCDClear();
                LCDLine1Write("USER_AUTO_MODE");
            }
            //...............................
            if(state_variable==NORMAL){
                switch(menu_position){
                    case 0:
                        LCDClear();
                        LCDLine1Write("0-SET_FIND_PARROT");
                        break;
                    case 1:
                        LCDClear();
                        LCDLine1Write("1-SET_MODE_USER_MANUAL");
                        break;
                }
            }

        }

        ////////////////////////////////////////////////////////
        if((ptrInput->current_state)==FACTORY_MODE){
            //............................
            if(state_variable==ENTRY){
                LCDClear();
                LCDLine1Write("FACTORY_MODE");
            }
            //...............................
            if(state_variable==NORMAL){
                switch(menu_position){
                    case 0:
                        LCDClear();
                        LCDLine1Write("0-SET_PID_GAINS");
                        break;
                    case 1:
                        LCDClear();
                        LCDLine1Write("1-SET_SPEED_MAX");
                        break;
                    case 2:
                        LCDClear();
                        LCDLine1Write("2-SET_YAW_RATE_MAX");
                        break;
                    case 3:
                        LCDClear();
                        LCDLine1Write("3-SET_IR_SAMPLES_PER_ESTIMATE");
                        break;
                    case 4:
                        LCDClear();
                        LCDLine1Write("4-SET_IR_SAMPLE_RATE");
                        break;
                    case 5:
                        LCDClear();
                        LCDLine1Write("5-SET_RF_SAMPLES_PER_ESTIMATE");
                        break;
                    case 6:
                        LCDClear();
                        LCDLine1Write("6-SET_MODE_USER_MANUAL");
                        break;
                }
            }
            //..............................
            if(state_variable==PARAMETER){
                switch(menu_position){
                    case 0:
                        break;
                    case 1:
                        LCDClear();

                        sprintf(string,"%d",(ptrInput->max_robot_speed));
                        LCDLine1Write("MAX SPEED=");
                        LCDLine2Write(string);
                        break;
                    case 2:
                        LCDClear();

                        sprintf(string,"%d",(ptrInput->max_yaw_rate));
                        LCDLine1Write("MAX YAW RATE=");
                        LCDLine2Write(string);
                        break;
                    case 3:
                        LCDClear();

                        sprintf(string,"%d",(ptrInput->ir_samples));
                        LCDLine1Write("IR SAMPLES PER ESTIMATE=");
                        LCDLine2Write(string);
                        break;
                    case 4:
                        LCDClear();

                        sprintf(string,"%d",(ptrInput->ir_rate));
                        LCDLine1Write("IR SAMPLE RATE=");
                        LCDLine2Write(string);
                        break;
                    case 5:
                        LCDClear();

                        sprintf(string,"%d",(ptrInput->rf_samples));
                        LCDLine1Write("RF SAMPLES PER ESTIMATE=");
                        LCDLine2Write(string);
                        break;
                }
            }
            if(state_variable==PID){
            	switch(menu_position){
            		case 0:
                        LCDClear();
                        sprintf(string,"%d",(ptrInput->p_gain));
                        LCDLine1Write("PROPORTIONAL GAIN=");
                        LCDLine2Write(string);
                        break;
            		case 1:
                        LCDClear();
                        sprintf(string,"%d",(ptrInput->i_gain));
                        LCDLine1Write("INTEGRAL GAIN=");
                        LCDLine2Write(string);
                        break;
            		case 2:
                        LCDClear();
                        sprintf(string,"%d",(ptrInput->d_gain));
                        LCDLine1Write("DERIVATIVE GAIN=");
                        LCDLine2Write(string);
                        break;

            	}
            }
        }
    }
    else if(interface_mode==PRIMARY_INTERFACE_MODE){

        if((ptrInput->current_state)==USER_MANUAL_MODE){
            //............................
            switch(state_variable){
                case ENTRY:
                    LCDClear();
                    LCDLine1Write("USER_MANUAL_MODE");
                    break;
                case NORMAL:
                	if((ptrInput->full_scan)){
						LCDClear();
						LCDLine1Write("Full Scan");
						LCDLine2Write("Scanning...");
					}else if((ptrInput->half_scan)){
						LCDClear();
						LCDLine1Write("Half Scan");
						LCDLine2Write("Scanning...");
					}else{
                    LCDClear();
                    sprintf(string,"LEFT: %d cm RIGHT %d cm",(ptrInput->ir_left),(ptrInput->ir_right));
                    LCDLine1Write(string);
                    sprintf(string,"FRONT: %d cm",(ptrInput->ir_front));
                    LCDLine2Write(string);
					}
                    break;
            }
        }
        if((ptrInput->current_state)==USER_AUTO_MODE){
            //............................
            switch(state_variable){
                case ENTRY:
                    LCDClear();
                    LCDLine1Write("USER_AUTO_MODE");
                    break;
                case NORMAL:
                	if((ptrInput->full_scan)){
						LCDClear();
						LCDLine1Write("Full Scan");
						LCDLine2Write("Scanning...");
					}else if((ptrInput->half_scan)){
						LCDClear();
						LCDLine1Write("Half Scan");
						LCDLine2Write("Scanning...");
					}else{
                    LCDClear();
                    LCDLine1Write("USER_AUTO_MODE");
					}
                    break;
            }
        }
        if((ptrInput->current_state)==FACTORY_MODE){
            switch(state_variable){
                case ENTRY:
                    LCDClear();
                    LCDLine1Write("FACTORY_MODE");
                    break;
                case NORMAL:
                	if((ptrInput->full_scan)){
                		LCDClear();
                		LCDLine1Write("Full Scan");
                		LCDLine2Write("Scanning...");
                	}else if((ptrInput->half_scan)){
                		LCDClear();
                		LCDLine1Write("Half Scan");
                		LCDLine2Write("Scanning...");
                	}else{
                    LCDClear();
                    sprintf(string,"LEFT: %d cm RIGHT %d cm",(ptrInput->ir_left),(ptrInput->ir_right));
                    LCDLine1Write(string);
                    sprintf(string,"FRONT: %d cm",(ptrInput->ir_front));
                    LCDLine2Write(string);
                	}
                    break;
            }
        }
    }
}
