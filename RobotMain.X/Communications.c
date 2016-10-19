void commsSetup(void) {
    
}


char transmitData(int* IRVals,char signalStrength,char processComplete) {
    
}

/*Called during receive interrupt to store data in buffer, sets flag high*/
char receiveData(char* buffer){
    return 1;
}

/*Parses the receive buffer and modifies the instructions and instruction flag*/
char processReceived(char* buffer, int* instMag,char* instDir,char* commandFlag) {
    
}