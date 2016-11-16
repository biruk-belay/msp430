#include <msp430f1611.h>
#include "blink.h"
#include <msp430.h>

#define on 1 
#define off 0

volatile int i = on , j =0; 

void main(void)
{
WDTCTL = WDTPW + WDTHOLD;   

//P1DIR |= 0x04;   // Output
//P1SEL |= 0x04;   // TA1 option
//P2DIR |= 0x01;   // Output
//P2SEL |= 0x01;   // TA2 option
TACCR0 = 0xFF6F-1;   // PWM Period
TACCTL0 |= 0x10 ;   // Reset/set

TACTL |= TAIE;// Reset/set
//TACCTL0 &= ~0x1;

//TACCR1 = 35000;      // Duty cycle
//TACCTL1 |= CCIE;      // Reset/set


//TACCR1 = CCIE ;      // Duty cycle
//TACTL &= ~0x1;


TACTL |= TASSEL_1 + MC_2 + ID_0 ; 

init_mcu ();




led_on(RED_LED);

_BIS_SR(LPM3_bits + GIE);

while (1);
}

/*
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A(void) {
*/


#pragma vector=TIMERA1_VECTOR

__interrupt void Timer_A1(void)
//if (TAIV & 0xA){
{

if (i == on)
{
led_on(BLUE_LED);
i = off;
}

else
{

led_off (BLUE_LED);
i = on;

}


TAIV & ~0xA;
//TACCTL1 &= ~0X1; 
_BIS_SR(LPM3_bits + GIE);

//}



//if (i == 0xFFFF -1)
//i=0;

//TACCTL0 &= ~0x1;
//_BIS_SR(LPM3_bits + GIE);




//if (i == 0xFFFF)
//i=0;
}



#pragma vector=TIMERA0_VECTOR

__interrupt void Timer_A0(void)
{
if (i == on)
{
led_on(BLUE_LED);
i = off;
}

else
{

led_off (BLUE_LED);
i = on;

}
_BIS_SR(LPM3_bits + GIE);

}  
