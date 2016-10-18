#include <string.h>
#include <stdio.h>
#include <math.h>





int calcEncoder(char*MovType, int Val,int*EncodIn,int*TargetEncod)
{
    
    int wheel2cent_R;
    int wheel_r;
    int EncodErr;
    if(!strcmp(MovType,"forward"))
    {
        *TargetEncod =  64*val/(2*pi*r);
        
       EncodErr = *TargetEncod -*EncodIn ;
        TargetEncod++;
        return EncodErr;
    }     
    else if(!strcmp(MovType, "rotate"))
    {
     switch(Val)
        {
         case 90:
            
            *TargetEncod = 64*((2*pi*wheel2cent_R/4)/(2*pi*r));
            EncodErr = *TargetEncod - *EncodIn;
            TargetEncod++;
            return EncodErr
             
         case 360:
            *TargetEncod = 64*((2*pi*wheel2cent_R)/(2*pi*r));
            EncodErr = *TargertEncod - *EncodIn;
            TargetEncod++;
            return EncodErr;
         default:
             return;
        }
    
    }
    
} 
