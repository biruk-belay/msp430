#include "uart.h"
#include <stdarg.h>

#define LINE_FEED 0xA
#define CAR_RETURN 0xD

void SWString(unsigned char * string);
void SWUInt(unsigned int dataword);
void SWInt(int num);
void printf_x(const unsigned char *format, ...)
{
	unsigned int pos = 0;
	va_list args;
	va_start(args, format); 

	while(format[pos] != '\0')

	{
		if(format[pos] == '%')
		{
			pos++;

			if(format[pos] == '\0')
			{
				return ;
			}

			switch(format[pos])

			{
				case 'd':
					SWInt(va_arg(args, int));
					break;

				case 'i':
					SWInt(va_arg(args, int));
					break;

				case 'u':
					SWUInt(va_arg(args, unsigned int));
					break;

				case 'c':
					uart_send(va_arg(args, int));
					break;

				case 's':
					SWString(va_arg(args, unsigned char *));
					break;

				default:
					uart_send(format[pos]);
			}}

		else if(format[pos] == '\n')
		{
			uart_send(CAR_RETURN);
			uart_send(LINE_FEED); //On windows New-Line is 'CR+LF'
		}
		else
		{
			uart_send(format[pos]);
		}
		pos++;
	}
    va_end(args);  
	}

	
	void SWString(unsigned char * string)
	{
			uart_send_text( string );
	}

	void SWUInt(unsigned int dataword)
	{
		//NOTE : Source code for this function has been derived from Internet.
	unsigned char buffer[11];
	char temp;
	unsigned int count;
	unsigned int len;
	unsigned int halflen;
	//size = 1;

	if(dataword == 0)
	{
		buffer[0] = '0';
		buffer[1] = '\0';
	}
	else

	{
		for(count = 0; count < 10; count++)
		{
			buffer[count] = (dataword % 10) + 48;
			dataword /= 10;

			if (dataword == 0)
				break;}

		buffer[count + 1] = '\0';
		len = count;
		halflen = (len + 1) / 2;

		for(count = 0; count < halflen; count++)
		{
			temp = buffer[count];
			buffer[count] = buffer[len];
			buffer[len] = temp;
			len -= 1;
		}}

		SWString(buffer);
	}

	void SWInt(int num)
		{
	if(num < 0)
		{
		uart_send('-');
		SWUInt(-num);
	}

	else
		SWUInt(num);
}

