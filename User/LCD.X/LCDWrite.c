#include "xlcd.h" 

void LCDInitialise(void){
    OpenXLCD( FOUR_BIT & LINES_5X7 );
}

void LCDLine1Write(const rom char *buff){
    while (BusyXLCD());
    WriteCmdXLCD(0x01);         //Clear LCD
    while (BusyXLCD());
    WriteCmdXLCD(0x00 | 0x80); // write start of line one
    while (BusyXLCD());
    DelayXLCD(); //check if able to remove
    putrsXLCD( buff );
}

void LCDLine2Write(const rom char *buff){
    while (BusyXLCD());
    WriteCmdXLCD(0x01);
    while (BusyXLCD());
    WriteCmdXLCD(0x40 | 0x80); // write start of line one
    while (BusyXLCD());
    DelayXLCD(); //check if able to remove
    putrsXLCD( buff );
}

