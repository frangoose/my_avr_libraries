//Version 1.0
//4/10/20
#include "TWI.h"

void TWI_init(void)
{
    TWSR = 0x00; // Set prescaler to 0
    //TWBR = 0x48; // Set bitrate to 100kHz
    TWBR = 0x0C; // Set bitrate to 400kHz
    TWCR = (1 << TWEN);
}

void TWI_start(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // Send START condition
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set. This indicates that the START condition has been transmitted
}

void TWI_write(uint8_t data)
{
    TWDR = data; // Load data register
    TWCR = (1 << TWINT) | (1 << TWEN); // Clear TWINT bit and set TWEN to begin writing data
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set. This indicates that the ACK/NACK has been received after writing data
}

uint8_t TWI_read(void)
{
    return 0;
}

void TWI_stop(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); // Sent STOP condition
}