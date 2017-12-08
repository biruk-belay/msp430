#include <stdint.h>
#include "blink.h"

void delay () 
{
    int i =0;
    for (; i<10000; i++ );

//  return 0;
}

void init_gpio()
{
    WDTCTL = WDTPW + WDTHOLD; // disable watch dog
    P5DIR |= 0x70 ; // set P5.4, P5.5 & P5.6 as outputs
    P5OUT  = 0x70;   // all leds off
}

void led_on(int led) 
{
    if (led == RED_LED)
        P5OUT &=0XEF;

    if (led == GREEN_LED)
        P5OUT &= 0XDF;

    if (led == BLUE_LED)
        P5OUT &= 0XBF;
    
    if (led == PIN_1)
        P1OUT &= 0XBF;
    
    
}

void led_off (int led) 
{
    if (led == RED_LED)
        P5OUT |=0X10;

    if (led == GREEN_LED)
        P5OUT |=0X20;
    
    if (led == BLUE_LED)
        P5OUT |= 0X40;
    
    if (led == PIN_1)
        P1OUT |= 0X40;
}

void led_toggle (int led) 
{
    int temp = led;

    led_on (temp);
    delay();

    led_off (temp);  
    delay();
}
