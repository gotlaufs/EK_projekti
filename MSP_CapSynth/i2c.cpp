#include <msp430.h>

#include "i2c.hpp"

void cI2C::initialize(uint8_t slaveAddr)
{
	/* GPIO */
	/* P1.6 & P1.7 as SCL & SDA respectively */
	P1SEL  |=  BIT6 | BIT7;
	P1SEL2 |=  BIT6 | BIT7;

	/* USCI B */
	UCB0CTL1 |= UCSWRST;

	UCB0CTL0 = UCMST | UCMODE_3 | UCSYNC;	/* I2C master */
	UCB0CTL1 = UCSSEL_3 | UCSWRST;			/* SMCLK as USCIB clock */
	UCB0BR0 = 48;                           /* fSCL = 16M/48 = ~400kHz */
	UCB0BR1 = 0;
	//UCB0I2CIE = UCNACKIE;					/* Enable NACK interrupt */

	slaveAddress = slaveAddr;
	UCB0I2CSA = slaveAddress;

	UCB0CTL1 &= ~UCSWRST;

	if(P1IN & BIT7)	/* If slave is holding SDA low */
	{
		UCB0CTL1 |= UCTXSTT;
		UCB0CTL1 |= UCTXSTP;
	}

	state = DONE;

	//IE2 = UCB0TXIE | UCB0RXIE;
}

void cI2C::interruptTaskTx()
{
	switch(state)
	{
		case SEND_N_BYTE:
			UCB0TXBUF = *currDataPntr;
			currDataPntr++;
			bytesLeft--;
			if(!bytesLeft)
				state = SEND_STOP;
			break;

		case SEND_STOP:
			IFG2 &= ~UCB0TXIFG;
			UCB0CTL1 |= UCTXSTP;
			state = DONE;
			break;

		case SEND_ADDRESS:
			IFG2 &= ~UCB0TXIFG;
			UCB0CTL1 &= ~UCTR;
			UCB0CTL1 |= UCTXSTT;
			state = READ_N_BYTE;
			break;

		case DONE:
		default:
			//IFG2 &= ~UCB0TXIFG;
			break;
	}
}

void cI2C::interruptTaskRx()
{
	switch(state)
	{
		case READ_N_BYTE:
			*currDataPntr = UCB0RXBUF;
			currDataPntr++;
			bytesLeft--;
			if(!bytesLeft)
			{
				UCB0CTL1 |= UCTXSTP;
				state = SEND_STOP;
			}
			break;

		case SEND_STOP:
			UCB0RXBUF = UCB0RXBUF;	/* Fake read to make the reader happy */
			//IFG2 &= ~UCB0RXIFG;
			state = DONE;
			break;

		case DONE:
		default:
			//IFG2 &= ~UCB0RXIFG;
			break;
	}
}

void cI2C::interruptTaskNack()
{
	UCB0STAT &=~UCNACKIFG;
	UCB0CTL1 |= UCTXSTP;
}

int cI2C::sendByte(uint8_t data)
{
	buffer[0] = data;
	return sendBytes(buffer, 1);
}

int cI2C::sendBytes(uint8_t* data, uint8_t length)
{
	if(state != DONE || (UCB0CTL1 & UCTXSTT) || (UCB0CTL1 & UCTXSTP) || (UCB0STAT & UCBBUSY))
		return -1;

	//IE2 &=~ UCB0TXIE | UCB0RXIE;
	currDataPntr = data;
	bytesLeft = length;
	state = SEND_N_BYTE;
	UCB0CTL1 |= UCTR;
	UCB0CTL1 |= UCTXSTT;
	//IE2 |= UCB0TXIE | UCB0RXIE;

	return 0;
}

int cI2C::readByte(uint8_t* data)
{
	return readBytes(data, 1);
}

int cI2C::readBytes(uint8_t* data, uint8_t length)
{
	if(state != DONE || (UCB0CTL1 & UCTXSTT) || (UCB0CTL1 & UCTXSTP) || (UCB0STAT & UCBBUSY))
		return -1;

	//IE2 &=~ UCB0TXIE | UCB0RXIE;
	UCB0CTL1 &= ~UCTR;
	currDataPntr = data;
	bytesLeft = length;
	state = READ_N_BYTE;
	//IE2 |= UCB0TXIE | UCB0RXIE;
	return 0;
}

int cI2C::writeRegister(uint8_t address, uint8_t data)
{
	buffer[0] = data;
	writeRegisters(address, buffer, 1);
}

int cI2C::writeRegisters(uint8_t address, uint8_t* data, uint8_t length)
{
	if(state != DONE || (UCB0CTL1 & UCTXSTT) || (UCB0CTL1 & UCTXSTP) || (UCB0STAT & UCBBUSY))
		return -1;

	//IE2 &=~ UCB0TXIE | UCB0RXIE;
	UCB0CTL1 |= UCTR;
	UCB0CTL1 |= UCTXSTT;
	while(UCB0CTL1 & UCTXSTP);	/* TODO: Replace with sleep */
	UCB0TXBUF = address;
	currDataPntr = data;
	bytesLeft = length;
	state = SEND_N_BYTE;
	//IE2 |= UCB0TXIE | UCB0RXIE;
	return 0;
}

int cI2C::readRegister(uint8_t address, uint8_t* data)
{
	return readRegisters(address, data, 1);
}

int cI2C::readRegisters(uint8_t address, uint8_t* data, uint8_t length)
{
	if(state != DONE || (UCB0CTL1 & UCTXSTT) || (UCB0CTL1 & UCTXSTP) || (UCB0STAT & UCBBUSY))
		return -1;

	//IE2 &=~ UCB0TXIE | UCB0RXIE;
	UCB0CTL1 |= UCTR;
	UCB0CTL1 |= UCTXSTT;
	while(UCB0CTL1 & UCTXSTP);	/* TODO: Replace with sleep */
	UCB0TXBUF = address;
	currDataPntr = data;
	bytesLeft = length;
	state = SEND_ADDRESS;
	//IE2 |= UCB0TXIE | UCB0RXIE;
	return 0;
}

int cI2C::operationDone()
{
	return (state == DONE && !(UCB0CTL1 & UCTXSTT) && !(UCB0CTL1 & UCTXSTP) && !(UCB0STAT & UCBBUSY));
}

void cI2C::waitUntilDone()
{
	while(state != DONE || (UCB0CTL1 & UCTXSTT) || (UCB0CTL1 & UCTXSTP) || (UCB0STAT & UCBBUSY));	/* TODO: Replace with sleep */
}

