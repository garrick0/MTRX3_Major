#include <stdio.h>
#include <stdlib.h>
#include <p18f4520.h>
#include    <usart.h>
#include    <delays.h>

#include "ConfigRegs_18F4520.h"
#include "xlcd.h"
#include "UserInterface.h"

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


char	UIbuffer[1];			//stores user inputs
int UIdelay=0;
//USERINTERFACE
    
    //Input and output structs
    
    //Holds values input by the user
    struct UserInterfaceInput UIInput;
    struct UserInterfaceInput *ptrUIInput=&UIInput;
    
    //Holds values output to the user
    struct UserInterfaceOutput UIOutput;
    struct UserInterfaceOutput *ptrUIOutput=&UIOutput;
    
   
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
    UISetup();
    //code for testing
    (ptrUIInput->State)=INITIALISE;
    (ptrUIInput->max_robot_speed)=10;	//request new values of all parameters
    (ptrUIInput->max_yaw_rate)=10;		//note values can only be adjusted by integer increments
    (ptrUIInput->ir_samples)=10;
    (ptrUIInput->ir_rate)=10;
    (ptrUIInput->rf_samples)=10;
    (ptrUIInput->p_gain)=10;
    (ptrUIInput->i_gain)=10;
    (ptrUIInput->d_gain)=10;			//also need: motors=On/Off and find_parrot=on/off requests
    (ptrUIInput->motors)=0;
    (ptrUIInput->find_parrot)=0;
    
    (ptrUIOutput->parrotDirection)=0;;
    (ptrUIOutput->parrotDistance)=10;;
    (ptrUIOutput->ir_left)=30;;
    (ptrUIOutput->ir_front)=20;
    (ptrUIOutput->ir_right)=10;
    (ptrUIOutput->parrot_moving)=0;
    (ptrUIOutput->parrot_found)=0;
    (ptrUIOutput->instMag)=0;
    (ptrUIOutput->instDir)=0;
    (ptrUIOutput->instructionFlag)=0;
    (ptrUIOutput->half_scan)=0;			//1 when scanning, 0 when not scanning
	(ptrUIOutput->full_scan)=0;
	(ptrUIOutput->current_direction)=0;	//angle between 0 and 360
    //end test code
	while(1){
        inputUI(UIbuffer,ptrUIInput);
        //test code
        (ptrUIOutput->State)=(ptrUIInput->State);
        (ptrUIOutput->max_robot_speed)=(ptrUIInput->max_robot_speed);	//return values of all parameters
        (ptrUIOutput->max_yaw_rate)=(ptrUIInput->max_yaw_rate);
        (ptrUIOutput->ir_samples)=(ptrUIInput->ir_samples);
        (ptrUIOutput->ir_rate)=(ptrUIInput->ir_rate);
        (ptrUIOutput->p_gain)=(ptrUIInput->p_gain);
        (ptrUIOutput->i_gain)=(ptrUIInput->i_gain);
        (ptrUIOutput->d_gain)=(ptrUIInput->d_gain);
        (ptrUIOutput->rf_samples)=(ptrUIInput->rf_samples);
        //end test code
        outputUI(ptrUIOutput);
    }				
}

#pragma interrupt lowPriorityIsr
void lowPriorityIsr(void){

	if(ORInput){				//check if user input triggered interrupt
        INTCON3bits.INT1IF = 0;	//clear PORTB1 interrupt flag
		CheckUserInput(UIbuffer);
        
	}else if(INTCONbits.TMR0IF){
        INTCONbits.TMR0IF=0;
        INTCONbits.TMR0IE =0;       //disable interrupt
        T0CONbits.TMR0ON =0;        //turn timer off       
        UIdelay=1;
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
		Emergency_Stop(UIbuffer);
	}
}

         




