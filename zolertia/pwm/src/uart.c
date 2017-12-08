#include <msp430f2617.h>
//#include <stdlib.h>

#define NULL ( (void *) 0)

void init_uart ()
{
	P3SEL    = 0xC0; 
    UCA1CTL1 = UCSWRST;						//reset software to configure 
    UCA1CTL1 |= UCSSEL_1;
    UCA1CTL0 |= UCPEN + UCSPB + UCPAR;
    UCA1BR1  = 0x0;
    UCA1BR0  = 0x3;
    UCA1MCTL = 0x6;
    UCA1CTL1 &= ~UCSWRST;
    UCA1TXBUF = 0x1;
    /*
    U1TCTL = I2CSSEL_1;					//Select Auxilary clock 32Khz
    U1CTL |= PENA + PEV + CHAR + SPB;	//Even parity,8bits,2stp bits
	U1BR1 = 0X0;						//baud rate 9600
	U1BR0 = 0x3;
    U1MCTL = 0X4A;
    ME2 = UTXE1 + URXE1;				//enable the tx/rx
    U1CTL &= ~SWRST;
    //IE2 = UTXIE1 + URXIE1;				//enable interrupt
*/
}

void uart_send(unsigned char val) 
{
    while ((UC1IFG & UCA1TXIFG) == 0);
    UCA1TXBUF = val;
}

void uart_send_text(unsigned char *ptr)
{
    while (*ptr) {
        uart_send(*ptr);
        ptr++;
    }
}

unsigned char uart_read ()
{
    while ((UC1IFG & UCA1RXIFG) == 0);
    return UCA1RXBUF;
}
