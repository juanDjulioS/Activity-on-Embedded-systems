#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int dec7seg[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xB8,0x80,0x90}; //common anode (Vcc) representation of each digit
int digits[] = {0,0,0,0}; // vector to save units, tens, hundreds, and thousands unit of the number
int td = 5; // time in which each display must be on
int t_long = 100; // time in milliseconds that a number should last

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
	
	PORTB = 0b11111110 | th_mask;				// enable transistor i-th
	PORTD = thousand;				// show number
	delayms(td);					// delay a time td
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
		
int main(void)
{
	DDRD  = 0xFF;
	PORTD = 0xFF;
	DDRB  = 0x0F;
	PORTB = 0x0F;
	int count = 0;
	
	while(1)
	{
		numFragmenter(count);
		for(int i=0; i < t_long/(4*td); i++) display(dec7seg[digits[3]],dec7seg[digits[2]],dec7seg[digits[1]],dec7seg[digits[0]]);
		count++;
		if(count >=1999)
		{
			count = 0;
			for (int i=0; i<4;i++) digits[i]=0;
		}
	}
}
