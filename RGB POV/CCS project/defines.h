/**
 *  Header file for global pound defines.
 *
 *  TODO: Check the usage of these defines. Maybe not sane to put everything
 *      here.
 *  TODO: Check if button is actve low or high. Most likely low. Comment it.
 *  TODO: Find out "AD0" and "INT" pin usage. Comment it.
 */

#ifndef _DEFINES_H_
#define _DEFINES_H_

// Pin defines
//PORT 1
#define OE      0x01    // 74HC595 Output-Enable.
#define BUTTON  0x02    // On-board button (active ?).
#define SCL     0x04    // I2C Clock line.
#define SDA     0x08    // I2C Data line.
#define AD0     0x10    // (?).
#define INT     0x20    // (?).

//PORT 2
#define STR     0x01    // 74HC595 Strobe input.
#define CLK     0x02    // SPI Clock line (for 74HC595).
#define DATA    0x04    // SPI Data line (for 74HC595).
#define RFET    0x08    // Red color enable MOSFET (active low).
#define GFET    0x10    // Green color enable MOSFET (active low).
#define BFET    0x20    // Blue color enable MOSFET (active low).

#define SPIDELAY    10  // SPI CLK and STR pulse length (in CPU cycles).

//MPU6050 I2C commands.
#define MPU6050_ADDRESS 0x68*2  // +0x01 for read
#define MPU6050_RA_WHO_AM_I 0x75
#define I2CDELAY    0


/*
 * These do not appear to be used anywhere.
 */
//Color Bits - 0bRRRR RGGG GGGB BBBB
#define REDB    0xF800
#define GREENB  0x07E0
#define BLUEB   0x001F

#endif // _DEFINES_H_
