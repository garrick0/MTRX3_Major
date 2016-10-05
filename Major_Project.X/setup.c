/**
 *  @file setup.c
 *  @author Monadil
 *  @date 29/9/16
 *  @breif Setup files. 
 *
 *  Contains all the various setup files (e.g. AD, IO, Serial).
 * 
 */

#include    <p18f452.h>
#include    "setup.h"


void setupLEDs(void){
    PORTB = 0x00;
    TRISB = OUTPUT;
    
}
