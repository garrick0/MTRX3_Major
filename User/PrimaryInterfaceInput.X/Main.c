/* 
 * File:   Main.c
 * Author: W
 *To do: -check required output type of ReadUserInputBuffer
 *       -add low pass filters on ORInput, EmergencyStop and On/Off to 
 * prevent triggering on rising edge due to noise  
 * Created on 11 October 2016, 13:18
 */

#include <stdio.h>
#include <stdlib.h>
#include <p18f4520.h>
#include "ConfigRegs_18F4520.h"
#include "UserInput.h"

#define  EmergencyStop	PORTBbits.RB0
#define  ORInput        PORTBbits.RB1
#define  On_Off_Switch	PORTBbits.RB4

//setup interrupts
void low_interrupt( void );
void lowPriorityIsr(void);
void highPriorityIsr(void);

#pragma code highPriorityInterruptAddress=0x0008
void high_interrupt(void){  
    _asm GOTO highPriorityIsr _endasm   
}
#pragma code lowPriorityInterruptAddress=0x0018
void low_interrupt( void ){
    _asm GOTO lowPriorityIsr _endasm       
}


char	UserInputBuffer[10];			//stores user inputs
int 	idx=0;                          //indicators for UserInputBuffer idx=current buffer location

#pragma code
void main( void ){
        
   
}

void LowPriorityISR(void){

	if(ORInput){				//check if user input triggered interrupt
        INTCON3bits.INT1IF = 0;	//clear PORTB1 interrupt flag
		CheckUserInput();
	}
}


void HighPriorityISR(void){

	if(INTCONbits.RBIF){            //check if user input triggered interrupt
		INTCONbits.RBIF = 0;        //clear PORTB 4:7 interrupt flag
        ON_OFF();
	}
		
	if(EmergencyStop){              //check if user input triggered interrupt
        INTCONbits.INT0IF = 0;      //clear PORTB0 interrupt flag
		Emergency_Stop();
	}
}

