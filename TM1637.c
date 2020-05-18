/* FILENAME     TM1637.c
 * TARGET       ATMEL ATMEGA328P
 * DATE CREATED 5/14/2020
 * AUTHOR       NICK FRANGOS
 */

#include "TM1637.h"

// Segment Mapping
const uint8_t segmap[] = {
    0x3F, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71 // 8-9, A-F
};

void TM_init(void)
{
    TM_DDR  &= ~(1<<TM_DIO) | (1<<TM_CLK); // set pins to input
    TM_PORT |=  (1<<TM_DIO) | (1<<TM_CLK); // enable pullup resistors in pull pins to logic HIGH
    _delay_us(TM_DELAY);
}

void TM_start(void)
{
    TM_diolow();
}
void TM_stop(void)
{
    TM_clklow();
    TM_diolow();
    TM_clkhigh();
    TM_diohigh();
}

void TM_send(uint8_t byte)
{
    uint8_t data = byte;
    for(uint8_t i = 0; i < 8; i++)
    {
        TM_clklow();
        if(data & 0x01)
        {
           TM_diohigh(); 
        }
        else
        {
           TM_diolow(); 
        }
        _delay_us(TM_DELAY);
        data = data >> 1;
        TM_clkhigh();
    }
    // Wait for ACK
    TM_clklow();
    TM_clkhigh();
}

void TM_diolow()
{
    TM_DDR  |=  (1<<TM_DIO); // set DIO pin to output
    TM_PORT &= ~(1<<TM_DIO); // set DIO pin to logic LOW
    _delay_us(TM_DELAY);
}
void TM_diohigh()
{
    TM_DDR  &= ~(1<<TM_DIO); // set DIO pin to input to allow pullup resistors to pull to logic HIGH
    TM_PORT |=  (1<<TM_DIO); // set DIO pin to logic HIGH to enable pull-up resistor
    _delay_us(TM_DELAY);
}
void TM_clklow()
{
    TM_DDR  |=  (1<<TM_CLK); // set CLK pin to output
    TM_PORT &= ~(1<<TM_CLK); // set CLK pin to logic LOW
    _delay_us(TM_DELAY);
}
void TM_clkhigh()
{
    TM_DDR  &= ~(1<<TM_CLK); // set CLK pin to input to allow pullup resistors to pull to logic HIGH
    TM_PORT |=  (1<<TM_CLK); // set CLK pin to logic HIGH to enable pull-up resistor
    _delay_us(TM_DELAY);
}
