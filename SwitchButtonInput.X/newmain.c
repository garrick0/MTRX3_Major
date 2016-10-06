/* 
 * File:   newmain.c
 * Author: Monadil
 *
 * Created on 6 October 2016, 3:59 PM
 */

#include    <p18f452.h>
#include    "ConfigRegs.h"

void main (void){
    PORTA = 0x00;
    TRISA = 0xFF;
    PORTB = 0x00;
    PORTB = 0x00;
    
    while(1){
            if (PORTAbits.RA0 != 0)
        {
            PORTB = 0xF1;
        }
    }

}
