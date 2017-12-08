#include <msp430f2617.h>
#include "blink.h"
#include "printf.h"

void main(void)
{
    init_gpio();
    init_mcu ();

_BIS_SR(LPM0_bits + GIE); //low power mode_0
}
