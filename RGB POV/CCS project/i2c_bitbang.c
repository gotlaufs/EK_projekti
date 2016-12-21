/*
 *  I2C bitbang library for RGB POV EK prject.
 *
 *
 * TODO: Add documentation to functions.
 */

#include <msp430.h>
#include "i2c_bitbang.h"
#include "defines.h"

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
    uint8_t i;
    for(i=0;i<8;i++){
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
    uint8_t i;
    for(i=0;i<8;i++){
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
