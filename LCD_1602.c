//Version 2.0
//3/15/20

#include "LCD_1602.h"

/*    
*    initLCD - initialize LCD
*    Usage: Run during setup code before main while loop to configure a 1602 LCD for 4-bit mode operation
*/
void LCD_init(void)
{
    LCD_DDR |= (1<<LCD_D4) | (1<<LCD_D5) | (1<<LCD_D6) | (1<<LCD_D7) | (1<<LCD_RS) | (1<<LCD_EN);
    LCD_PORT = (1<<LCD_D4) | (1<<LCD_D5);    // Set 8-bit mode for init sequence
    _delay_ms(40);                            // Wait 40ms for LCD to power on
    LCD_toggleEn();                            // Toggle enable for 8-bit mode first time
    _delay_ms(5);                            // Wait 5ms
    LCD_toggleEn();                            // Toggle enable for 8-bit mode second time
    _delay_ms(5);                            // Wait 5ms
    LCD_toggleEn();                            // Toggle enable for 8-bit mode third time
    LCD_PORT &= ~(1<<LCD_D4);                // Set 4-bit mode
    _delay_ms(5);                            // Wait 5ms
    LCD_toggleEn();                            // Toggle enable for 4-bit mode
    LCD_sendCmd(LCD_FUNCSET1602);            // set function for 2-lines, 5x8 pixel characters
    LCD_sendCmd(LCD_CLEARDISPLAY);            // clear display
    LCD_sendCmd(LCD_RETURNHOME);            // set cursor to home position (addr=0x00)
    LCD_sendCmd(LCD_DISPLAYCTL +            // Turn on display and blink cursor
                LCD_BLINKON + 
                LCD_DISPLAYON);
}
/*
*    LCD_sendCmd - send command to LCD
*    uint8_t data: see HD44780 data sheet for list of 1-byte commands
*    Usage: Send command to LCD as 2 nibbles in 4-bit mode operation
*/
void LCD_sendCmd(uint8_t data)
{
    //Send upper nibble
    LCD_PORT = 0x00;
    LCD_PORT |= ((data>>4)<<LCD_D4);
    LCD_PORT |= ((data>>5)<<LCD_D5);
    LCD_PORT |= ((data>>6)<<LCD_D6);
    LCD_PORT |= ((data>>7)<<LCD_D7);    
    LCD_PORT &= ~(1<<LCD_RS); //clear RS pin to send command
    LCD_toggleEn();
    
    //Send lower nibble
    LCD_PORT = 0x00;
    LCD_PORT |= (data<<LCD_D4);
    LCD_PORT |= ((data>>1)<<LCD_D5);
    LCD_PORT |= ((data>>2)<<LCD_D6);
    LCD_PORT |= ((data>>3)<<LCD_D7);
    LCD_PORT &= ~(1<<LCD_RS); //clear RS pin to send command
    LCD_toggleEn();
}

/*
*    LCD_sendChar - send char to LCD
*    char data: ASCII char
*    Usage: Send ASCII char to LCD as 2 nibbles in 4-bit mode operation
*/
void LCD_sendChar(char data)
{
    //Send upper nibble
    LCD_PORT = 0x00;
    LCD_PORT |= ((data>>4)<<LCD_D4);
    LCD_PORT |= ((data>>5)<<LCD_D5);
    LCD_PORT |= ((data>>6)<<LCD_D6);
    LCD_PORT |= ((data>>7)<<LCD_D7);
    LCD_PORT |= (1<<LCD_RS); //set RS pin to send data
    LCD_toggleEn();
        
    //Send lower nibble
    LCD_PORT = 0x00;
    LCD_PORT |= (data<<LCD_D4);
    LCD_PORT |= ((data>>1)<<LCD_D5);
    LCD_PORT |= ((data>>2)<<LCD_D6);
    LCD_PORT |= ((data>>3)<<LCD_D7);
    LCD_PORT |= (1<<LCD_RS); //set RS pin to send data
    LCD_toggleEn();    
}

/*
*    LCD_sendString - send string of chars to LCD
*    char data[]: array of ASCII chars (string)
*    Usage: Send string of ASCII char to LCD as 2 nibbles in 4-bit mode operation
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
*    LCD_setCursor - set LCD cursor position
*    uint8_t addr: LCD cursor address (0x00 - 0x4F)
*    Usage: Set LCD cursor to specific address in display memory
*/
void LCD_setCursor(uint8_t addr)
{
    LCD_sendCmd(0x80 + addr); // set function
}

/*
*    LCD_toggleEn - toggle LCD enable pin
*    Usage: Toggle LCD enable between sending data or commands to LCD
*/
void LCD_toggleEn(void)
{
    LCD_PORT |= (1<<LCD_EN);
    _delay_us(LCD_DELAY);
    LCD_PORT &= ~(1<<LCD_EN);
    _delay_us(LCD_DELAY);
}

/*
*    LCD_cola
*    Usage: Prints sample text to LCD for testing purposes
*/
void LCD_cola(void)
{
    LCD_sendString("Enjoy Refreshing,");
    LCD_setCursor(0x40);
    LCD_sendString("Cold Coca-Cola!");
}