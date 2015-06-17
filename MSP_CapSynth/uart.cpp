#include <msp430.h>

#include "uart.hpp"

void cUART::initialize()
{
	state = DONE;

	/* USCI A0 */
	UCA0CTL1 |= UCSWRST;							/* Put peripheral in reset */

	UCA0CTL0 = UCCKPH | UCMST | UCMODE_0; 			/* Data capture on first clock edge, master, 3-pin UART */
	UCA0CTL1 = UCSSEL_3 | UCSWRST; 					/* SMCLK as USCIA clock */
	UCA0BR0 = 138;									/* UCBR settings for 16MHz main clock and 115200 UART */
	UCA0BR1 = 0;
	UCA0MCTL = 7<<1;								/* UCBRSx and UCBRFx settings*/

	/* GPIO */
	/* P1.1 & P1.2 as RX and TX respectively */
	P1SEL  |=  BIT1 | BIT2;
	P1SEL2 |=  BIT1 | BIT2;

	UCA0CTL1 &= ~UCSWRST;							/* Take peripheral out of reset */
}

void cUART::interruptTask()
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
		default:
			IE2  &=~ UCA0TXIE;
			state = DONE;
			break;
	}
}

int cUART::sendByte(uint8_t data)
{
	singleByteBuffer = data;
	return sendBytes(&singleByteBuffer, 1);
}

int cUART::sendBytes(uint8_t* data, uint8_t length)
{
	if(state != DONE || UCA0STAT & UCBUSY)
		return -1;

	currDataPntr = data;
	bytesLeft = length;
	state = SEND_N_BYTE;
	IE2 |= UCA0TXIE;
	return 0;
}

int cUART::operationDone()
{
	return state == DONE;
}

void cUART::waitUntilDone()
{
	while(state != DONE)
		__no_operation();/* TODO: Replace with sleep */
}
