#include <msp430f1611.h>
#include "blink.h"
//#include <stdlib.h>

#define NULL ( (void *) 0)

unsigned char array [] = "HI I am biruk";
unsigned char value ;
static int i =0;

void uart_init ()
{
	P3SEL = 0xC0; 
    U1CTL = SWRST;						//reset software to configure 
    U1TCTL = I2CSSEL_1;					//Select Auxilary clock 32Khz
    U1CTL |= PENA + PEV + CHAR + SPB;	//Even parity,8bits,2stp bits
	U1BR1 = 0X0;						//baud rate 9600
	U1BR0 = 0x3;
    U1MCTL = 0X4A;
    ME2 = UTXE1 + URXE1;				//enable the tx/rx
    U1CTL &= ~SWRST;
    //IE2 = UTXIE1 + URXIE1;				//enable interrupt
}

void uart_send(char val) 
{
    while ((IFG2 &UTXIFG1)==0);
//	led_toggle(GREEN_LED);
    U1TXBUF = val;
}

void uart_send_text(char *ptr)
{
    while (*ptr) {
        uart_send(*ptr);
        ptr++;
	//led_toggle (RED_LED);
    }
}


unsigned char uart_read ()
{
    while ((IFG2 & URXIFG1) == 0);
//	led_toggle (BLUE_LED);
    return U1RXBUF;
}

#pragma vector=UART1TX_VECTOR			//Transmit ISR
__interrupt void UART1TX_ISR()
{	
    U1TXBUF = array[i++];
	led_toggle (RED_LED);
	if (i>13)
		i =0;
//    uart_send();

}

#pragma vector=UART1RX_VECTOR			//Recieve ISR
__interrupt void UART1RX_ISR()
{
	value = U1RXBUF; 
    led_toggle(GREEN_LED);
}
