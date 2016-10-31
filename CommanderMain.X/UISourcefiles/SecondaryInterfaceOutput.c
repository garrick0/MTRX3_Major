/**
 * @file SecondaryInterfaceOutput.c
 * @date October 2016
 * @brief Output to PC screen 
 * 
 * Writes messages to PC screen based on current state of UI module
 * 
 * @author Wilhelm Marais
 *
 * 
 */
#include <stdio.h>
#include <p18f4520.h>
#include    <usart.h>
#include    <delays.h>
#include "UserInterface.h"

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
//unsigned char   *(UIOutput->max_robot_speed);


void initialiseComs(void);
void waitTransmit(void);
void PCROMWrite(rom char *Data);
void PCRAMWrite(char *Data);
/** Initialise PC read and write. Initialise USART module for writing
 * to PC screen and to generate an interrupt on user input
 * to PC screen.
 */
void initialiseComs(void)
{
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 1;
    
    Delay10KTCYx(250);
    
    OpenUSART( USART_TX_INT_OFF  &
             USART_RX_INT_ON  &
             USART_ASYNCH_MODE &
             USART_EIGHT_BIT   &
             USART_CONT_RX &
             USART_BRGH_HIGH, 64 );
    IPR1bits.RCIP=0;    //set receive interrupts to low priority
}
/** PC write functions. Functions to write to 
 * PC screen from ROM or RAM.
 */
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

/** 
 * A string array.
 * Used for storing parameter values for printing
 * using sprintf function.
 */
char str[80];

/** Outputs to secondary interface. Based on current state
 * of the UI module, outputs to PC screen.
 */
void    SecondaryInterfaceOutput(struct UserInterfaceOutput *UIOutput,int interface_mode,int state_variable,int menu_position){

    //////////////////////////////////////////////////////////////
    if((UIOutput->State)==INITIALISE){
        //............................
        switch(state_variable){
            case ENTRY:
                PCROMWrite("\fWelcome to the Harambe Soul Seeker\n\rPress A/ENTER to enter commands and UP/DOWN arrows to scroll\n\rInitialising...\n\r");
                break;
            case NORMAL:
                PCROMWrite("Initialising...\n\r");
                break;
        }
    }

    if(interface_mode==SECONDARY_INTERFACE_MODE){

        //////////////////////////////////////////////////////////////
        if((UIOutput->State)==USER_MANUAL_MODE){
            //............................
            if(state_variable==ENTRY){
                PCROMWrite("\fUSER_MANUAL_MODE\n\n\r0-SET_MOTORS_ON\n\r1-SET_MOTORS_OFF\n\r2-SET_SPEED_MAX\n\r3-SET_MODE_USER_AUTO\n\r4-SET_MODE_FACTORY\n\r");
                PCROMWrite("Use UP/DOWN arrows to scroll\n\rPress A/ENTER to select\n\rPress B/BACKSPACE to exit\n\n\rPlease Wait\n\r");
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
                        PCROMWrite("\n\rMOTORS_ON\n\r");
                        break;
                    case 1:
                        PCROMWrite("\n\rMOTORS_OFF\n\r");
                        break;

                    case 2:
                        //PCWrite("\nMAX SPEED=\n\r");           //////////////////change
                        PCLineClear();

                        sprintf(str,"MAX SPEED= %d\r",(UIOutput->max_robot_speed));
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
        if((UIOutput->State)==USER_AUTO_MODE){
            //............................
            if(state_variable==ENTRY){
                PCROMWrite("\fUSER_AUTO_MODE\n\n\r0-SET_FIND_PARROT\n\r1-SET_MODE_USER_MANUAL\n\r");
                PCROMWrite("Use UP/DOWN arrows to scroll\n\rPress A/ENTER to select\n\rPress B/BACKSPACE to exit\n\n\rPlease Wait\n\r");
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
        if((UIOutput->State)==FACTORY_MODE){
            //............................
            if(state_variable==ENTRY){
                PCROMWrite("\fFACTORY_MODE\n\n\r0-SET_PID_GAINS\n\r1-SET_SPEED_MAX\n\r2-SET_YAW_RATE_MAX\n\r3-SET_IR_SAMPLES_PER_ESTIMATE\n\r4-SET_IR_SAMPLE_RATE\n\r5-SET_RF_SAMPLES_PER_ESTIMATE\n\r6-SET_MODE_USER_MANUAL\n\r");
                PCROMWrite("Use UP/DOWN arrows to scroll\n\rPress A/ENTER to select\n\rPress B/BACKSPACE to exit\n\n\rPlease Wait\n\r");
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

						sprintf(str,"MAX SPEED= %d\r",(UIOutput->max_robot_speed));
						PCRAMWrite(str);
						break;
                    case 2:
                    	PCLineClear();

						sprintf(str,"MAX YAW RATE= %d\r",(UIOutput->max_yaw_rate));
						PCRAMWrite(str);
                        break;
                    case 3:
                    	PCLineClear();

						sprintf(str,"IR SAMPLES PER ESTIMATE= %d\r",(UIOutput->ir_samples));
						PCRAMWrite(str);
                        break;
                    case 4:
                    	PCLineClear();

						sprintf(str,"IR SAMPLE RATE= %d\r",(UIOutput->ir_rate));
						PCRAMWrite(str);
                        break;
                    case 5:
                    	PCLineClear();

						sprintf(str,"RF SAMPLES PER ESTIMATE= %d\r",(UIOutput->rf_samples));
						PCRAMWrite(str);
                        break;
                }
            }
            if(state_variable==PID){
            	switch(menu_position){
            		case 0:
                    	PCLineClear();
						sprintf(str,"Proportional Gain= %d\r",(UIOutput->p_gain));
						PCRAMWrite(str);
                        break;
            		case 1:
                    	PCLineClear();
						sprintf(str,"Integral Gain= %d\r",(UIOutput->i_gain));
						PCRAMWrite(str);
                        break;
            		case 2:
                    	PCLineClear();
						sprintf(str,"Derivative Gain= %d\r",(UIOutput->d_gain));
						PCRAMWrite(str);
                        break;
            	}
            }
        }
    }
    else if(interface_mode==PRIMARY_INTERFACE_MODE){
        if((UIOutput->parrot_found)){
           // PCWrite("\n PARROT FOUND!!!!\n");
        }
        switch(UIOutput->State){
            case USER_MANUAL_MODE:
                if(state_variable==ENTRY){
                    PCROMWrite("\fUSER_MANUAL_MODE\n\r");
                    //PCROMWrite("\n\rPlease wait\n\r");
                }else if(state_variable==NORMAL){
                    //PCROMWrite("\fUSER_MANUAL_MODE");
                    //PCROMWrite("\n\rPress A/ENTER to enter command\n\rUse Dpad to control mobile robot\n\r");
                    //PCLineClear();
                    sprintf(str,"RSSI= %d\r",(UIOutput->parrotDistance));
                    PCRAMWrite(str);
                    //*flag=1;
                }
                break;
            case USER_AUTO_MODE:
                if(state_variable==ENTRY){
                    PCROMWrite("\fUSER_AUTO_MODE");
                    PCROMWrite("\n\rPlease wait\n\r");
                }else if(state_variable==NORMAL){
                    PCROMWrite("\fUSER_AUTO_MODE");
                    PCROMWrite("\n\rPress A/ENTER to enter command\n\r");
                }
                break;
            case FACTORY_MODE:
                if(state_variable==ENTRY){
                    PCROMWrite("\fFACTORY_MODE");
                    PCROMWrite("\n\rPlease wait\n\r");
                }else if(state_variable==NORMAL){
                    PCROMWrite("\fFACTORY_MODE");
                    PCROMWrite("\n\rPress A/ENTER to enter command\n\rUse Dpad to control mobile robot");
                }
                break;
        }
        
    }
        
}
