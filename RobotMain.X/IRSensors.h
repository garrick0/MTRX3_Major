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
    


#ifdef	__cplusplus
}
#endif


    void IRDetect( int numAverage,char* detectArray);
    void sampleIR(void);
    void IRSetup(void);


#endif	/* IRSENSORS_H */

