/*
 * ATTiny 24A dice project
 * Accompanying information can be found at http://0x4C4A.com/attiny-dice
 */

#include <avr/io.h>
#include <avr/interrupt.h>

/********************** Global variables **********************/
/* Current position of the scrolling dice image*/
volatile uint8_t iterator;

/* Current operation mode of the dice */
volatile enum {
    DEEPSLEEP = 0,  /* Waiting for button push to wake up */
    WAITING,        /* LEDs on, waiting for button push to roll */
    ROLLING,        /* Rolling the "dice" (button is held) */
    SLOWING         /* Button is released, "dice" roll slowing down */
} opMode;


/*********** Stuff related to the displayed patterns ************/
/* See the next comment */
struct sLedRegs{
    uint8_t DirA;   /* Data to be written to the GPIOA pin direction register */
    uint8_t OutA;   /* Data to be written to the GPIOA pin output register */
    uint8_t DirB;   /* Data to be written to the GPIOB pin direction register */
    uint8_t OutB;   /* Data to be written to the GPIOB pin output register */
};

/* Describes register settings for lighting specific diodes in the charlieplexed matrix */
struct sLedRegs ledRegisters[3][3] = {
    {{0x18, 0x10, 0x00, 0x00}, {0x24, 0x20, 0x00, 0x00}, {0x40, 0x40, 0x04, 0x00}},
    {{0x18, 0x08, 0x00, 0x00}, {0x24, 0x04, 0x00, 0x00}, {0x40, 0x00, 0x04, 0x04}},
    {{0x30, 0x20, 0x00, 0x00}, {0x60, 0x40, 0x00, 0x00}, {0xC0, 0x80, 0x00, 0x00}}
};

/* Frames describing the LED patterns to be shown
 * 0x04 - first LED, 0x02 - second LED, 0x01 - third LED
 * 0x04 + 0x02 = 0x06 : first and second LED etc. */
#define FULL_FRAME_COUNT 21
#define UNIQUE_FRAME_COUNT 18
uint8_t frames[FULL_FRAME_COUNT] = {
    /* One */
    0x00,   /* --- */
    0x02,   /* -X- */
    0x00,   /* --- */
    /* Two */
    0x04,   /* X-- */
    0x00,   /* --- */
    0x01,   /* --X */
    /* Three */
    0x01,   /* --X */
    0x02,   /* -X- */
    0x04,   /* X-- */
    /* Four */
    0x05,   /* X-X */
    0x00,   /* --- */
    0x05,   /* X-X */
    /* Five */
    0x05,   /* X-X */
    0x02,   /* -X- */
    0x05,   /* X-X */
    /* Six */
    0x05,   /* X-X */
    0x05,   /* X-X */
    0x05,   /* X-X */
    /* One - duplicate, so that looping is easier */
    0x00,   /* --- */
    0x02,   /* -X- */
    0x00    /* --- */
};


/*********** Helper functions ************/
/* Returns 1 if the button at PA0 is pushed and 0 otherwise */
inline uint8_t buttonIsPressed()
{
    return !(PINA & 0x01);
}

/* Turns on specified LED, if ledOn != 0 (All other LEDs are turned off, regardless) */
void charliePlex(uint8_t x, uint8_t y, uint8_t ledOn)
{
    PORTA = (ledOn ? ledRegisters[y][x].OutA : 0x00) | 0x01;    /* Button @ PA0 needs a pull-up */
    DDRA  =  ledOn ? ledRegisters[y][x].DirA : 0x00;
    PORTB =  ledOn ? ledRegisters[y][x].OutB : 0x00;
    DDRB  =  ledOn ? ledRegisters[y][x].DirB : 0x00;
}

/*********** Main function - where all the magic happens ************/
int main(void)
{
    /* Disable USI and ADC peripherals for reduced power consumption */
    PRR = 0x03;

    /* Configure button as interrupt source */
    GIMSK  = 1<<4;      /* Enable pin change 0 interrupt */
    PCMSK0 = 0x01;      /* Set PA0 as pin change 0 interrupt generator */

    /* Set up Timer0 for LED multiplexing */
    TCCR0A = 0x02;      /* Timer mode - upon reaching OCR0A, reset timer value to 0 */
    TCCR0B = 0x01;      /* Set other count mode bits, start counter */
    TCNT0  = 0x00;      /* Set timer counter to zero */
    OCR0A  = 0x01;      /* Compare the timer counter value to this number*/
    TIMSK0 = 1<<1;      /* Enable interrupt for when timer value reaches OCR0A */

    /* Set up Timer1 for delay managing */
    TCCR1A = 0x00;      /* Timer mode - upon reaching OCR1A, reset timer value to 0 */
    TCCR1B = 0x09;      /* Setting other count mode bits, and start counter */
    TCNT1  = 0x0000;    /* Set timer counter to zero */
    OCR1A  = 0x03FF;    /* Compare the timer counter value to this number*/
    TIMSK1 = 1<<1;      /* Enable interrupt for when timer value reaches OCR1A */

    /* Read last roll from EEPROM */
    EEAR  = 0x00;       /* Last roll is stored in the 0x00 EEPROM address */
    EECR |= 1<<0;       /* Initiate a read from the specified address */
    iterator = EEDR;    /* Use the just-read value */
    if(iterator > (UNIQUE_FRAME_COUNT-1))   /* Protection against corrupt data */
        iterator = 0;

    /* Set up the variables */
    opMode = DEEPSLEEP;
    charliePlex(0,0,0); /* Turn all LEDs off */

    /* Enable interrupt calling */
    sei();

    while(1)
    {
        if(opMode == DEEPSLEEP)
            MCUCR = 0x20 | 0x10;    /* Enable sleep and set the "power down" sleep mode */
        else
            MCUCR = 0x20;           /* Enable sleep and set the "idle" sleep mode */

        __asm("SLEEP");             /* Go to sleep */
    }
}


/************* Interrupt functions **************/
/* Timer0 interrupt - seamlessly multiplexes the diodes at a high frequency */
ISR(TIM0_COMPA_vect, ISR_BLOCK)
{
    static uint8_t i = 0;   /* Current diode X */
    static uint8_t k = 0;   /* Current diode Y */

    if(++i > 2)
    {
        i = 0;
        if(++k > 2)
            k = 0;
    }

    charliePlex(i,k,frames[k + iterator] & (1<<i));
}

/* Timer1 interrupt - for switching modes, auto-off etc. */
ISR(TIM1_COMPA_vect, ISR_BLOCK)
{
    switch(opMode)
    {
        case ROLLING:
            OCR1A = 0x0001;
            if(++iterator > (UNIQUE_FRAME_COUNT-1))
                iterator = 0;
            break;

        case SLOWING:
            if(++iterator > (UNIQUE_FRAME_COUNT-1))
                iterator = 0;

            OCR1A += 5;
            if(OCR1A > 200)         /* It's rolled long enough */
            {
                if(iterator % 3)
                    break;          /* If display is between numbers, roll further */

                OCR1A = 10*1000;    /* ~10s timeout timer for wait-mode */
                TCNT1 = 0x0000;

                /* Save the roll value to EEPROM */
                uint8_t timeout = 0;
                while((EECR & 0x02) && (timeout++ < 60))
                    __asm("NOP");   /* Wait until EEPROM is available */
                if(!(EECR & 0x02))  /* If EEPROM is available, write the roll value */
                {
                    EECR &= ~(0x3<<4);  /* Atomic write mode */
                    EEDR  = iterator;
                    EEAR  = 0x00;
                    EECR |= 1<<2;   /* Enable EEPROM programming */
                    EECR |= 1<<1;   /* Program the EEPROM */
                }

                opMode = WAITING;
            }
            break;

        case WAITING:

            TCCR0B &= ~0x07;            /* Turn off Timer0 to save power */
            TCCR1B &= ~0x07;            /* Turn off Timer1 to save power */

            if(TIFR0 & 0x02)
                TIFR0 |= 0x02;      /* If Timer0 interrupt was due, cancel it */

            charliePlex(0,0,0);         /* Turn off any LED that might be on */

            opMode = DEEPSLEEP;         /* Send controller to deep sleep mode */

            break;

        default:
            break;  /* This interrupt shouldn't be called under any other opModes */
    }
}

/* PA0 button interrupt */
ISR(PCINT0_vect, ISR_BLOCK)
{
    switch(opMode)
    {
        case DEEPSLEEP: /* Wake the device up, if button is pushed while in deep sleep */
            if(buttonIsPressed())   /* Only on button press, not release */
            {
                TCCR0B &= ~0x07;
                TCCR0B |=  0x04;    /* Set Timer0 clock to mainClk/256 */

                OCR1A = 10*1000;    /* ~10s timeout timer for wait-mode */
                TCNT1 = 0x0001;

                TCCR1B &= ~0x07;
                TCCR1B |=  0x05;    /* Set Timer1 clock to mainClk/1024 */

                opMode = WAITING;
            }
            break;

        case WAITING:   /* If button is pushed while waiting, initiate roll */
            if(buttonIsPressed())   /* Only on button press, not release */
            {
                OCR1A = 0x0001;
                TCNT1 = 0x0000;     /* Reset Timer1 to 0 */
                opMode = ROLLING;
            }
            break;

        case ROLLING:   /* If rolling and button is released, start slowing the roll */
            if(!buttonIsPressed())  /* Only on button release, not press */
                opMode = SLOWING;
            break;

        case SLOWING:   /* If button is pressed again while the die is slowing, speed it up again */
            if(buttonIsPressed())   /* Only on button press, not release */
            {
                OCR1A = 0x0001;
                TCNT1 = 0x0000;     /* Reset Timer1 to 0 */
                opMode = ROLLING;
            }
            break;
    }
}