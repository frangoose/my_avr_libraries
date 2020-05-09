//Version 1.0
//4/10/20
#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>

void TWI_init(void);
void TWI_start(void);
void TWI_write(uint8_t data);
uint8_t TWI_read(void);
void TWI_stop(void);

#endif /* TWI_H_ */