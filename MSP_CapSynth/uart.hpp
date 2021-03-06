#ifndef __UART_HPP
#define __UART_HPP

#include <stdint.h>

#ifndef NULL
#define NULL 0	/* NULL pointer */
#endif

class cUART{
private:
	volatile enum{
		DONE,
		SEND_N_BYTE,
		FINISH,
	} state;

	volatile uint8_t  bytesLeft;
	volatile uint8_t* currDataPntr;
	uint8_t  singleByteBuffer;

public:
	void initialize();
	void interruptTask();

	int sendByte(uint8_t data);
	int sendBytes(uint8_t* data, uint8_t length);

	int operationDone();
	void waitUntilDone();
};

#endif /* __UART_HPP */