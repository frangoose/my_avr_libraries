// Version 1.0
// 10/13/19

#include "USART.h"

void USART_Init(unsigned int ubrr)
{
	//Set the baud rate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)(ubrr);
	//enable receiver and transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	//Set frame format to 8 data bits, 1 stop bit (USBS0 register remains clear, not shown)
	UCSR0C = (3<<UCSZ00);
}

void USART_Transmit(unsigned char data)
{
	//Wait for empty transmit buffer
	while(!(UCSR0A & (1<<UDRE0)))
	;
	//Puts data in a buffer, then sends the data
	UDR0 = data;
}

unsigned char USART_Receieve(void)
{
	//Wait for data to be received
	while(!(UCSR0A & (1<< RXC0)))
	;
	//Get and return received data from buffer
	return UDR0;
}

void USART_Test(){
	//Transmits all 8-bit binary values from 0 - 255
	uint8_t x = 0;
	for(x = 0; x < 256; x++)
	{
		USART_Transmit(x);
	}
}