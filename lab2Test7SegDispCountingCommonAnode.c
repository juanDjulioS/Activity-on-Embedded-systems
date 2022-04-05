/*
 * sevenSegementDisplays.c
 *
 * Created: 24/03/2022 11:14:42 a. m.
 * Author : FJ
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL

int decimal7seg[11]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xB8,0x80,0x90,0x7F}; //common anode (Vcc)
int td = 5; // time for each display
volatile int digits[4] = {0,0,0,0};

void delayms (int n){
	while(n--){
		_delay_ms(1);
	}
}
void Display(int n){
	DDRD = 0xFF; // all pins as output
	PORTD = 0xFF; // initialize in turn-off (active low)
	switch(n){
		case 0: PORTD = decimal7seg[0]; break;
		case 1: PORTD = decimal7seg[1]; break;
		case 2: PORTD = decimal7seg[2]; break;
		case 3: PORTD = decimal7seg[3]; break;
		case 4: PORTD = decimal7seg[4]; break;
		case 5: PORTD = decimal7seg[5]; break;
		case 6: PORTD = decimal7seg[6]; break;
		case 7: PORTD = decimal7seg[7]; break;
		case 8: PORTD = decimal7seg[8]; break;
		case 9: PORTD = decimal7seg[9]; break;
	}
}
void numFragmenter(int num){
	unsigned int w = 0;
	while(num!=0){
		digits[w] = num%10;
		num /=10;
		w++;
	}
	for (int j= 0; j < 1000/(4*td);j++) // the number of iterations must last 1000 ms
	{
		PORTB = 0b11111110;		// enable transistor i-th
		Display(digits[3]);	// show number
		delayms(td);		// delay a time td
		PORTB = 0b11111101;		// enable transistor i-th
		Display(digits[2]);	// show number
		delayms(td);		// delay a time td
		PORTB = 0b11111011;		// enable transistor i-th
		Display(digits[1]);	// show number
		delayms(td);		// delay a time td
		PORTB = 0b11110111;		// enable transistor i-th
		Display(digits[0]);	// show number
		delayms(td);		// delay a time td
	}
}
		
int main(void)
{
	DDRD |= 0xFF;
	DDRB |= 0x0F;
	PORTB = 0x0F;	
	int c = 0;
	while (1)
	{
		numFragmenter(c);
		c++;
		if(c >= 9999) c = 0;
	}
}
