// Version 1.2
// 4/29/19

#include "USART.h"

void USART_Init(uint32_t baudrate)
{
	//Set the baud rate
    uint32_t ubrr = (F_CPU/16/baudrate)-1;
    UBRR0H = (uint8_t)(ubrr>>8);
	UBRR0L = (uint8_t)(ubrr);
	//enable receiver and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	
    //Set frame format to 8 data bits, 1 stop bit
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    UCSR0C &= ~(1 << USBS0);
}

void USART_Transmit(uint8_t data)
{
	//Wait for empty transmit buffer
	while(!(UCSR0A & (1 << UDRE0)))
	;
	//Puts data in a buffer, then sends the data
	UDR0 = data;
}

uint8_t USART_Receive(void)
{
	//Wait for data to be received
	while(!(UCSR0A & (1 <<  RXC0)))
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