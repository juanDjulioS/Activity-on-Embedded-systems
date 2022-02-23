/***********************************************************
*  Program to create a 8-led sequence 
*  This sequence consists in a counting from 0 to 255
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

const int time=1000;
const int n = 8; // number of led/bits

//*************** Main Program **********************
int main(void)
{

  //**********Ports Setting **********************
  //Port D as output
  //0xFF = 0b11111111

  DDRD |= 0xFF;

  while(true) // endless loop
  {
    PORTD = 0xFF;
    for (int i = 0; i < pow(2.0,n); i++)
    {
      PORTD = i;
      _delay_ms(time);//1seg delay
    }
  }
  return 0;
}//** End of Program
