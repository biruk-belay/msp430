#include <msp430.h>
#include <stdint.h>
#include "msp430f1611.h" //use your msp430 configuration!
#include "blink.h"



int main() {                    // The main function

init_mcu ();

    while (1) {
      
//led_toggle (RED_LED);

//led_toggle (GREEN_LED);

led_toggle (BLUE_LED);
//delay();
}}
