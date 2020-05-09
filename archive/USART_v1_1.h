// Version 1.1
// 10/13/19

#ifndef USART_H_
#define USART_H_

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>

void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
unsigned char USART_Receieve(void);
void USART_Test(void);

#endif /* USART_H_ */