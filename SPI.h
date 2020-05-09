// Version 1.0
// 10/13/19

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

void SPI_MasterInit(void);
void SPI_MasterTransmit(char data);
void SPI_MasterTest(void);
void SPI_SlaveInit(void);
char SPI_SlaveReceive(void);

#endif /* SPI_H_ */