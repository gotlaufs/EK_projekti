/**
 *  I2C bitbang library header.
 *
 * TODO: Add documentation.
 */

#ifndef _I2C_BITBANG_H_
#define _I2C_BITBANG_H_
#include <stdint.h>

void I2C_start(void);
void I2C_ack_wait(void);
void I2C_ack_give(void);
void I2C_send(uint8_t data);
uint8_t I2Cread(uint8_t device_address, uint8_t reg_address);

#endif // _I2C_BITBANG_H_
