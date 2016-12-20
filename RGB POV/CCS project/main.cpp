/*
 * main.c
 */
/*
 * Things to test:
 *
 * TODO: Test stdint variable declarations.
 */
#include <stdint.h>
#include <msp430.h> 


//PORT 1
#define OE 		0x01
#define BUTTON	0x02
#define SCL		0x04
#define SDA		0x08
#define AD0		0x10
#define INT		0x20

//PORT 2
#define STR		0x01
#define CLK		0x02
#define DATA 	0x04
#define RFET 	0x08
#define GFET 	0x10
#define BFET 	0x20

//MPU6050 I2C
#define MPU6050_ADDRESS 0x68*2	// +0x01 for read
#define MPU6050_RA_WHO_AM_I 0x75
#define I2CDELAY	0

//Color Bits - 0bRRRR RGGG GGGB BBBB
#define REDB 	0xF800
#define GREENB 	0x07E0
#define BLUEB 	0x001F

// GLOBALS
uint8_t ActiveColor=RFET;	//Must be non-zero
uint8_t ActiveFrame=0;
uint8_t DutyFrame=0;
uint8_t RedFrame[8]={0};
uint8_t GreenFrame[8]={0};
uint8_t BlueFrame[8]={0};
uint16_t Pause=0;
uint8_t MaxFrame=8-1;
//uint16_t Data[8][11]={0x0000, 0xF800, 0x07E0, 0x001F, 0x001F, 0x07E0, 0xF800, 0x0000, 0xF800, 0x07E0, 0x001F, 0xFFFF, 0xFFFF, 0x001F, 0x07E0, 0xF800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07FF, 0x27FF, 0x57FF, 0x77FF, 0x9FFF, 0xBFFF, 0xDFFF, 0xFFFF, 0xF81F, 0xF95F, 0xFA5F, 0xFB5F, 0xFC7F, 0xFD7F, 0xFE7F, 0xFEFF, 0x07E0, 0x07E6, 0x07EA, 0x07EE, 0x07F3, 0x07F7, 0x07FB, 0x07FF, 0xF800, 0xF806, 0xF80A, 0xF80E, 0xF813, 0xF817, 0xF81B, 0xF81F, 0xF800, 0xF940, 0xFA40, 0xFBA0, 0xFCE0, 0xFE20, 0xFF20, 0xFFE0, 0xF800, 0x07E0, 0x001F, 0xFFFF, 0xFFFF, 0x001F, 0x07E0, 0xF800, 0x0000, 0xF800, 0x07E0, 0x001F, 0x001F, 0x07E0, 0xF800, 0x0000};
//uint16_t Data[8][8]={0x001F, 0x07E0, 0xF800, 0xFFFF, 0x0000, 0x0000, 0xFFE0, 0x07FF, 0x07E0, 0xF800, 0xFFFF, 0x0000, 0x0000, 0xFFE0, 0x07FF, 0x001F, 0xF800, 0xFFFF, 0x0000, 0x0000, 0xFFE0, 0x07FF, 0x001F, 0x07E0, 0xFFFF, 0x0000, 0x0000, 0xFFE0, 0x07FF, 0x001F, 0x07E0, 0xF800, 0x0000, 0x0000, 0xFFE0, 0x07FF, 0x001F, 0x07E0, 0xF800, 0xFFFF, 0x0000, 0xFFE0, 0x07FF, 0x001F, 0x07E0, 0xF800, 0xFFFF, 0x0000, 0xFFE0, 0x07FF, 0x001F, 0x07E0, 0xF800, 0xFFFF, 0x0000, 0x0000, 0x07FF, 0x001F, 0x07E0, 0xF800, 0xFFFF, 0x0000, 0x0000, 0x0000};
uint16_t Data[8][8]={0xF800, 0x07E0, 0x001F, 0xFFFF, 0x0000, 0x001F, 0x07E0, 0xF800, 0xF800, 0x07E0, 0x001F, 0x0000, 0xFFFF, 0x001F, 0x07E0, 0xF800, 0xF800, 0x07E0, 0x001F, 0xFFFF, 0x0000, 0x001F, 0x07E0, 0xF800, 0xF800, 0x07E0, 0x001F, 0x0000, 0xFFFF, 0x001F, 0x07E0, 0xF800, 0xF800, 0x07E0, 0x001F, 0xFFFF, 0x0000, 0x001F, 0x07E0, 0xF800, 0xF800, 0x07E0, 0x001F, 0x0000, 0xFFFF, 0x001F, 0x07E0, 0xF800, 0xF800, 0x07E0, 0x001F, 0xFFFF, 0x0000, 0x001F, 0x07E0, 0xF800, 0xF800, 0x07E0, 0x001F, 0x0000, 0xFFFF, 0x001F, 0x07E0, 0xF800};

// Pushes a single line to the shift register. Takes into account the reversed polarity.
void PushLine(uint8_t Line){
	for(uint8_t i=0;i<8;i++){
		if((Line>>i)&0x01)
			P2OUT&=~DATA;
		else
			P2OUT|=DATA;
		P2OUT|=CLK;
		__delay_cycles(10);
		P2OUT&=~CLK;
	}
	P2OUT|=STR;
	__delay_cycles(10);
	P2OUT&=~STR;
}

void I2C_start(void){
	P1OUT|=SDA|SCL;
	P1DIR|=SDA|SCL;
	__delay_cycles(I2CDELAY);
	P1OUT&=~SDA;
	P1OUT&=~SCL;
}

void I2C_ack_wait(void){
	P1DIR&=~SDA;
	P1OUT|=SCL;
	P1OUT&=~SCL;
	P1DIR|=SDA;
}

void I2C_ack_give(void){
	P1OUT&=~SDA;
	P1DIR|=SDA;
	P1OUT|=SCL;
	P1OUT&=~SCL;
}

void I2C_send(uint8_t data){
	for(uint8_t i=0;i<8;i++){
		if(data&(0x01<<(7-i)))
			P1OUT|=SDA;
		__delay_cycles(I2CDELAY);
		P1OUT|=SCL;
		__delay_cycles(I2CDELAY);
		P1OUT&=~(SDA|SCL);
	}
	I2C_ack_wait();
}


uint8_t I2Cread(uint8_t device_address, uint8_t reg_address){
	//ADDRESS + REG ADDRESS
	I2C_start();
	//ADDRESS
	I2C_send(device_address);

	I2C_send(reg_address);
	//ADDRESS AND RECEIVE
	I2C_start();

	I2C_send(device_address|0x01);

	uint8_t received=0;
	P1DIR&=~SDA;
	for(uint8_t i=0;i<8;i++){
		P1OUT|=SCL;
		__delay_cycles(I2CDELAY);
		received|=(P1IN&SDA)?(0x01<<(7-i)):0;
		P1OUT&=~SCL;
	}
	I2C_ack_give();
	P1OUT|=SDA|SCL;
	P1DIR&=~(SDA|SCL);
	return received;
}
// Switches MOSFET to change to next color.
void NextColor(void){
	ActiveColor = ((ActiveColor<<0x01)&0x38)?(ActiveColor<<0x01):RFET;
	P2OUT|=0x38;
	P2OUT&=~ActiveColor;
}

void Initialisation(void){
	P1OUT=0x00;
	P2OUT=0x00|RFET|GFET|BFET;		// For the MOSFETs all to be off
	P1DIR=OE|AD0;
	P2DIR=STR|CLK|DATA|RFET|GFET|BFET;

	BCSCTL1 = CALBC1_16MHZ;         // Set DCO to 16MHz factory calibration value
	DCOCTL  = CALDCO_16MHZ;

    TACTL=TASSEL_2+MC_1;			// Timer for color switch
    CCTL0=CCIE;
    TACCR0=999;
    __enable_interrupt();
}

int16_t main(void) {
	Initialisation();
    WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	uint8_t i=0;
	P2OUT&=~BFET;
	while(1){
		//i=I2Cread(MPU6050_ADDRESS,MPU6050_RA_WHO_AM_I);
		//P2OUT|=RFET;
		//P2OUT&=~BFET;
    	//PushLine(i);
    	//NextColor();
    	//__delay_cycles(16000000);
    	//P2OUT|=BFET;
    	//P2OUT&=~RFET;
    	//PushLine(0xFF);

    }
	return 0;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0 (void){
	__disable_interrupt();
	if(Pause){
		PushLine(0x00);
		Pause--;
		return;
	}
	int8_t Line=0;
	if((DutyFrame==0)&&(ActiveColor==BFET)){
		if(++ActiveFrame>MaxFrame){
			ActiveFrame=0;
			Pause=1000;
		}
		for(uint8_t i=0;i<8;i++){
			RedFrame[i]=0x1F&(Data[i][ActiveFrame]>>11);
			GreenFrame[i]=0x1F&(Data[i][ActiveFrame]>>6);
			BlueFrame[i]=0x1F&(Data[i][ActiveFrame]);
		}
	}
	P1OUT|=OE;
	NextColor();
	switch(ActiveColor){
	case RFET:
		for(uint8_t i=0;i<8;i++)
			if(RedFrame[i]>DutyFrame)
				Line|=0x01<<i;
		break;
	case GFET:
		for(uint8_t i=0;i<8;i++)
			if(GreenFrame[i]>DutyFrame)
				Line|=0x01<<i;
		break;
	case BFET:
		for(uint8_t i=0;i<8;i++)
			if(BlueFrame[i]>DutyFrame)
				Line|=0x01<<i;
		DutyFrame=(DutyFrame+0x01)&0x1F;
		break;
	}
	PushLine(Line);
	P1OUT&=~OE;
	__enable_interrupt();
}
