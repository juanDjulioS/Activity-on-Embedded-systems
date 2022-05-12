/*
 * C code for Digital Voltmeter using ATmega32 Microcontroller
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


#define enable            2
#define registerselection 0

void send_a_command(unsigned char command);
void send_a_character(unsigned char character);
void send_a_string(char *string_of_characters);

int main(void)
{
    DDRD = 0xFF;
    DDRC = 0; // adc
    DDRB = 0xFF;
    _delay_ms(50);

    ADMUX |=(1<<REFS0);
    ADCSRA |=(1<<ADEN)|(1<<ADATE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);

    char voltageshow [7];

    send_a_command(0x01); //Clear Screen 0x01 = 00000001
    _delay_ms(50);
    send_a_command(0x38);
    _delay_ms(50);
    send_a_command( 0x0F);
    _delay_ms(50);

    ADCSRA |=(1<<ADSC);
    while(1)
    {
        float voltage = ADC; 
		send_a_string ("CIRCUIT DIGEST  ");
		send_a_command(0x80 + 0x40 + 0);
        send_a_string ("VOLTAGE=");
        send_a_command(0x80 + 0x40 + 8);
        dtostrf(voltage, 5, 3, voltageshow);
        send_a_string(voltageshow);
        send_a_string("V   ");
        send_a_command(0x80 + 0);
    }
}


void send_a_command(unsigned char command)
{

    PORTD = command;
    PORTB &= ~ (1<<registerselection);
    PORTB |= 1<<enable;
    _delay_ms(2);
    PORTB &= ~1<<enable;
    PORTD = 0;
}


void send_a_character(unsigned char character)
{
    PORTD = character;
    PORTB |= 1<<registerselection;
    PORTB |= 1<<enable;
    _delay_ms(2);
    PORTB &= ~1<<enable;
    PORTD = 0;
}

void send_a_string(char *string_of_characters)
{
    while(*string_of_characters > 0)
    {
        send_a_character(*string_of_characters++);
    }
}

