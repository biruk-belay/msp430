#include <msp430f1611.h>
#include "blink.h"
#include "printf.h"

int temp;

void adc_init()
{
    WDTCTL = WDTPW + WDTHOLD;   // disable watch dog
    //P6SEL  = 0x10;              //select pin as ADC
    ADC12CTL0 = ~ENC;
    ADC12CTL0 |= ADC12ON + MSC + SHT0_4; //Multiple conv, sample_time /=adclk
    ADC12CTL0 |= REFON + REF2_5V;  //REF 2.5v enabled
    ADC12CTL1  = ADC12DIV_7 + SHP + CONSEQ_2 ;//Repeat single channel
    ADC12CTL1 |= CSTARTADD_0 + ADC12SSEL_1;
    ADC12MCTL0 = INCH_5+ SREF_1;
    ADC12CTL0 |= ENC +ADC12SC ;/* ADC12TOVIE + ADC12OVIE*/;
    ADC12IE = 0x1;
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC_12()
{
	switch (ADC12IV) {
	
	case 0x6:
        ADC12CTL0 &=~ENC;
        temp = (0.1734* ADC12MEM0) - 282;
        printf_x("temp is %i \n", ADC12MEM0);
        led_toggle(BLUE_LED);
        printf_x ("after toggle \n");
        ADC12CTL0 |=ENC;
       //BIC #CPUOFF+SCG1+SCG0,0(SP) ;
        ADC12IFG &= 0X0;
		break;

	case 0x2:
		led_toggle (RED_LED);
		break;

	default:
	//	led_toggle(BLUE_LED);
		break;
	}
}

int get_temp ()
{
 return temp; 
}
