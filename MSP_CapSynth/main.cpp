#include <msp430.h>
#include <stdint.h>

#include "i2c.hpp"
#include "spi.hpp"
#include "uart.hpp"

uint16_t oct4Adders[12] = {289,307,325,344,365,386,409,434,460,487,516,547};

enum dacPowerdown{
	NORMAL   	= 0x0,
	_1K_TO_GND	= 0x1,
	_100K_TO_GND = 0x2,
	THREE_STATE = 0x3
};

enum MTCH6102_Registers{
	/* Core RAM */
	FWMAJOR    		= 0x00,
	FWMINOR    		= 0x01,
	APPID_H	   		= 0x02,
	APPID_L    		= 0x03,
	CMD 	   		= 0x04,
	MODE 	   		= 0x05,
	MODECON    		= 0x06,
	/* Touch RAM */
	TOUCHSTATE	 	= 0x10,
	TOUCHX		 	= 0x11,
	TOUCHY		 	= 0x12,
	TOUCHLSB	 	= 0x13,
	GESTURESTATE 	= 0x14,
	GESTUREDIAG		= 0x15,
	/* Configuration RAM */
	XCHANNUMBER 	= 0x20,
	YCHANNUMBER 	= 0x21,
	SCANCOUNT 		= 0x22,
	TOUCHTHRESHX 	= 0x23,
	TOUCHTHRESHY 	= 0x24,
	ACTIVEPERIODL 	= 0x25,
	ACTIVEPERIODH 	= 0x26,
	IDLEPERIODL 	= 0x27,
	IDLEPERIODH 	= 0x28,
	IDLETIMEOUT 	= 0x29,
	HYSTERESIS 		= 0x2A,
	DEBOUNCEUP 		= 0x2B,
	DEBOUNCEDOWN 	= 0x2C,
	BASEINTERVALL 	= 0x2D,
	BASEINTERVALH 	= 0x2E,
	BASEPOSFILTER 	= 0x2F,
	BASENEGFILTER 	= 0x30,
	FILTERTYPE 		= 0x31,
	FILTERSTRENGTH 	= 0x32,
	BASEFILTERTYPE 	= 0x33,
	BASEFILTRSTRGTH = 0x34,
	LRGACTVTHRESHL	= 0x35,
	LRGACTVTHRESHH 	= 0x36,
	HORISWIPEDIST	= 0x37,
	VERTSWIPEDIST	= 0x38,
	SWIPEHLDBOUND	= 0x39,
	TAPDISTANCE 	= 0x3A,
	DISTBTWNTAPS 	= 0x3B,
	TAPHOLDTIMEL 	= 0x3C,
	TAPHOLDTIMEH 	= 0x3D,
	GESTURECLCKTIME = 0x3E,
	SWIPEHOLDTHRESH = 0x3F,
	MINSWIPEVLCITY  = 0x40,
	HORIGESTUREANGL = 0x41,
	VERTGESTUREANGL = 0x42,
	I2CADDR 		= 0x43
};

volatile uint16_t currX = 0;
volatile uint16_t currY = 0;
volatile uint16_t adder = 0;
volatile uint16_t env = 0;

volatile bool touch = false;
cI2C i2c;
cSPI spi;
cUART uart;

//bool spiSendToDAC(enum dacPowerdown pwrDwn, uint16_t value)
//{
//	/* Value limit and bitshift depends upon DAC choice (AD 5601/5611/5621) */
//	if(value > 255)
//		value = 255;
//	uint16_t payload = (pwrDwn<<13) | (value<<5);
//	return spi.sendByte(payload);
//}


void initTimerA(void)
{
	TACCR0 = 16000; 			/* SMCLK being 16MHz, this gives ~30kHz */
	TACCTL0 = CCIE;				/* Interrupt on TACCR0 match */
	TACTL = TASSEL_2 | MC_1; 	/* SMCLK as Timer A clock, up mode */
}

void initGPIO(void)
{
	/* Generic output for logic analyzer */
	P1OUT &= ~BIT3;
	P1DIR |=  BIT3;
	P2OUT &= ~BIT2;
	P2DIR |=  BIT2;

	/* Buttons at P2.3 and P2.4 */
	P2DIR &= ~(BIT3 | BIT4);

    /* Status LEDs as outputs (P3.1 - Touch, P3.2 - Mode0, P3.3 - Mode1) */
	P3OUT &= ~(BIT1 | BIT2 | BIT3);
	P3DIR |=   BIT1 | BIT2 | BIT3;

	/* MTCH6102 ~RESET - P3.0, AMP ~Shutdown - P3.6, SPI DAC CS pin - P3.7 */
	P3DIR |= BIT0 | BIT6 | BIT7;	/* MTCH6102 seems to bug out */
	//P3DIR |= BIT6 | BIT7;

	P3OUT &= ~BIT0;			/* Reset MTCH6102 */
	__delay_cycles(100000);
	P3OUT |= BIT0 | BIT6; 	/* MTCH6102 out of reset, Amp shutdown off */
	_delay_cycles(1000000);
}

void toggleDacSyncPin()
{
	P3OUT |=  BIT7;	/* Strobe SYNC pin, to make device load the new value */
	P3OUT &=~ BIT7;
}


/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    /* 16 MHz frequency */
    BCSCTL1 = CALBC1_16MHZ;
    DCOCTL  = CALDCO_16MHZ;


    initGPIO();
    __delay_cycles(100000);
    i2c.initialize(0x25);
    uart.initialize();
    //spi.initialize();
	//spi.txFinishCallback = toggleDacSyncPin;
	initTimerA();

	__delay_cycles(100000);

	__bis_SR_register(GIE);

	uint8_t  temp[4] = {0};
	uint8_t* touchState = &temp[0];
	uint8_t* tempX = &temp[1];
	uint8_t* tempY = &temp[2];
	uint8_t* tempXY= &temp[3];

	//i2c.writeRegister(0x04, 0x41);
	//i2c.waitUntilDone();
	//i2c.writeRegister(0x05, 0x03);
	//i2c.waitUntilDone();

	while(1)
	{
		if(i2c.operationDone())
		{
			currX = (*tempX)<<4 | (((*tempXY)>>4) & 0x0F);
			currY = (*tempY)<<4 | ((*tempXY) & 0x0F);

			env = (currY/3)<<9;
			adder = oct4Adders[currX/48];

			touch = (*touchState) & BIT0;


			if(touch)
				P3OUT |= BIT1;
			else
				P3OUT &= ~BIT1;

			if((*touchState) & BIT2)
				P3OUT |= BIT2;
			else
				P3OUT &= ~BIT2;

			i2c.readRegisters(0x10, temp, 4);
			//i2c.waitUntilDone();
		}

		/* I2C interrupt handlers */
		if(IFG2 & UCB0TXIFG)
			i2c.interruptTaskTx();
		if(IFG2 & UCB0RXIFG)
			i2c.interruptTaskRx();
		if(UCB0STAT & UCNACKIFG)
			i2c.interruptTaskNack();

		//if(touch)
		//	UCA0TXBUF = currX;
		//__delay_cycles(10000);
	}
	return 0;
}



// USCI_A/B Data ISR (RX and TX share this interrupt vector)
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
	P2OUT |= BIT2;
	/* SPI interrupt handler */
	if(IFG2 & UCA0TXIFG)
	{
		uart.interruptTask();
		//spi.interruptTask();
	}
	P2OUT &= ~BIT2;
}


// USCI_B0 Data ISR (RX and TX share this interrupt vector)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
	static uint16_t phaseAccu = 0xAAAA;
	static uint16_t data = 0x0000;
	static uint16_t tempData = 0x0000;
	static uint8_t output = 0;

	data = tempData;
	//spi.sendBytes((uint8_t*)&data, 2);
	if(touch)
		uart.sendBytes((uint8_t *)&currX, 2);
	//P1OUT |= BIT3;
	tempData = NORMAL<<13 | (touch ? ((uint16_t)output)<<5 : 0);

	phaseAccu += adder;
	output = (phaseAccu > 0x8000) ? 0xFF : 0x00;//(phaseAccu>>21)&0xFF;// & env;
	//i += currY<<1;
	//P1OUT &= ~BIT3;
}

