/***********************************************************
*  Program to alternate between two 8-led sequences when a
*  button is pressed
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
*  PD2 depict pin D2
*  #define <nameMacro> (port & (1<<portPin))>>portPin
***************************************************************/

#define pulsador0 (PINC & (1<<PC4))>>PC4

//********** Global variables definition  ***********

const short time=50;
const short n = 10; // number of sequences
//*************** Main Program **********************
int main(void)
{
	//**********Ports Setting **********************
	//Port D as output
	//0xFF = 0b11111111
	//PORT C as input
	//0x00 = 0b00000000

	DDRD |= 0xFF;
	DDRC |= 0x00;
	// variable to alternate the sequence, or equivalently to 
	// identify it (0 = sequence 1, 1 = sequence 2)
	char alt = 0;									
  
	while(1){ // endless loop
		PORTD = 0x00;
		PORTC = 0x00;
	  
		// if button is pressed,toggle alt
		if (pulsador0){
			_delay_ms(250); // wait for possible signal debouncing
			alt = 1;
		}					
												
		// if alt = 0 run sequence 1
		if (alt == 0) seq1();					
	  
		// if alt = 1 run sequence 2 and then check out if button 
		// has been pressed again, in that case turn alt to zero.
		if (alt == 1){									
			seq2();
			if (pulsador0){
				_delay_ms(250);
				alt = 0;
			}
		}
	}	  
	return 0;
}//** End of Program

void seq1(){
	int sequence1[] = {25,50,75,100,125,150,175,200,225,250};
	for (int i = 0; i < n; i++)
	{
		// if button is pressed while sequence is running, 
		// then stop and return to main loop to check the state of alt
		if (pulsador0) {
			break;
		}
		else {
			PORTD = sequence1[i];
			_delay_ms(time); //delay of 'time' milliseconds between sequences
		}
	}
}
void seq2(){
	int sequence2[] ={3,5,8,13,21,34,55,89,144,233};
	for (int i = 0; i < n; i++)
	{
		
		if (pulsador0){
			break;
		}
		else {
			PORTD = sequence2[i];
			_delay_ms(time);
		}
	}
}

