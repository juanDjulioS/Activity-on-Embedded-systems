/***********************************************************
*  Program to create 10 8-led sequence 
*  This sequence consists in a counting from 0 to 255 twenty-five by twenty-five
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

const int time=50;
const int n = 8; // number of led/bits

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
	int i = 5;
	while (i < pow(2.0,n))
	{
		PORTD = i;
		_delay_ms(time);//1seg delay
		i = i + 25;
	}
  }
  return 0;
}//** End of Program
