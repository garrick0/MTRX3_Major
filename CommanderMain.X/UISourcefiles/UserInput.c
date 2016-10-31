/**
 * @file UserInput.c
 * @date September 2016
 * @brief Contains all functions to handle user inputs
 * 
 * Contains all functions to handle inputs to the primary and secondary UI
 * and stores them in a buffer which is read when ready. UI inputs trigger 
 * interrupts to store input to buffer.
 * 
 * @author Wilhelm Marais
 *
 * 
 */
//#include "ConfigRegs_18F4520.h"
#include    <p18f4520.h>

#define  dpadRIGHT      PORTAbits.RA0
#define  dpadDOWN       PORTAbits.RA1
#define  dpadUP         PORTAbits.RA2
#define  dpadLEFT      PORTAbits.RA3
#define  Bbutton        PORTAbits.RA4
#define  Abutton        PORTAbits.RA5

#define  EmergencyStop	PORTBbits.RB0
#define  ORInput        PORTBbits.RB1
#define  HalfScan       PORTCbits.RC3
#define  FullScan       PORTBbits.RB3 
#define  On_Off_Switch	PORTBbits.RB4

/** Set up User Input Interrupts. 
 */
void UserInputSetup(void){
    INTCON2bits.RBPU = 1;	//PORTB internal pullups disabled
    PORTB=0x00;             //set PORTB as outputs
    TRISB = 0x1F;           //set PORTB 0:4 pins to inputs and 5:7 pins as outputs 
    TRISCbits.RC3=1;
    ADCON1=0x0F;            //set all PORTS as digital I/O (may have to change for f452)

    //interrupt setup for emergency stop
    INTCONbits.INT0IE = 1;	//enable PORTB0 interrupt (high priority interrupt) 
    INTCONbits.INT0IF = 0;	//clear PORTB0 interrupt flag
    INTCON2bits.INTEDG0 = 1;	//PORTB0 interrupt on rising edge

    //interrupt setup for OR input
    INTCON3bits.INT1IE = 1;	//enable PORTB1 interrupt
    INTCON3bits.INT1IP = 0;	//set PORTB1 interrupt to low priority
    INTCON3bits.INT1IF = 0;	//clear PORTB1 interrupt flag
    INTCON2bits.INTEDG1 = 1;	//PORTB1 interrupt on rising edge

    //disable interrupt on PORTB2
    INTCON3bits.INT2IE = 0; 	//disable PORTB2 interrupt
    INTCON3bits.INT2IF = 0;     //clear PORTB2 interrupt flag

    //interrupt setup for state change of ON/OFF switch
    INTCONbits.RBIF = 0;	//clear PORTB 4:7 interrupt flag
    INTCONbits.RBIE = 0;	//disable interrupt in PORTB 4:7 
    INTCON2bits.RBIP = 1;	//set interrupt to high priority
    

}

/** Write to the UI buffer on interrupt. 
 */
void WriteUserInputBuffer(const rom char *letter,char *UserInputBuffer){
	
	UserInputBuffer[0]=*letter;     //store letter in buffer
	//*idx %= sizeof(UserInputBuffer);		//if end of buffer reached, reset pointer
}
/** Check user input. Checks user input and stores 
 * appropriate character in buffer. 
 */
void CheckUserInput(char *UserInputBuffer){
	if(Bbutton){
		WriteUserInputBuffer("B",UserInputBuffer);
	}    
    else if(Abutton){
		WriteUserInputBuffer("A",UserInputBuffer);
	}
    else if(FullScan){
        WriteUserInputBuffer("F",UserInputBuffer);
    }
    else if(HalfScan){
        WriteUserInputBuffer("H",UserInputBuffer);
    }
    else if(dpadRIGHT){
		WriteUserInputBuffer("R",UserInputBuffer);
	}
    else if(dpadLEFT){
		WriteUserInputBuffer("L",UserInputBuffer);
	}
	else if(dpadDOWN){
		WriteUserInputBuffer("D",UserInputBuffer);
	}
    else if(dpadUP){
		WriteUserInputBuffer("U",UserInputBuffer);
	}
}

/** Check PC input. Checks user input and stores 
 * appropriate character in buffer. 
 */
void CheckPCInput(char *UserInputBuffer){ 
    if(RCREG == 0x7F){  //backspace
		WriteUserInputBuffer("B",UserInputBuffer);
	}    
    else if(RCREG == '\r'){ // 
		WriteUserInputBuffer("A",UserInputBuffer);
	}
    else if(RCREG == 'f' || RCREG == 'F'){
        WriteUserInputBuffer("F",UserInputBuffer);
    }
    else if(RCREG == 'h' || RCREG == 'H'){
        WriteUserInputBuffer("H",UserInputBuffer);
    }
    else if(RCREG == 'a' || RCREG == 'A'){
		WriteUserInputBuffer("L",UserInputBuffer);
	}
    else if(RCREG == 'd' || RCREG == 'D'){
		WriteUserInputBuffer("R",UserInputBuffer);
	}
	else if(RCREG  == 's' || RCREG == 'S'){
		WriteUserInputBuffer("D",UserInputBuffer);
	}
    else if(RCREG == 'w' || RCREG == 'W'){
		WriteUserInputBuffer("U",UserInputBuffer);
	}
    
}

//stores user input letter in circular buffer


//have to decide the type of output and if the whole buffer is read at once
//if whole buffer is read at once, output type must also be a char buffer
//if characters are read 1 at a time (current setup):
//possible issue-buffer inputs may be overwritten by WriteUserInputBuffer
//
//reads user inputs from circular buffer
/** Read user input buffer. Reads user inputs buffer and returns 
 * value. Also clears buffer after reading. 
 */
char ReadUserInputBuffer(char *UserInputBuffer){
	//int counter=sizeof(UserInputBuffer);
	//while(counter--){
		char output;
        output=UserInputBuffer[0];		//read buffer
		*UserInputBuffer='\0';		//clear buffer after reading
		//*idx %= sizeof(UserInputBuffer);		//if end of buffer reached, reset pointer
        //}
		return output;				
}
/** Clear user input buffer.
 */
void ClearUserInputBuffer(char *UserInputBuffer){
	//int counter=sizeof(UserInputBuffer);
	//while(counter--){           
		UserInputBuffer[0]='\0';
	//}
}
/** On/Off function. Not implemented. 
 */
void ON_OFF(void){
    if(On_Off_Switch){
    //goto initialise    
    }
    if(On_Off_Switch==0){
    //send stop to mobile robot
    //send enter sleep mode instruction to mobile robot
    //stop communications
    //disable all interrupts except On/Off switch
    //robot commander sleep
    }
}
/** Emergency stop function. Not implemented. 
 */
void Emergency_Stop(char *UserInputBuffer){
    //send stop to mobile robot
    ClearUserInputBuffer(UserInputBuffer);
    //delay for approx 3 seconds
    
}