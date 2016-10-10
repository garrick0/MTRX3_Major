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
//RA4 -------Auto/manul
#include    <p18f452.h>
#include    "ConfigRegs.h"

int trsflag=0x00;

/*config Port
*/
void main (void){
    PORTA = 0x00;   /*port A as input*/
    TRISA = 0xFF;   
    PORTB = 0x00;
    TRISA = 0x00;
    
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
        
         if (PORTAbits.RA4 != 0)
        {
            PORTB = 0x0f; /* LED for testing*/
        }
        
     // Priority logic
     
     // if none of switch is on 
        if (PORTA==0)
        {
        trsflag=0x00;    // none signal
        }
        
      if ((PORTAbits.RA0 !=0) && (PORTAbits.RA1 ==0)&&(PORTAbits.RA2 ==0)&&(PORTAbits.RA3 ==0)&&(PORTAbits.RA4 ==0))
        {
        trsflag=0x01; // up signal
        }
        if ((PORTAbits.RA1 !=0) && (PORTAbits.RA0 ==0)&&(PORTAbits.RA2 ==0)&&(PORTAbits.RA3 ==0)&&(PORTAbits.RA4 ==0))
        {
        trsflag=0x02; // down signal
        }
         if ((PORTAbits.RA2 !=0) && (PORTAbits.RA0 ==0)&&(PORTAbits.RA1 ==0)&&(PORTAbits.RA3 ==0)&&(PORTAbits.RA4 ==0))
        {
        trsflag=0x04; // left signal
        }
        if ((PORTAbits.RA3 !=0) && (PORTAbits.RA0 ==0)&&(PORTAbits.RA1 ==0)&&(PORTAbits.RA2 ==0)&&(PORTAbits.RA4 ==0))
        {
        trsflag=0x08; // right signal
        }
         if ((PORTAbits.RA4 !=0) && (PORTAbits.RA0 ==0)&&(PORTAbits.RA1 ==0)&&(PORTAbits.RA2 ==0)&&(PORTAbits.RA3 ==0))
        {
        trsflag=0x10; // automode
        }
         if ((PORTAbits.RA4 ==0) && (PORTAbits.RA0 ==0)&&(PORTAbits.RA1 ==0)&&(PORTAbits.RA2 ==0)&&(PORTAbits.RA3 ==0))
        {
        trsflag=0x00; // manuel mode
    }

}
