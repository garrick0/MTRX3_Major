#include <string.h>
#include <stdio.h>
#include <math.h>
//|calcEncoder|
//Takes inputs for wheel movements (forward or rotations) and produces number of encoder
//values required for the total movement
//inputs: Movement Type, Value
//        Movement Type: "forward", "rotate" 
//        Value:         " 
//outputs: Total Number of encoder clicks required
//        Total number of encoder rotations required for each wheel 
int calcEncoder(char MovType, int Val)
{
    static int  TargetEncod;
    float PI = 3.1415;
    int wheel2cent_R = 10;
    int wheel_r = 4.5;
    int EncodErr;
    float rads;
    if(!strcmp(MovType,"forward"))
    {
        TargetEncod =  64*Val/(2*PI*wheel_r); //Calculate number of encoder clicks
       
        return TargetEncod;
    }     
    else if(!strcmp(MovType, "rotate"))
    {
        float rads = Val/180;
        TargetEncod = 64*((wheel2cent_R*rads)/(2*PI*wheel_r)); //Calculate number of encoders 

        return TargetEncod;
    }
    
    }
    
 
