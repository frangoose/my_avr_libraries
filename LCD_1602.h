//Version 2.0
//3/15/20

#ifndef LCD_1602_H_
#define LCD_1602_H_

#ifndef F_CPU 
#define F_CPU 16000000UL
#endif

#define LCD_DELAY 1000 // in microseconds

// User configurable settings
// By default PC0-PC3 are LCD Data pins D4-D7; PC4 is LCD EN; PC5 is LCD RS; PC6 is LCD RW
#define LCD_DDR DDRC
#define LCD_PORT PORTC
#define LCD_D4 0
#define LCD_D5 1
#define LCD_D6 2
#define LCD_D7 3
#define LCD_EN 4
#define LCD_RS 5
#define LCD_RW 6

// Macros for LCD instructions
#define LCD_CLEARDISPLAY    0x01
#define LCD_RETURNHOME      0x02

#define LCD_ENTRYMODESET    0x04
#define LCD_ENTRYSHIFTDEC   0x00
#define LCD_ENTRYRIGHT      0x00
#define LCD_ENTRYSHIFTINC   0x01
#define LCD_ENTRYLEFT       0x02

#define LCD_DISPLAYCTL      0x08
#define LCD_BLINKOFF        0x00
#define LCD_CURSOROFF       0x00
#define LCD_DISPLAYOFF      0x00
#define LCD_BLINKON         0x01
#define LCD_CURSORON        0x02
#define LCD_DISPLAYON       0x04

#define LCD_SHIFT           0x10
#define LCD_SHIFTDISPLAY    0x08
#define LCD_SHIFTCURSOR     0x00
#define LCD_SHIFTRIGHT      0x04
#define LCD_SHIFTLEFT       0x00

#define LCD_FUNCSET         0x20
#define LCD_FUNCSET1602     0x28
#define LCD_SETCGRAMADDR    0x40
#define LCD_SETDDRAMADDR    0x80

#include <avr/io.h>
#include <util/delay.h>

void LCD_init(void);
void LCD_sendCmd(uint8_t data);
void LCD_sendChar(char data);
void LCD_sendString(char data[]);
void LCD_setCursor(uint8_t addr);
void LCD_toggleEn(void);
void LCD_cola(void);

#endif /* LCD_1602_H_ */