#include   "LCDWrite.h"

#define INITIALISE          0
#define USER_MANUAL_MODE 	1
#define USER_AUTO_MODE 		2
#define	FACTORY_MODE		3

#define	PRIMARY_INTERFACE_MODE	0
#define	SECONDARY_INTERFACE_MODE	1

#define ENTRY               0
#define NORMAL              1
#define PARAMETER           2

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
    //clock cycles between toggles = delay(10us)*2.5MHz
    CCPR1L=	(25*Delay)&0x00FF;	  //store lower byte
    CCPR1H= (25*Delay)&0xFF00;    //store upper byte
}

//check: delays of 1ms is 0deg, 1.5ms is 90deg, 2ms is 1800deg
void    ServoOutput(int CURRENT_DIRECTION){
    if(ServoControl==0){
        ServoControl=1;
        ServoDelay10us(int(CURRENT_DIRECTION*0.38+80)); //set 20ms low time
    }else{
        ServoControl=0;
        ServoDelayms(int(CURRENT_DIRECTION*0.38+80));     //change
    }
}

void    PrimaryInterfaceOutput(int CURRENT_STATE,int INTERFACE_MODE,int STATE_VARIABLE,int MENU_POSITION,char *MAX_ROBOT_SPEED,char *MAX_YAW_RATE,char *IR_SAMPLES,char *IR_RATE,char *RF_SAMPLES,int PARROT_MOVING,int PARROT_FOUND,int CURRENT_DIRECTION){
    
    LEDOutput(PARROT_FOUND,PARROT_MOVING);
    ServoOutput(CURRENT_DIRECTION);
    
    if(CURRENT_STATE==INITIALISE){
            //............................
        switch(STATE_VARIABLE){
            case ENTRY:
                LCDClear();
                LCDLine1Write("Welcome to...");
                LCDLine2Write("Initialising..")
                break;
            case NORMAL:
                LCDClear();
                LCDLine1Write("USER_MANUAL_MODE"); 
                break;
        }
    }
    if(INTERFACE_MODE==SECONDARY_INTERFACE_MODE){
        
        //////////////////////////////////////////////////////////////
        
        //////////////////////////////////////////////////////////////
        if(CURRENT_STATE==USER_MANUAL_MODE){
            //............................
            if(STATE_VARIABLE==ENTRY){
                LCDClear();
                LCDLine1Write("USER_MANUAL_MODE");              
            }
            //...............................
            if(STATE_VARIABLE==NORMAL){
                switch(MENU_POSITION){
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
            if(STATE_VARIABLE==PARAMETER){
                switch(MENU_POSITION){
                    case 0:                
                        LCDClear();
                        LCDLine1Write("MOTORS_ON"); 
                        break;
                    case 1:
                        LCDClear();
                        LCDLine1Write("MOTORS_OFF");
                        break;
                    case 2:
                        LCDClear();
                        LCDLine1Write("MAX SPEED=");           
                        LCDLine2Write(MAX_ROBOT_SPEED);
                        break;
                    case 4:
                        LCDClear();
                        LCDLine1Write("Enter Passcode:");
                        break;
                }
            }
                    
        }
        
        ////////////////////////////////////////////////////////
        if(CURRENT_STATE==USER_AUTO_MODE){
            //............................
            if(STATE_VARIABLE==ENTRY){
                LCDClear();
                LCDLine1Write("USER_AUTO_MODE");
            }
            //...............................
            if(STATE_VARIABLE==NORMAL){
                switch(MENU_POSITION){
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
        if(CURRENT_STATE==FACTORY_MODE){
            //............................
            if(STATE_VARIABLE==ENTRY){
                LCDClear();
                LCDLine1Write("FACTORY_MODE");               
            }
            //...............................
            if(STATE_VARIABLE==NORMAL){
                switch(MENU_POSITION){
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
            if(STATE_VARIABLE==PARAMETER){
                switch(MENU_POSITION){
                    case 0:                
                        LCDClear();
                        LCDLine1Write("PID Gains");           //figure out how to change PID gains
                        break;
                    case 1:
                        LCDClear();
                        LCDLine1Write("MAX SPEED=");           //////////////////change                  
                        LCDLine2Write(MAX_ROBOT_SPEED);
                        break;
                    case 2:
                        LCDClear();
                        LCDLine1Write("MAX YAW RATE=");           //////////////////change
                        LCDLine2Write(MAX_YAW_RATE);
                        break;
                    case 3:
                        LCDClear();
                        LCDLine1Write("IR SAMPLES PER ESTIMATE=");           //////////////////change
                        LCDLine2Write(IR_SAMPLES);
                        break;
                    case 4:
                        LCDClear();
                        LCDLine1Write("IR SAMPLE RATE=");           //////////////////change
                        LCDLine2Write(IR_RATE);
                        break;
                    case 5:
                        LCDClear();
                        LCDLine1Write("RF SAMPLES PER ESTIMATE=");           //////////////////change                  
                        LCDLine2Write(RF_SAMPLES);
                        break;
                }
            }
        }
    }
    if(INTERFACE_MODE==PRIMARY_INTERFACE_MODE){
       
        if(CURRENT_STATE==USER_MANUAL_MODE){
            //............................
            switch(STATE_VARIABLE){
                case ENTRY:
                    LCDClear();
                    LCDLine1Write("USER_MANUAL_MODE");              
                    break;          
                case NORMAL:
                    LCDClear();
                    LCDLine1Write("LEFT: RIGHT:")
                    LCDLine2Write("FRONT:")        
                    break;       
            }
        }
        if(CURRENT_STATE==USER_AUTO_MODE){
            //............................
            switch(STATE_VARIABLE){
                case ENTRY:
                    LCDClear();
                    LCDLine1Write("USER_AUTO_MODE");
                    break;
                case NORMAL:
                    LCDClear();
                    LCDLine1Write("USER_AUTO_MODE");
                    break;
            }
        }
        if(CURRENT_STATE==FACTORY_MODE){
            switch(STATE_VARIABLE){
                case ENTRY:
                    LCDClear();
                    LCDLine1Write("FACTORY_MODE");               
                    break;
                case NORMAL:
                    LCDClear();
                    LCDLine1Write("LEFT: RIGHT:")
                    LCDLine2Write("FRONT:") 
                    break;
            }
        }
    } 
}