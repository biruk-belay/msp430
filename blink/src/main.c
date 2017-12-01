#include <msp430.h>
#include <stdint.h>
#include "blink.h"



int main() {                    // The main function

init_mcu ();
// _BIS_SR(LPM4_bits + GIE);

    while (1) {  
    led_toggle(RED_LED);
    //led_on (BLUE_LED);
    //led_on (GREEN_LED);
    //delay();
    //led_off (RED_LED);
    }
}
