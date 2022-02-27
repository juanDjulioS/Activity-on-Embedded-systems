/***********************************************************
*  Program to alternate between twos 8-led sequences 
*  These sequences consist in some terms of Fibonacci sequence (sequence 1)
*  and a counting from 0 to 255 (sequence 2) k by k
*  Micro: Atmega328P
*  Date: 24-02-2022
************************************************************/

//*************** Macros **********************************
#define F_CPU 16000000UL // 16 MHz clock speed


//*************** Librerias *******************************
#include <avr/io.h> // avr library
#include <util/delay.h>  //delay library


//*************** Functions and subroutines ******************
void seq1();
void seq2();


/************************************************************** 
 *  Pin-reading definition through a macro #define
 *  PD2 depict pin D2
 *  #define <nombremacro> (port & (1<<pinpuerto))>>pinpuerto
 ***************************************************************/

#define pulsador0 (PINC & (1<<PC5))>>PC5

//********** Global variables definition  ***********

const int time=50;
const int n = 8; // number of led/bits
const int k = 25; // to count in step by step
//*************** Main Program **********************
int main(void)
{

  //**********Ports Setting **********************
  //Port D as output
  //0xFF = 0b11111111
  //PORT C as input
  // 0b00000000 = 0x00 

  DDRD |= 0xFF;
  DDRC |= 0x00;
  char alt = 0;     									// variable to alternate the sequence, or equivalently to identify it (0 = sequence 1, 1 = sequence 2)
  
  while(1){ // endless loop
	  PORTC = 0x00;
	  PORTD = 0x00;
	  if (pulsador0)
	  {
		  alt = 1;
	  }
													// if button is pressed,toggle alt
	  if (alt == 0) seq1();							// if alt = 0 run sequence 1 but, check out if button has been pressed again
	  if (alt == 1)
	  {												//to turn alt again to zero, if that's not the case, run sequence 2
		  seq2();
		  if (pulsador0)
		  {
			  alt = 0;
		  }
	  }
  }
	  
  return 0;
}//** End of Program

void seq1(){
	int FibTerms[10] ={3,5,8,13,21,34,55,89,144,233};
	for (int i = 0; i < 10; i++)
	{
	 // if button is pressed while sequence is running, then stop to return to main loop and check the state of alt
		if (pulsador0) 
		{
			break;
		} 
		else
		{
			PORTD = FibTerms[i];
			_delay_ms(time); //delay of 'time' milliseconds
		}
	}	
}
void seq2(){
	for (int i = 5; i < pow(2.0,n); i= i + k)
	{
		if (pulsador0)
		{
			break;
		}
		else
		{
			PORTD = i;
			_delay_ms(time*2);
		}
	}
}

