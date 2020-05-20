/* FILENAME     TM1637.h
 * TARGET       ATMEL ATMEGA328P
 * DATE CREATED 5/14/2020
 * AUTHOR       NICK FRANGOS
 */

#ifndef TM1637_4DIG_DISPLAY_H
#define TM1637_4DIG_DISPLAY_H

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define TM_DELAY 5 // microseconds

// IO Macros
#define TM_DDR  DDRD
#define TM_PORT PORTD
#define TM_CLK  2
#define TM_DIO  3

// Command Macros
#define TM_AUTOADDR 0x40
#define TM_FIXADDR  0x44
#define TM_GRID1    0xC0
#define TM_GRID2    0xC1
#define TM_GRID3    0xC2
#define TM_GRID4    0xC3
#define TM_GRID5    0xC4
#define TM_GRID6    0xC5
#define TM_DISPOFF  0x80
#define TM_DISPON   0x8F

#include <avr/io.h>
#include <util/delay.h>

void TM_init(void);
void TM_start(void);
void TM_stop(void);
void TM_send(uint8_t byte);
void TM_diolow();
void TM_diohigh();
void TM_clklow();
void TM_clkhigh();
void TM_clearDisplay();
void TM_printValue(uint8_t grid1, uint8_t grid2, uint8_t grid3, uint8_t grid4);

#endif
