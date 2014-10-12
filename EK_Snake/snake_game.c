
#include "stm8s.h"

/* pin defs */
#define LED       0x01 /* PORT D */

#define DC_PIN    0x10 /* PORT C */
#define RESET_PIN 0x04 /* PORT C */
#define CS_PIN    0x08 /* PORT C */

#define BUTTON1   0x01 /* PORT B */
#define BUTTON2   0x02 /* PORT B */
#define BUTTON3   0x04 /* PORT B */
#define BUTTON4   0x08 /* PORT B */

#define SET_DATA    GPIOC->ODR |=  DC_PIN   // Set the LCD for DATA INPUT mode  (set the D/~C pin to HIGH)
#define SET_COMMAND GPIOC->ODR &= ~DC_PIN   // Set the LCD for COMMAND mode   (set the D/~C pin to LOW)
#define SET_RESET   GPIOC->ODR &= ~RESET_PIN 
#define CLR_RESET   GPIOC->ODR |=  RESET_PIN
#define SET_CS      GPIOC->ODR &= ~CS_PIN
#define CLR_CS      GPIOC->ODR |=  CS_PIN

volatile uint8_t LCD_RAM[84][6];
volatile uint8_t LCD_X = 0;
volatile uint8_t LCD_Y = 0;
const    uint8_t init_sequence[] = {0x21,   // Switch to extended commands
                                    0xAF,   // Set value of LCD voltage (contrast) 
                                    0x04,   // Set temperature coefficient
                                    0x13,   // Set bias mode to 1:48 (screen is multiplexed that way)
                                    0x20,   // Switch back to regular commands
                                    0x0C,   // Enable normal display (black on white), set to horizontal addressing
                                    0x00};  // End of initialisation sequence

/* Tiles are formed with two uin8_t's in the following format (b describes bit)
 * First two columns are the first variable, second two columns are the second
 * variable.
 * The tiles are saved as two 8 bit numbers instead of a single 16bit, due to
 * the MCU having an 8 bit core - therefore 8 bits should be faster to handle.
 * 
 * b0  b4  b8  b12
 * b1  b5  b9  b13
 * b2  b6  b10 b14
 * b3  b7  b11 b15
 */
const uint8_t snake_tiles[19][2] = {{0x64, 0x26}, /* Straight horizontal */
                                    {0x0B, 0xD0}, /* Straight vertical */

                                    {0x6A, 0xC0}, /* Left-down turn */
                                    {0x65, 0x30}, /* Left-up turn */
                                    {0x0C, 0xA6}, /* Right-down turn */
                                    {0x03, 0x56}, /* Right-up turn */

                                    {0x56, 0x60}, /* Head facing right */
                                    {0x06, 0x65}, /* Head facing left */
                                    {0x0E, 0x68}, /* Head facing up */
                                    {0x16, 0x70}, /* Head facing down */

                                    {0x44, 0x66}, /* Tail going right */
                                    {0x66, 0x44}, /* Tail going left */
                                    {0x0F, 0x30}, /* Tail going up */
                                    {0x0C, 0xF0}, /* Tail going down */

                                    {0x6D, 0xB6}, /* Straight horiz. w/ food */
                                    {0x6B, 0xD6}, /* Straight vert. w/ food */

                                    {0x4A, 0x40}, /* Bait */
                                    {0x00, 0x00}  /* Blank */
};

enum Snake_tile{ /* These correspond to the entries in the snake_tiles array */
    S_H = 0,
    S_V,

    S_LD,
    S_LU,
    S_RD,
    S_RU,

    S_HR,
    S_HL,
    S_HU,
    S_HD,

    S_TR,
    S_TL,
    S_TU,
    S_TD,

    S_HF,
    S_VF,

    S_BAIT,
    S_BLANK
};

enum snake_orientation{
    INITIAL = 0,  
    LEFT,
    RIGHT,
    UP,
    DOWN,
    DEAD
} snake_heading = INITIAL;

volatile uint8_t Snake_array[21][10] = {{0}}; 

struct position{
    volatile uint8_t x;
    volatile uint8_t y;
    volatile enum snake_orientation direction;
};

volatile struct position bait_pos = {0, 0};
volatile struct snake_pos{
    struct position tail;
    struct position head;
    uint8_t length;
} snake = {{0,0, INITIAL},{0,0, INITIAL}, 0};


void gotoX(uint8_t X);
void gotoY(uint8_t Y);
void writeData(uint8_t data);

inline void delay16b(uint16_t delay)
{
    uint16_t i;
    for(i = 0; i < delay; i++)
        __asm__("nop");
}

inline void delay8b(uint8_t delay)
{
    uint8_t i;
    for(i = 0; i < delay; i++)
        __asm__("nop");
}

/**
 * @brief Waits for one of the bits of the register set in the bitmask to go high
 * 
 * @param reg  Pointer to register 
 * @param mask Bitmask of bits to wait for
 */
inline void waitForHi(uint8_t* reg, uint8_t mask)
{
    while(!(*reg & mask))
        __asm__("nop");
}

/**
 * @brief Waits for one of the bits of the register set in the bitmask to go low
 * 
 * @param reg  Pointer to register 
 * @param mask Bitmask of bits to wait for
 */
inline void waitForLo(uint8_t* reg, uint8_t mask)
{
    while(*reg & mask)
        __asm__("nop");
}

void initLCD(void)
{
    uint16_t x;
    uint8_t i=0;
    delay16b(60000);
    SET_RESET;
    delay16b(60000);

    CLR_RESET;
    SET_CS;
    SET_COMMAND;
    delay16b(2540);

    while(init_sequence[i] != 0x00){
        waitForLo(&SPI->SR, 0x80);  /* Wait while SPI is busy transmitting data */
        SPI->DR = init_sequence[i];
        i++;
    }

    gotoX(0);
    gotoY(0);
    for(i = 0; i < 6; i++){
        gotoY(i);
        for(x=0; x < 84; x++){
            writeData(0);
            LCD_RAM[x][i] = 0;
        }
    }
}

void gotoX(uint8_t X_address)
{
    LCD_X = X_address;
    waitForLo(&SPI->SR, 0x80);  /* Wait while SPI is busy transmitting data */
    SET_COMMAND;
    SPI->DR = X_address | 0x80;
}

void gotoY(uint8_t Y_address)
{
    LCD_Y = Y_address;
    waitForLo(&SPI->SR, 0x80);  /* Wait while SPI is busy transmitting data */
    SET_COMMAND;
    SPI->DR = (Y_address & 0x07) | 0x40;
}

void writeDataFast(uint8_t data)
{
    waitForLo(&SPI->SR, 0x80);  /* Wait while SPI is busy transmitting data */
    SET_DATA;
    SPI->DR = data;
}

void writeData(uint8_t data)
{
    LCD_RAM[LCD_X][LCD_Y] = data;
    LCD_X++;
    if( LCD_X > 83 ){
        LCD_X = 0;
        LCD_Y++;
        if( LCD_Y > 5)
                LCD_Y = 0;
    }
    waitForLo(&SPI->SR, 0x80);  /* Wait while SPI is busy transmitting data */
    SET_DATA;
    SPI->DR = data;
}

void refreshBlock(uint8_t x, uint8_t y)
{
    gotoX(x);
    gotoY(y);
    writeDataFast(LCD_RAM[LCD_X][LCD_Y]);
}

void refreshSnakeTile(uint8_t x, uint8_t y)
{
    uint8_t i;
    uint8_t lcd_tmp_x = x<<2;
    uint8_t lcd_tmp_y = y>>1;
    gotoX(lcd_tmp_x);
    gotoY(lcd_tmp_y);
    for(i = 0; i < 4; i++)
        writeDataFast(LCD_RAM[lcd_tmp_x + i][lcd_tmp_y]);
}

void setPixel(uint8_t x, uint8_t y)
{
    uint8_t row = y >> 3;
    uint8_t bit = 0x01 << (y & 0x07);
    gotoX(x);
    gotoY(row);
    writeData( LCD_RAM[x][row] | bit );
}

void clrPixel(uint8_t x, uint8_t y)
{
    uint8_t row = y >> 3;
    uint8_t bit = 1 << (y & 0x07);
    gotoX(x);
    gotoY(row);
    writeData( LCD_RAM[LCD_X][LCD_Y] & ~bit );
}

uint8_t ADCread(uint8_t channel)
{
    ADC1->CSR &=~ 0x0F;
    ADC1->CSR |= channel & 0x0F;
    ADC1->CR1 |= (1<<0);  /* initiate conversion */
    waitForHi( &ADC1->CSR, 1 << 7 );
    ADC1->CSR &= ~(1<<7); /* Clear conversion-done flag */
    return ADC1->DRH;
}

// void drawSnakeTile(uint8_t x, uint8_t y, uint8_t tileID)
// {
//   gotoX(x << 2);
//   gotoY(y >> 1);
//   if( y & 0x01 ){ /* Top tile */
//     writeData(snake_tiles[tileID][0] & 0xF0);
//     writeData(snake_tiles[tileID][0] << 4);
//     writeData(snake_tiles[tileID][1] & 0xF0);
//     writeData(snake_tiles[tileID][1] << 4);
//   }
//   else{
//     writeData(snake_tiles[tileID][0] >> 4);
//     writeData(snake_tiles[tileID][0] & 0x0F);
//     writeData(snake_tiles[tileID][1] >> 4);
//     writeData(snake_tiles[tileID][1] & 0x0F);
//   }
// }

void setSnakeTile(uint8_t x, uint8_t y, enum Snake_tile tileID)
{
    uint8_t tmp_x = x << 2;
    uint8_t tmp_y = y >> 1;

    Snake_array[x][y] = tileID;
    
    if( y & 0x01 ){ /* Top tile */
        LCD_RAM[tmp_x][tmp_y] &= ~0xF0;
        LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][0] & 0xF0;
        tmp_x++;
        LCD_RAM[tmp_x][tmp_y] &= ~0xF0;
        LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][0] << 4;
        tmp_x++;
        LCD_RAM[tmp_x][tmp_y] &= ~0xF0;
        LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][1] & 0xF0;
        tmp_x++;    
        LCD_RAM[tmp_x][tmp_y] &= ~0xF0;
        LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][1] << 4;
    }
    else{
        LCD_RAM[tmp_x][tmp_y] &= ~0x0F;
        LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][0] >> 4;
        tmp_x++;
        LCD_RAM[tmp_x][tmp_y] &= ~0x0F;
        LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][0] & 0x0F;
        tmp_x++;
        LCD_RAM[tmp_x][tmp_y] &= ~0x0F;
        LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][1] >> 4;
        tmp_x++;    
        LCD_RAM[tmp_x][tmp_y] &= ~0x0F;
        LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][1] & 0x0F;
    }

    refreshSnakeTile(x,y);
}

inline void setSnakeHeadTile(enum Snake_tile tileID)
{
    setSnakeTile(snake.head.x, snake.head.y, tileID);
}

inline void setSnakeTailTile(enum Snake_tile tileID)
{
    setSnakeTile(snake.tail.x, snake.tail.y, tileID);
}

void iterateSnakeHead()
{
    /* Move the head */
    switch(snake.head.direction){
        case INITIAL:
            setSnakeTile(12, 6, S_TD);
            setSnakeTile(12, 7, S_V);
            setSnakeTile(12, 8, S_V);
            setSnakeTile(12, 9, S_HD);

            snake.tail.x = 12;
            snake.tail.y = 6;

            snake.head.x = 12;
            snake.head.y = 9;
            
            snake.length = 4;
            snake.head.direction = DOWN;
            snake.tail.direction = DOWN;
            return; /* Quit function, everything is set up*/

        case LEFT:
            setSnakeHeadTile(S_H);
            snake.head.x--;
            if(snake.head.x > 20)
                snake.head.x = 20;
            setSnakeHeadTile(S_HL);
            break;

        case RIGHT: 
            setSnakeHeadTile(S_H);
            snake.head.x++;
            if(snake.head.x > 20)
                snake.head.x = 0;
            setSnakeHeadTile(S_HR);
            break;

        case UP:
            setSnakeHeadTile(S_V);
            snake.head.y--;
            if(snake.head.y > 9)
                snake.head.y = 9;
            setSnakeHeadTile(S_HU);
            break;

        case DOWN: 
            setSnakeHeadTile(S_V);
            snake.head.y++;
            if(snake.head.y > 9)
                snake.head.y = 0;
            setSnakeHeadTile(S_HD);
            break;

        case DEAD:
            break;
    }
}

void iterateSnakeTail()
{
    setSnakeTailTile(S_BLANK);

    switch(snake.tail.direction){
        case RIGHT:
            snake.tail.x++;
            if(snake.tail.x > 20)
                snake.tail.x = 0;

            switch(Snake_array[snake.tail.x][snake.tail.y]){
                case(S_LU): snake.tail.direction = UP;    break;
                case(S_LD): snake.tail.direction = DOWN;  break;
                default:    snake.tail.direction = RIGHT; break;
            }
            break;

        case LEFT:
            snake.tail.x--;
            if(snake.tail.x > 20)
                snake.tail.x = 20;

            switch(Snake_array[snake.tail.x][snake.tail.y]){
                case(S_RU): snake.tail.direction = UP;    break;
                case(S_RD): snake.tail.direction = DOWN;  break;
                default:    snake.tail.direction = LEFT;  break;
            }
            break;

        case UP:
            snake.tail.y--;
            if(snake.tail.y > 9)
                snake.tail.y = 9;

            switch(Snake_array[snake.tail.x][snake.tail.y]){
                case(S_LD): snake.tail.direction = LEFT;  break;
                case(S_RD): snake.tail.direction = RIGHT; break;
                default:    snake.tail.direction = UP;    break;
            }
            break;

        case DOWN:
            snake.tail.y++;
            if(snake.tail.y > 9)
                snake.tail.y = 0;

            switch(Snake_array[snake.tail.x][snake.tail.y]){
                case(S_LU): snake.tail.direction = LEFT;  break;
                case(S_RU): snake.tail.direction = RIGHT; break;
                default:    snake.tail.direction = DOWN;  break;
            }
            break;
    }

    switch(snake.tail.direction){
        case(RIGHT): setSnakeTailTile(S_TR); break;
        case(LEFT):  setSnakeTailTile(S_TL); break;
        case(UP):    setSnakeTailTile(S_TU); break;
        case(DOWN):  setSnakeTailTile(S_TD); break;
    }
}

void moveSnake(enum snake_orientation move_direction)
{
    switch(move_direction){
        case RIGHT:
            switch(snake.head.direction){
                case UP:    setSnakeHeadTile(S_RD); break;
                case DOWN:  setSnakeHeadTile(S_RU); break;  
                default:    setSnakeHeadTile(S_H);  break;
            }
            snake.head.x++;
            if(snake.head.x > 20)
                snake.head.x = 0;
            setSnakeHeadTile(S_HR);
            break;

        case LEFT:
            switch(snake.head.direction){
                case UP:    setSnakeHeadTile(S_LD); break;
                case DOWN:  setSnakeHeadTile(S_LU); break;
                default:    setSnakeHeadTile(S_H);  break;
            }
            snake.head.x--;
            if(snake.head.x > 20)
                snake.head.x = 20;
            setSnakeHeadTile(S_HL);
            break;

        case UP:
            switch(snake.head.direction){
                case RIGHT: setSnakeHeadTile(S_LU); break;
                case LEFT:  setSnakeHeadTile(S_RU); break;
                default:    setSnakeHeadTile(S_V);  break;
            }
            snake.head.y--;
            if(snake.head.y > 9)
                snake.head.y = 9;
            setSnakeHeadTile(S_HU);
            break;

        case DOWN:
            switch(snake.head.direction){
                case RIGHT: setSnakeHeadTile(S_LD); break;
                case LEFT:  setSnakeHeadTile(S_RD); break;
                default:    setSnakeHeadTile(S_V);  break;
            }
            snake.head.y++;
            if(snake.head.y > 9)
                snake.head.y = 0;
            setSnakeHeadTile(S_HD);
            break;
    }

    snake.head.direction = move_direction;

    iterateSnakeTail();
}

int main(void){
    uint8_t volatile j = 0, i = 0, k =0;

    /* GPIO config */
    GPIOD->DDR |= LED;    /* Pin directions */
    GPIOD->CR1 |= LED;    /* Set pin to high speed push-pull */
    GPIOD->CR2 |= LED;
    
    GPIOC->DDR |= (1<<6)|(1<<5)|DC_PIN|RESET_PIN|CS_PIN;  /* SPI MOSI and SPI CLK */
    GPIOC->CR1 |= (1<<6)|(1<<5)|DC_PIN|RESET_PIN|CS_PIN;  /* Fast push pull for quick SPI transmissions */
    GPIOC->CR2 |= (1<<6)|(1<<5)|DC_PIN|RESET_PIN|CS_PIN;

    GPIOB->DDR &=~ (BUTTON1 | BUTTON2 | BUTTON3 | BUTTON4); /* Set to input */
    GPIOB->CR1 |=  (BUTTON1 | BUTTON2 | BUTTON3 | BUTTON4); /* Pull-up without interrupts */

    CLR_CS;
    
    /* CLK config */
    CLK->SWCR  |= 1<<1;   /* Enable clock source switch */
    CLK->SWR    = 0xE1;   /* Switch to high speed internal clock */
    CLK->CKDIVR = 0x00;   /* Set CPU and HSI prescalers to 1 */
    CLK->PCKENR1= (1<<1); /* Enable SPI clock */
    CLK->PCKENR2= (1<<3); /* Enable ADC clock */

    /* SPI config */
    SPI->CR1  = (1<<6)|(1<<2)|(0x3<<3);   /* Enable SPI, set to master mode */
    SPI->CR2  = (1<<7)|(1<<6);            /* Transmit only */
    SPI->CR2 |= (1<<0)|(1<<1);

    /* ADC config */
    ADC1->CSR = (0x7<<4); /* Prescaler fmaster/6 */
    //ADC1->CR1 = (1<<0); /* Turn ADC on */
    ADC1->CR2 = 0; /* Data aligned to the left */
    initLCD();

    while(1){
        GPIOD->ODR ^= LED;
        
        for(i = 0; i < 16; i++)
            delay16b(65000);


        if(!(GPIOB->IDR & BUTTON1)){
            if(snake.head.direction != DOWN)
                moveSnake(UP);
        }
        else if(!(GPIOB->IDR & BUTTON2)){
            if(snake.head.direction != UP)
                moveSnake(DOWN);
        }
        else if(!(GPIOB->IDR & BUTTON3)){
            if(snake.head.direction != RIGHT)
                moveSnake(LEFT);
        }
        else if(!(GPIOB->IDR & BUTTON4)){
            if(snake.head.direction != LEFT)
                moveSnake(RIGHT);
        }
        else{
            iterateSnakeHead();
            iterateSnakeTail();
        }
    }
}