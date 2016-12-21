/**
 *  Header file for global pound defines.
 *
 *  TODO: Check the usage of these defines. Maybe not sane to put everything
 *      here.
 */

#ifndef _DEFINES_H_
#define _DEFINES_H_

// Pin defines
//PORT 1
#define OE      0x01
#define BUTTON  0x02
#define SCL     0x04
#define SDA     0x08
#define AD0     0x10
#define INT     0x20

//PORT 2
#define STR     0x01
#define CLK     0x02
#define DATA    0x04
#define RFET    0x08
#define GFET    0x10
#define BFET    0x20

//MPU6050 I2C
#define MPU6050_ADDRESS 0x68*2  // +0x01 for read
#define MPU6050_RA_WHO_AM_I 0x75
#define I2CDELAY    0

//Color Bits - 0bRRRR RGGG GGGB BBBB
#define REDB    0xF800
#define GREENB  0x07E0
#define BLUEB   0x001F

#endif // _DEFINES_H_
