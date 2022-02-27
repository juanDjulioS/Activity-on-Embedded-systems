/***********************************************************
*  Program to create 10 8-led sequence 
*  This sequence consists in a counting from 0 to 255 k by k
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

const char time=50;
const char n = 8; // number of led/bits
const char k = 25;
//*************** Main Program **********************
int main(void)
{

  //**********Ports Setting **********************
  //Port D as output
  //0xFF = 0b11111111

  DDRD |= 0xFF;

  while(1) // endless loop
  {
    PORTD = 0xFF;
    for (int i = 5; i < pow(2.0,n); i= i + k)
	{
		PORTD = i;
		_delay_ms(time*2);
	}
  }
  return 0;
}//** End of Program
