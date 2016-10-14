#include <p18f4520.h>
#include "ConfigRegs_18F4520.h"

//setup interrupts
void low_interrupt( void );
void high_interrupt(void);
void lowPriorityIsr(void);
void highPriorityIsr(void);
void CheckUserInput(void);
void WriteUserInputBuffer(const rom char *letter, int *idx,char *UserInputBuffer);
char ReadUserInputBuffer(char *UserInputBuffer,int *idx);
void ON_OFF(void);
void Emergency_Stop(void);
void  StateChange(char Instruction,int CURRENT_STATE,int INTERFACE_MODE);

char	UserInputBuffer[10];			//stores user inputs
int 	idx=0;    

#define  dpadUP         PORTAbits.RA0
#define  dpadDOWN       PORTAbits.RA1
#define  dpadLEFT       PORTAbits.RA2
#define  dpadRIGHT      PORTAbits.RA3
#define  Abutton        PORTAbits.RA4
#define  Bbutton        PORTAbits.RA5
#define  EmergencyStop	PORTBbits.RB0
#define  ORInput        PORTBbits.RB1
#define  HalfScan       PORTBbits.RB2
#define  FullScan       PORTBbits.RB3 
#define  On_Off_Switch	PORTBbits.RB4
//state defined
#define USER_MANUAL_MODE 	0
#define USER_AUTO_MODE 		1
#define	FACTORY_MODE		2
#define	PRIMARY_INTERFACE_MODE	0
#define	SECONDARY_INTERFACE_MODE	1

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

void UserInputSetup(void){
    INTCONbits.GIE_GIEH = 0;    //global interrupt disable
	INTCONbits.PEIE_GIEL = 0;   //peripheral interrupt disable
    RCONbits.IPEN = 1;		//enable priority on interrupts
    
    //
    INTCON2bits.RBPU = 1;	//PORTB internal pullups disabled
    
    PORTA=0x00;
    PORTB=0x00;             //set PORTB as outputs
    TRISB = 0x1F;       //set PORTB 0:4 pins to inputs and 5:7 pins as outputs
    TRISA = 0x3F;       //set PORTA 0:5 pins to inputs and 5:7 pins as outputs
    ADCON1=0x0F;        //set all PORTS as digital I/O (may have to change for f452)

    
    
    
    
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
    INTCONbits.RBIE = 1;	//enable interrupt in PORTB 4:7 
    INTCON2bits.RBIP = 1;	//set interrupt to high priority
    
    INTCONbits.GIE_GIEH = 1;    //global interrupt enable
	INTCONbits.PEIE_GIEL = 1;   //peripheral interrupt enable
}





void CheckUserInput(void){
	if(dpadUP){
		WriteUserInputBuffer("U",&idx,UserInputBuffer);
	}
	if(dpadDOWN){
		WriteUserInputBuffer("D",&idx,UserInputBuffer);
	}
	if(dpadLEFT){
		WriteUserInputBuffer("L",&idx,UserInputBuffer);
	}
	if(dpadRIGHT){
		WriteUserInputBuffer("R",&idx,UserInputBuffer);
	}
	if(Abutton){
		WriteUserInputBuffer("A",&idx,UserInputBuffer);
	}
	if(Bbutton){
		WriteUserInputBuffer("B",&idx,UserInputBuffer);
	}
    if(FullScan){
        WriteUserInputBuffer("F",&idx,UserInputBuffer);
    }
    if(HalfScan){
        WriteUserInputBuffer("H",&idx,UserInputBuffer);
    }
}

//stores user input letter in circular buffer
void WriteUserInputBuffer(const rom char *letter, int *idx,char *UserInputBuffer){
	
	UserInputBuffer[*idx++]=*letter;     //store letter in buffer
	*idx %= sizeof(UserInputBuffer);		//if end of buffer reached, reset pointer
}





//have to decide the type of output and if the whole buffer is read at once
//if whole buffer is read at once, output type must also be a char buffer
//if characters are read 1 at a time (current setup):
//possible issue-buffer inputs may be overwritten by WriteUserInputBuffer
//reads user inputs from circular buffer	
char ReadUserInputBuffer(char *UserInputBuffer,int *idx){
	//int counter=sizeof(UserInputBuffer);
	//while(counter--){
		char output=UserInputBuffer[*idx];		//read buffer
		UserInputBuffer[*idx++]='\0';		//clear buffer after reading
		*idx %= sizeof(UserInputBuffer);		//if end of buffer reached, reset pointer

	//}
		return output;				
}

void ClearUserInputBuffer(void){
	int counter=sizeof(UserInputBuffer);
	while(counter--){           
		UserInputBuffer[counter]='\0';
	}
}

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

void Emergency_Stop(void){
    //send stop to mobile robot
    ClearUserInputBuffer();
    //delay for approx 3 seconds
    
}

void  StateChange(char Instruction,int CURRENT_STATE,int INTERFACE_MODE){
    if((INTERFACE_MODE==PRIMARY_INTERFACE_MODE) && (Instruction == 'A')){
        
        INTERFACE_MODE= SECONDARY_INTERFACE_MODE;    
        
    }
    if((INTERFACE_MODE==SECONDARY_INTERFACE_MODE) && (Instruction == 'B')){
        
        INTERFACE_MODE= PRIMARY_INTERFACE_MODE;
        
    }
   
}

void main( void ){
 UserInputSetup();
    
while(1){
}    
   
}

#pragma interrupt highPriorityIsr
void highPriorityIsr(void) {
  	if(INTCONbits.RBIF){            //check if user input triggered interrupt
		INTCONbits.RBIF = 0;        //clear PORTB 4:7 interrupt flag
        ON_OFF();
	}
		
	if(EmergencyStop){              //check if user input triggered interrupt
        INTCONbits.INT0IF = 0;      //clear PORTB0 interrupt flag
		Emergency_Stop();
	}
}
#pragma interrupt lowPriorityIsr
void lowPriorityIsr(void) {
	if(ORInput){				//check if user input triggered interrupt
        INTCON3bits.INT1IF = 0;	//clear PORTB1 interrupt flag
		CheckUserInput();
	}
}

