/* FILENAME     buzzer.h
 * TARGET       ATMEL ATMEGA328P
 * DATE CREATED 6/26/2020
 * AUTHOR       NICK FRANGOS
 */

#ifndef BUZZER_H
#define BUZZER_H

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define TEMPO 190
#define ENOTE ((60000/TEMPO))/2
#define QNOTE ((60000/TEMPO))
#define HNOTE ((60000/TEMPO))*2
#define WNOTE ((60000/TEMPO))*4

void BZR_init(void);
void BZR_play_note(uint16_t pitch, uint16_t duration);
void BZR_play_mario(void);

#endif
