//Version 2.0
//10/17/19

#ifndef NOKIA_5110_H_
#define NOKIA_5110_H_

#define LCD_HEIGHT 48
#define LCD_WIDTH 84
#define CLR_PIXEL 0x00
#define SET_PIXEL 0x01

#include <stdint.h>
#include <stdlib.h>
#include "SPI.h"

//ARDUINO UNO
//Use hardware SPI pins D11 & D13
//Use D5 for DC pin and D7 for CE(or SCE) pin

#define SET_NOKIA_DC PORTD |= (1 << PORTD5) // Arduino UNO D5
#define CLR_NOKIA_DC PORTD &= ~(1 << PORTD5)
#define SET_NOKIA_CE PORTD |= (1 << PORTD7) // Arduino UNO D7
#define CLR_NOKIA_CE PORTD &= ~(1 << PORTD7)

//Command Functions
void NOKIA_Send_Command(char cmd);
void NOKIA_Init(void);
void NOKIA_Invert(void);
void NOKIA_Set_Origin(uint8_t x_position, uint8_t y_position);

//Data Functions
void NOKIA_Send_Data(char data);
void NOKIA_Update_Display();
void NOKIA_Fill_Display(char fill);
void NOKIA_Draw_Chkr(void);
void NOKIA_Draw_Char(char ascii_char, uint8_t x_position, uint8_t y_position);
void NOKIA_Draw_String(char ascii_chars[], uint8_t size, uint8_t x_position, uint8_t y_position);
void NOKIA_Set_Pixel(uint8_t x_position, uint8_t y_position, uint8_t bw);
void NOKIA_Draw_Line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t bw);
void NOKIA_Draw_Rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t bw);

//Data Maps
extern char display_map[LCD_HEIGHT * LCD_WIDTH / 8];

extern const char ASCII[][5];

#endif /* NOKIA_5110_H_ */