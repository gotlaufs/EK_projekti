;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (Apr  5 2014) (Linux)
; This file was generated Mon Oct 13 02:05:09 2014
;--------------------------------------------------------
	.module snake_game
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _snake_tiles
	.globl _init_sequence
	.globl _main
	.globl _moveSnake
	.globl _iterateSnakeTail
	.globl _iterateSnakeHead
	.globl _setSnakeTile
	.globl _ADCread
	.globl _clrPixel
	.globl _setPixel
	.globl _refreshSnakeTile
	.globl _refreshBlock
	.globl _writeDataFast
	.globl _initLCD
	.globl _snake
	.globl _bait_pos
	.globl _Snake_array
	.globl _snake_heading
	.globl _LCD_Y
	.globl _LCD_X
	.globl _LCD_RAM
	.globl _gotoX
	.globl _gotoY
	.globl _writeData
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
_LCD_RAM::
	.ds 504
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area INITIALIZED
_LCD_X::
	.ds 1
_LCD_Y::
	.ds 1
_snake_heading::
	.ds 1
_Snake_array::
	.ds 210
_bait_pos::
	.ds 3
_snake::
	.ds 7
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG
__start__stack:
	.ds	1

;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area DABS (ABS)
;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area HOME
__interrupt_vect:
	int s_GSINIT ;reset
	int 0x0000 ;trap
	int 0x0000 ;int0
	int 0x0000 ;int1
	int 0x0000 ;int2
	int 0x0000 ;int3
	int 0x0000 ;int4
	int 0x0000 ;int5
	int 0x0000 ;int6
	int 0x0000 ;int7
	int 0x0000 ;int8
	int 0x0000 ;int9
	int 0x0000 ;int10
	int 0x0000 ;int11
	int 0x0000 ;int12
	int 0x0000 ;int13
	int 0x0000 ;int14
	int 0x0000 ;int15
	int 0x0000 ;int16
	int 0x0000 ;int17
	int 0x0000 ;int18
	int 0x0000 ;int19
	int 0x0000 ;int20
	int 0x0000 ;int21
	int 0x0000 ;int22
	int 0x0000 ;int23
	int 0x0000 ;int24
	int 0x0000 ;int25
	int 0x0000 ;int26
	int 0x0000 ;int27
	int 0x0000 ;int28
	int 0x0000 ;int29
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area GSINIT
__sdcc_gs_init_startup:
__sdcc_init_data:
; stm8_genXINIT() start
	ldw x, #l_DATA
	jreq	00002$
00001$:
	clr (s_DATA - 1, x)
	decw x
	jrne	00001$
00002$:
	ldw	x, #l_INITIALIZER
	jreq	00004$
00003$:
	ld	a, (s_INITIALIZER - 1, x)
	ld	(s_INITIALIZED - 1, x), a
	decw	x
	jrne	00003$
00004$:
; stm8_genXINIT() end
	.area GSFINAL
	jp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME
	.area HOME
__sdcc_program_startup:
	jp	_main
;	return from main will return to caller
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CODE
;	snake_game.c: 163: void initLCD(void)
;	-----------------------------------------
;	 function initLCD
;	-----------------------------------------
_initLCD:
	sub	sp, #9
;	snake_game.c: 128: for(i = 0; i < delay; i++)
	clrw	x
00117$:
	cpw	x, #0xea60
	jrnc	00107$
;	snake_game.c: 129: __asm__("nop");
	nop
;	snake_game.c: 128: for(i = 0; i < delay; i++)
	incw	x
	jra	00117$
;	snake_game.c: 167: delay16b(60000);
00107$:
;	snake_game.c: 168: SET_RESET;
	ldw	x, #0x500a
	ld	a, (x)
	and	a, #0xfb
	ld	(x), a
;	snake_game.c: 128: for(i = 0; i < delay; i++)
	clrw	x
00120$:
	cpw	x, #0xea60
	jrnc	00109$
;	snake_game.c: 129: __asm__("nop");
	nop
;	snake_game.c: 128: for(i = 0; i < delay; i++)
	incw	x
	jra	00120$
;	snake_game.c: 169: delay16b(60000);
00109$:
;	snake_game.c: 171: CLR_RESET;
	ldw	x, #0x500a
	ld	a, (x)
	or	a, #0x04
	ld	(x), a
;	snake_game.c: 172: SET_CS;
	ldw	x, #0x500a
	ld	a, (x)
	and	a, #0xf7
	ld	(x), a
;	snake_game.c: 173: SET_COMMAND;
	ldw	x, #0x500a
	ld	a, (x)
	and	a, #0xef
	ld	(x), a
;	snake_game.c: 128: for(i = 0; i < delay; i++)
	clrw	x
00123$:
	cpw	x, #0x09ec
	jrnc	00140$
;	snake_game.c: 129: __asm__("nop");
	nop
;	snake_game.c: 128: for(i = 0; i < delay; i++)
	incw	x
	jra	00123$
;	snake_game.c: 176: while(init_sequence[i] != 0x00){
00140$:
	ldw	x, #_init_sequence+0
	ldw	(0x08, sp), x
	clr	(0x01, sp)
00101$:
	clrw	x
	ld	a, (0x01, sp)
	ld	xl, a
	addw	x, (0x08, sp)
	ld	a, (x)
	tnz	a
	jreq	00103$
;	snake_game.c: 159: while(*reg & mask)
00112$:
	ldw	y, #0x5203
	ld	a, (y)
	sll	a
	jrnc	00115$
;	snake_game.c: 160: __asm__("nop");
	nop
	jra	00112$
;	snake_game.c: 177: waitForLo(&SPI->SR, 0x80);  /* Wait while SPI is busy transmitting data */
00115$:
;	snake_game.c: 178: SPI->DR = init_sequence[i];
	ld	a, (x)
	ldw	x, #0x5204
	ld	(x), a
;	snake_game.c: 179: i++;
	inc	(0x01, sp)
	jra	00101$
00103$:
;	snake_game.c: 182: gotoX(0);
	push	#0x00
	call	_gotoX
	pop	a
;	snake_game.c: 183: gotoY(0);
	push	#0x00
	call	_gotoY
	pop	a
;	snake_game.c: 184: for(i = 0; i < 6; i++){
	clr	a
00127$:
;	snake_game.c: 185: gotoY(i);
	push	a
	push	a
	call	_gotoY
	pop	a
	pop	a
;	snake_game.c: 186: for(x=0; x < 84; x++){
	clrw	x
	ldw	(0x02, sp), x
	clrw	x
	ldw	(0x06, sp), x
00125$:
;	snake_game.c: 187: writeData(0);
	push	a
	push	#0x00
	call	_writeData
	pop	a
	pop	a
;	snake_game.c: 188: LCD_RAM[x][i] = 0;
	ldw	x, #_LCD_RAM+0
	addw	x, (0x06, sp)
	ldw	(0x04, sp), x
	clrw	x
	ld	xl, a
	addw	x, (0x04, sp)
	clr	(x)
;	snake_game.c: 186: for(x=0; x < 84; x++){
	ldw	x, (0x06, sp)
	addw	x, #0x0006
	ldw	(0x06, sp), x
	ldw	x, (0x02, sp)
	incw	x
	ldw	(0x02, sp), x
	ldw	x, (0x02, sp)
	cpw	x, #0x0054
	jrc	00125$
;	snake_game.c: 184: for(i = 0; i < 6; i++){
	inc	a
	cp	a, #0x06
	jrc	00127$
	addw	sp, #9
	ret
;	snake_game.c: 193: void gotoX(uint8_t X_address)
;	-----------------------------------------
;	 function gotoX
;	-----------------------------------------
_gotoX:
;	snake_game.c: 195: LCD_X = X_address;
	ld	a, (0x03, sp)
	ld	_LCD_X+0, a
;	snake_game.c: 159: while(*reg & mask)
00101$:
	ldw	x, #0x5203
	ld	a, (x)
	sll	a
	jrnc	00104$
;	snake_game.c: 160: __asm__("nop");
	nop
	jra	00101$
;	snake_game.c: 196: waitForLo(&SPI->SR, 0x80);  /* Wait while SPI is busy transmitting data */
00104$:
;	snake_game.c: 197: SET_COMMAND;
	ldw	x, #0x500a
	ld	a, (x)
	and	a, #0xef
	ld	(x), a
;	snake_game.c: 198: SPI->DR = X_address | 0x80;
	ld	a, (0x03, sp)
	or	a, #0x80
	ldw	x, #0x5204
	ld	(x), a
	ret
;	snake_game.c: 201: void gotoY(uint8_t Y_address)
;	-----------------------------------------
;	 function gotoY
;	-----------------------------------------
_gotoY:
;	snake_game.c: 203: LCD_Y = Y_address;
	ld	a, (0x03, sp)
	ld	_LCD_Y+0, a
;	snake_game.c: 159: while(*reg & mask)
00101$:
	ldw	x, #0x5203
	ld	a, (x)
	sll	a
	jrnc	00104$
;	snake_game.c: 160: __asm__("nop");
	nop
	jra	00101$
;	snake_game.c: 204: waitForLo(&SPI->SR, 0x80);  /* Wait while SPI is busy transmitting data */
00104$:
;	snake_game.c: 205: SET_COMMAND;
	ldw	x, #0x500a
	ld	a, (x)
	and	a, #0xef
	ld	(x), a
;	snake_game.c: 206: SPI->DR = (Y_address & 0x07) | 0x40;
	ld	a, (0x03, sp)
	and	a, #0x07
	or	a, #0x40
	ldw	x, #0x5204
	ld	(x), a
	ret
;	snake_game.c: 209: void writeDataFast(uint8_t data)
;	-----------------------------------------
;	 function writeDataFast
;	-----------------------------------------
_writeDataFast:
;	snake_game.c: 159: while(*reg & mask)
00101$:
	ldw	x, #0x5203
	ld	a, (x)
	sll	a
	jrnc	00104$
;	snake_game.c: 160: __asm__("nop");
	nop
	jra	00101$
;	snake_game.c: 211: waitForLo(&SPI->SR, 0x80);  /* Wait while SPI is busy transmitting data */
00104$:
;	snake_game.c: 212: SET_DATA;
	ldw	x, #0x500a
	ld	a, (x)
	or	a, #0x10
	ld	(x), a
;	snake_game.c: 213: SPI->DR = data;
	ldw	x, #0x5204
	ld	a, (0x03, sp)
	ld	(x), a
	ret
;	snake_game.c: 216: void writeData(uint8_t data)
;	-----------------------------------------
;	 function writeData
;	-----------------------------------------
_writeData:
	sub	sp, #4
;	snake_game.c: 218: LCD_RAM[LCD_X][LCD_Y] = data;
	ldw	x, #_LCD_RAM+0
	ldw	(0x01, sp), x
	ld	a, _LCD_X+0
	ld	xl, a
	ld	a, #0x06
	mul	x, a
	addw	x, (0x01, sp)
	ldw	(0x03, sp), x
	ld	a, _LCD_Y+0
	clrw	x
	ld	xl, a
	addw	x, (0x03, sp)
	ld	a, (0x07, sp)
	ld	(x), a
;	snake_game.c: 219: LCD_X++;
	inc	_LCD_X+0
;	snake_game.c: 220: if( LCD_X > 83 ){
	ld	a, _LCD_X+0
	cp	a, #0x53
	jrule	00105$
;	snake_game.c: 221: LCD_X = 0;
	clr	_LCD_X+0
;	snake_game.c: 222: LCD_Y++;
	inc	_LCD_Y+0
;	snake_game.c: 223: if( LCD_Y > 5)
	ld	a, _LCD_Y+0
	cp	a, #0x05
	jrule	00105$
;	snake_game.c: 224: LCD_Y = 0;
	clr	_LCD_Y+0
;	snake_game.c: 159: while(*reg & mask)
00105$:
	ldw	x, #0x5203
	ld	a, (x)
	sll	a
	jrnc	00108$
;	snake_game.c: 160: __asm__("nop");
	nop
	jra	00105$
;	snake_game.c: 226: waitForLo(&SPI->SR, 0x80);  /* Wait while SPI is busy transmitting data */
00108$:
;	snake_game.c: 227: SET_DATA;
	ldw	x, #0x500a
	ld	a, (x)
	or	a, #0x10
	ld	(x), a
;	snake_game.c: 228: SPI->DR = data;
	ldw	x, #0x5204
	ld	a, (0x07, sp)
	ld	(x), a
	addw	sp, #4
	ret
;	snake_game.c: 231: void refreshBlock(uint8_t x, uint8_t y)
;	-----------------------------------------
;	 function refreshBlock
;	-----------------------------------------
_refreshBlock:
	sub	sp, #4
;	snake_game.c: 233: gotoX(x);
	ld	a, (0x07, sp)
	push	a
	call	_gotoX
	pop	a
;	snake_game.c: 234: gotoY(y);
	ld	a, (0x08, sp)
	push	a
	call	_gotoY
	pop	a
;	snake_game.c: 235: writeDataFast(LCD_RAM[LCD_X][LCD_Y]);
	ldw	x, #_LCD_RAM+0
	ldw	(0x03, sp), x
	ld	a, _LCD_X+0
	ld	xl, a
	ld	a, #0x06
	mul	x, a
	addw	x, (0x03, sp)
	ldw	(0x01, sp), x
	ld	a, _LCD_Y+0
	clrw	x
	ld	xl, a
	addw	x, (0x01, sp)
	ld	a, (x)
	push	a
	call	_writeDataFast
	pop	a
	addw	sp, #4
	ret
;	snake_game.c: 238: void refreshSnakeTile(uint8_t x, uint8_t y)
;	-----------------------------------------
;	 function refreshSnakeTile
;	-----------------------------------------
_refreshSnakeTile:
	sub	sp, #5
;	snake_game.c: 241: uint8_t lcd_tmp_x = x<<2;
	ld	a, (0x08, sp)
	sll	a
	sll	a
	ld	(0x02, sp), a
;	snake_game.c: 242: uint8_t lcd_tmp_y = y>>1;
	ld	a, (0x09, sp)
	srl	a
	ld	(0x01, sp), a
;	snake_game.c: 243: gotoX(lcd_tmp_x);
	ld	a, (0x02, sp)
	push	a
	call	_gotoX
	pop	a
;	snake_game.c: 244: gotoY(lcd_tmp_y);
	ld	a, (0x01, sp)
	push	a
	call	_gotoY
	pop	a
;	snake_game.c: 245: for(i = 0; i < 4; i++)
	clr	(0x03, sp)
00102$:
;	snake_game.c: 246: writeDataFast(LCD_RAM[lcd_tmp_x + i][lcd_tmp_y]);
	ldw	x, #_LCD_RAM+0
	ldw	(0x04, sp), x
	ld	a, (0x02, sp)
	add	a, (0x03, sp)
	ld	xl, a
	ld	a, #0x06
	mul	x, a
	addw	x, (0x04, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ld	a, (x)
	push	a
	call	_writeDataFast
	pop	a
;	snake_game.c: 245: for(i = 0; i < 4; i++)
	inc	(0x03, sp)
	ld	a, (0x03, sp)
	cp	a, #0x04
	jrc	00102$
	addw	sp, #5
	ret
;	snake_game.c: 249: void setPixel(uint8_t x, uint8_t y)
;	-----------------------------------------
;	 function setPixel
;	-----------------------------------------
_setPixel:
	sub	sp, #4
;	snake_game.c: 251: uint8_t row = y >> 3;
	ld	a, (0x08, sp)
	srl	a
	srl	a
	srl	a
	ld	(0x02, sp), a
;	snake_game.c: 252: uint8_t bit = 0x01 << (y & 0x07);
	ld	a, (0x08, sp)
	and	a, #0x07
	ld	xh, a
	ld	a, #0x01
	ld	(0x01, sp), a
	ld	a, xh
	tnz	a
	jreq	00104$
00103$:
	sll	(0x01, sp)
	dec	a
	jrne	00103$
00104$:
;	snake_game.c: 253: gotoX(x);
	ld	a, (0x07, sp)
	push	a
	call	_gotoX
	pop	a
;	snake_game.c: 254: gotoY(row);
	ld	a, (0x02, sp)
	push	a
	call	_gotoY
	pop	a
;	snake_game.c: 255: writeData( LCD_RAM[x][row] | bit );
	ldw	x, #_LCD_RAM+0
	ldw	(0x03, sp), x
	ld	a, (0x07, sp)
	ld	xl, a
	ld	a, #0x06
	mul	x, a
	addw	x, (0x03, sp)
	ld	a, xl
	add	a, (0x02, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ld	a, (x)
	or	a, (0x01, sp)
	push	a
	call	_writeData
	pop	a
	addw	sp, #4
	ret
;	snake_game.c: 258: void clrPixel(uint8_t x, uint8_t y)
;	-----------------------------------------
;	 function clrPixel
;	-----------------------------------------
_clrPixel:
	sub	sp, #7
;	snake_game.c: 260: uint8_t row = y >> 3;
	ld	a, (0x0b, sp)
	srl	a
	srl	a
	srl	a
	ld	(0x02, sp), a
;	snake_game.c: 261: uint8_t bit = 1 << (y & 0x07);
	ld	a, (0x0b, sp)
	and	a, #0x07
	ld	xh, a
	ld	a, #0x01
	ld	(0x01, sp), a
	ld	a, xh
	tnz	a
	jreq	00104$
00103$:
	sll	(0x01, sp)
	dec	a
	jrne	00103$
00104$:
;	snake_game.c: 262: gotoX(x);
	ld	a, (0x0a, sp)
	push	a
	call	_gotoX
	pop	a
;	snake_game.c: 263: gotoY(row);
	ld	a, (0x02, sp)
	push	a
	call	_gotoY
	pop	a
;	snake_game.c: 264: writeData( LCD_RAM[LCD_X][LCD_Y] & ~bit );
	ldw	x, #_LCD_RAM+0
	ldw	(0x03, sp), x
	ld	a, _LCD_X+0
	ld	xl, a
	ld	a, #0x06
	mul	x, a
	addw	x, (0x03, sp)
	ldw	(0x06, sp), x
	ld	a, _LCD_Y+0
	clrw	x
	ld	xl, a
	addw	x, (0x06, sp)
	ld	a, (0x01, sp)
	cpl	a
	ld	(0x05, sp), a
	ld	a, (x)
	and	a, (0x05, sp)
	push	a
	call	_writeData
	pop	a
	addw	sp, #7
	ret
;	snake_game.c: 267: uint8_t ADCread(uint8_t channel)
;	-----------------------------------------
;	 function ADCread
;	-----------------------------------------
_ADCread:
	push	a
;	snake_game.c: 269: ADC1->CSR &=~ 0x0F;
	ldw	x, #0x5400
	ld	a, (x)
	and	a, #0xf0
	ld	(x), a
;	snake_game.c: 270: ADC1->CSR |= channel & 0x0F;
	ldw	x, #0x5400
	ld	a, (x)
	ld	(0x01, sp), a
	ld	a, (0x04, sp)
	and	a, #0x0f
	or	a, (0x01, sp)
	ldw	x, #0x5400
	ld	(x), a
;	snake_game.c: 271: ADC1->CR1 |= (1<<0);  /* initiate conversion */
	bset	0x5401, #0
;	snake_game.c: 147: while(!(*reg & mask))
00101$:
	ldw	x, #0x5400
	ld	a, (x)
	sll	a
	jrc	00104$
;	snake_game.c: 148: __asm__("nop");
	nop
	jra	00101$
;	snake_game.c: 272: waitForHi( &ADC1->CSR, 1 << 7 );
00104$:
;	snake_game.c: 273: ADC1->CSR &= ~(1<<7); /* Clear conversion-done flag */
	bres	0x5400, #7
;	snake_game.c: 274: return ADC1->DRH;
	ldw	x, #0x5404
	ld	a, (x)
	addw	sp, #1
	ret
;	snake_game.c: 295: void setSnakeTile(uint8_t x, uint8_t y, enum Snake_tile tileID)
;	-----------------------------------------
;	 function setSnakeTile
;	-----------------------------------------
_setSnakeTile:
	sub	sp, #66
;	snake_game.c: 297: uint8_t tmp_x = x << 2;
	ld	a, (0x45, sp)
	sll	a
	sll	a
	ld	(0x42, sp), a
;	snake_game.c: 298: uint8_t tmp_y = y >> 1;
	ld	a, (0x46, sp)
	srl	a
	ld	(0x01, sp), a
;	snake_game.c: 300: Snake_array[x][y] = tileID;
	ldw	x, #_Snake_array+0
	ldw	(0x25, sp), x
	ld	a, (0x45, sp)
	ld	xl, a
	ld	a, #0x0a
	mul	x, a
	addw	x, (0x25, sp)
	ld	a, (0x46, sp)
	ld	(0x2c, sp), a
	ld	a, xl
	add	a, (0x2c, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ld	a, (0x47, sp)
	ld	(x), a
;	snake_game.c: 303: LCD_RAM[tmp_x][tmp_y] &= ~0xF0;
	ld	a, (0x42, sp)
	ld	xl, a
	ld	a, #0x06
	mul	x, a
	ldw	(0x2e, sp), x
;	snake_game.c: 304: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][0] & 0xF0;
	clrw	x
	ld	a, (0x47, sp)
	ld	xl, a
;	snake_game.c: 305: tmp_x++;
	ld	a, (0x42, sp)
	inc	a
	ld	(0x2d, sp), a
;	snake_game.c: 304: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][0] & 0xF0;
	sllw	x
	ldw	(0x2a, sp), x
;	snake_game.c: 302: if( y & 0x01 ){ /* Top tile */
	ld	a, (0x2c, sp)
	srl	a
	jrc	00110$
	jp	00102$
00110$:
;	snake_game.c: 303: LCD_RAM[tmp_x][tmp_y] &= ~0xF0;
	ldw	x, #_LCD_RAM+0
	addw	x, (0x2e, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	yl, a
	ld	a, xh
	adc	a, #0x00
	ld	yh, a
	ldw	x, #_LCD_RAM+0
	addw	x, (0x2e, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ld	a, (x)
	and	a, #0x0f
	ld	(y), a
;	snake_game.c: 304: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][0] & 0xF0;
	ldw	x, #_LCD_RAM+0
	addw	x, (0x2e, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	(0x29, sp), a
	ld	a, xh
	adc	a, #0x00
	ld	(0x28, sp), a
	ldw	x, #_LCD_RAM+0
	addw	x, (0x2e, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ldw	y, #_snake_tiles+0
	addw	y, (0x2a, sp)
	ld	a, (y)
	and	a, #0xf0
	ld	(0x27, sp), a
	ld	a, (x)
	or	a, (0x27, sp)
	ldw	x, (0x28, sp)
	ld	(x), a
;	snake_game.c: 305: tmp_x++;
	ld	a, (0x2d, sp)
	ld	(0x41, sp), a
;	snake_game.c: 306: LCD_RAM[tmp_x][tmp_y] &= ~0xF0;
	ldw	x, #_LCD_RAM+0
	pushw	x
	ld	a, (0x43, sp)
	ld	xl, a
	ld	a, #0x06
	mul	x, a
	ldw	(0x41, sp), x
	popw	x
	addw	x, (0x3f, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	(0x3e, sp), a
	ld	a, xh
	adc	a, #0x00
	ld	(0x3d, sp), a
	ldw	x, #_LCD_RAM+0
	addw	x, (0x3f, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ld	a, (x)
	and	a, #0x0f
	ldw	x, (0x3d, sp)
	ld	(x), a
;	snake_game.c: 307: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][0] << 4;
	ldw	x, #_LCD_RAM+0
	addw	x, (0x3f, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	(0x3c, sp), a
	ld	a, xh
	adc	a, #0x00
	ld	(0x3b, sp), a
	ldw	x, #_LCD_RAM+0
	addw	x, (0x3f, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ld	a, (y)
	sll	a
	sll	a
	sll	a
	sll	a
	ld	(0x3a, sp), a
	ld	a, (x)
	or	a, (0x3a, sp)
	ldw	x, (0x3b, sp)
	ld	(x), a
;	snake_game.c: 308: tmp_x++;
	ld	a, (0x41, sp)
	inc	a
	ld	(0x39, sp), a
	ld	a, (0x39, sp)
	ld	(0x38, sp), a
;	snake_game.c: 309: LCD_RAM[tmp_x][tmp_y] &= ~0xF0;
	ldw	x, #_LCD_RAM+0
	pushw	x
	ld	a, (0x3a, sp)
	ld	xl, a
	ld	a, #0x06
	mul	x, a
	ldw	(0x38, sp), x
	popw	x
	addw	x, (0x36, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	(0x35, sp), a
	ld	a, xh
	adc	a, #0x00
	ld	(0x34, sp), a
	ldw	x, #_LCD_RAM+0
	addw	x, (0x36, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ld	a, (x)
	and	a, #0x0f
	ldw	x, (0x34, sp)
	ld	(x), a
;	snake_game.c: 310: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][1] & 0xF0;
	ldw	x, #_LCD_RAM+0
	addw	x, (0x36, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	(0x33, sp), a
	ld	a, xh
	adc	a, #0x00
	ld	(0x32, sp), a
	ldw	x, #_LCD_RAM+0
	addw	x, (0x36, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	incw	y
	ld	a, (y)
	and	a, #0xf0
	ld	(0x31, sp), a
	ld	a, (x)
	or	a, (0x31, sp)
	ldw	x, (0x32, sp)
	ld	(x), a
;	snake_game.c: 311: tmp_x++;    
	ld	a, (0x38, sp)
	inc	a
	ld	(0x30, sp), a
	ld	a, (0x30, sp)
	ld	(0x02, sp), a
;	snake_game.c: 312: LCD_RAM[tmp_x][tmp_y] &= ~0xF0;
	ldw	x, #_LCD_RAM+0
	pushw	x
	ld	a, (0x04, sp)
	ld	xl, a
	ld	a, #0x06
	mul	x, a
	ldw	(0x25, sp), x
	popw	x
	addw	x, (0x23, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	(0x22, sp), a
	ld	a, xh
	adc	a, #0x00
	ld	(0x21, sp), a
	ldw	x, #_LCD_RAM+0
	addw	x, (0x23, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ld	a, (x)
	and	a, #0x0f
	ldw	x, (0x21, sp)
	ld	(x), a
;	snake_game.c: 313: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][1] << 4;
	ldw	x, #_LCD_RAM+0
	addw	x, (0x23, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	(0x20, sp), a
	ld	a, xh
	adc	a, #0x00
	ld	(0x1f, sp), a
	ldw	x, #_LCD_RAM+0
	addw	x, (0x23, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ld	a, (y)
	sll	a
	sll	a
	sll	a
	sll	a
	ld	(0x1e, sp), a
	ld	a, (x)
	or	a, (0x1e, sp)
	ldw	x, (0x1f, sp)
	ld	(x), a
	jp	00103$
00102$:
;	snake_game.c: 316: LCD_RAM[tmp_x][tmp_y] &= ~0x0F;
	ldw	x, #_LCD_RAM+0
	addw	x, (0x2e, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	yl, a
	ld	a, xh
	adc	a, #0x00
	ld	yh, a
	ldw	x, #_LCD_RAM+0
	addw	x, (0x2e, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ld	a, (x)
	and	a, #0xf0
	ld	(y), a
;	snake_game.c: 317: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][0] >> 4;
	ldw	x, #_LCD_RAM+0
	addw	x, (0x2e, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	(0x1d, sp), a
	ld	a, xh
	adc	a, #0x00
	ld	(0x1c, sp), a
	ldw	x, #_LCD_RAM+0
	addw	x, (0x2e, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ldw	y, #_snake_tiles+0
	addw	y, (0x2a, sp)
	ld	a, (y)
	swap	a
	and	a, #0x0f
	ld	(0x1b, sp), a
	ld	a, (x)
	or	a, (0x1b, sp)
	ldw	x, (0x1c, sp)
	ld	(x), a
;	snake_game.c: 318: tmp_x++;
	ld	a, (0x2d, sp)
	ld	(0x1a, sp), a
;	snake_game.c: 319: LCD_RAM[tmp_x][tmp_y] &= ~0x0F;
	ldw	x, #_LCD_RAM+0
	pushw	x
	ld	a, (0x1c, sp)
	ld	xl, a
	ld	a, #0x06
	mul	x, a
	ldw	(0x1a, sp), x
	popw	x
	addw	x, (0x18, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	(0x17, sp), a
	ld	a, xh
	adc	a, #0x00
	ld	(0x16, sp), a
	ldw	x, #_LCD_RAM+0
	addw	x, (0x18, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ld	a, (x)
	and	a, #0xf0
	ldw	x, (0x16, sp)
	ld	(x), a
;	snake_game.c: 320: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][0] & 0x0F;
	ldw	x, #_LCD_RAM+0
	addw	x, (0x18, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	(0x15, sp), a
	ld	a, xh
	adc	a, #0x00
	ld	(0x14, sp), a
	ldw	x, #_LCD_RAM+0
	addw	x, (0x18, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ld	a, (y)
	and	a, #0x0f
	ld	(0x13, sp), a
	ld	a, (x)
	or	a, (0x13, sp)
	ldw	x, (0x14, sp)
	ld	(x), a
;	snake_game.c: 321: tmp_x++;
	ld	a, (0x1a, sp)
	inc	a
	ld	(0x12, sp), a
	ld	a, (0x12, sp)
	ld	(0x11, sp), a
;	snake_game.c: 322: LCD_RAM[tmp_x][tmp_y] &= ~0x0F;
	ldw	x, #_LCD_RAM+0
	pushw	x
	ld	a, (0x13, sp)
	ld	xl, a
	ld	a, #0x06
	mul	x, a
	ldw	(0x11, sp), x
	popw	x
	addw	x, (0x0f, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	(0x0e, sp), a
	ld	a, xh
	adc	a, #0x00
	ld	(0x0d, sp), a
	ldw	x, #_LCD_RAM+0
	addw	x, (0x0f, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ld	a, (x)
	and	a, #0xf0
	ldw	x, (0x0d, sp)
	ld	(x), a
;	snake_game.c: 323: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][1] >> 4;
	ldw	x, #_LCD_RAM+0
	addw	x, (0x0f, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	(0x0c, sp), a
	ld	a, xh
	adc	a, #0x00
	ld	(0x0b, sp), a
	ldw	x, #_LCD_RAM+0
	addw	x, (0x0f, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	incw	y
	ld	a, (y)
	swap	a
	and	a, #0x0f
	ld	(0x0a, sp), a
	ld	a, (x)
	or	a, (0x0a, sp)
	ldw	x, (0x0b, sp)
	ld	(x), a
;	snake_game.c: 324: tmp_x++;    
	ld	a, (0x11, sp)
	inc	a
;	snake_game.c: 325: LCD_RAM[tmp_x][tmp_y] &= ~0x0F;
	ldw	x, #_LCD_RAM+0
	pushw	x
	exg	a, xl
	ld	a, #0x06
	exg	a, xl
	mul	x, a
	ldw	(0x0a, sp), x
	popw	x
	addw	x, (0x08, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	(0x07, sp), a
	ld	a, xh
	adc	a, #0x00
	ld	(0x06, sp), a
	ldw	x, #_LCD_RAM+0
	addw	x, (0x08, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ld	a, (x)
	and	a, #0xf0
	ldw	x, (0x06, sp)
	ld	(x), a
;	snake_game.c: 326: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][1] & 0x0F;
	ldw	x, #_LCD_RAM+0
	addw	x, (0x08, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	(0x05, sp), a
	ld	a, xh
	adc	a, #0x00
	ld	(0x04, sp), a
	ldw	x, #_LCD_RAM+0
	addw	x, (0x08, sp)
	ld	a, xl
	add	a, (0x01, sp)
	ld	xl, a
	ld	a, xh
	adc	a, #0x00
	ld	xh, a
	ld	a, (y)
	and	a, #0x0f
	ld	(0x03, sp), a
	ld	a, (x)
	or	a, (0x03, sp)
	ldw	x, (0x04, sp)
	ld	(x), a
00103$:
;	snake_game.c: 329: refreshSnakeTile(x,y);
	ld	a, (0x2c, sp)
	push	a
	ld	a, (0x46, sp)
	push	a
	call	_refreshSnakeTile
	addw	sp, #2
	addw	sp, #66
	ret
;	snake_game.c: 342: void iterateSnakeHead()
;	-----------------------------------------
;	 function iterateSnakeHead
;	-----------------------------------------
_iterateSnakeHead:
	push	a
;	snake_game.c: 345: switch(snake.head.direction){
	ldw	x, #_snake+5
	ld	a, (x)
	ld	(0x01, sp), a
	ld	a, (0x01, sp)
	cp	a, #0x05
	jrule	00146$
	jp	00124$
00146$:
	clrw	x
	ld	a, (0x01, sp)
	ld	xl, a
	sllw	x
	ldw	x, (#00147$, x)
	jp	(x)
00147$:
	.dw	#00101$
	.dw	#00102$
	.dw	#00105$
	.dw	#00108$
	.dw	#00111$
	.dw	#00114$
;	snake_game.c: 346: case INITIAL:
00101$:
;	snake_game.c: 347: setSnakeTile(12, 6, S_TD);
	push	#0x0d
	push	#0x06
	push	#0x0c
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 348: setSnakeTile(12, 7, S_V);
	push	#0x01
	push	#0x07
	push	#0x0c
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 349: setSnakeTile(12, 8, S_V);
	push	#0x01
	push	#0x08
	push	#0x0c
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 350: setSnakeTile(12, 9, S_HD);
	push	#0x09
	push	#0x09
	push	#0x0c
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 352: snake.tail.x = 12;
	ldw	x, #_snake+0
	ld	a, #0x0c
	ld	(x), a
;	snake_game.c: 353: snake.tail.y = 6;
	ldw	x, #_snake+1
	ld	a, #0x06
	ld	(x), a
;	snake_game.c: 355: snake.head.x = 12;
	ldw	x, #_snake+3
	ld	a, #0x0c
	ld	(x), a
;	snake_game.c: 356: snake.head.y = 9;
	ldw	x, #_snake+4
	ld	a, #0x09
	ld	(x), a
;	snake_game.c: 358: snake.length = 4;
	ldw	x, #_snake+6
	ld	a, #0x04
	ld	(x), a
;	snake_game.c: 359: snake.head.direction = DOWN;
	ldw	x, #_snake+5
	ld	a, #0x04
	ld	(x), a
;	snake_game.c: 360: snake.tail.direction = DOWN;
	ldw	x, #_snake+2
	ld	a, #0x04
	ld	(x), a
;	snake_game.c: 361: return; /* Quit function, everything is set up*/
	jp	00124$
;	snake_game.c: 363: case LEFT:
00102$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x00
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 365: snake.head.x--;
	ldw	x, #_snake+3
	dec	(x)
;	snake_game.c: 366: if(snake.head.x > 20)
	ldw	x, #_snake+3
	ld	a, (x)
	cp	a, #0x14
	jrule	00104$
;	snake_game.c: 367: snake.head.x = 20;
	ldw	x, #_snake+3
	ld	a, #0x14
	ld	(x), a
00104$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x07
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 369: break;
	jp	00124$
;	snake_game.c: 371: case RIGHT: 
00105$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x00
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 373: snake.head.x++;
	ldw	x, #_snake+3
	inc	(x)
;	snake_game.c: 374: if(snake.head.x > 20)
	ldw	x, #_snake+3
	ld	a, (x)
	cp	a, #0x14
	jrule	00107$
;	snake_game.c: 375: snake.head.x = 0;
	ldw	x, #_snake+3
	clr	(x)
00107$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x06
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 377: break;
	jp	00124$
;	snake_game.c: 379: case UP:
00108$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x01
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 381: snake.head.y--;
	ldw	x, #_snake+4
	dec	(x)
;	snake_game.c: 382: if(snake.head.y > 9)
	ldw	x, #_snake+4
	ld	a, (x)
	cp	a, #0x09
	jrule	00110$
;	snake_game.c: 383: snake.head.y = 9;
	ldw	x, #_snake+4
	ld	a, #0x09
	ld	(x), a
00110$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x08
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 385: break;
	jra	00124$
;	snake_game.c: 387: case DOWN: 
00111$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x01
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 389: snake.head.y++;
	ldw	x, #_snake+4
	inc	(x)
;	snake_game.c: 390: if(snake.head.y > 9)
	ldw	x, #_snake+4
	ld	a, (x)
	cp	a, #0x09
	jrule	00113$
;	snake_game.c: 391: snake.head.y = 0;
	ldw	x, #_snake+4
	clr	(x)
00113$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x09
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 393: break;
;	snake_game.c: 395: case DEAD:
;	snake_game.c: 397: }
00114$:
00124$:
	pop	a
	ret
;	snake_game.c: 400: void iterateSnakeTail()
;	-----------------------------------------
;	 function iterateSnakeTail
;	-----------------------------------------
_iterateSnakeTail:
	sub	sp, #18
;	snake_game.c: 339: setSnakeTile(snake.tail.x, snake.tail.y, tileID);
	ldw	x, #_snake+1
	ld	a, (x)
	ldw	x, #_snake+0
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x11
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 404: switch(snake.tail.direction){
	ldw	x, #_snake+2
	ld	a, (x)
	ld	(0x12, sp), a
	ld	a, (0x12, sp)
	cp	a, #0x01
	jrne	00223$
	jp	00108$
00223$:
	ld	a, (0x12, sp)
	cp	a, #0x02
	jreq	00101$
	ld	a, (0x12, sp)
	cp	a, #0x03
	jrne	00229$
	jp	00115$
00229$:
	ld	a, (0x12, sp)
	cp	a, #0x04
	jrne	00232$
	jp	00122$
00232$:
	jp	00129$
;	snake_game.c: 405: case RIGHT:
00101$:
;	snake_game.c: 406: snake.tail.x++;
	ldw	x, #_snake+0
	inc	(x)
;	snake_game.c: 407: if(snake.tail.x > 20)
	ldw	x, #_snake+0
	ld	a, (x)
	cp	a, #0x14
	jrule	00103$
;	snake_game.c: 408: snake.tail.x = 0;
	ldw	x, #_snake+0
	clr	(x)
00103$:
;	snake_game.c: 410: switch(Snake_array[snake.tail.x][snake.tail.y]){
	ldw	x, #_Snake_array+0
	ldw	(0x10, sp), x
	ldw	x, #_snake+0
	ld	a, (x)
	ld	xl, a
	ld	a, #0x0a
	mul	x, a
	addw	x, (0x10, sp)
	ldw	(0x01, sp), x
	ldw	x, #_snake+1
	ld	a, (x)
	clrw	x
	ld	xl, a
	addw	x, (0x01, sp)
	ld	a, (x)
	cp	a, #0x02
	jreq	00105$
	cp	a, #0x03
	jrne	00106$
;	snake_game.c: 411: case(S_LU): snake.tail.direction = UP;    break;
	ldw	x, #_snake+2
	ld	a, #0x03
	ld	(x), a
	jp	00129$
;	snake_game.c: 412: case(S_LD): snake.tail.direction = DOWN;  break;
00105$:
	ldw	x, #_snake+2
	ld	a, #0x04
	ld	(x), a
	jp	00129$
;	snake_game.c: 413: default:    snake.tail.direction = RIGHT; break;
00106$:
	ldw	x, #_snake+2
	ld	a, #0x02
	ld	(x), a
;	snake_game.c: 415: break;
	jp	00129$
;	snake_game.c: 417: case LEFT:
00108$:
;	snake_game.c: 418: snake.tail.x--;
	ldw	x, #_snake+0
	dec	(x)
;	snake_game.c: 419: if(snake.tail.x > 20)
	ldw	x, #_snake+0
	ld	a, (x)
	cp	a, #0x14
	jrule	00110$
;	snake_game.c: 420: snake.tail.x = 20;
	ldw	x, #_snake+0
	ld	a, #0x14
	ld	(x), a
00110$:
;	snake_game.c: 422: switch(Snake_array[snake.tail.x][snake.tail.y]){
	ldw	x, #_Snake_array+0
	ldw	(0x09, sp), x
	ldw	x, #_snake+0
	ld	a, (x)
	ld	xl, a
	ld	a, #0x0a
	mul	x, a
	addw	x, (0x09, sp)
	ldw	(0x0d, sp), x
	ldw	x, #_snake+1
	ld	a, (x)
	clrw	x
	ld	xl, a
	addw	x, (0x0d, sp)
	ld	a, (x)
	cp	a, #0x04
	jreq	00112$
	cp	a, #0x05
	jrne	00113$
;	snake_game.c: 423: case(S_RU): snake.tail.direction = UP;    break;
	ldw	x, #_snake+2
	ld	a, #0x03
	ld	(x), a
	jp	00129$
;	snake_game.c: 424: case(S_RD): snake.tail.direction = DOWN;  break;
00112$:
	ldw	x, #_snake+2
	ld	a, #0x04
	ld	(x), a
	jp	00129$
;	snake_game.c: 425: default:    snake.tail.direction = LEFT;  break;
00113$:
	ldw	x, #_snake+2
	ld	a, #0x01
	ld	(x), a
;	snake_game.c: 427: break;
	jp	00129$
;	snake_game.c: 429: case UP:
00115$:
;	snake_game.c: 430: snake.tail.y--;
	ldw	x, #_snake+1
	dec	(x)
;	snake_game.c: 431: if(snake.tail.y > 9)
	ldw	x, #_snake+1
	ld	a, (x)
	cp	a, #0x09
	jrule	00117$
;	snake_game.c: 432: snake.tail.y = 9;
	ldw	x, #_snake+1
	ld	a, #0x09
	ld	(x), a
00117$:
;	snake_game.c: 434: switch(Snake_array[snake.tail.x][snake.tail.y]){
	ldw	x, #_Snake_array+0
	ldw	(0x05, sp), x
	ldw	x, #_snake+0
	ld	a, (x)
	ld	xl, a
	ld	a, #0x0a
	mul	x, a
	addw	x, (0x05, sp)
	ldw	(0x03, sp), x
	ldw	x, #_snake+1
	ld	a, (x)
	clrw	x
	ld	xl, a
	addw	x, (0x03, sp)
	ld	a, (x)
	cp	a, #0x02
	jreq	00118$
	cp	a, #0x04
	jreq	00119$
	jra	00120$
;	snake_game.c: 435: case(S_LD): snake.tail.direction = LEFT;  break;
00118$:
	ldw	x, #_snake+2
	ld	a, #0x01
	ld	(x), a
	jra	00129$
;	snake_game.c: 436: case(S_RD): snake.tail.direction = RIGHT; break;
00119$:
	ldw	x, #_snake+2
	ld	a, #0x02
	ld	(x), a
	jra	00129$
;	snake_game.c: 437: default:    snake.tail.direction = UP;    break;
00120$:
	ldw	x, #_snake+2
	ld	a, #0x03
	ld	(x), a
;	snake_game.c: 439: break;
	jra	00129$
;	snake_game.c: 441: case DOWN:
00122$:
;	snake_game.c: 442: snake.tail.y++;
	ldw	x, #_snake+1
	inc	(x)
;	snake_game.c: 443: if(snake.tail.y > 9)
	ldw	x, #_snake+1
	ld	a, (x)
	cp	a, #0x09
	jrule	00124$
;	snake_game.c: 444: snake.tail.y = 0;
	ldw	x, #_snake+1
	clr	(x)
00124$:
;	snake_game.c: 446: switch(Snake_array[snake.tail.x][snake.tail.y]){
	ldw	x, #_Snake_array+0
	ldw	(0x0b, sp), x
	ldw	x, #_snake+0
	ld	a, (x)
	ld	xl, a
	ld	a, #0x0a
	mul	x, a
	addw	x, (0x0b, sp)
	ldw	(0x07, sp), x
	ldw	x, #_snake+1
	ld	a, (x)
	clrw	x
	ld	xl, a
	addw	x, (0x07, sp)
	ld	a, (x)
	cp	a, #0x03
	jreq	00125$
	cp	a, #0x05
	jreq	00126$
	jra	00127$
;	snake_game.c: 447: case(S_LU): snake.tail.direction = LEFT;  break;
00125$:
	ldw	x, #_snake+2
	ld	a, #0x01
	ld	(x), a
	jra	00129$
;	snake_game.c: 448: case(S_RU): snake.tail.direction = RIGHT; break;
00126$:
	ldw	x, #_snake+2
	ld	a, #0x02
	ld	(x), a
	jra	00129$
;	snake_game.c: 449: default:    snake.tail.direction = DOWN;  break;
00127$:
	ldw	x, #_snake+2
	ld	a, #0x04
	ld	(x), a
;	snake_game.c: 452: }
00129$:
;	snake_game.c: 454: switch(snake.tail.direction){
	ldw	x, #_snake+2
	ld	a, (x)
	ld	(0x0f, sp), a
	ld	a, (0x0f, sp)
	cp	a, #0x01
	jreq	00131$
	ld	a, (0x0f, sp)
	cp	a, #0x02
	jreq	00130$
	ld	a, (0x0f, sp)
	cp	a, #0x03
	jreq	00132$
	ld	a, (0x0f, sp)
	cp	a, #0x04
	jreq	00133$
	jra	00140$
;	snake_game.c: 455: case(RIGHT): setSnakeTailTile(S_TR); break;
00130$:
;	snake_game.c: 339: setSnakeTile(snake.tail.x, snake.tail.y, tileID);
	ldw	x, #_snake+1
	ld	a, (x)
	ldw	x, #_snake+0
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x0a
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 455: case(RIGHT): setSnakeTailTile(S_TR); break;
	jra	00140$
;	snake_game.c: 456: case(LEFT):  setSnakeTailTile(S_TL); break;
00131$:
;	snake_game.c: 339: setSnakeTile(snake.tail.x, snake.tail.y, tileID);
	ldw	x, #_snake+1
	ld	a, (x)
	ldw	x, #_snake+0
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x0b
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 456: case(LEFT):  setSnakeTailTile(S_TL); break;
	jra	00140$
;	snake_game.c: 457: case(UP):    setSnakeTailTile(S_TU); break;
00132$:
;	snake_game.c: 339: setSnakeTile(snake.tail.x, snake.tail.y, tileID);
	ldw	x, #_snake+1
	ld	a, (x)
	ldw	x, #_snake+0
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x0c
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 457: case(UP):    setSnakeTailTile(S_TU); break;
	jra	00140$
;	snake_game.c: 458: case(DOWN):  setSnakeTailTile(S_TD); break;
00133$:
;	snake_game.c: 339: setSnakeTile(snake.tail.x, snake.tail.y, tileID);
	ldw	x, #_snake+1
	ld	a, (x)
	ldw	x, #_snake+0
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x0d
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 459: }
00140$:
	addw	sp, #18
	ret
;	snake_game.c: 462: void moveSnake(enum snake_orientation move_direction)
;	-----------------------------------------
;	 function moveSnake
;	-----------------------------------------
_moveSnake:
	sub	sp, #4
;	snake_game.c: 464: switch(move_direction){
	ld	a, (0x07, sp)
	cp	a, #0x01
	jrne	00213$
	jp	00108$
00213$:
	ld	a, (0x07, sp)
	cp	a, #0x02
	jreq	00101$
	ld	a, (0x07, sp)
	cp	a, #0x03
	jrne	00219$
	jp	00115$
00219$:
	ld	a, (0x07, sp)
	cp	a, #0x04
	jrne	00222$
	jp	00122$
00222$:
	jp	00129$
;	snake_game.c: 465: case RIGHT:
00101$:
;	snake_game.c: 466: switch(snake.head.direction){
	ldw	x, #_snake+5
	ld	a, (x)
	ld	(0x02, sp), a
	ld	a, (0x02, sp)
	cp	a, #0x03
	jreq	00102$
	ld	a, (0x02, sp)
	cp	a, #0x04
	jreq	00103$
	jra	00104$
;	snake_game.c: 467: case UP:    setSnakeHeadTile(S_RD); break;
00102$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x04
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 467: case UP:    setSnakeHeadTile(S_RD); break;
	jra	00105$
;	snake_game.c: 468: case DOWN:  setSnakeHeadTile(S_RU); break;  
00103$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x05
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 468: case DOWN:  setSnakeHeadTile(S_RU); break;  
	jra	00105$
;	snake_game.c: 469: default:    setSnakeHeadTile(S_H);  break;
00104$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x00
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 470: }
00105$:
;	snake_game.c: 471: snake.head.x++;
	ldw	x, #_snake+3
	inc	(x)
;	snake_game.c: 472: if(snake.head.x > 20)
	ldw	x, #_snake+3
	ld	a, (x)
	cp	a, #0x14
	jrule	00107$
;	snake_game.c: 473: snake.head.x = 0;
	ldw	x, #_snake+3
	clr	(x)
00107$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x06
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 475: break;
	jp	00129$
;	snake_game.c: 477: case LEFT:
00108$:
;	snake_game.c: 478: switch(snake.head.direction){
	ldw	x, #_snake+5
	ld	a, (x)
	ld	(0x01, sp), a
	ld	a, (0x01, sp)
	cp	a, #0x03
	jreq	00109$
	ld	a, (0x01, sp)
	cp	a, #0x04
	jreq	00110$
	jra	00111$
;	snake_game.c: 479: case UP:    setSnakeHeadTile(S_LD); break;
00109$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x02
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 479: case UP:    setSnakeHeadTile(S_LD); break;
	jra	00112$
;	snake_game.c: 480: case DOWN:  setSnakeHeadTile(S_LU); break;
00110$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x03
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 480: case DOWN:  setSnakeHeadTile(S_LU); break;
	jra	00112$
;	snake_game.c: 481: default:    setSnakeHeadTile(S_H);  break;
00111$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x00
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 482: }
00112$:
;	snake_game.c: 483: snake.head.x--;
	ldw	x, #_snake+3
	dec	(x)
;	snake_game.c: 484: if(snake.head.x > 20)
	ldw	x, #_snake+3
	ld	a, (x)
	cp	a, #0x14
	jrule	00114$
;	snake_game.c: 485: snake.head.x = 20;
	ldw	x, #_snake+3
	ld	a, #0x14
	ld	(x), a
00114$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x07
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 487: break;
	jp	00129$
;	snake_game.c: 489: case UP:
00115$:
;	snake_game.c: 490: switch(snake.head.direction){
	ldw	x, #_snake+5
	ld	a, (x)
	ld	(0x04, sp), a
	ld	a, (0x04, sp)
	cp	a, #0x01
	jreq	00117$
	ld	a, (0x04, sp)
	cp	a, #0x02
	jrne	00118$
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x03
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 491: case RIGHT: setSnakeHeadTile(S_LU); break;
	jra	00119$
;	snake_game.c: 492: case LEFT:  setSnakeHeadTile(S_RU); break;
00117$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x05
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 492: case LEFT:  setSnakeHeadTile(S_RU); break;
	jra	00119$
;	snake_game.c: 493: default:    setSnakeHeadTile(S_V);  break;
00118$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x01
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 494: }
00119$:
;	snake_game.c: 495: snake.head.y--;
	ldw	x, #_snake+4
	dec	(x)
;	snake_game.c: 496: if(snake.head.y > 9)
	ldw	x, #_snake+4
	ld	a, (x)
	cp	a, #0x09
	jrule	00121$
;	snake_game.c: 497: snake.head.y = 9;
	ldw	x, #_snake+4
	ld	a, #0x09
	ld	(x), a
00121$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x08
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 499: break;
	jp	00129$
;	snake_game.c: 501: case DOWN:
00122$:
;	snake_game.c: 502: switch(snake.head.direction){
	ldw	x, #_snake+5
	ld	a, (x)
	ld	(0x03, sp), a
	ld	a, (0x03, sp)
	cp	a, #0x01
	jreq	00124$
	ld	a, (0x03, sp)
	cp	a, #0x02
	jrne	00125$
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x02
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 503: case RIGHT: setSnakeHeadTile(S_LD); break;
	jra	00126$
;	snake_game.c: 504: case LEFT:  setSnakeHeadTile(S_RD); break;
00124$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x04
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 504: case LEFT:  setSnakeHeadTile(S_RD); break;
	jra	00126$
;	snake_game.c: 505: default:    setSnakeHeadTile(S_V);  break;
00125$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x01
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 506: }
00126$:
;	snake_game.c: 507: snake.head.y++;
	ldw	x, #_snake+4
	inc	(x)
;	snake_game.c: 508: if(snake.head.y > 9)
	ldw	x, #_snake+4
	ld	a, (x)
	cp	a, #0x09
	jrule	00128$
;	snake_game.c: 509: snake.head.y = 0;
	ldw	x, #_snake+4
	clr	(x)
00128$:
;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
	ldw	x, #_snake+4
	ld	a, (x)
	ldw	x, #_snake+3
	push	a
	ld	a, (x)
	ld	xl, a
	pop	a
	push	#0x09
	push	a
	ld	a, xl
	push	a
	call	_setSnakeTile
	addw	sp, #3
;	snake_game.c: 512: }
00129$:
;	snake_game.c: 514: snake.head.direction = move_direction;
	ldw	x, #_snake+5
	ld	a, (0x07, sp)
	ld	(x), a
;	snake_game.c: 516: iterateSnakeTail();
	call	_iterateSnakeTail
	addw	sp, #4
	ret
;	snake_game.c: 519: int main(void){
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
	sub	sp, #3
;	snake_game.c: 520: uint8_t volatile j = 0, i = 0, k =0;
	clr	(0x03, sp)
	clr	(0x02, sp)
	clr	(0x01, sp)
;	snake_game.c: 523: GPIOD->DDR |= LED;    /* Pin directions */
	bset	0x5011, #0
;	snake_game.c: 524: GPIOD->CR1 |= LED;    /* Set pin to high speed push-pull */
	bset	0x5012, #0
;	snake_game.c: 525: GPIOD->CR2 |= LED;
	bset	0x5013, #0
;	snake_game.c: 527: GPIOC->DDR |= (1<<6)|(1<<5)|DC_PIN|RESET_PIN|CS_PIN;  /* SPI MOSI and SPI CLK */
	ldw	x, #0x500c
	ld	a, (x)
	or	a, #0x7c
	ld	(x), a
;	snake_game.c: 528: GPIOC->CR1 |= (1<<6)|(1<<5)|DC_PIN|RESET_PIN|CS_PIN;  /* Fast push pull for quick SPI transmissions */
	ldw	x, #0x500d
	ld	a, (x)
	or	a, #0x7c
	ld	(x), a
;	snake_game.c: 529: GPIOC->CR2 |= (1<<6)|(1<<5)|DC_PIN|RESET_PIN|CS_PIN;
	ldw	x, #0x500e
	ld	a, (x)
	or	a, #0x7c
	ld	(x), a
;	snake_game.c: 531: GPIOB->DDR &=~ (BUTTON1 | BUTTON2 | BUTTON3 | BUTTON4); /* Set to input */
	ldw	x, #0x5007
	ld	a, (x)
	and	a, #0xf0
	ld	(x), a
;	snake_game.c: 532: GPIOB->CR1 |=  (BUTTON1 | BUTTON2 | BUTTON3 | BUTTON4); /* Pull-up without interrupts */
	ldw	x, #0x5008
	ld	a, (x)
	or	a, #0x0f
	ld	(x), a
;	snake_game.c: 534: CLR_CS;
	ldw	x, #0x500a
	ld	a, (x)
	or	a, #0x08
	ld	(x), a
;	snake_game.c: 537: CLK->SWCR  |= 1<<1;   /* Enable clock source switch */
	ldw	x, #0x50c5
	ld	a, (x)
	or	a, #0x02
	ld	(x), a
;	snake_game.c: 538: CLK->SWR    = 0xE1;   /* Switch to high speed internal clock */
	ldw	x, #0x50c4
	ld	a, #0xe1
	ld	(x), a
;	snake_game.c: 539: CLK->CKDIVR = 0x00;   /* Set CPU and HSI prescalers to 1 */
	ldw	x, #0x50c6
	clr	(x)
;	snake_game.c: 540: CLK->PCKENR1= (1<<1); /* Enable SPI clock */
	ldw	x, #0x50c7
	ld	a, #0x02
	ld	(x), a
;	snake_game.c: 541: CLK->PCKENR2= (1<<3); /* Enable ADC clock */
	ldw	x, #0x50ca
	ld	a, #0x08
	ld	(x), a
;	snake_game.c: 544: SPI->CR1  = (1<<6)|(1<<2)|(0x3<<3);   /* Enable SPI, set to master mode */
	ldw	x, #0x5200
	ld	a, #0x5c
	ld	(x), a
;	snake_game.c: 545: SPI->CR2  = (1<<7)|(1<<6);            /* Transmit only */
	ldw	x, #0x5201
	ld	a, #0xc0
	ld	(x), a
;	snake_game.c: 546: SPI->CR2 |= (1<<0)|(1<<1);
	ldw	x, #0x5201
	ld	a, (x)
	or	a, #0x03
	ld	(x), a
;	snake_game.c: 549: ADC1->CSR = (0x7<<4); /* Prescaler fmaster/6 */
	ldw	x, #0x5400
	ld	a, #0x70
	ld	(x), a
;	snake_game.c: 551: ADC1->CR2 = 0; /* Data aligned to the left */
	ldw	x, #0x5402
	clr	(x)
;	snake_game.c: 552: initLCD();
	call	_initLCD
;	snake_game.c: 554: while(1){
00123$:
;	snake_game.c: 555: GPIOD->ODR ^= LED;
	ldw	x, #0x500f
	ld	a, (x)
	xor	a, #0x01
	ld	(x), a
;	snake_game.c: 557: for(i = 0; i < 16; i++)
	clr	(0x02, sp)
00131$:
	ld	a, (0x02, sp)
	cp	a, #0x10
	jrnc	00101$
;	snake_game.c: 128: for(i = 0; i < delay; i++)
	clrw	x
00128$:
	cpw	x, #0xfde8
	jrnc	00126$
;	snake_game.c: 129: __asm__("nop");
	nop
;	snake_game.c: 128: for(i = 0; i < delay; i++)
	incw	x
	jra	00128$
;	snake_game.c: 558: delay16b(65000);
00126$:
;	snake_game.c: 557: for(i = 0; i < 16; i++)
	ld	a, (0x02, sp)
	inc	a
	ld	(0x02, sp), a
	jra	00131$
00101$:
;	snake_game.c: 561: if(!(GPIOB->IDR & BUTTON1)){
	ldw	x, #0x5006
	ld	a, (x)
	srl	a
	jrc	00120$
;	snake_game.c: 562: if(snake.head.direction != DOWN)
	ldw	x, #_snake+5
	ld	a, (x)
	cp	a, #0x04
	jreq	00123$
;	snake_game.c: 563: moveSnake(UP);
	push	#0x03
	call	_moveSnake
	pop	a
	jra	00123$
00120$:
;	snake_game.c: 565: else if(!(GPIOB->IDR & BUTTON2)){
	ldw	x, #0x5006
	ld	a, (x)
	bcp	a, #0x02
	jrne	00117$
;	snake_game.c: 566: if(snake.head.direction != UP)
	ldw	x, #_snake+5
	ld	a, (x)
	cp	a, #0x03
	jreq	00123$
;	snake_game.c: 567: moveSnake(DOWN);
	push	#0x04
	call	_moveSnake
	pop	a
	jra	00123$
00117$:
;	snake_game.c: 569: else if(!(GPIOB->IDR & BUTTON3)){
	ldw	x, #0x5006
	ld	a, (x)
	bcp	a, #0x04
	jrne	00114$
;	snake_game.c: 570: if(snake.head.direction != RIGHT)
	ldw	x, #_snake+5
	ld	a, (x)
	cp	a, #0x02
	jrne	00200$
	jp	00123$
00200$:
;	snake_game.c: 571: moveSnake(LEFT);
	push	#0x01
	call	_moveSnake
	pop	a
	jp	00123$
00114$:
;	snake_game.c: 573: else if(!(GPIOB->IDR & BUTTON4)){
	ldw	x, #0x5006
	ld	a, (x)
	bcp	a, #0x08
	jrne	00111$
;	snake_game.c: 574: if(snake.head.direction != LEFT)
	ldw	x, #_snake+5
	ld	a, (x)
	cp	a, #0x01
	jrne	00204$
	jp	00123$
00204$:
;	snake_game.c: 575: moveSnake(RIGHT);
	push	#0x02
	call	_moveSnake
	pop	a
	jp	00123$
00111$:
;	snake_game.c: 578: iterateSnakeHead();
	call	_iterateSnakeHead
;	snake_game.c: 579: iterateSnakeTail();
	call	_iterateSnakeTail
	jp	00123$
	addw	sp, #3
	ret
	.area CODE
_init_sequence:
	.db #0x21	; 33
	.db #0xAF	; 175
	.db #0x04	; 4
	.db #0x13	; 19
	.db #0x20	; 32
	.db #0x0C	; 12
	.db #0x00	; 0
_snake_tiles:
	.db #0x64	; 100	'd'
	.db #0x26	; 38
	.db #0x0B	; 11
	.db #0xD0	; 208
	.db #0x6A	; 106	'j'
	.db #0xC0	; 192
	.db #0x65	; 101	'e'
	.db #0x30	; 48	'0'
	.db #0x0C	; 12
	.db #0xA6	; 166
	.db #0x03	; 3
	.db #0x56	; 86	'V'
	.db #0x56	; 86	'V'
	.db #0x60	; 96
	.db #0x06	; 6
	.db #0x65	; 101	'e'
	.db #0x0E	; 14
	.db #0x68	; 104	'h'
	.db #0x16	; 22
	.db #0x70	; 112	'p'
	.db #0x44	; 68	'D'
	.db #0x66	; 102	'f'
	.db #0x66	; 102	'f'
	.db #0x44	; 68	'D'
	.db #0x0F	; 15
	.db #0x30	; 48	'0'
	.db #0x0C	; 12
	.db #0xF0	; 240
	.db #0x6D	; 109	'm'
	.db #0xB6	; 182
	.db #0x6B	; 107	'k'
	.db #0xD6	; 214
	.db #0x4A	; 74	'J'
	.db #0x40	; 64
	.db #0x00	; 0
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.area INITIALIZER
__xinit__LCD_X:
	.db #0x00	; 0
__xinit__LCD_Y:
	.db #0x00	; 0
__xinit__snake_heading:
	.db #0x00	; 0
__xinit__Snake_array:
	.db #0x00	; 0
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
	.db 0x00
__xinit__bait_pos:
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
__xinit__snake:
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.area CABS (ABS)
