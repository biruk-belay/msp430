#include <msp430f1611.h>
#include "blink.h"
#include <msp430.h>
#include "interrupt.h"


//#define on 1 
//#define off 0

//volatile unsigned int num =0 ;
void main(void)
{
init_mcu ();
init_interrupt ();

//led_on(RED_LED);

_BIS_SR(LPM3_bits + GIE);

while (1);
}


 
