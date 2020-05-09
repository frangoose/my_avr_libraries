// Version 1.2
// 4/29/19

#ifndef USART_H_
#define USART_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>

void USART_Init(uint32_t baudrate);
void USART_Transmit(uint8_t data);
uint8_t USART_Receive(void);
void USART_Test(void);

#endif /* USART_H_ */