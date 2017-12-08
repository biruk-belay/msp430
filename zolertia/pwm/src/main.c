#include <msp430f2617.h>
#include "blink.h"
#include "printf.h"

//#define on 1 
//#define off 0

//volatile unsigned int num =0 ;
void main(void)
{
    init_gpio();
    init_mcu ();
//    init_uart();

//led_on(RED_LED);

_BIS_SR(LPM0_bits + GIE); 
}
