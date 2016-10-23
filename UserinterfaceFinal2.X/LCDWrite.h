/* 
 * File:   LCDWrite.h
 * Author: W
 *
 * Created on 07 October 2016, 10:51
 */

#ifndef LCDWRITE_H
#define	LCDWRITE_H

void LCDInitialise(void);
void LCDLine1ROMWrite(char buff[]);
void LCDLine1RAMWrite(char *buff);
void LCDLine2ROMWrite(char buff[]);
void LCDLine2RAMWrite(char *buff);
void LCDClear(void);

#endif	/* LCDWRITE_H */

