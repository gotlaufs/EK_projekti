/**
 * Shift register 74HC595 bitbang library for RGB POV EK prject.
 *
 *
 * TODO: Add documentation to functions.
 */
#include <msp430.h>
#include "hc595_bitbang.h"
#include "defines.h"

/**
 * Initialize SPI pins.
 */
void InitSPI(void){
    P2DIR|=STR|CLK|DATA;
}


/**
 * Pushes a single line to the shift register. Takes into account the reversed
 * polarity.
 */
void PushLine(uint8_t Line){
    uint8_t i;
    for(i=0;i<8;i++){
        if((Line>>i)&0x01)
            P2OUT&=~DATA;
        else
            P2OUT|=DATA;
        P2OUT|=CLK;
        __delay_cycles(SPIDELAY);
        P2OUT&=~CLK;
    }
    P2OUT|=STR;
    __delay_cycles(SPIDELAY);
    P2OUT&=~STR;
}
