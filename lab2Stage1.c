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
int digits[] = {0,0,0,0}; 
int td = 5;			// time in which each display must be on
int t_long = 100;	// time in milliseconds that a number should last


/********************* Functions and subroutines **********************/
void delayms (int n){
	while(n--){
		_delay_ms(1);
	}
}
void numFragmenter(int num){
	unsigned int i = 0;
	while(num!=0){
		digits[i] = num%10;
		num /=10;
		i++;
	}
}
void display(int thousand, int hundred, int ten, int one){
	int th_mask = 0b11111110, hun_mask = 0b11111101, te_mask =0b11111011;
	if (digits[3]== 0 && digits[2] ==  0 && digits[1] ==  0 && (digits[1] <= digits[0])) {
		th_mask = hun_mask = te_mask = 0xFF;
	}
	if (digits[3]== 0 && digits[2] ==  0 && (digits[2] < digits[1])){
		th_mask = hun_mask = 0xFF;
	}
	if (digits[3]== 0 && (digits[3] < digits[2])) th_mask = 0xFF;
	
	PORTB = 0b11111110 | th_mask;		// enable transistor i-th
	PORTD = thousand;			// show number
	delayms(td);				// delay a time td
	PORTB = 0b11111101 | hun_mask;
	PORTD = hundred;
	delayms(td);			
	PORTB = 0b11111011 | te_mask;		
	PORTD = ten;
	delayms(td);		
	PORTB = 0b11110111;	
	PORTD = one;	
	delayms(td);		
}

/************************** Main Program ******************************/		
int main(void)
{
	/*************** variable initialization **************************/
	int count = 0;
	/*******************Ports Setting *********************************/
	DDRD  = 0xFF; // as output to turn on/off four digit 7 segment displays
	PORTD = 0xFF; // to enable/disable  PNP transistors 2n3906 (active low)
	DDRB  = 0x0F;
	PORTB = 0x0F;


	while(1)
	{
		numFragmenter(count);
		for(int i=0; i < t_long/(4*td); i++) 
		display(dec7seg[digits[3]],dec7seg[digits[2]],dec7seg[digits[1]],dec7seg[digits[0]]);
		if(count >=9999)
		{
			// reset counting and vector of fragmented number returned to zero
			count = 0;
			for (int i=0; i<4;i++) digits[i]=0; 
		}
		count++;
	}
} //** End of Program
