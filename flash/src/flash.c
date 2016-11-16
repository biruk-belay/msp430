#include "flash.h" 
#include "printf.h"
#include "blink.h"

#define BLOCK_SIZE  64
#define START_ADDR 0xFA00

#if START_ADDR == 0x1000
#define SEG_SIZE 128
#else 
#define SEG_SIZE 512
#endif

void init_flash()
{

     IE1 = ACCVIE; //Enable NMI
}

/* Write Block
  --calculate the address based on block number & seg number
  --BLKWRT isn't possible since code is on flash so write each char
 */

void flash_write_block(int block, int seg,  unsigned char *val)
{
    unsigned char *address;
    int i;

/* Calculate the block address */ 
    address = (unsigned char *) ((block * BLOCK_SIZE) +
                                 (seg * SEG_SIZE) + START_ADDR);

    while (*val) {
    FCTL2 = FWKEY + FSSEL_1 + FN2; //Mclk divided by 3 (~330KHZ)
    
    while (FCTL3 & BUSY);         //Loop while flash is busy

    FCTL3 = FWKEY;                //unlock
    FCTL1 = FWKEY + WRT;          //configure write 

    *address  = *val;             //write to address

    address +=1;
    val +=1;
 
    FCTL1 = FWKEY;                //Clear write
    while (FCTL3 & BUSY);
    FCTL3 = FWKEY + LOCK;         //lock
    delay ();                     //wait for a while before writing again
    }   

}
/* Read a block
   --calculate the address based on the block & seg numbers
*/

void flash_read_block(int block, int seg, unsigned char *buffer)
{   
    int i;
    unsigned char *address;
    address = (unsigned char *) ((block * BLOCK_SIZE) + 
                                (seg * SEG_SIZE) + START_ADDR);

     while (*buffer) {          //Read until string termination
         *buffer = *address;
         buffer+=1;
         address+=1;
    }

    printf_x(" %s \n", buffer);
}

/* Erase a segment */

void flash_erase(unsigned int seg)
{    
    FCTL2 = FWKEY + FSSEL_1 + FN2;  // MCLK div by 3 (~330KHZ)
    unsigned int *address;
    address = (int *) ((seg * SEG_SIZE) + START_ADDR);//calulate segment

    FCTL3 = FWKEY;          //unlock
    FCTL1 = FWKEY + ERASE;  //set erase;
    *(address +1 ) = 0;     //write to a random byte in the address space
    
    while (FCTL3 & BUSY);   //Wait
    FCTL3 = FWKEY + LOCK;   //lock and finish
}

/* NMI Interrupt handler for ACCVIFG (cpu trying to access while flash is busy)*/

#pragma vector = NMI_VECTOR 
__interrupt void nmi()
{
    if (FCTL3 & ACCVIFG) {
        led_toggle(RED_LED); //Toggle led
        FCTL3 &= ~ACCVIFG;   //reset flag
        IE1 |= ACCVIE;      //Enable the interrupt again 
    }
}

/*Write 0 to the whole ram */

/* 
void destroy_ram()
{
    unsigned char *address = (unsigned char *) 0x1100;

    while (address <0x4000) {
        *address = 0;
        address +=1; 
    }
}*/
