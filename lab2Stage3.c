/***********************************************************************
* a descending counter from 9999 to 0 using a four-digit 7 segment
* display and buttons to START, STOP and RESET the counting. a PROGRAM 
* button to change the initial value of the counting (and additionally, 
* speed up the counter) when is pressed.
* Micro: Atmega328P
* Date: 7-04-2022
***********************************************************************/
/***************************** Macros *********************************/
#define F_CPU 16000000UL // 16 MHz clock speed
#define START (PINC & (1<<PC5))
#define RESET (PINC & (1<<PC2))
#define STOP (PINC & (1<<PC3))
#define PROGRAM (PINC & (1<<PC4))
/***************************** Libraries ******************************/
#include <avr/io.h>
#include <util/delay.h> //delay library

/******************* Global Variables Definition **********************/
//common anode (Vcc) representation of each digit
int dec7seg[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

// vector to save units, tens, hundreds, and thousands unit of the number
int digits[4] = {0,0,0,0}; 
int td = 5;			// time in which each display must be on
int t_base = 1000;	// time in milliseconds that a number should last
int th_mask = 0x0E, hun_mask = 0x0D, ten_mask =0x0B;
int start_f, stop_f;
int speed_up_t = 20;
int init = 9999;

/********************* Functions and subroutines **********************/

// function to do delays with variables
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
	PORTB = 0x0E | th_mask;		    // enable transistor i-th
	PORTD = thousand;				// show number
	delayms(td);				    // delay a time td
	PORTB = 0x0D | hun_mask;
	PORTD = hundred;
	delayms(td);			
	PORTB = 0x0B | ten_mask;		
	PORTD = ten;
	delayms(td);		
	PORTB = 0x07;	
	PORTD = one;	
	delayms(td);
	th_mask = 0x0E, hun_mask = 0x0D, ten_mask =0x0B; // reset mask
}

/************************** Main Program ******************************/		
int main(void)
{
	/*************** variable initialization **************************/

	int count = init;
	int new_init = init;
	int t_long = t_base;
	int current_count = count;
	/*******************Ports Setting *********************************/
	DDRD |= 0xFF; // as output to turn on/off four digit 7 segment displays
	PORTD = 0xFF; // to enable/disable  PNP transistors 2n3906 (active low)
	DDRB  = 0x0F;
	PORTB = 0x0F;
	DDRC |= 0x00;  //  all as input
	
	while(1)
	{
		if (START) {start_f = 1; stop_f = 0;}
		if (start_f == 1)
		{
			if(count < 0 || RESET)
				{
					if (new_init == 0) count = init; // restart the counting
					else count = new_init;
				}
		
			else for(int i=0; i < 4; i++) digits[i] = 0; // reset digits (clear previous value)
			numFragmenter(count);
			for(int i=0; i < t_long/(4*td); i++)
			{
				display(dec7seg[digits[0]],dec7seg[digits[1]],dec7seg[digits[2]],dec7seg[digits[3]]);
			}
			if (STOP) stop_f = 1;
			if (PROGRAM) {current_count = count; t_long = speed_up_t;}
			else t_long = t_base;
			if (t_long == t_base) new_init = current_count;
			if (!stop_f) count--;
		}
	}
} //** End of Program
