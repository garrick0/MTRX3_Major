#include "UserInterface.h"
//#include "servo.h"

#define INITIALISE          0
#define USER_MANUAL_MODE 	1
#define USER_AUTO_MODE 		2
#define	FACTORY_MODE		3


#define	PRIMARY_INTERFACE_MODE	0
#define	SECONDARY_INTERFACE_MODE	1

#define ENTRY               0
#define NORMAL              1
#define PARAMETER           2

char userinput;
int interface_mode=PRIMARY_INTERFACE_MODE;
int	state_variable=ENTRY;
int menu_position=0;
int     flag=1;  


void UISetup(void) {
    LCDInitialise();
    UserInputSetup();
    initialiseComs();
    LEDSetup();
    //servoSetup();
    //initialiseCCP2();
}


/*Stores user input through button interrupts, returns 1 to set input flag high and trigger inputUI on next loop*/
char storeUI(char* UIBuffer) {
    return 1;
}
//this function is not needed, inputUI should be called every loop since state changes occur without user input

/*Processes stored user input, outputs are state change and direction commands which are modified through pointers*/
void inputUI(char* UIbuffer,struct UserInterfaceInput* UIInput) {
    userinput=ReadUserInputBuffer(UIbuffer);
    StateTransition(UIInput,&interface_mode, &state_variable,&menu_position,&userinput,&flag);		
}

/*Outputs internal values to the user for display*/
void outputUI(struct UserInterfaceOutput *UIOutput){
    if(flag){
        SecondaryInterfaceOutput(UIOutput,interface_mode, state_variable,menu_position);
        flag=0;
    }
    PrimaryInterfaceOutput(UIOutput,interface_mode,state_variable,menu_position);
}

