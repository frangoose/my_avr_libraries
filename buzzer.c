/* FILENAME     buzzer.c
 * TARGET       ATMEL ATMEGA328P
 * DATE CREATED 6/26/2020
 * AUTHOR       NICK FRANGOS
 */

#include "pitches.h"
#include "buzzer.h"

void BZR_init(void)
{
    DDRB |= (1 << DDB1); // Timer1 output pin
    TCCR1A |= (1 << COM1A0) | (1 << WGM10);
    TCCR1B |= (1 << CS11) | (1 << CS10) | (1 << WGM13);
    OCR1A = (0x0001);
}

void BZR_playnote(uint16_t pitch, uint16_t duration)
{
    OCR1A = (pitch);
    for(int i = 0; i < duration; i++)
    {
        _delay_ms(1);
    }
    OCR1A = (0x0001);
    _delay_ms(50);
}

void BZR_playmario(void)
{
        BZR_playnote(E6, ENOTE);
        BZR_playnote(E6, QNOTE);
        BZR_playnote(E6, QNOTE);
        BZR_playnote(C6, ENOTE);
        BZR_playnote(E6, QNOTE);
        BZR_playnote(G6, HNOTE);
        BZR_playnote(G5, HNOTE);
        BZR_playnote(0x0001, 1000);
}
