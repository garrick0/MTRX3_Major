/* 
 * File:   RFmodule.h
 * Author: wege5641
 *
 * Created on 7 October 2016, 1:55 PM
 */

#ifndef RFMODULE_H
#define	RFMODULE_H
#include "p18f452.h"
#include <stdio.h>
#include <stdlib.h>
#include "usart.h"
#define CR 0x0D

// put null terminated string in to be sent to RF module
void sendMsg(char *ptr);
void sendMsg(char *ptr){
    while (*ptr)
    {
        while (TXSTAbits.TRMT != 1); // wait till transmit buffer is empty
        putcUSART(*ptr); // write command 
        ptr++;  
    }
}
// save the RSSI and the status in separate buffers both null terminated
void findRSSI(char *RSSIbuffer, char *statusBuffer);
void findRSSI(char *RSSIbuffer, char *statusBuffer){
    
    sendMsg(ATCommandStart); // start command mode
    checkForResponse(statusBuffer);
    sendMsg(ATCommandRSSI); // save RSSI
    checkForResponse(RSSIbuffer);
    sendMsg(ATCommandEnd); // end command mode
    checkForResponse(statusBuffer);

    return 0;
}
// check the response of the AT command
void checkForResponse(char *buffer);
void checkForResponse(char *buffer){
    while(PIR1bits.RCIF == 0);
    while(RCREG != CR){
        *buffer = RCREG;
        while(PIR1bits.RCIF == 0);
        buffer++;
    } 
    *buffer = 0x00;
    return 0;
}
