
#include <p18f4520.h>           

//performs any config required for encoders
void SetupEncoders(void) {
    TRISCbits.RC0 = 1;
    TRISD = 0;
    PORTD = 0;
    //16-bit counter wheel 1
    T0CONbits.TMR0ON = 1;
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 1;
    T0CONbits.T0SE = 0;
    T0CONbits.PSA = 1;
    
    //ADCON1bits.PCFG0 = 1;
    //ADCON1bits.PCFG1 = 1;
    //ADCON1bits.PCFG2 = 0;
    //ADCON1bits.PCFG3 = 1;
    TRISAbits.RA4 = 1;
      
    //16-bit counter wheel 2
    T1CONbits.RD16 = 0;
    T1CONbits.T1RUN = 0;
    T1CONbits.T1CKPS0= 0;
    T1CONbits.T1CKPS1= 0;
    T1CONbits.T1OSCEN = 0;
    T1CONbits.T1SYNC = 1;
    T1CONbits.TMR1CS = 1;
    T1CONbits.TMR1ON = 1;
}

// Read encoder values
void sampleEncoders(int* encoderValues) {
    int wheel1_counterl,wheel1_counterh,wheel2_counterl,wheel2_counterh;
}

