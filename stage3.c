/***********************************************************
*  Program to alternate between two 8-led sequences with two buttons, 
*  and to change between five velocities with two buttons
*  Micro: Atmega328P
*  Date: 24-02-2022
************************************************************/

//*************** Macros **********************************
#define F_CPU 16000000UL // 16 MHz clock speed


//*************** Libraries *******************************
#include <avr/io.h> // avr library
#include <util/delay.h>  //delay library


//*************** Functions and subroutines ******************
void seq1();
void seq2();

/************************************************************** 
*  Pin-reading definition through a macro #define
*  PDx depict pin Dx
*  #define <nameMacro> (port & (1<<portPin))>>portPin
***************************************************************/
#define buttonSeq1 (PINC & (1<<PC5))>>PC5
#define buttonSeq2 (PINC & (1<<PC4))>>PC4
#define incrVel (PINC & (1<<PC3))>>PC3
#define decrVel (PINC & (1<<PC2))>>PC2
//********** Global variables definition  ***********

const short time=50;
const short n = 10; // number of sequences
//*************** Main Program **********************
int main(void)
{
	//**********Ports Setting **********************
	//Port D as output
	//0xFF = 0b11111111
	//PORT B as output
	//0xFF = 0b11111111
	//PORT C as input
	//0x00 = 0b00000000

	DDRD |= 0xFF;
	DDRB |= 0xFF;
	DDRC |= 0x00;
	// variable to alternate the sequence, or equivalently to 
	// identify it (0 = sequence 1, 1 = sequence 2)
	char alt = 0;									
  
	while(1){ // endless loop
		PORTC = 0x00;
		// if button is pressed,toggle alt
		if (buttonSeq1){
			_delay_ms(250); // wait for possible signal debouncing
			alt = 1;
		}					
												
		// if alt = 0 run sequence 1
		if (alt == 0) seq1();					
	  
		// if alt = 1 run sequence 2 and then check out if button 
		// has been pressed again, in that case turn alt to zero.
		if (alt == 1){									
			seq2();
			if (buttonSeq1){
				_delay_ms(250);
				alt = 0;
			}
		}
	}	  
	return 0;
}//** End of Program

void seq1(){
	int sequence1[] = {103,205,307,409,511,612,714,816,918,1023};
	PORTD = 0x00;
	PORTB = 0x00;
	for (int i = 0; i < n; i++)
	{
		// if button is pressed while sequence is running,
		// then stop and return to main loop to check the state of alt
		if (buttonSeq1) {
			break;
		}
		else {
			if (i>1)
			{
				PORTD = sequence1[i] & 0xFF;
				PORTB = sequence1[i] >> (n-2);
				_delay_ms(time); //delay of 'time' milliseconds between sequences
			} 
			else
			{
				PORTD = sequence1[i];
				_delay_ms(time);
			}
		}
	}
}
void seq2(){
	int sequence2[] ={13,21,34,55,89,144,233,377,610,987};
	PORTD = 0x00;
	PORTB = 0x00;
	for (int i = 0; i < n-2; i++)
	{
		
		if (buttonSeq1){
			break;
		}
		else {
			if (i>6)
			{
				PORTD = sequence2[i] & 0xFF;
				PORTB = sequence2[i] >> (n-2);
				_delay_ms(time); //delay of 'time' milliseconds between sequences
			}
			else
			{
				PORTD = sequence2[i];
				_delay_ms(time);
			}
		}
	}
}
