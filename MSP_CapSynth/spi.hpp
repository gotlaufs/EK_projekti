#ifndef __SPI_HPP
#define __SPI_HPP

#include <stdint.h>

#ifndef NULL
#define NULL 0	/* NULL pointer */
#endif

class cSPI{
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

	void (*txFinishCallback)(void);

	void initialize();
	void interruptTask();

	int sendByte(uint8_t data);
	int sendBytes(uint8_t* data, uint8_t length);

	int operationDone();
	void waitUntilDone();
};

#endif /* __SPI_HPP */