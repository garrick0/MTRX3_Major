/* 
 * File:   RFmodule.h
 * Author: wege5641
 *
 * Created on 7 October 2016, 1:55 PM
 */

#ifndef ASCII_H
#define	ASCII_H
#include "p18f452.h"
#include <stdio.h>
#include <stdlib.h>
#include "usart.h"
#define CR 0x0D
#define typeMask 0xF0
#define valMask 0x0F
#define letterType1 0x60
#define letterType2 0x70
#define numType 0x30


// return ASCII type: 1- num 2- letter 3- ??
int typeDetect(char ASCII);
int typeDetect(char ASCII){
    char ASCIItype;
    int type;
    ASCIItype = ASCII&typeMask;
    switch(ASCIItype){
        case letterType1:
            type = 2;
            break;
        case letterType2:
            type = 2;
            break;
        case numType:
            type = 1;
            break;
        default:
            type = 3;
    }
    return type;
}
// ASCII to number, input a string of ASCII numbers null terminated, 0-255 only
char ASCIItoNum(char *ASCIIBuffer);
char ASCIItoNum(char *ASCIIBuffer){
    char num, totalNum = 0;
    int shift = 1;
    while(*ASCIIBuffer != 0x00){
        shift --;
        num = *ASCIIBuffer&valMask;
        num = num*(shift*16);
        ASCIIBuffer ++;
        totalNum = num + totalNum;
    }
    return totalNum;
}

