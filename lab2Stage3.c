/***********************************************************************
* a descending counter from 9999 to 0 using a four-digit 7 segment
* display and buttons to START, STOP and RESET the counting. a PROGRAM 
* button to change the initial value of the counting, and additionally, 
* a button to speed up the counter.
* Micro: Atmega328P
* Date: 7-04-2022
***********************************************************************/
/***************************** Macros *********************************/
#define F_CPU 16000000UL // 16 MHz clock speed
#define START (PINC & (1<<PC5))
#define RESET (PINC & (1<<PC2))
#define STOP (PINC & (1<<PC3))
#define SPEED (PINC & (1<<PC4))
#define PROGRAM (PINC & (1<<PC1))
/***************************** Libraries ******************************/
#include <avr/io.h>
#include <util/delay.h> //delay library

/******************* Global Variables Definition **********************/
//common anode (Vcc) representation of each digit
uint8_t dec7seg[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

// vector to save units, tens, hundreds, and thousands unit of the number
uint8_t digits[4]; 
short td = 5;			// time in which each display must be on
short t_base = 1000;	// time in milliseconds that a number should last
uint8_t th_mask = 0x0E, hun_mask = 0x0D, ten_mask =0x0B;
uint8_t start_f, stop_f;   // f_ means "flag"
uint8_t speed_f;
uint8_t speed_up_t = 20;
short init = 9999;

/********************* Functions and subroutines **********************/

// function to do delays with variables
void delayms (short n){
	while(n--){
		_delay_ms(1);
	}
}

// function to break up a number into its digits
void numFragmenter(short num)
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
void redundant_zeros(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3){
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

// function to let speed up or not the velocity of the counting
void debounce_speed_button(uint8_t BUTTON){
	static unsigned char count = 0;
	static unsigned char button_state = 0;
	if (BUTTON != button_state)
	{
		count++;
		if (count >= 4)
		{
			button_state = BUTTON;
			if (BUTTON != 0) speed_f = 1;
			count = 0;
		}
	}
	else count = 0;
}

void display(uint8_t thousand, uint8_t hundred, uint8_t ten, uint8_t one)
{
	redundant_zeros(digits[0],digits[1],digits[2],digits[3]);
	PORTB = 0x0E | th_mask;			// enable transistor i-th
	PORTD = thousand;			// show number
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
	th_mask = 0x0E, hun_mask = 0x0D, ten_mask =0x0B; // reset mask
}

/************************** Main Program ******************************/		
int main(void)
{
	/*************** variable initialization **************************/
	short count = init;
	short new_init = init;
	short t_long = t_base;
	uint8_t on_off_speed = 0;
	short current_count = count;
	/*******************Ports Setting *********************************/
	DDRD |= 0xFF; // as output to turn on/off four digit 7 segment displays
	PORTD = 0xFF; 
	DDRB  = 0x0F; // to enable/disable  PNP transistors 2n3906 (active low)
	PORTB = 0x0F;
	DDRC |= 0x00;  //  all as input (buttons with pull-down resistors)
	
	while(1)
	{	
		if (START) {start_f = 1; stop_f = 0;}
		if (start_f == 1)
		{	
			if (count < 0 || RESET)
			{
				if (new_init == 0) count = init; // restart the counting to the initial value
				else count = new_init;			// restart to the new initial value
			}
			for(int i=0; i < 4; i++) digits[i] = 0; // reset digits (clear previous value)
			numFragmenter(count);					// break up the number
			for(int i=0; i < t_long/(4*td); i++)
			{
				display(dec7seg[digits[0]],dec7seg[digits[1]],dec7seg[digits[2]],dec7seg[digits[3]]);
				debounce_speed_button(SPEED);
				if (speed_f)
				{
					speed_f = 0;
					on_off_speed ^=1;
				}
				if(on_off_speed) t_long = speed_up_t;
				else t_long = t_base;
				current_count = count; 

				if (PROGRAM && (t_long == t_base)) new_init = current_count;
				if (STOP) stop_f = 1;
			}
			if (!stop_f) count--;
		}
	}
} //** End of Program
