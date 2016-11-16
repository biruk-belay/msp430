#include <msp430f1611.h>
//#include "blink.h"
#include "uart.h"
#include "adc.h"
#include "printf.h"

void main ()
{
	init_mcu();
	uart_init();
	adc_init();
	
	_BIS_SR(LPM0_bits + GIE);   	
}
