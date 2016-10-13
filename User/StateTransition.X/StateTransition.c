#define INITIALISE          0
#define USER_MANUAL_MODE 	1
#define USER_AUTO_MODE 		2
#define	FACTORY_MODE		3

#define	PRIMARY_INTERFACE_MODE	0
#define	SECONDARY_INTERFACE_MODE	1

#define ENTRY               0
#define NORMAL              1
#define PARAMETER           2

//secondary output flag flag;

int StateTransition(int CURRENT_STATE,int INTERFACE_MODE,int STATE_VARIABLE,int MENU_POSITION,char USERINPUT,int timeout){
    
    if(INTERFACE_MODE==PRIMARY_INTERFACE_MODE){
        
        switch(CURRENT_STATE){
            
            case INITIALISE:
                switch(STATE_VARIABLE){
                    case ENTRY:
                        if(timeout){
                            STATE_VARIABLE=NORMAL;
                        }
                        break;
                    case NORMAL:
                        if(timeout){
                            CURRENT_STATE=USER_MANUAL_MODE;     //request state change
                            STATE_VARIABLE=ENTRY;
                        }
                        break;
                }                         
                break;
                
            case USER_MANUAL_MODE:
                switch(STATE_VARIABLE){
                    case ENTRY:
                        if(timeout){
                            STATE_VARIABLE=NORMAL;
                        }
                        break;
                    case NORMAL:
                        if(USERINPUT=='A'){
                            //CURRENT_STATE=USER_MANUAL_MODE;
                            INTERFACE_MODE=SECONDARY_INTERFACE_MODE;
                            STATE_VARIABLE=ENTRY;
                            MENU_POSITION=0;
                        }
                        break;
                }                         
                break;
             
            case USER_AUTO_MODE:
                switch(STATE_VARIABLE){
                    case ENTRY:
                        if(timeout){
                            STATE_VARIABLE=NORMAL;
                        }
                        break;
                    case NORMAL:
                        if(USERINPUT=='A'){
                            //CURRENT_STATE=USER_MANUAL_MODE;
                            INTERFACE_MODE=SECONDARY_INTERFACE_MODE;
                            STATE_VARIABLE=ENTRY;
                            MENU_POSITION=0;
                        }
                        break;
                }                         
                break;
                         
            case FACTORY_MODE:
                switch(STATE_VARIABLE){
                    case ENTRY:
                        if(timeout){
                            STATE_VARIABLE=NORMAL;
                        }
                        break;
                    case NORMAL:
                        if(USERINPUT=='A'){
                            //CURRENT_STATE=USER_MANUAL_MODE;
                            INTERFACE_MODE=SECONDARY_INTERFACE_MODE;
                            STATE_VARIABLE=ENTRY;
                            MENU_POSITION=0;
                        }
                        break;
                }                         
                break;
                
        }
    }
    
    if(INTERFACE_MODE==SECONDARY_INTERFACE_MODE){
        
        switch(CURRENT_STATE){
                     
            case USER_MANUAL_MODE:
                switch(STATE_VARIABLE){
                    case ENTRY:
                        if(timeout){
                            STATE_VARIABLE=NORMAL;
                        }
                        break;
                    case NORMAL:
                        if(USERINPUT=='A'){
                            if(MENU_POSITION!=3){
                                STATE_VARIABLE=PARAMETER;
                            }else if(MENU_POSITION==3){                                                    
                                CURRENT_STATE=USER_AUTO_MODE;   //request
                                STATE_VARIABLE=ENTRY;
                                MENU_POSITION=0;
                            }
                                
                        }
                        if(USERINPUT=='B'){
                            INTERFACE_MODE=PRIMARY_INTERFACE_MODE;
                            STATE_VARIABLE=ENTRY;
                            MENU_POSITION=0;
                        }
                        if(USERINPUT=='U'){
                            if(MENU_POSITION>0){                              
                                MENU_POSITION--;
                            }
                        }
                        if(USERINPUT=='D'){
                            if(MENU_POSITION<4){
                                MENU_POSITION++;
                            }
                        }
                        break;
                    case PARAMETER:
                        switch(MENU_POSITION){
                            case 0:
                                MOTORS_ON;           //request
                                //MENU_POSITION=0;
                                STATE_VARIABLE=NORMAL;
                                break;
                            case 1:
                                MOTORS_OFF;         //request
                                //MENU_POSITION=0;
                                STATE_VARIABLE=NORMAL;
                                break;
                            case 2:
                                if(USERINPUT='L'){
                                    MAX_ROBOT_SPEED--;       //request
                                }
                                if(USERINPUT='R'){
                                    MAX_ROBOT_SPEED++;
                                }
                                if(USERINPUT='B'){
                                    STATE_VARIABLE=NORMAL;
                                }
                                break;                           
                            case 4:
                                if(USERINPUT='R'){
                                    CURRENT_STATE=FACTORY_MODE;
                                    STATE_VARIABLE=ENTRY:
                                    MENU_POSITION=0;
                                }
                                else{
                                    STATE_VARIABLE=NORMAL;
                                    PCWrite("Wrong Passcode");
                                }
                                break;
                                
                        }
                        break;
                }                         
                break;
             
            case USER_AUTO_MODE:
                switch(STATE_VARIABLE){
                    case ENTRY:
                        if(timeout){
                            STATE_VARIABLE=NORMAL;
                        }
                        break;
                    case NORMAL:
                        if(USERINPUT=='A'){
                            switch(MENU_POSITION){
                                case 0:
                                    FIND_PARROT=ON;
                                    break;
                                case 1:
                                    CURRENT_STATE=USER_MANUAL_MODE; //request
                                    MENU_POSITION=0;
                                    STATE_VARIABLE=ENTRY;
                                    break;
                            }
                        }
                        if(USERINPUT=='B'){
                            INTERFACE_MODE=PRIMARY_INTERFACE_MODE;
                            STATE_VARIABLE=ENTRY;
                            MENU_POSITION=0;
                        }
                        if(USERINPUT=='U'){
                            if(MENU_POSITION>0){                              
                                MENU_POSITION--;
                            }
                        }
                        if(USERINPUT=='D'){
                            if(MENU_POSITION<1){
                                MENU_POSITION++;
                            }
                        }
                        break;
                }                         
                break;
                         
            case FACTORY_MODE:  ////////////////////////////
                switch(STATE_VARIABLE){
                    case ENTRY:
                        if(timeout){
                            STATE_VARIABLE=NORMAL;
                        }
                        break;
                    case NORMAL:
                        if(USERINPUT=='A'){
                            if(MENU_POSITION!=6){
                                STATE_VARIABLE=PARAMETER;
                            }else if(MENU_POSITION==6){                                                    
                                CURRENT_STATE=USER_MANUAL_MODE;   //request
                                STATE_VARIABLE=ENTRY;
                                MENU_POSITION=0;
                            }
                        }
                        if(USERINPUT=='B'){
                            INTERFACE_MODE=PRIMARY_INTERFACE_MODE;
                            STATE_VARIABLE=ENTRY;
                            MENU_POSITION=0;
                        }
                        if(USERINPUT=='U'){
                            if(MENU_POSITION>0){                              
                                MENU_POSITION--;
                            }
                        }
                        if(USERINPUT=='D'){
                            if(MENU_POSITION<6){
                                MENU_POSITION++;
                            }
                        }
                        break;
                    case PARAMETER:
                        switch(MENU_POSITION){
                            case 0:
                                //MOTORS_ON;           //request
                                //MENU_POSITION=0;
                                //STATE_VARIABLE=NORMAL;  ///////////////////////////////////////////////////////////////////////////////////////
                                break;
                            case 1:
                                if(USERINPUT='L'){
                                    MAX_ROBOT_SPEED--;       //request
                                }
                                if(USERINPUT='R'){
                                    MAX_ROBOT_SPEED++;
                                }
                                if(USERINPUT='B'){
                                    STATE_VARIABLE=NORMAL;
                                }
                                break;            
                            case 2:
                                if(USERINPUT='L'){
                                    MAX_YAW_RATE--;       //request
                                }
                                if(USERINPUT='R'){
                                    MAX_YAW_RATE++;
                                }
                                if(USERINPUT='B'){
                                    STATE_VARIABLE=NORMAL;
                                }
                                break;
                            case 3:
                                if(USERINPUT='L'){
                                    IR_SAMPLES--;       //request
                                }
                                if(USERINPUT='R'){
                                    IR_SAMPLES++;
                                }
                                if(USERINPUT='B'){
                                    STATE_VARIABLE=NORMAL;
                                }
                                break;
                            case 4:
                                if(USERINPUT='L'){
                                    IR_RATE--;       //request
                                }
                                if(USERINPUT='R'){
                                    IR_RATE++;
                                }
                                if(USERINPUT='B'){
                                    STATE_VARIABLE=NORMAL;
                                }
                                break;
                            case 5:
                                if(USERINPUT='L'){
                                    RF_SAMPLES--;       //request
                                }
                                if(USERINPUT='R'){
                                    RF_SAMPLES++;
                                }
                                if(USERINPUT='B'){
                                    STATE_VARIABLE=NORMAL;
                                }
                                break;
                                
                        }
                        break;
                }                         
                break;
                
        }
    }
}
   