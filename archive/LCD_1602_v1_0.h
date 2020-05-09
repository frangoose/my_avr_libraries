//Version 1.0
//3/1/20

#ifndef LCD_1602_H_
#define LCD_1602_H_

#ifndef F_CPU 
#define F_CPU 16000000UL
#endif

#define LCD_DELAY _delay_us(1000)

#include <avr/io.h>
#include <util/delay.h>


void LCD_init(void);
void LCD_sendCmd(uint8_t data);
void LCD_sendChar(char data);
void LCD_sendString(char data[]);
void LCD_setCursor(uint8_t addr);
void LCD_shiftCursor(uint8_t cmd);
void LCD_toggleEn(void);
void LCD_cola(void);

#endif /* LCD_1602_H_ */