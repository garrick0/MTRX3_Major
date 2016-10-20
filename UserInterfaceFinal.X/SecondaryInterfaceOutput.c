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
#include <stdio.h>
#include <p18f4520.h>
#include    <usart.h>
#include    <delays.h>


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


void initialiseComs(void);
void waitTransmit(void);
void PCROMWrite(rom char *Data);
void PCRAMWrite(char *Data);

void initialiseComs(void)
{
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 1;
    
    Delay10KTCYx(250);
    
    OpenUSART( USART_TX_INT_OFF  &
             USART_RX_INT_OFF  &
             USART_ASYNCH_MODE &
             USART_EIGHT_BIT   &
             USART_CONT_RX &
             USART_BRGH_HIGH, 64 );
}

void  PCROMWrite(rom char *Data)
{
	while(*Data != '\0'){

        while(TXSTAbits.TRMT != 1);
        
        putcUSART(*Data);
        
        Data++;
    }
}

void  PCRAMWrite(char *Data)
{
	while(*Data != '\0'){

        while(TXSTAbits.TRMT != 1);
        
        putcUSART(*Data);
        
        Data++;
    }
}



void    PCLineClear(void){
    PCROMWrite("\r                                          \r");
}

char str[80];

void    SecondaryInterfaceOutput(struct UserinterfaceInput *ptrInput,int interface_mode,int state_variable,int menu_position){

    //////////////////////////////////////////////////////////////
    if((ptrInput->current_state)==INITIALISE){
        //............................
        switch(state_variable){
            case ENTRY:
                PCROMWrite("Welcome to...\n\rPress A to enter commands and UP/DOWN arrows to scroll\n\rInitialising...\n\r");
                break;
            case NORMAL:
                PCROMWrite("USER_MANUAL_MODE\n\rPress A to enter command\n\r");
                break;
        }
    }

    if(interface_mode==SECONDARY_INTERFACE_MODE){

        //////////////////////////////////////////////////////////////
        if((ptrInput->current_state)==USER_MANUAL_MODE){
            //............................
            if(state_variable==ENTRY){
                PCROMWrite("USER_MANUAL_MODE\n\n\r0-SET_MOTORS_ON\n\r1-SET_MOTORS_OFF\n\r2-SET_SPEED_MAX\n\r3-SET_MODE_USER_AUTO\n\r4-SET_MODE_FACTORY\n\r");
                PCROMWrite("Use UP/DOWN arrows to scroll\n\rPress A to select\n\rPress B to exit\n\n\r");
            }
            //...............................
            if(state_variable==NORMAL){

                switch(menu_position){
                    case 0:
                        PCLineClear();
                        PCROMWrite("0-SET_MOTORS_ON");
                        break;
                    case 1:
                        PCLineClear();
                        PCROMWrite("1-SET_MOTORS_OFF");
                        break;
                    case 2:
                        PCLineClear();
                        PCROMWrite("2-SET_SPEED_MAX");
                        break;
                    case 3:
                        PCLineClear();
                        PCROMWrite("3-SET_MODE_USER_AUTO");
                        break;
                    case 4:
                        PCLineClear();
                        PCROMWrite("4-SET_MODE_FACTORY");
                        break;
                }

            }
            //..............................
            if(state_variable==PARAMETER){

                switch(menu_position){
                    case 0:
                        PCROMWrite("\nMOTORS_ON\n\r");
                        break;
                    case 1:
                        PCROMWrite("\nMOTORS_OFF\n\r");
                        break;

                    case 2:
                        //PCWrite("\nMAX SPEED=\n\r");           //////////////////change
                        PCLineClear();

                        sprintf(str,"MAX SPEED= %d\r",(ptrInput->max_robot_speed));
                        PCRAMWrite(str);
                        break;
                    case 4:
                    	PCLineClear();
                        PCROMWrite("Enter Passcode:\r");
                        break;
                }
            }

        }

        ////////////////////////////////////////////////////////
        if((ptrInput->current_state)==USER_AUTO_MODE){
            //............................
            if(state_variable==ENTRY){
                PCROMWrite("\nUSER_AUTO_MODE\n\r0-SET_FIND_PARROT\n\r1-SET_MODE_USER_MANUAL\n\r");
                PCROMWrite("Use UP/DOWN arrows to scroll\n\rPress A to select\n\rPress B to exit\n\n\r");
            }
            //...............................
            if(state_variable==NORMAL){
                switch(menu_position){
                    case 0:
                        PCLineClear();
                        PCROMWrite("0-SET_FIND_PARROT\r");
                        break;
                    case 1:
                        PCLineClear();
                        PCROMWrite("1-SET_MODE_USER_MANUAL\r");
                        break;
                }
            }
            if(state_variable==PARAMETER){
            	PCROMWrite("\nFinding Parrot\n\r");
            }
        }

        ////////////////////////////////////////////////////////
        if((ptrInput->current_state)==FACTORY_MODE){
            //............................
            if(state_variable==ENTRY){
                PCROMWrite("\nFACTORY_MODE\n\r0-SET_PID_GAINS\n\r1-SET_SPEED_MAX\n\r2-SET_YAW_RATE_MAX\n\r3-SET_IR_SAMPLES_PER_ESTIMATE\n\r4-SET_IR_SAMPLE_RATE\n\r5-SET_RF_SAMPLES_PER_ESTIMATE\n\r6-SET_MODE_USER_MANUAL\n\r");
                PCROMWrite("Use UP/DOWN arrows to scroll\n\rPress A to select\n\rPress B to exit\n\n\r");
            }
            //...............................
            if(state_variable==NORMAL){
                switch(menu_position){
                    case 0:
                        PCLineClear();
                        PCROMWrite("0-SET_PID_GAINS\r");
                        break;
                    case 1:
                        PCLineClear();
                        PCROMWrite("1-SET_SPEED_MAX\r");
                        break;
                    case 2:
                        PCLineClear();
                        PCROMWrite("2-SET_YAW_RATE_MAX\r");
                        break;
                    case 3:
                        PCLineClear();
                        PCROMWrite("3-SET_IR_SAMPLES_PER_ESTIMATE\r");
                        break;
                    case 4:
                        PCLineClear();
                        PCROMWrite("4-SET_IR_SAMPLE_RATE\r");
                        break;
                    case 5:
                        PCLineClear();
                        PCROMWrite("5-SET_RF_SAMPLES_PER_ESTIMATE\r");
                        break;
                    case 6:
                        PCLineClear();
                        PCROMWrite("6-SET_MODE_USER_MANUAL\r");
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

						sprintf(str,"MAX SPEED= %d\r",(ptrInput->max_robot_speed));
						PCRAMWrite(str);
						break;
                    case 2:
                    	PCLineClear();

						sprintf(str,"MAX YAW RATE= %d\r",(ptrInput->max_yaw_rate));
						PCRAMWrite(str);
                        break;
                    case 3:
                    	PCLineClear();

						sprintf(str,"IR SAMPLES PER ESTIMATE= %d\r",(ptrInput->ir_samples));
						PCRAMWrite(str);
                        break;
                    case 4:
                    	PCLineClear();

						sprintf(str,"IR SAMPLE RATE= %d\r",(ptrInput->ir_rate));
						PCRAMWrite(str);
                        break;
                    case 5:
                    	PCLineClear();

						sprintf(str,"RF SAMPLES PER ESTIMATE= %d\r",(ptrInput->rf_samples));
						PCRAMWrite(str);
                        break;
                }
            }
            if(state_variable==PID){
            	switch(menu_position){
            		case 0:
                    	PCLineClear();
						sprintf(str,"Proportional Gain= %d\r",(ptrInput->p_gain));
						PCRAMWrite(str);
                        break;
            		case 1:
                    	PCLineClear();
						sprintf(str,"Integral Gain= %d\r",(ptrInput->i_gain));
						PCRAMWrite(str);
                        break;
            		case 2:
                    	PCLineClear();
						sprintf(str,"Derivative Gain= %d\r",(ptrInput->d_gain));
						PCRAMWrite(str);
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












