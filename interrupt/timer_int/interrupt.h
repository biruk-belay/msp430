#include <msp430f1611.h>
#include "blink.h"
#define BIT(n) (1<<n)

//volatile int num =0 ;

#define on 1 
#define off 0

#define TIMER_INT_CCR0
#define TIMER_INT_TAIV
 


void init_interrupt ();


