#ifndef __I2C_HPP
#define __I2C_HPP

#include <stdint.h>

class cI2C{
private:
	volatile enum{
		DONE,
		SEND_STOP,
		SEND_N_BYTE,
		SEND_ADDRESS,
		READ_N_BYTE
	} state;

	volatile uint8_t  bytesLeft;
	volatile uint8_t* currDataPntr;
	uint8_t  buffer[2];
	volatile uint8_t  slaveAddress;

public:

	void initialize(uint8_t slaveAddr);
	void interruptTaskTx();
	void interruptTaskRx();
	void interruptTaskNack();

	int sendByte(uint8_t  data);
	int sendBytes(uint8_t* data, uint8_t length);

	int readByte(uint8_t* data);
	int readBytes(uint8_t* data, uint8_t length);

	int writeRegister(uint8_t address, uint8_t data);
	int writeRegisters(uint8_t address, uint8_t* data, uint8_t length);

	int readRegister(uint8_t address, uint8_t* data);
	int readRegisters(uint8_t address, uint8_t* data, uint8_t length);

	int operationDone();
	void waitUntilDone();
};

#endif /* __I2C_HPP */