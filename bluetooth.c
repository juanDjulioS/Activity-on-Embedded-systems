#define F_CPU 16000000UL

#include <avr/io.h>
#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)


void USART_Init(unsigned long BAUDRATE)				/* USART initialize function */
{
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);				/* Enable USART transmitter and receiver */
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);	/* Write USCRC for 8 bit data and 1 stop bit */
	UBRR0L = BAUD_PRESCALE;							/* Load UBRRL with lower 8 bit of prescale value */
	UBRR0H = (BAUD_PRESCALE >> 8);					/* Load UBRRH with upper 8 bit of prescale value */
}
char USART_RxChar()									/* Data receiving function */
{
	while (!(UCSR0A & (1 << RXC0)));					/* Wait until new data receive */
	return(UDR0);									/* Get and return received data */
}

void USART_TxChar(char data)						/* Data transmitting function */
{
	UDR0 = data;										/* Write data to be transmitting in UDR */
	while (!(UCSR0A & (1<<UDRE0)));					/* Wait until data transmit and buffer get empty */
}

int main(void)
{
	char Data_in;
	DDRD = 0x00;
	DDRC = 0xff;							/* make PORT as output port */
	USART_Init(9600);						/* initialize USART with 9600 baud rate */
	PORTC = 0;
	while(1)
	{
		Data_in = USART_RxChar();						/* receive data from Bluetooth device*/
		if(Data_in =='1')
		{
			PORTC = (1<<PC4);							/* Turn ON LED */
			
		}
		else if(Data_in =='2')
		{
			PORTC &= ~(1<<PC4);							/* Turn OFF LED */
		}
	}
	return 0;
}
