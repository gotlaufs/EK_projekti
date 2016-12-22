/**
 * RTU Elektronikas Klubs RGB POV.
 *
 *
 * TODO: Add documentation.
 * TODO: Maybe split out data to another file. Maybe not.
 */

#include <stdint.h>
#include <msp430.h>
#include "defines.h"
#include "i2c_bitbang.h"
#include "hc595_bitbang.h"

// GLOBALS
uint8_t ActiveColor=RFET;   //Must be non-zero
uint8_t ActiveFrame=0;
uint8_t DutyFrame=0;
uint8_t RedFrame[8]={0};
uint8_t GreenFrame[8]={0};
uint8_t BlueFrame[8]={0};
uint16_t Pause=0;

uint8_t MaxFrame=10-1;
uint16_t Data[10][8]={
    {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF},
    {0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF},
    {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}
};

// Switches MOSFET to change to next color.
void NextColor(void){
    ActiveColor = ((ActiveColor<<0x01)&0x38)?(ActiveColor<<0x01):RFET;

    P2OUT|=RFET|GFET|BFET;  // All MOSFETs off.
    P2OUT&=~ActiveColor;    // Active color on.
}

void Initialisation(void){
    P1OUT=0x00;
    P2OUT=0x00;
    P2OUT|=RFET|GFET|BFET;      // For the MOSFETs all to be off
    P1OUT&=~OE;
    P1DIR=OE|AD0;
    P2DIR|=RFET|GFET|BFET;
    InitSPI();

    BCSCTL1 = CALBC1_16MHZ;     // Set DCO to 16MHz factory calibration value
    DCOCTL  = CALDCO_16MHZ;

    TACTL=TASSEL_2+MC_1+TACLR;        // Timer for color switch
    TACCR0=1100;
    TA0CCTL0=CCIE;
    __enable_interrupt();
}

int16_t main(void) {
    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer
    Initialisation();

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
    uint8_t i;
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
            Pause=750;
        }
        for(i=0;i<8;i++){
            RedFrame[i]=0x1F&(Data[ActiveFrame][i]>>11);
            GreenFrame[i]=0x1F&(Data[ActiveFrame][i]>>6);
            BlueFrame[i]=0x1F&(Data[ActiveFrame][i]);
        }
    }

    NextColor();

    switch(ActiveColor){
    case RFET:
        for(i=0;i<8;i++)
            if(RedFrame[i]>DutyFrame)
                Line|=0x01<<i;
        break;
    case GFET:
        for(i=0;i<8;i++)
            if(GreenFrame[i]>DutyFrame)
                Line|=0x01<<i;
        break;
    case BFET:
        for(i=0;i<8;i++)
            if(BlueFrame[i]>DutyFrame)
                Line|=0x01<<i;
        DutyFrame=(DutyFrame+0x01)&0x1F;
        break;
    }
    PushLine(Line);
    __enable_interrupt();
}
