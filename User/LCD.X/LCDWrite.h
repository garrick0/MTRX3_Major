/* 
 * File:   LCDWrite.h
 * Author: W
 *
 * Created on 07 October 2016, 10:51
 */

#ifndef LCDWRITE_H
#define	LCDWRITE_H

void LCDInitialise(void);
void LCDLine1Write(const rom char *buff);
void LCDLine2Write(const rom char *buff);
void LCDClear(void);

#endif	/* LCDWRITE_H */

