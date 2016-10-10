/* 
 * File:   newmain.c
 * Author: Monadil + Kewei
 *
 * TODO: Finish off designing hardware
 * Created on 6 October 2016, 3:59 PM
 */

//config the control
//RA0 -------Up
//RA1 -------down
//RA2 -------Left
//RA3 -------Right

#include    <p18f452.h>
#include    "ConfigRegs.h"

/*config Port
*/
void main (void){
    PORTA = 0x00;   /*port A as input*/
    TRISA = 0xFF;   
    PORTB = 0x00;
    PORTB = 0x00;
    
    while(1){
        
     //LED test    
            if (PORTAbits.RA0 != 0)  //
        {
            PORTB = 0x08; /* LED for testing*/
        }
           
            if (PORTAbits.RA1 != 0)
        {
            PORTB = 0x04; /* LED for testing*/
        }
          if (PORTAbits.RA2 != 0)
        {
            PORTB = 0x02; /* LED for testing*/
        }
        
         if (PORTAbits.RA3 != 0)
        {
            PORTB = 0x01; /* LED for testing*/
        }
        
     // Priority logic
        
        
    
        
        
    }

}
