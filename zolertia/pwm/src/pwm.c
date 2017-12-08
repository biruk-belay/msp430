#include <stdint.h>
#include "../include/blink.h"
#include "msp430f2617.h" //use your msp430 configuration!

#define DIM 0
#define BRIGHTEN 1

#define MIN_BRIGHTNESS 100
#define MAX_BRIGHTNESS 9500
#define STEP 10

uint16_t temp;
uint16_t mode = DIM;

void change_led();

void init_mcu()
{
	WDTCTL = WDTPW + WDTHOLD; // disable watch dog
	P1DIR |= 0x40;  // Set P1.6 output
    P1SEL |= 0x40;  // set P1.6 as TA1
    
    TACTL |= TAIE;  //enable interrupt
    TACTL |= TASSEL_2 + MC_1 + ID_0; //1MHz, up mode, div by 1
    TACCR0 = 10000;         //This value sets the frequency of PWM to 50hz
    TACCR1 = 0;             
    TACCTL1  = OUTMOD_3;    //set/Reset method
}

#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void){

        switch (TAIV) {
            case 0xA :
                if((TACCR1 + STEP >= MAX_BRIGHTNESS)) {
                    mode = BRIGHTEN;
                }
                    
                if((TACCR1 - STEP <= MIN_BRIGHTNESS)) {
                    mode = DIM;
                }

                change_led();
                break;

            case 0x2 :
                break;
        }
}

#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0(void)
{
    led_toggle(GREEN_LED);
}

void change_led()
{
    if (mode == DIM)
        TACCR1 += STEP;
    else
        TACCR1 -= STEP;
}
