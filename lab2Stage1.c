/***********************************************************************
* a counter from 0 to 9999 ascending using 7 segment display
*  Micro: Atmega328P
*  Date: 5-04-2022
***********************************************************************/
/***************************** Macros *********************************/
#define F_CPU 16000000UL // 16 MHz clock speed
/***************************** Libraries ******************************/
#include <avr/io.h>
#include <util/delay.h> //delay library
/******************* Global Variables Definition **********************/
//common anode (Vcc) representation of each digit
int dec7seg[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xB8,0x80,0x90}; 
// vector to save units, tens, hundreds, and thousands unit of the number
int digits[4] = {0,0,0,0}; 
int td = 4;			// time in which each display must be on
int t_long = 16;	// time in milliseconds that a number should last
int th_mask, hun_mask, ten_mask;
/********************* Functions and subroutines **********************/
// function to do delay with variables
void delayms (int n){
	while(n--){
		_delay_ms(1);
	}
}
// function to break up a number into its digits
void numFragmenter(int num)
{
	unsigned int i = 3;
	while(num != 0)
	{
		digits[i]=num % 10;
		num /= 10;
		i--;	
	}
}
// function to avoid displaying zeros in front of a digit whose power 
// of 10 is less(e.g. 0012 ==> 12)
void redundant_zeros(int d0, int d1, int d2, int d3){
	int th_mask = 0x0E, hun_mask = 0x0D, ten_mask =0x0B;
	if (d0== 0 && (d1 >= d0))
	{
		th_mask = 0xFF;
		if (d1==0 && (d2 >= d1))
		{
			hun_mask = 0xFF;
			if (d2==0 && (d3 >= d2))
			{
				ten_mask = 0xFF;
			}
		}
	}
}
void display(int thousand, int hundred, int ten, int one)
{	
	redundant_zeros(digits[0],digits[1],digits[2],digits[3]);
	PORTB = 0x0E | th_mask;		// enable transistor i-th
	PORTD = thousand;			    // show number
	delayms(td);				// delay a time td
	PORTB = 0x0D | hun_mask;
	PORTD = hundred;
	delayms(td);			
	PORTB = 0x0B | ten_mask;		
	PORTD = ten;
	delayms(td);		
	PORTB = 0x07;	
	PORTD = one;	
	delayms(td);	
}
/************************** Main Program ******************************/		
int main(void)
{
	/*************** variable initialization **************************/
	int init = 9999;
	int count = init;
	/*******************Ports Setting *********************************/
	DDRD  = 0xFF; // as output to turn on/off four digit 7 segment displays
	PORTD = 0xFF; // to enable/disable  PNP transistors 2n3906 (active low)
	DDRB  = 0x0F;
	PORTB = 0x0F;
	while(1)
	{
		if(count < 0) count = init; // restart the counting
		else for(int i=0; i < 4; i++) digits[i] = 0; // reset digits (clear previous value)
		numFragmenter(count);
		for(int i=0; i < t_long/(4*td); i++)
		{ 
			display(dec7seg[digits[0]],dec7seg[digits[1]],dec7seg[digits[2]],dec7seg[digits[3]]);
		}
		count--;
	}
} //** End of Program
