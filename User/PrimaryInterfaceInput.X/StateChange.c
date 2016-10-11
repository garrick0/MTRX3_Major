#define USER_MANUAL_MODE 	0
#define USER_AUTO_MODE 		1
#define	FACTORY_MODE		2

#define	PRIMARY_INTERFACE_MODE	0
#define	SECONDARY_INTERFACE_MODE	1

void  StateChange(char Instruction,int CURRENT_STATE,int INTERFACE_MODE){
    if((INTERFACE_MODE==PRIMARY_INTERFACE_MODE) && (Instruction == 'A')){
        
        INTERFACE_MODE= SECONDARY_INTERFACE_MODE;    
        
    }
    if((INTERFACE_MODE==SECONDARY_INTERFACE_MODE) && (Instruction == 'B')){
        
        INTERFACE_MODE= PRIMARY_INTERFACE_MODE;
        
    }
   
}
