# RTU Elektronikas Klubs RGB POV.
 
This is a small toy with 8 RGB diodes that you wave in the air and it draws
something in the air due to human persistence of vision (hence the name).
Use `Color generator.html` to create image for display.
 
## Features:
* 8 RGB diodes;
* 1 Pushbutton;
* MSP430G2553 MCU;
* MPU6050 accelerometer module;
* Small web-app to create image for loading on the device.

Diodes are driven by 74HC595 shift register and 3 MOSFET's that switch on R, G
or B color channel.

## Future features:
* Use accelerometer to sync the display to hand-waving;
* Multiple display image support;
* Loading of new image via UART (don't know how feasible this is).

### Issues
Currently the toy only displays static data that is programmed in the code.
Also the accelerometer is not used.

As of PCB rev 1, both the shift register and the accelerometer module are
connected to the MCU pins where HW I2C and SPI peripherals are not available, so
protocol bit-banging is used.
In a future PCB re-spin this should be fixed and the "i2c_bitbang" and
"hc595_bitbang" libraries should be replaced by proper HW ones.
