// Version 1.0
// 10/13/19

#include"SPI.h"

void SPI_MasterInit(void)
{
	//Set SS, MOSI and SCK output, all others as input
	DDRB = (1<<DDB2) | (1<<DDB3) | (1<<DDB5);
	PORTB |= (1<<PORTB2);
	//Enable SPI, set as Master, set clock rate fosc/16
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
}

void SPI_MasterTransmit(char data)
{
	//Start transmission
	SPDR = data;
	//Pull Chip Select Low
	PORTB &= ~(1<<PORTB2);
	//Wait for transmission to complete
	while(!(SPSR & (1<<SPIF)))
	;
	PORTB |= (1<<PORTB2);
}

void SPI_MasterTest(void)
{
	uint8_t x = 0;
	for(x = 0; x < 256; x++)
	{
		SPI_MasterTransmit(x);
	}
}

void SPI_SlaveInit(void)
{
	// Set MISO output, all others as input
	DDRB = (1<<DDB4);
	//Enable SPI
	SPCR = (1<<SPE);
}

char SPI_SlaveReceive(void)
{
	//Wait for reception to complete
	while(!(SPSR & (1<<SPIF)))
	;
	//Return SPI Data Register
	return SPDR;
}