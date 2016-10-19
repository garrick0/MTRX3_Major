/* 
 * File:   IRSensors.h
 * Author: sgle6040
 *
 * Created on 8 October 2016, 2:29 PM
 */

#ifndef IRSENSORS_H
#define	IRSENSORS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define MAXIMUM_IR 3
    
    unsigned int IRBuffer1[MAXIMUM_IR]  = {0};
    unsigned int IRBuffer2[MAXIMUM_IR]  = {0};
    unsigned int IRBuffer0[MAXIMUM_IR]  = {0};
    unsigned char IRIndex1 = 0;
    unsigned char IRIndex2 = 0;
    unsigned char IRIndex0 = 0;
    
    
    
    
    




#ifdef	__cplusplus
}
#endif

#endif	/* IRSENSORS_H */

