/*!
    @file       ConfigReg.h
    @brief      Include file to set the Configuration Bits of a PIC18F452.
    If the macro __DEBUG is defined, the bits are set as appropriate for
    development and debugging:
        - HS PLL Oscillator; Oscillator Switch disabled; Power-On Timer;
        - Brown-out Reset disabled;
        - Watchdog Timer disabled;
        - CCP2 Multiplex disabled;
        - Stack Overflow Reset;
        - Low-voltage Programming disabled, Debug mode enabled;
        - No protection bits set.
    If the macro __DEBUG is NOT defined, the bits are set as appropriate for
    production code release:
        - HS PLL Oscillator; Oscillator Switch disabled; Power-On Timer;
        - Brown-out Reset enabled at 4.2V;
        - Watchdog Timer disabled;
        - CCP2 Multiplex disabled;
        - Stack Overflow Reset;
        - Low-voltage Programming and Debug mode disabled;
        - No protection bits set.
    @version    0.1
    @date       12-Apr-2005
    @author     David Rye
    @note   This file was generated by the compiler from the command line:
            mcc18 -p18f452 --help-config > configReg.h
    @todo   Consider if Watchdog Timer should be enabled for RELEASE, and add
            WDT management code if so.
    @todo   Change startup code c016iz.c so that everything (including
            initialised variables) correctly re-starts if main() ever exits
            or a BOR or WDT reset occurs.
    @todo   Consider if Stack Overflow Reset should be enabled for RELEASE. It
            may be better not to, as there is no re-entrant or recursive code,
            or dynamic memory allocation here - if the code loads statically
            it should run.
*/



#ifndef CONFIG_REG_H
#define CONFIG_REG_H


#include <p18cxxx.h>



// Configuration settings available for 18F452 Processor
// =====================================================

#ifndef __18F4520
#error  "ERROR: Configuration-header file mismatch.  Verify selected processor."
#endif


//  Oscillator Selection:
//    OSC = LP          LP
//    OSC = XT          XT
//        OSC = HS          HS				     (use for Minimal Board)
//    OSC = RC          RC
//    OSC = EC          EC-OSC2 as Clock Out (use for PICDEM 2 Plus board)
//    OSC = ECIO        EC-OSC2 as RA6
//    OSC = HSPLL       HS-PLL Enabled		 (alternate for Minimal Board)
//    OSC = RCIO        RC-OSC2 as RA6
//
//  Osc. Switch Enable:
//    OSCS = ON         Enabled
//    OSCS = OFF        Disabled
//
//  Power Up Timer:
//    PWRT = ON         Enabled
//    PWRT = OFF        Disabled

#pragma config OSC  = HS // For MNML
// #pragma config OSCS = OFF
#pragma config PWRT = ON


#pragma config BORV = 3

#if __DEBUG
#pragma config BOREN = OFF
#else
#pragma config BOREN = ON
#endif


//  Watchdog Timer:
//    WDT = OFF         DisabledST
//    WDT = ON          Enabled
//
//  Watchdog Postscaler:
//    WDTPS = 1         1:1
//    WDTPS = 2         1:2
//    WDTPS = 4         1:4
//    WDTPS = 8         1:8
//    WDTPS = 16        1:16
//    WDTPS = 32        1:32
//    WDTPS = 64        1:64
//    WDTPS = 128       1:128

#pragma config WDT = OFF, WDTPS = 128


//  CCP2 Mux:
//    CCP2MUX = OFF     Disable (CCP2 is on RB3)
//    CCP2MUX = ON      Enable  (CCP2 is on RC1)

#pragma config CCP2MX = PORTC


//  Stack Overflow Reset:
//    STVREN = OFF        Disabled
//    STVREN = ON         Enabled
//
//  Low Voltage ICSP:
//    LVP = OFF         Disabled
//    LVP = ON          Enabled
//
//  Background Debugger Enable:
//    DEBUG = ON        Enabled
//    DEBUG = OFF       Disabled

//  NOTE: LVP = ON is not compatible with DEBUG = ON

#pragma config STVREN = ON, LVP = OFF

#if __DEBUG
#pragma config DEBUG = ON
#else
#pragma config DEBUG = OFF
#endif


//  Code Protection Block 0:
//    CP0 = ON          Enabled
//    CP0 = OFF         Disabled
//
//  Code Protection Block 1:
//    CP1 = ON          Enabled
//    CP1 = OFF         Disabled
//
//  Code Protection Block 2:
//    CP2 = ON          Enabled
//    CP2 = OFF         Disabled
//
//  Code Protection Block 3:
//    CP3 = ON          Enabled
//    CP3 = OFF         Disabled

#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF


//  Boot Block Code Protection:
//    CPB = ON          Enabled
//    CPB = OFF         Disabled
//
//  Data EEPROM Code Protection:
//    CPD = ON          Enabled
//    CPD = OFF         Disabled

#pragma config CPB = OFF, CPD = OFF


//  Write Protection Block 0:
//    WRT0 = ON         Enabled
//    WRT0 = OFF        Disabled
//
//  Write Protection Block 1:
//    WRT1 = ON         Enabled
//    WRT1 = OFF        Disabled
//
//  Write Protection Block 2:
//    WRT2 = ON         Enabled
//    WRT2 = OFF        Disabled
//
//  Write Protection Block 3:
//    WRT3 = ON         Enabled
//    WRT3 = OFF        Disabled

#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF


//  Boot Block Write Protection:
//    WRTB = ON         Enabled
//    WRTB = OFF        Disabled
//
//  Configuration Register Write Protection:
//    WRTC = ON         Enabled
//    WRTC = OFF        Disabled
//
//  Data EEPROM Write Protection:
//    WRTD = ON         Enabled
//    WRTD = OFF        Disabled

#pragma config WRTB = OFF, WRTC = OFF, WRTD = OFF


//  Table Read Protection Block 0:
//    EBTR0 = ON        Enabled
//    EBTR0 = OFF       Disabled
//
//  Table Read Protection Block 1:
//    EBTR1 = ON        Enabled
//    EBTR1 = OFF       Disabled
//
//  Table Read Protection Block 2:
//    EBTR2 = ON        Enabled
//    EBTR2 = OFF       Disabled
//
//  Table Read Protection Block 3:
//    EBTR3 = ON        Enabled
//    EBTR3 = OFF       Disabled

#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF


//  Boot Block Table Read Protection:
//    EBTRB = ON        Enabled
//    EBTRB = OFF       Disabled

#pragma config EBTRB = OFF


#endif  // #ifndef CONFIG_REGISTERS_H