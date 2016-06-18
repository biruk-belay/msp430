#include <msp430f1611.h>
//#include "blink.h"
#include <msp430.h>
#include "interrupt.h"

unsigned int inter;

//#define PORT2_INT 1
 

void main (void) {
init_mcu ();

init_interrupt ();


_BIS_SR(LPM3_bits + GIE);


while (1);
//_BIS_SR(LPM3_bits + GIE);


}

