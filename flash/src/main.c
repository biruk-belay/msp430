#include "printf.h"
#include "uart.h"
#include <msp430f1611.h>

#define TO_INT(x) ((int) (x-48))

unsigned char buffer [64];

void read_flash();
void write_flash();
void erase_flash ();

int  main ()
{
    unsigned char opt;
    uart_init();
    init_flash();
    
    delay();

    while (1) {

        printf_x(" \n Welcome flash console \n");
        printf_x(" Press R for read and W for write and E to erase \n");

        opt= uart_read();                // Read from UART input
        uart_send(opt);                 // Display option on Terminal

        switch (opt) {

            case 'R' | 'r':

            read_flash();
            printf_x ("\n");

            break;

            case 'W' | 'w':

            write_flash();
            break;

            case 'E' | 'e':
            erase_flash();
            break;

            case 'D' | 'd':
            //destroy_ram();
            break;


            default :
            printf_x(" \n Please enter the correct option \n");
            break;
        } 
    
    }
    return 0;
}

void read_flash()
{
    unsigned char block, seg;

    printf_x (" \nEnter the block number \n");
    block= uart_read();    
    uart_send(block);

    printf_x ("\n Enter the seg number \n");
    seg= uart_read();    
    uart_send(seg);

    flash_read_block(TO_INT(block), TO_INT(seg), buffer);
    
    printf_x(" \n%s", buffer);
}

void write_flash()
{

    int i =0;
     char opt, data, seg;
    printf_x (" \n Enter the text \n");

    // Enter the 16 byte text... If entry less than 16 bytes 0's are appended to buffer

    do 
    {       

        buffer[i]= uart_read();

        if(buffer[i] == 0xD) {
            if(i<64)
                for (;i<64;i++)
                    buffer[i]=0;
            break;
        }  
        printf_x("%c", buffer[i]);

    } while (++i<64);

    printf_x ("\n Enter the block number \n");
    opt = uart_read();
    uart_send(opt);
    
    printf_x ("\n Enter the seg number \n");  
    seg = uart_read();
    uart_send(seg);
    
    flash_write_block (TO_INT(opt), TO_INT(seg), buffer); //
}

void erase_flash()
{
    unsigned char seg;

    printf_x ("\n Enter the seg number \n");
    seg = uart_read();
    uart_send(seg);

    flash_erase (TO_INT(seg));
    
    printf_x (" \n Flash Erased \n");
}
