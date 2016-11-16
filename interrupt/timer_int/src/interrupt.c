#include <msp430f1611.h>
#include "blink.h"
#include "interrupt.h"

volatile unsigned int flag_TAIFG =0 ;
volatile unsigned int flag_CCR0 =0 ;
volatile unsigned int flag_CCR1 =0 ;

 
void init_interrupt () {

#ifdef PORT2_INT

P2IES |= BIT(7);   // Output
P2IE  |= BIT(7);

#endif

#ifdef PORT1_INT
/*

*/
#endif


#ifdef TIMER_INT_TAIV

TACTL |= TAIE;       // enable TAIFG
TACCR1 = 44000;      // Duty cycle
TACCTL1 |= CCIE;      // enable CCIFG

#endif


#ifdef TIMER_INT_CCR0

TACCR0 = 22000;   // duty cycle
TACCTL0 |= 0x10 ;   // enable CCIFG
TACTL |=TAIE;

#endif

TACTL |= TASSEL_1 + MC_2 + ID_0 ;
}



/*

Interrupt handler for the low priority interrupt sources i.e TAIFG, CCIFG1, CCIFG2

*/
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void){

switch (TAIV) {

    case 0xA :	//if source is the TAIFG
    
        if (flag_TAIFG == on) {
            led_on(RED_LED);
            flag_TAIFG = off;
        }   


        else {

            led_off (RED_LED);
            flag_TAIFG = on;

        }

        break ;


    case 0x2 :	// if source is CCR1
        if (flag_CCR1 == on) {
           led_on(GREEN_LED);
           flag_CCR1= off;
        }


        else
        {
            led_off (GREEN_LED);
            flag_CCR1 = on;

        }

        break;

//TAIV & ~0xB;	

_BIS_SR(LPM3_bits + GIE);
}}


#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0(void)
{


    if (flag_CCR0 == on){
        led_on(BLUE_LED);
        flag_CCR0 = off;
    }


    else
    {

        led_off (BLUE_LED);
        flag_CCR0 = on;

    }
_BIS_SR(LPM3_bits + GIE);

}


