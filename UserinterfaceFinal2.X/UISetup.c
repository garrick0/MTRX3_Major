#include "UserInput.h"
#include "LCDWrite.h"
#include "SecondaryInterfaceOutput.h"
#include "PrimaryInterfaceOutput.h"

void UISetup(void){
    LCDInitialise();
    UserInputSetup();
    initialiseComs();
    LEDSetup();
}
