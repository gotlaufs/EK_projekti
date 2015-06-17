#include <msp430.h>

#include "spi.hpp"

void cSPI::initialize()
{
	state = DONE;
	txFinishCallback = NULL;

	/* USCI A0 */
	UCA0CTL1 |= UCSWRST;							/* Put peripheral in reset */

	UCA0CTL0 = UCCKPH | UCMST | UCMODE_0 | UCSYNC; 	/* Data capture on first clock edge, master, 3-pin SPI */
	UCA0CTL1 = UCSSEL_3 | UCSWRST; 					/* SMCLK as USCIA clock */
	UCA0BR0 = 4;                            		/* fSCL = SMCLK/16 = 1MHz */
	UCA0BR1 = 0;

	/* GPIO */
	/* P1.2 & P1.4 as SIMO and SCLK respectively */
	P1SEL  |=  BIT2 | BIT4;
	P1SEL2 |=  BIT2 | BIT4;

	UCA0CTL1 &= ~UCSWRST;							/* Take peripheral out of reset */
}

void cSPI::interruptTask()
{
	switch(state)
	{
		case SEND_N_BYTE:
			UCA0TXBUF = *currDataPntr;
			currDataPntr++;
			bytesLeft--;
			if(!bytesLeft)
				state = FINISH;
			break;

		case FINISH:
			if(txFinishCallback != NULL)
				txFinishCallback();
		default:
			IE2  &=~ UCA0TXIE;
			state = DONE;
			break;
	}
}

int cSPI::sendByte(uint8_t data)
{
	singleByteBuffer = data;
	return sendBytes(&singleByteBuffer, 1);
}

int cSPI::sendBytes(uint8_t* data, uint8_t length)
{
	if(state != DONE || UCA0STAT & UCBUSY)
		return -1;

	currDataPntr = data;
	bytesLeft = length;
	state = SEND_N_BYTE;
	IE2 |= UCA0TXIE;
	return 0;
}

int cSPI::operationDone()
{
	return state == DONE;
}

void cSPI::waitUntilDone()
{
	while(state != DONE)
		__no_operation();/* TODO: Replace with sleep */
}
