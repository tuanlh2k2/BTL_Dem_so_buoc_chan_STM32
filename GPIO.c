#include "GPIO.h"

void init_GP(unsigned short port, unsigned short pin, unsigned short dir, unsigned short opt)
{
 volatile unsigned long * CR;
 unsigned short tPIN = pin;
 unsigned short offset = 0x00;
	
	if(pin > 7)
		{
			tPIN -= 8;
			offset = 0x01;
		}
		
	if(port == 1)
		{
			RCC_APB2ENR |= 4; //// Enabling PORT A
			CR = (volatile unsigned long *) (&GPIO_A + offset);
		}
	else if(port == 2)
		{
			RCC_APB2ENR |= 8; //// Enabling PORT B
			CR = (volatile unsigned long *) (&GPIO_B + offset);
		}
	else if(port == 3)
		{
			RCC_APB2ENR |= 0x10; //// Enabling PORT C
			CR = (volatile unsigned long *) (&GPIO_C + offset);
		}
		
		*CR &= ~(0xf<<(tPIN)*4); ///Reset the taget pin
		*CR |= ((dir <<(tPIN*4)) | (opt<<(tPIN*4+2))); //// Set up the direction and the option of the PIN
}