#include <msp430f1611.h>
#include "blink.h"
#include "interrupt.h"

volatile int i =0;

 
void init_interrupt () {

#ifdef PORT2_INT

P2IES |= BIT(7);   // Output
P2IE  |= BIT(7);
#endif

#ifdef PORT1_INT

#endif

}


#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void) {

if (++i %2 !=0)

led_on(BLUE_LED);
else

led_off (BLUE_LED);


P2IFG &= ~0X80;
_BIS_SR(LPM3_bits + GIE);
}
