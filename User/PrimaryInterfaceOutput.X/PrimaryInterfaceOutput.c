#include   "LCDWrite.h"


#define USER_MANUAL_MODE 	0
#define USER_AUTO_MODE 		1
#define	FACTORY_MODE		2

#define	PRIMARY_INTERFACE_MODE	0
#define	SECONDARY_INTERFACE_MODE	1


#define BirdMoving      PORTCbits.RC0
#define BirdFound       PORTCbits.RC1
#define ServoControl    PORTCbits.RC2
#define PiezoControl    PORTCbits.RC3

void    LEDOutput(int PARROT_FOUND,int PARROT_MOVING){
    if(PARROT_FOUND){
        BirdFound=1;
    }else{
        BirdFound=0;
    }
    if(PARROT_MOVING){
        BirdMoving=1;
    }else{
        BirdMoving=0;
    }
}

//assuming global variable CURRENT_DIRECTION is relative orientation
//servo requires compare interrupts to generate control PWM
void    InitialiseServo(void){
 
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
    //clock cycles between toggles = delay(ms)*2.5MHz
    CCPR1L=	(25*Delay)&0x00FF;	  //store lower byte
    CCPR1H= (25*Delay)&0xFF00;    //store upper byte
}

//check: delays of 800us is 0deg, 1500us is 180deg, 2200 is 360deg
void    ServoOutput(int CURRENT_DIRECTION){
    if(ServoControl){
        ServoControl=0;
        ServoDelayms(20); //set 20ms low time
    }else{
        ServoControl=1;
        ServoDelay10us(int(CURRENT_DIRECTION*0.38+80));     //change
    }
}

void    PrimaryInterfaceOutput(int CURRENT_STATE,int INTERFACE_MODE,int PARROT_FOUND,int PARROT_MOVING,int CURRENT_DIRECTION){
    
    LEDOutput();
    
    if(CURRENT_STATE==USER_MANUAL_MODE){
        if(INTERFACE_MODE==PRIMARY_INTERFACE_MODE){
            
        }
        if(INTERFACE_MODE==SECONDARY_INTERFACE_MODE){
            
        }
    }
    if(CURRENT_STATE==USER_AUTO_MODE){
        
    }
    if(CURRENT_STATE==FACTORY_MODE)
    LEDOutput(int PARROT_FOUND,int PARROT_MOVING);
    ServoOutput(int CURRENT_DIRECTION);
    
}