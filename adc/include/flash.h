#include <msp430f1611.h>

void flash_write_single(int block, int seg, int val);
void flash_write_block(int block, int seg, unsigned char *val);
void flash_read_single(int block, int seg, int*);
void flash_read_block(int block, int seg, unsigned char *);  
void flash_erase(unsigned int); 
void init_flash();
void destroy_ram();


