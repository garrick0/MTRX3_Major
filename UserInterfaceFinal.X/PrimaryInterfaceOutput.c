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

char string[16];

void    PrimaryInterfaceOutput(struct UserinterfaceInput *ptrInput,int interface_mode,int state_variable,int menu_position){

    LEDOutput((ptrInput->parrot_found),(ptrInput->parrot_moving));
    //ServoOutput(CURRENT_DIRECTION);

    if((ptrInput->current_state)==INITIALISE){
            //............................
        switch(state_variable){
            case ENTRY:
                //LCDClear();
                LCDLine1ROMWrite("Welcome to...   ");
                LCDLine2ROMWrite("Initialising... ");
                break;
            case NORMAL:
                //LCDClear();
                LCDLine1ROMWrite("USER_MANUAL_MODE");
                LCDLine2ROMWrite("                ");
                break;
        }
    }
    if(interface_mode==SECONDARY_INTERFACE_MODE){

        //////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////
        if((ptrInput->current_state)==USER_MANUAL_MODE){
            //............................
            if(state_variable==ENTRY){
                //LCDClear();
                LCDLine1ROMWrite("USER_MANUAL_MODE");
                LCDLine2ROMWrite("                ");
            }
            //...............................
            if(state_variable==NORMAL){
                switch(menu_position){
                    case 0:
                        //LCDClear();
                        LCDLine1ROMWrite("0-SET_MOTORS_ON ");
                        LCDLine2ROMWrite("                ");
                        break;
                    case 1:
                        //LCDClear();
                        LCDLine1ROMWrite("1-SET_MOTORS_OFF");
                        LCDLine2ROMWrite("                ");
                        break;
                    case 2:
                        //LCDClear();
                        LCDLine1ROMWrite("2-SET_SPEED_MAX ");
                        LCDLine2ROMWrite("                ");
                        break;
                    case 3:
                        //LCDClear();
                        LCDLine1ROMWrite("3-SET_USER_AUTO ");
                        LCDLine2ROMWrite("                ");
                        break;
                    case 4:
                        //LCDClear();
                        LCDLine1ROMWrite("4-SET_FACTORY   ");
                        LCDLine2ROMWrite("                ");
                        break;
                }

            }
            //..............................
            if(state_variable==PARAMETER){
                switch(menu_position){
                    case 0:
                        //LCDClear();
                        LCDLine1ROMWrite("MOTORS_ON");				/////////////////////////////////////////////////////////
                        LCDLine2ROMWrite("                ");
                        break;
                    case 1:
                        //LCDClear();
                        LCDLine1ROMWrite("MOTORS_OFF");			/////////////////////////////////////////////////////////
                        LCDLine2ROMWrite("                ");
                        break;
                    case 2:
                        //LCDClear();

                        sprintf(string,"%d               ",(ptrInput->max_robot_speed));
                        LCDLine1ROMWrite("MAX SPEED=      ");
                        LCDLine2RAMWrite(string);
                        break;
                    case 4:
                        //LCDClear();
                        LCDLine1ROMWrite("Enter Passcode: ");
                        LCDLine2ROMWrite("                ");
                        break;
                }
            }

        }

        ////////////////////////////////////////////////////////
        if((ptrInput->current_state)==USER_AUTO_MODE){
            //............................
            if(state_variable==ENTRY){
                //LCDClear();
                LCDLine1ROMWrite("USER_AUTO_MODE  ");
                LCDLine2ROMWrite("                ");
            }
            //...............................
            if(state_variable==NORMAL){
                switch(menu_position){
                    case 0:
                        //LCDClear();
                        LCDLine1ROMWrite("0-SET_FINDPARROT");
                        LCDLine2ROMWrite("                ");
                        break;
                    case 1:
                        //LCDClear();
                        LCDLine1ROMWrite("1-SET_USERMANUAL");
                        LCDLine2ROMWrite("                ");
                        break;
                }
            }

        }

        ////////////////////////////////////////////////////////
        if((ptrInput->current_state)==FACTORY_MODE){
            //............................
            if(state_variable==ENTRY){
                //LCDClear();
                LCDLine1ROMWrite("FACTORY_MODE    ");
                LCDLine2ROMWrite("                ");
            }
            //...............................
            if(state_variable==NORMAL){
                switch(menu_position){
                    case 0:
                        //LCDClear();
                        LCDLine1ROMWrite("0-SET_PID_GAINS ");
                        LCDLine2ROMWrite("                ");
                        break;
                    case 1:
                        //LCDClear();
                        LCDLine1ROMWrite("1-SET_SPEED_MAX ");
                        LCDLine2ROMWrite("                ");
                        break;
                    case 2:
                        //LCDClear();
                        LCDLine1ROMWrite("2-SET_YAW_RATE  ");
                        LCDLine2ROMWrite("                ");
                        break;
                    case 3:
                        //LCDClear();
                        LCDLine1ROMWrite("3-SET_IR_SAMPLES");
                        LCDLine2ROMWrite("                ");
                        break;
                    case 4:
                        //LCDClear();
                        LCDLine1ROMWrite("4-SET_IR_RATE   ");
                        LCDLine2ROMWrite("                ");
                        break;
                    case 5:
                        //LCDClear();
                        LCDLine1ROMWrite("5-SET_RF_SAMPLES");
                        LCDLine2ROMWrite("                ");
                        break;
                    case 6:
                        //LCDClear();
                        LCDLine1ROMWrite("6-SET_MODEMANUAL");
                        LCDLine2ROMWrite("                ");
                        break;
                }
            }
            //..............................
            if(state_variable==PARAMETER){
                switch(menu_position){
                    case 0:
                        break;
                    case 1:
                        //LCDClear();

                        sprintf(string,"%d               ",(ptrInput->max_robot_speed));
                        LCDLine1ROMWrite("MAX SPEED=      ");
                        LCDLine2RAMWrite(string);
                        break;
                    case 2:
                        //LCDClear();

                        sprintf(string,"%d               ",(ptrInput->max_yaw_rate));
                        LCDLine1ROMWrite("MAX YAW RATE=   ");
                        LCDLine2RAMWrite(string);
                        break;
                    case 3:
                        //LCDClear();

                        sprintf(string,"%d               ",(ptrInput->ir_samples));
                        LCDLine1ROMWrite("IR SAMPLES=     ");
                        LCDLine2RAMWrite(string);
                        break;
                    case 4:
                        //LDClear();

                        sprintf(string,"%d               ",(ptrInput->ir_rate));
                        LCDLine1ROMWrite("IR SAMPLE RATE= ");
                        LCDLine2RAMWrite(string);
                        break;
                    case 5:
                        //LCDClear();

                        sprintf(string,"%d               ",(ptrInput->rf_samples));
                        LCDLine1ROMWrite("RF SAMPLES=     ");
                        LCDLine2RAMWrite(string);
                        break;
                }
            }
            if(state_variable==PID){
            	switch(menu_position){
            		case 0:
                        //LCDClear();
                        sprintf(string,"%d               ",(ptrInput->p_gain));
                        LCDLine1ROMWrite("P GAIN=         ");
                        LCDLine2RAMWrite(string);
                        break;
            		case 1:
                        LCDClear();
                        sprintf(string,"%d               ",(ptrInput->i_gain));
                        LCDLine1ROMWrite("I GAIN=         ");
                        LCDLine2RAMWrite(string);
                        break;
            		case 2:
                        LCDClear();
                        sprintf(string,"%d               ",(ptrInput->d_gain));
                        LCDLine1ROMWrite("D GAIN=         ");
                        LCDLine2RAMWrite(string);
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
                    //LCDClear();
                    LCDLine1ROMWrite("USER_MANUAL_MODE");
                    LCDLine2ROMWrite("                ");
                    break;
                case NORMAL:
                	if((ptrInput->full_scan)){
						//LCDClear();
						LCDLine1ROMWrite("Full Scan       ");
						LCDLine2ROMWrite("Scanning...     ");
					}else if((ptrInput->half_scan)){
						//LCDClear();
						LCDLine1ROMWrite("Half Scan       ");
						LCDLine2ROMWrite("Scanning...     ");
					}else{
                    //LCDClear();
                    sprintf(string,"L=%d cm R=%d cm ",(ptrInput->ir_left),(ptrInput->ir_right));
                    LCDLine1RAMWrite(string);
                    sprintf(string,"FRONT:%d cm     ",(ptrInput->ir_front));
                    LCDLine2RAMWrite(string);
					}
                    break;
            }
        }
        if((ptrInput->current_state)==USER_AUTO_MODE){
            //............................
            switch(state_variable){
                case ENTRY:
                    //LCDClear();
                    LCDLine1ROMWrite("USER_AUTO_MODE  ");
                    LCDLine2ROMWrite("                ");
                    break;
                case NORMAL:
                	if((ptrInput->full_scan)){
						//LCDClear();
						LCDLine1ROMWrite("Full Scan       ");
						LCDLine2ROMWrite("Scanning...     ");
					}else if((ptrInput->half_scan)){
						//LCDClear();
						LCDLine1ROMWrite("Half Scan       ");
						LCDLine2ROMWrite("Scanning...     ");
					}else{
                    //LCDClear();
                    LCDLine1ROMWrite("USER_AUTO_MODE  ");
                    LCDLine2ROMWrite("                ");
					}
                    break;
            }
        }
        if((ptrInput->current_state)==FACTORY_MODE){
            switch(state_variable){
                case ENTRY:
                    //LCDClear();
                    LCDLine1ROMWrite("FACTORY_MODE    ");
                    LCDLine2ROMWrite("                ");
                    break;
                case NORMAL:
                	if((ptrInput->full_scan)){
                		//LCDClear();
                		LCDLine1ROMWrite("Full Scan       ");
                		LCDLine2ROMWrite("Scanning...     ");
                	}else if((ptrInput->half_scan)){
                		//LCDClear();
                		LCDLine1ROMWrite("Half Scan       ");
                		LCDLine2ROMWrite("Scanning...     ");
                	}else{
                    //LCDClear();
                    sprintf(string,"L=%d cm R=%d cm ",(ptrInput->ir_left),(ptrInput->ir_right));
                    LCDLine1RAMWrite(string);
                    sprintf(string,"FRONT:%d cm     ",(ptrInput->ir_front));
                    LCDLine2RAMWrite(string);
                	}
                    break;
            }
        }
    }
}
