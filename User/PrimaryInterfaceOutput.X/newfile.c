

    //setup CCP1 for compare and special event
void inibuzzer(){
 
    
 PORTCbits.RC3=0;    //set PortC R3 as output  
 TRISCbits.RC3=0;

}


void    ServoDelayms(int Delay){
    //clock cycles between toggles = delay(ms)*2.5MHz
    CCPR2L=	(2500*Delay)&0x00FF;	  //store lower byte
    CCPR2H= (2500*Delay)&0xFF00;    //store upper byte
}
void    ServoDelay10us(int Delay){
    //clock cycles between toggles = delay(ms)*2.5MHz
    CCPR2L=	(25*Delay)&0x00FF;	  //store lower byte
    CCPR2H= (25*Delay)&0xFF00;    //store upper byte
}

void BuzzerOut(int distance) {}