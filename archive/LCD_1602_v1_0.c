//Version 1.0
//3/4/20

#include "LCD_1602.h"

/*	
*	initLCD - initialize LCD
*	Usage: Run during setup code before main while loop to configure 1602 LCD for 4-bit mode operation
*/
void LCD_init(void)
{
	DDRC |= (1<<DDC0) | (1<<DDC1) | (1<<DDC2) | (1<<DDC3) | (1<<DDC4) | (1<<DDC5); //PC0-PC3 are LCD Data pins D4-D7; PC4 is LCD RS; PC5 in LCD EN
	PORTC = 0x03;		// Set 8-bit mode for init sequence
	_delay_ms(40);		// Wait 40ms for LCD to power on
	LCD_toggleEn();		// Toggle enable for 8-bit mode first time
	_delay_ms(5);		// Wait 5ms
	LCD_toggleEn();		// Toggle enable for 8-bit mode second time
	_delay_ms(5);		// Wait 5ms
	LCD_toggleEn();		// Toggle enable for 8-bit mode third time
	PORTC = 0x02;		// Set 4-bit mode
	_delay_ms(5);		// Wait 5ms
	LCD_toggleEn();		// Toggle enable for 4-bit mode
	LCD_sendCmd(0x28);	// set function for 2-lines, 5x8 pixel characters
	LCD_sendCmd(0x01);	// clear display
	LCD_sendCmd(0x02);	// set cursor to home position (addr=0x00)
	LCD_sendCmd(0x0F);	// Turn on display and blink cursor
}

/*
*	LCD_sendCmd - send command to LCD
*	uint8_t data: see HD44780 data sheet for list of 1-byte commands
*	Usage: Send command to LCD as 2 nibbles in 4-bit mode operation
*/
void LCD_sendCmd(uint8_t data)
{
	PORTC = 0x00;
	PORTC |= (data>>4); //upper nibble
	PORTC &= ~(1<<PORTC4); //clear RS pin to send command
	LCD_toggleEn();
	PORTC = 0x00;
	PORTC |= (data & 0x0F); //lower nibble
	PORTC &= ~(1<<PORTC4); //clear RS pin to send command
	LCD_toggleEn();
}

/*
*	LCD_sendChar - send char to LCD
*	char data: ASCII char
*	Usage: Send ASCII char to LCD as 2 nibbles in 4-bit mode operation
*/
void LCD_sendChar(char data)
{
	PORTC = 0x00;
	PORTC |= (data>>4); //upper nibble
	PORTC |= (1<<PORTC4); //set RS pin to send data
	LCD_toggleEn();
	PORTC = 0x00;
	PORTC |= (data & 0x0F); //lower nibble
	PORTC |= (1<<PORTC4); //set RS pin to send data
	LCD_toggleEn();
}

/*
*	LCD_sendString - send string of chars to LCD
*	char data[]: array of ASCII chars (string)
*	Usage: Send string of ASCII char to LCD as 2 nibbles in 4-bit mode operation
*/
void LCD_sendString(char data[])
{
	int i = 0;
	while(data[i] != '\0')
	{
		LCD_sendChar(data[i]);
		i++;
	}
}

/*
*	LCD_setCursor - set LCD cursor position
*	uint8_t addr: LCD cursor address (0x00 - 0x4F)
*	Usage: Set LCD cursor to specific address in display memory
*/
void LCD_setCursor(uint8_t addr)
{
	LCD_sendCmd(0x80 + addr); // set function
}

/*
*	LCD_shiftCursor - shift LCD cursor position
*	uint8_t cmd: LCD shift command
*	Usage: Shift LCD cursor left or right by 1 using proper command from data sheet
*/
void LCD_shiftCursor(uint8_t cmd)
{
	LCD_sendCmd(0x10 + cmd); // set function
}

/*
*	LCD_toggleEn - toggle LCD enable pin
*	Usage: Toggle LCD enable between sending data or commands to LCD
*/
void LCD_toggleEn(void)
{
	PORTC |= (1<<PORTC5);
	LCD_DELAY;
	PORTC &= ~(1<<PORTC5);
	LCD_DELAY;
}

/*
*	LCD_cola
*	Usage: Prints sample text to LCD for testing purposes
*/
void LCD_cola(void)
{
	LCD_sendString("Enjoy Refreshing,");
	LCD_setCursor(0x40);
	LCD_sendString("Cold Coca-Cola!");
}