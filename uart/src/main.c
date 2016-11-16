#include <msp430f1611.h>
#include "blink.h"
#include "printf.h"

int main () 
{
	unsigned char val [] = "Biruk here";
//    uart_init();
    init_mcu();
	uart_init();
//	_BIS_SR(LPM3_bits + GIE);

	while(1) {
    printf_x("Temperature %i \n", 100);
    delay();
	}
return 0;
}
