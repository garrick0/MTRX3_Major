#define INITIALISE          0
#define USER_MANUAL_MODE 	1
#define USER_AUTO_MODE 		2
#define	FACTORY_MODE		3

#define	PRIMARY_INTERFACE_MODE	0
#define	SECONDARY_INTERFACE_MODE	1

#define ENTRY               0
#define NORMAL              1
#define PARAMETER           2

//unsigned char   MAX_ROBOT_SPEED;


void    PCWrite(char *Data){
    
}
void    PCLineClear(void){
    
}


void    SecondaryInterfaceOutput(int CURRENT_STATE,int INTERFACE_MODE,int STATE_VARIABLE,int MENU_POSITION,int PARROT_FOUND,char *MAX_ROBOT_SPEED,char *MAX_YAW_RATE,char *IR_SAMPLES,char *IR_RATE,char *RF_SAMPLES){
    
    //////////////////////////////////////////////////////////////
    if(CURRENT_STATE==INITIALISE){
        //............................
        switch(STATE_VARIABLE){
            case ENTRY:
                PCWrite("Welcome to...\nPress A to enter commands and UP/DOWN arrows to scroll/nInitialising...\n");
                break;
            case NORMAL:
                PCWrite("USER_MANUAL_MODE\nPress A to enter command\n");
                break;
        }
    }
    
    if(INTERFACE_MODE==SECONDARY_INTERFACE_MODE){
      
        //////////////////////////////////////////////////////////////
        if(CURRENT_STATE==USER_MANUAL_MODE){
            //............................
            if(STATE_VARIABLE==ENTRY){
                PCWrite("USER_MANUAL_MODE\n0-SET_MOTORS_ON\n1-SET_MOTORS_OFF\n2-SET_SPEED_MAX\n3-SET_MODE_USER_AUTO\n4-SET_MODE_FACTORY\n");
                PCWrite("Use UP/DOWN arrows to scroll\nPress A to select\nPress B to exit\n\n");
            }
            //...............................
            if(STATE_VARIABLE==NORMAL){
                
                switch(MENU_POSITION){
                    case 0:
                        PCLineClear();
                        PCWrite("0-SET_MOTORS_ON"); 
                        break;
                    case 1:
                        PCLineClear();
                        PCWrite("1-SET_MOTORS_OFF");
                        break;
                    case 2:
                        PCLineClear();
                        PCWrite("2-SET_SPEED_MAX");
                        break;
                    case 3:
                        PCLineClear();
                        PCWrite("3-SET_MODE_USER_AUTO");
                        break;                       
                    case 4:
                        PCLineClear();
                        PCWrite("4-SET_MODE_FACTORY");
                        break;
                }
                
            }
            //..............................
            if(STATE_VARIABLE==PARAMETER){
                
                switch(MENU_POSITION){
                    case 0:                          
                        PCWrite("\nMOTORS_ON\n"); 
                        break;
                    case 1:
                        PCWrite("\nMOTORS_OFF\n");
                        break;
                
                    case 2:
                        PCWrite("\nMAX SPEED=\n");           //////////////////change
                        PCLineClear();
                        PCWrite(MAX_ROBOT_SPEED);
                        break;               
                    case 4:
                        PCWrite("\nEnter Passcode:\n");
                        break;
                }
            }
                    
        }
        
        ////////////////////////////////////////////////////////
        if(CURRENT_STATE==USER_AUTO_MODE){
            //............................
            if(STATE_VARIABLE==ENTRY){
                PCWrite("USER_AUTO_MODE\n0-SET_FIND_PARROT\n1-SET_MODE_USER_MANUAL\n");
                PCWrite("Use UP/DOWN arrows to scroll\nPress A to select\nPress B to exit\n\n");
            }
            //...............................
            if(STATE_VARIABLE==NORMAL){
                switch(MENU_POSITION){
                    case 0: 
                        PCLineClear();
                        PCWrite("0-SET_FIND_PARROT");
                        break;
                    case 1:
                        PCLineClear();
                        PCWrite("1-SET_MODE_USER_MANUAL");
                        break;
                }
            }                                              
        }
        
        ////////////////////////////////////////////////////////
        if(CURRENT_STATE==FACTORY_MODE){
            //............................
            if(STATE_VARIABLE==ENTRY){
                PCWrite("FACTORY_MODE\n0-SET_PID_GAINS\n1-SET_SPEED_MAX\n2-SET_YAW_RATE_MAX\n3-SET_IR_SAMPLES_PER_ESTIMATE\n4-SET_IR_SAMPLE_RATE\n5-SET_RF_SAMPLES_PER_ESTIMATE\n6-SET_MODE_USER_MANUAL\n");
                PCWrite("Use UP/DOWN arrows to scroll\nPress A to select\nPress B to exit\n\n");
            }
            //...............................
            if(STATE_VARIABLE==NORMAL){
                switch(MENU_POSITION){
                    case 0:
                        PCLineClear();
                        PCWrite("0-SET_PID_GAINS"); 
                        break;               
                    case 1:
                        PCLineClear();
                        PCWrite("1-SET_SPEED_MAX");
                        break;
                    case 2:
                        PCLineClear();
                        PCWrite("2-SET_YAW_RATE_MAX");
                        break;
                    case 3:
                        PCLineClear();
                        PCWrite("3-SET_IR_SAMPLES_PER_ESTIMATE");
                        break;
                    case 4:
                        PCLineClear();
                        PCWrite("4-SET_IR_SAMPLE_RATE");
                        break;
                    case 5:
                        PCLineClear();
                        PCWrite("5-SET_RF_SAMPLES_PER_ESTIMATE");
                        break;
                    case 6:
                        PCLineClear();
                        PCWrite("6-SET_MODE_USER_MANUAL");
                        break;
                }
            }
            //..............................
            if(STATE_VARIABLE==PARAMETER){
                switch(MENU_POSITION){
                    case 0:                
                        PCWrite("\nPID Gains\n");           //figure out how to change PID gains
                        break;
                    case 1:
                        PCWrite("\nMAX SPEED=\n");           //////////////////change
                        PCLineClear();
                        PCWrite(MAX_ROBOT_SPEED);
                        break;
                    case 2:
                        PCWrite("\nMAX YAW RATE=\n");           //////////////////change
                        PCLineClear();
                        PCWrite(MAX_YAW_RATE);
                        break;
                    case 3:
                        PCWrite("\nIR SAMPLES PER ESTIMATE=\n");           //////////////////change
                        PCLineClear();
                        PCWrite(IR_SAMPLES);
                        break;
                    case 4:
                        PCWrite("\nIR SAMPLE RATE=\n");           //////////////////change
                        PCLineClear();
                        PCWrite(IR_RATE);
                        break;
                    case 5:
                        PCWrite("\nRF SAMPLES PER ESTIMATE=\n");           //////////////////change
                        PCLineClear();
                        PCWrite(RF_SAMPLES);
                        break;
                }
            }
        }
    }
    if(INTERFACE_MODE==PRIMARY_INTERFACE_MODE){
        if(PARROT_FOUND){
            PCWrite("\n PARROT FOUND!!!!\n");
        }
    }
}












