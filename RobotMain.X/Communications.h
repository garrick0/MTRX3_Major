/* 
 * File:   Communications.h
 * Author: sgle6040
 *
 * Created on 24 October 2016, 2:37 PM
 */

#ifndef COMMUNICATIONS_H
#define	COMMUNICATIONS_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif



void commsSetup(void);
void transmitData(char* IRVals,char* signalStrength,char processComplete);
void receiveData(char* buffer, char *CRflag, char *recFlag);
char processReceived(char* buffer, int* instMag,char* instDir,char* commandFlag);
void getRSSI(char * buffer, char * signalStrength, char * rFlag, char *CRflag, char *saveF);




#endif	/* COMMUNICATIONS_H */

