/**
 * @file LCDWrite.c
 * @date October 2016
 * @brief Write to LCD
 * 
 * Displays text on LCD.
 * 
 * @author Wilhelm Marais
 *
 * 
 */
#include "xlcd.h" 
/** Initialise LCD.
 */
void LCDInitialise(void){
    OpenXLCD( FOUR_BIT & LINES_5X7 );
}

/** LCD write functions. Functions to write to LCD screen
 * line 1 or 2 from ROM or RAM. 
 */
void LCDLine1ROMWrite(char buff[]){
    while (BusyXLCD());
    WriteCmdXLCD(0x00 | 0x80); // write start of line one
    while (BusyXLCD());
    //DelayXLCD(); //check if able to remove
    putrsXLCD( buff );
}
void LCDLine1RAMWrite(char *buff){
    while (BusyXLCD());
    WriteCmdXLCD(0x00 | 0x80); // write start of line one
    while (BusyXLCD());
    //DelayXLCD(); //check if able to remove
    putsXLCD( buff );
}

void LCDLine2ROMWrite(char buff[]){    
    while (BusyXLCD());
    WriteCmdXLCD(0x40 | 0x80); // write start of line one
    while (BusyXLCD());
    //DelayXLCD(); //check if able to remove
    putrsXLCD( buff );
}
void LCDLine2RAMWrite(char *buff){    
    while (BusyXLCD());
    WriteCmdXLCD(0x40 | 0x80); // write start of line one
    while (BusyXLCD());
    //DelayXLCD(); //check if able to remove
    putsXLCD( buff );
}
/** Clear LCD.
 */
void LCDClear(void){
    while (BusyXLCD());
    WriteCmdXLCD(0x01);
}