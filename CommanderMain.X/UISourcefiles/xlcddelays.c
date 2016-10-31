/**
 * @file xlcd_delays.c
 * @date September 2016
 * @brief Implements delay functions for the LCD screen
 * 
 * Uses NOP's and for loops to create suitable delays on pic18f4520
 * 
 * @author Wilhelm Marais
 *
 * 
 */

/** Delay for 18 cycles. Uses 14 NOP assembly commands
 *  since it takes 4 cycles to enter and exit the function. 
 */
void DelayFor18TCY(void)
{
_asm
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
_endasm
}

#if defined(__18F4520)
/** Delay for 15 milliseconds. Delay for 37500 cycles 
 * at 2.5 MHz instruction rate. 
 */
          
void DelayPORXLCD(void)
{
    int i = 2882;

    _asm
        NOP
        NOP
        NOP
        NOP
    _endasm
            
    /*! This loop takes 13 cycles each iteration. */ 
    while(i)
    {
        --i;
    }           
}

/** Delay for 5 milliseconds. Delay for 12500 cycles 
 * at 2.5 MHz instruction rate. 
 */                
void DelayXLCD(void)
{
    int i = 959;
    
    _asm
        NOP
        NOP
        NOP
    _endasm
            
            
    /*! This loop takes 13 cycles each iteration. */ 
    while(i)
    {
        --i;
    }        
}

#endif

