#include <stdio.h>
#include <stdlib.h>
#include <p18f4520.h>
#include    <usart.h>
#include    <delays.h>

#include "ConfigRegs_18F4520.h"
#include "xlcd.h"
#include "xlcddelays.h"
#include "LCDWrite.h"
#include "UserInput.h"
#include "PrimaryInterfaceOutput.h"
#include "SecondaryInterfaceOutput.h"
#include "StateTransition.h"

#define  EmergencyStop	PORTBbits.RB0
#define  ORInput        PORTBbits.RB1
#define  On_Off_Switch	PORTBbits.RB4

#define INITIALISE          0
#define USER_MANUAL_MODE 	1
#define USER_AUTO_MODE 		2
#define	FACTORY_MODE		3

#define	PRIMARY_INTERFACE_MODE	0
#define	SECONDARY_INTERFACE_MODE	1

#define ENTRY               0
#define NORMAL              1
#define PARAMETER           2

void low_interrupt( void );
void high_interrupt(void);
void lowPriorityIsr(void);
void highPriorityIsr(void);
void initialisation(void);

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
	int d_gain;				//also need: motors=On/Off and find_parrot=on/off requests

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

char    userinput;                  
                     //flag for printing to screen
char	UserInputBuffer[1];			//stores user inputs


struct UserinterfaceOutput Output;
struct UserinterfaceInput  Input;
struct UserinterfaceOutput *ptrOutput=&Output;
struct UserinterfaceInput *ptrInput=&Input;
    

int interface_mode=PRIMARY_INTERFACE_MODE;
int	state_variable=ENTRY;
int menu_position=0;
int     flag=0;  

const ram char hello[] = "Testing\r\n";
//unsigned char *stringtest = "hello";
//char test_str[] = "Test code";
//char *string2 = "Test";

#pragma code highPriorityInterruptAddress=0x0008
void high_interrupt(void){  
    _asm GOTO highPriorityIsr _endasm   
}
#pragma code

#pragma code lowPriorityInterruptAddress=0x0018
void low_interrupt( void ){
    _asm GOTO lowPriorityIsr _endasm       
}
#pragma code

void main( void ){
    UserInputSetup();
    LCDInitialise();
    
    initialiseComs();
    initialisation();
	//PCWrite("hello");
    //PCRAMWrite(hello);
    //TRISCbits.RC0=0;
    //PORTCbits.RC0=1;

    //initialise parameters
	ptrInput -> current_state = INITIALISE;
	ptrInput -> initialising = 0;
	ptrInput -> full_scan = 0;
	ptrInput -> half_scan = 0;
	ptrInput -> max_robot_speed = 10;
	ptrInput -> max_yaw_rate = 10;
	ptrInput -> ir_samples = 10;
	ptrInput -> ir_rate = 10;
	ptrInput -> rf_samples = 10;
	ptrInput -> p_gain = 1;
	ptrInput -> i_gain = 0;
	ptrInput -> d_gain = 0;
	ptrInput -> parrot_moving = 0;
	ptrInput -> parrot_found = 0;
	ptrInput -> current_direction = 10;
	ptrInput -> ir_left = 30;
	ptrInput -> ir_right = 20;
	ptrInput -> ir_front = 15;

    
	while(1){
		
		
            userinput=ReadUserInputBuffer(UserInputBuffer);
			StateTransition(ptrInput,ptrOutput,&interface_mode, &state_variable,&menu_position,&userinput,&flag);
			//code for testing:
			(ptrInput->current_state)=(ptrOutput->current_state);
			(ptrInput->max_robot_speed)=(ptrOutput->max_robot_speed);
			(ptrInput->max_yaw_rate)=(ptrOutput->max_yaw_rate);
			(ptrInput->ir_samples)=(ptrOutput->ir_samples);
			(ptrInput->ir_rate)=(ptrOutput->ir_rate);
			(ptrInput->rf_samples)=(ptrOutput->rf_samples);
			(ptrInput->p_gain)=(ptrOutput->p_gain);
			(ptrInput->i_gain)=(ptrOutput->i_gain);
			(ptrInput->d_gain)=(ptrOutput->d_gain);
			//printf("user input:%c",(ptrOutput->userinput));


			if(flag){
				SecondaryInterfaceOutput(ptrInput,interface_mode, state_variable,menu_position);
				flag=0;
			}
			PrimaryInterfaceOutput(ptrInput,interface_mode,state_variable,menu_position);
			
		}
}

#pragma interrupt lowPriorityIsr
void lowPriorityIsr(void){

	if(ORInput){				//check if user input triggered interrupt
        INTCON3bits.INT1IF = 0;	//clear PORTB1 interrupt flag
		CheckUserInput(UserInputBuffer);
        
	}else if(INTCONbits.TMR0IF){
        INTCONbits.TMR0IF=0;
        INTCONbits.TMR0IE =0;       //disable interrupt
        T0CONbits.TMR0ON =0;        //turn timer off
        (ptrInput->initialising)=1;
    }
    
}

#pragma interrupt highPriorityIsr
void highPriorityIsr(void){

	if(INTCONbits.RBIF){            //check if user input triggered interrupt
		INTCONbits.RBIF = 0;        //clear PORTB 4:7 interrupt flag
        ON_OFF();
	}
		
	if(EmergencyStop){              //check if user input triggered interrupt
        INTCONbits.INT0IF = 0;      //clear PORTB0 interrupt flag
		Emergency_Stop(UserInputBuffer);
	}
}

void initialisation(void){
    T0CON=0x96;
    INTCONbits.TMR0IE=1;
    INTCONbits.TMR0IF=0;
    INTCON2bits.TMR0IP=0; //set to low priority
}








