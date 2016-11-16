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

//#define SEG_SIZE 128

void init_flash()
{

     IE1 = ACCVIE; 
}

void flash_write_single(int block, int seg, int val)
{
   unsigned int * address;

    address = (int *) ((block * BLOCK_SIZE) +
                                (seg * SEG_SIZE) + START_ADDR);

    printf_x(" \n write address is %i \n", address);

    FCTL3 = FWKEY;      //UNLOCK
    FCTL2 = FWKEY + FSSEL_1 + FN2;
    FCTL1 = FWKEY + WRT;
    *address = val;
    FCTL1 = FWKEY;
    FCTL3 = FWKEY + LOCK;
    printf_x(" char is %i \n",address);

}

void flash_write_block(int block, int seg,  unsigned char *val)
{
    unsigned char *address;
    int i;
 
    address = (unsigned char *) ((block * BLOCK_SIZE) +
                                 (seg * SEG_SIZE) + START_ADDR);

    while (*val) {
    FCTL2 = FWKEY + FSSEL_1 + FN2;
    
    while (FCTL3 & BUSY);

    FCTL3 = FWKEY;                  //UNLOCK
    FCTL1 = FWKEY + WRT;

    *address  = *val;

    address +=1;
    val +=1;
 
    printf_x(" char is %i \n", address);
    printf_x(" seg size is %i \n", SEG_SIZE);

    FCTL1 = FWKEY;
    while (FCTL3 & BUSY);
    FCTL3 = FWKEY + LOCK;
    delay ();    
}

}

void flash_read_block(int block, int seg, unsigned char *buffer)
{   
    int i;
    unsigned char *address;
    address = (unsigned char *) ((block * BLOCK_SIZE) + 
                                (seg * SEG_SIZE) + START_ADDR);
//    FCTL2 = FWKEY + FSSEL_1 + FN0;
    printf_x(" char is %i \n", address);
    while (*buffer) { 
        *buffer = *address;
        buffer+=1;
        address+=1;
    }

    printf_x(" %s \n", buffer);
}

void flash_erase(unsigned int seg)
{    
    FCTL2 = FWKEY + FSSEL_1 + FN2;
    unsigned int *address;
    address = (int *) ((seg * SEG_SIZE) + START_ADDR);

    printf_x("read address is %i", address);

    FCTL3 = FWKEY;      //UNLOCK
    FCTL1 = FWKEY + ERASE;// + MERAS;
    *(address +1 ) = 0;
    
    while (FCTL3 & BUSY);
     //   printf_x("waiting \n");
    //FCTL1 = FWKEY;
    FCTL3 = FWKEY + LOCK;
}

#pragma vector = NMI_VECTOR 
__interrupt void nmi()
{
    if (FCTL3 & ACCVIFG) {
        led_toggle(RED_LED);
        FCTL3 &= ~ACCVIFG;
        IE1 |= ACCVIE;
    }

}
/*
void destroy_ram()
{
    unsigned char *address = (unsigned char *) 0x1100;

    while (address <0x4000) {
        *address = 0;
        address +=1; 
    }
}*/
