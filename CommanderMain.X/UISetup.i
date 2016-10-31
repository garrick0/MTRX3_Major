#line 1 "UISourcefiles/UISetup.c"
#line 1 "UISourcefiles/UISetup.c"





void UISetup(void){
    LCDInitialise();
    UserInputSetup();
    initialiseComs();
    LEDSetup();
}
