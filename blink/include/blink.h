#include "msp430f1611.h"


#define RED_LED 1
#define GREEN_LED 2 
#define BLUE_LED 3


void delay ();

void init_mcu() ;

void led_on(int led);

void led_off (int led);

void led_toggle (int led);
