/**
 * RTU Elektronikas Klubs RGB POV.
 *
 *
 * TODO: Add documentation.
 * TODO: Edit the color generator html to output line by line array, not one big
 * blob, also limit line length to 80 chars.
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
uint8_t MaxFrame=8-1;
//uint16_t Data[8][11]={0x0000, 0xF800, 0x07E0, 0x001F, 0x001F, 0x07E0, 0xF800, 0x0000, 0xF800, 0x07E0, 0x001F, 0xFFFF, 0xFFFF, 0x001F, 0x07E0, 0xF800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x07FF, 0x27FF, 0x57FF, 0x77FF, 0x9FFF, 0xBFFF, 0xDFFF, 0xFFFF, 0xF81F, 0xF95F, 0xFA5F, 0xFB5F, 0xFC7F, 0xFD7F, 0xFE7F, 0xFEFF, 0x07E0, 0x07E6, 0x07EA, 0x07EE, 0x07F3, 0x07F7, 0x07FB, 0x07FF, 0xF800, 0xF806, 0xF80A, 0xF80E, 0xF813, 0xF817, 0xF81B, 0xF81F, 0xF800, 0xF940, 0xFA40, 0xFBA0, 0xFCE0, 0xFE20, 0xFF20, 0xFFE0, 0xF800, 0x07E0, 0x001F, 0xFFFF, 0xFFFF, 0x001F, 0x07E0, 0xF800, 0x0000, 0xF800, 0x07E0, 0x001F, 0x001F, 0x07E0, 0xF800, 0x0000};
//uint16_t Data[8][8]={0x001F, 0x07E0, 0xF800, 0xFFFF, 0x0000, 0x0000, 0xFFE0, 0x07FF, 0x07E0, 0xF800, 0xFFFF, 0x0000, 0x0000, 0xFFE0, 0x07FF, 0x001F, 0xF800, 0xFFFF, 0x0000, 0x0000, 0xFFE0, 0x07FF, 0x001F, 0x07E0, 0xFFFF, 0x0000, 0x0000, 0xFFE0, 0x07FF, 0x001F, 0x07E0, 0xF800, 0x0000, 0x0000, 0xFFE0, 0x07FF, 0x001F, 0x07E0, 0xF800, 0xFFFF, 0x0000, 0xFFE0, 0x07FF, 0x001F, 0x07E0, 0xF800, 0xFFFF, 0x0000, 0xFFE0, 0x07FF, 0x001F, 0x07E0, 0xF800, 0xFFFF, 0x0000, 0x0000, 0x07FF, 0x001F, 0x07E0, 0xF800, 0xFFFF, 0x0000, 0x0000, 0x0000};
uint16_t Data[8][8]={0xF800, 0x07E0, 0x001F, 0xFFFF, 0x0000, 0x001F, 0x07E0, 0xF800, 0xF800, 0x07E0, 0x001F, 0x0000, 0xFFFF, 0x001F, 0x07E0, 0xF800, 0xF800, 0x07E0, 0x001F, 0xFFFF, 0x0000, 0x001F, 0x07E0, 0xF800, 0xF800, 0x07E0, 0x001F, 0x0000, 0xFFFF, 0x001F, 0x07E0, 0xF800, 0xF800, 0x07E0, 0x001F, 0xFFFF, 0x0000, 0x001F, 0x07E0, 0xF800, 0xF800, 0x07E0, 0x001F, 0x0000, 0xFFFF, 0x001F, 0x07E0, 0xF800, 0xF800, 0x07E0, 0x001F, 0xFFFF, 0x0000, 0x001F, 0x07E0, 0xF800, 0xF800, 0x07E0, 0x001F, 0x0000, 0xFFFF, 0x001F, 0x07E0, 0xF800};


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
    P1DIR=OE|AD0;
    P2DIR|=RFET|GFET|BFET;
    InitSPI();

    BCSCTL1 = CALBC1_16MHZ;     // Set DCO to 16MHz factory calibration value
    DCOCTL  = CALDCO_16MHZ;

    TACTL=TASSEL_2+MC_1;        // Timer for color switch
    CCTL0=CCIE;
    TACCR0=999;
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
    __disable_interrupt();
    if(Pause){
        PushLine(0x00);
        Pause--;
        return;
    }

    int8_t Line=0;
    uint8_t i;
    if((DutyFrame==0)&&(ActiveColor==BFET)){
        if(++ActiveFrame>MaxFrame){
            ActiveFrame=0;
            Pause=1000;
        }
        for(i=0;i<8;i++){
            RedFrame[i]=0x1F&(Data[i][ActiveFrame]>>11);
            GreenFrame[i]=0x1F&(Data[i][ActiveFrame]>>6);
            BlueFrame[i]=0x1F&(Data[i][ActiveFrame]);
        }
    }

    // Turn off shift register outputs, while loading the next color.
    // TODO: Check if this is actually needed?
    // Output strobe should be enough.
    P1OUT|=OE;
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
    P1OUT&=~OE;
    __enable_interrupt();
}
