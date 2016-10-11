#include <p18f4520.h>
#include "ConfigRegs_18F4520.h"
#include "xlcd.h"
#include "xlcddelays.h"
#include "LCDWrite.h"

void main( void ){
  
    LCDInitialise();
    LCDLine1Write("Hello World!");
    LCDLine2Write("Hello World!!!");
}