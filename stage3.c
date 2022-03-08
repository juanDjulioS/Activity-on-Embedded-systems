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
void seq(int, int []);
void getPos();
void delayms(int);

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

const short n = 10; // number of sequences
int pos = 0;
// variable to alternate the sequence, or equivalently to
// identify it (1 = sequence 1, 2 = sequence 2)
char alt = 0;	// no sequence
int sequence1[] = {103,205,307,409,511,612,714,816,918,1023};
int sequence2[] ={13,21,34,55,89,144,233,377,610,987};
int velocities[] = {100,80,60,50,10};
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
						
	while(1){ // endless loop
		PORTC = 0x00;
		// if button is pressed,toggle alt
		if (buttonSeq1){
			_delay_ms(250); // wait for possible signal debouncing
			alt = 1;
		}
		if (buttonSeq2)
		{
			_delay_ms(250);
			alt = 2;
		} 		
//************************* execution of sequences *********************** 
		if (alt == 1) seq(buttonSeq2,sequence1);
		if (alt == 2) seq(buttonSeq1,sequence2);
	}	  
	return 0;
}//** End of Program

void seq(int c, int vec[]){
	PORTD = 0x00;
	PORTB = 0x00;
	for (int i = 0; i < n-2; i++)
	{
		
		if (c){
			break;
		}
		else {
			if (incrVel || decrVel)
			{
				getPos();
			}
			if (vec[i]>256)
			{
				PORTD = vec[i] & 0xFF;
				PORTB =vec[i] >> (n-2);
				delayms(velocities[pos]);
			}
			else
			{
				PORTD = vec[i];
				delayms(velocities[pos]);
			}
		}
	}
}
void getPos(){
	if (incrVel)
	{
		_delay_ms(250);
		pos++;
	}
	if (decrVel)
	{
		_delay_ms(250);
		pos--;
	}
	if (pos<0) pos = 0;
	if (pos>4) pos = 4;
}
void delayms(int n){
	// delayms(200) == 20 veces llamar _delay_ms(10)
	for (int i = 0; i < n; i++)
	{
		_delay_ms(1);
	}
}
