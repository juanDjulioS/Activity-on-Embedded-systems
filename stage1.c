/***********************************************************
*  Program to create 10 sequences with 8 leds
*  Micro: Atmega328P
*  Date: 17-02-2022
************************************************************/

//*************** Macros **********************************
#define F_CPU 16000000UL // 16 MHz clock speed


//*************** Librerias *******************************
#include <avr/io.h> // avr library
#include <util/delay.h>  //delay library


//*************** Functions and subroutines ******************



//********** Global variables definition  ***********
const char n = 10; // number of sequences
const short time=50; // time to delay
//*************** Main Program **********************
int main(void)
{
	short sequence1[] = {5,15,45,75,105,135,165,195,225,255};
	//**********Ports Setting **********************
	//Port D as output
	//0xFF = 0b11111111

	DDRD |= 0xFF;

	while(1) // endless loop
	{
		PORTD = 0x00;
		for (short i = 0; i < n; i++)
		{
			PORTD = sequence1[i];
			_delay_ms(time);
		}
	}
return 0;
}//** End of Program
