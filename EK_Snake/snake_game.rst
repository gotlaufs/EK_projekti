                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ANSI-C Compiler
                                      3 ; Version 3.4.0 #8981 (Apr  5 2014) (Linux)
                                      4 ; This file was generated Mon Oct 13 02:05:09 2014
                                      5 ;--------------------------------------------------------
                                      6 	.module snake_game
                                      7 	.optsdcc -mstm8
                                      8 	
                                      9 ;--------------------------------------------------------
                                     10 ; Public variables in this module
                                     11 ;--------------------------------------------------------
                                     12 	.globl _snake_tiles
                                     13 	.globl _init_sequence
                                     14 	.globl _main
                                     15 	.globl _moveSnake
                                     16 	.globl _iterateSnakeTail
                                     17 	.globl _iterateSnakeHead
                                     18 	.globl _setSnakeTile
                                     19 	.globl _ADCread
                                     20 	.globl _clrPixel
                                     21 	.globl _setPixel
                                     22 	.globl _refreshSnakeTile
                                     23 	.globl _refreshBlock
                                     24 	.globl _writeDataFast
                                     25 	.globl _initLCD
                                     26 	.globl _snake
                                     27 	.globl _bait_pos
                                     28 	.globl _Snake_array
                                     29 	.globl _snake_heading
                                     30 	.globl _LCD_Y
                                     31 	.globl _LCD_X
                                     32 	.globl _LCD_RAM
                                     33 	.globl _gotoX
                                     34 	.globl _gotoY
                                     35 	.globl _writeData
                                     36 ;--------------------------------------------------------
                                     37 ; ram data
                                     38 ;--------------------------------------------------------
                                     39 	.area DATA
      000001                         40 _LCD_RAM::
      000001                         41 	.ds 504
                                     42 ;--------------------------------------------------------
                                     43 ; ram data
                                     44 ;--------------------------------------------------------
                                     45 	.area INITIALIZED
      0001F9                         46 _LCD_X::
      0001F9                         47 	.ds 1
      0001FA                         48 _LCD_Y::
      0001FA                         49 	.ds 1
      0001FB                         50 _snake_heading::
      0001FB                         51 	.ds 1
      0001FC                         52 _Snake_array::
      0001FC                         53 	.ds 210
      0002CE                         54 _bait_pos::
      0002CE                         55 	.ds 3
      0002D1                         56 _snake::
      0002D1                         57 	.ds 7
                                     58 ;--------------------------------------------------------
                                     59 ; Stack segment in internal ram 
                                     60 ;--------------------------------------------------------
                                     61 	.area	SSEG
      000000                         62 __start__stack:
      000000                         63 	.ds	1
                                     64 
                                     65 ;--------------------------------------------------------
                                     66 ; absolute external ram data
                                     67 ;--------------------------------------------------------
                                     68 	.area DABS (ABS)
                                     69 ;--------------------------------------------------------
                                     70 ; interrupt vector 
                                     71 ;--------------------------------------------------------
                                     72 	.area HOME
      008000                         73 __interrupt_vect:
      008000 82 00 80 83             74 	int s_GSINIT ;reset
      008004 82 00 00 00             75 	int 0x0000 ;trap
      008008 82 00 00 00             76 	int 0x0000 ;int0
      00800C 82 00 00 00             77 	int 0x0000 ;int1
      008010 82 00 00 00             78 	int 0x0000 ;int2
      008014 82 00 00 00             79 	int 0x0000 ;int3
      008018 82 00 00 00             80 	int 0x0000 ;int4
      00801C 82 00 00 00             81 	int 0x0000 ;int5
      008020 82 00 00 00             82 	int 0x0000 ;int6
      008024 82 00 00 00             83 	int 0x0000 ;int7
      008028 82 00 00 00             84 	int 0x0000 ;int8
      00802C 82 00 00 00             85 	int 0x0000 ;int9
      008030 82 00 00 00             86 	int 0x0000 ;int10
      008034 82 00 00 00             87 	int 0x0000 ;int11
      008038 82 00 00 00             88 	int 0x0000 ;int12
      00803C 82 00 00 00             89 	int 0x0000 ;int13
      008040 82 00 00 00             90 	int 0x0000 ;int14
      008044 82 00 00 00             91 	int 0x0000 ;int15
      008048 82 00 00 00             92 	int 0x0000 ;int16
      00804C 82 00 00 00             93 	int 0x0000 ;int17
      008050 82 00 00 00             94 	int 0x0000 ;int18
      008054 82 00 00 00             95 	int 0x0000 ;int19
      008058 82 00 00 00             96 	int 0x0000 ;int20
      00805C 82 00 00 00             97 	int 0x0000 ;int21
      008060 82 00 00 00             98 	int 0x0000 ;int22
      008064 82 00 00 00             99 	int 0x0000 ;int23
      008068 82 00 00 00            100 	int 0x0000 ;int24
      00806C 82 00 00 00            101 	int 0x0000 ;int25
      008070 82 00 00 00            102 	int 0x0000 ;int26
      008074 82 00 00 00            103 	int 0x0000 ;int27
      008078 82 00 00 00            104 	int 0x0000 ;int28
      00807C 82 00 00 00            105 	int 0x0000 ;int29
                                    106 ;--------------------------------------------------------
                                    107 ; global & static initialisations
                                    108 ;--------------------------------------------------------
                                    109 	.area HOME
                                    110 	.area GSINIT
                                    111 	.area GSFINAL
                                    112 	.area GSINIT
      008083                        113 __sdcc_gs_init_startup:
      008083                        114 __sdcc_init_data:
                                    115 ; stm8_genXINIT() start
      008083 AE 01 F8         [ 2]  116 	ldw x, #l_DATA
      008086 27 07            [ 1]  117 	jreq	00002$
      008088                        118 00001$:
      008088 72 4F 00 00      [ 1]  119 	clr (s_DATA - 1, x)
      00808C 5A               [ 2]  120 	decw x
      00808D 26 F9            [ 1]  121 	jrne	00001$
      00808F                        122 00002$:
      00808F AE 00 DF         [ 2]  123 	ldw	x, #l_INITIALIZER
      008092 27 09            [ 1]  124 	jreq	00004$
      008094                        125 00003$:
      008094 D6 8D 52         [ 1]  126 	ld	a, (s_INITIALIZER - 1, x)
      008097 D7 01 F8         [ 1]  127 	ld	(s_INITIALIZED - 1, x), a
      00809A 5A               [ 2]  128 	decw	x
      00809B 26 F7            [ 1]  129 	jrne	00003$
      00809D                        130 00004$:
                                    131 ; stm8_genXINIT() end
                                    132 	.area GSFINAL
      00809D CC 80 80         [ 2]  133 	jp	__sdcc_program_startup
                                    134 ;--------------------------------------------------------
                                    135 ; Home
                                    136 ;--------------------------------------------------------
                                    137 	.area HOME
                                    138 	.area HOME
      008080                        139 __sdcc_program_startup:
      008080 CC 8C 18         [ 2]  140 	jp	_main
                                    141 ;	return from main will return to caller
                                    142 ;--------------------------------------------------------
                                    143 ; code
                                    144 ;--------------------------------------------------------
                                    145 	.area CODE
                                    146 ;	snake_game.c: 163: void initLCD(void)
                                    147 ;	-----------------------------------------
                                    148 ;	 function initLCD
                                    149 ;	-----------------------------------------
      0080A0                        150 _initLCD:
      0080A0 52 09            [ 2]  151 	sub	sp, #9
                                    152 ;	snake_game.c: 128: for(i = 0; i < delay; i++)
      0080A2 5F               [ 1]  153 	clrw	x
      0080A3                        154 00117$:
      0080A3 A3 EA 60         [ 2]  155 	cpw	x, #0xea60
      0080A6 24 04            [ 1]  156 	jrnc	00107$
                                    157 ;	snake_game.c: 129: __asm__("nop");
      0080A8 9D               [ 1]  158 	nop
                                    159 ;	snake_game.c: 128: for(i = 0; i < delay; i++)
      0080A9 5C               [ 2]  160 	incw	x
      0080AA 20 F7            [ 2]  161 	jra	00117$
                                    162 ;	snake_game.c: 167: delay16b(60000);
      0080AC                        163 00107$:
                                    164 ;	snake_game.c: 168: SET_RESET;
      0080AC AE 50 0A         [ 2]  165 	ldw	x, #0x500a
      0080AF F6               [ 1]  166 	ld	a, (x)
      0080B0 A4 FB            [ 1]  167 	and	a, #0xfb
      0080B2 F7               [ 1]  168 	ld	(x), a
                                    169 ;	snake_game.c: 128: for(i = 0; i < delay; i++)
      0080B3 5F               [ 1]  170 	clrw	x
      0080B4                        171 00120$:
      0080B4 A3 EA 60         [ 2]  172 	cpw	x, #0xea60
      0080B7 24 04            [ 1]  173 	jrnc	00109$
                                    174 ;	snake_game.c: 129: __asm__("nop");
      0080B9 9D               [ 1]  175 	nop
                                    176 ;	snake_game.c: 128: for(i = 0; i < delay; i++)
      0080BA 5C               [ 2]  177 	incw	x
      0080BB 20 F7            [ 2]  178 	jra	00120$
                                    179 ;	snake_game.c: 169: delay16b(60000);
      0080BD                        180 00109$:
                                    181 ;	snake_game.c: 171: CLR_RESET;
      0080BD AE 50 0A         [ 2]  182 	ldw	x, #0x500a
      0080C0 F6               [ 1]  183 	ld	a, (x)
      0080C1 AA 04            [ 1]  184 	or	a, #0x04
      0080C3 F7               [ 1]  185 	ld	(x), a
                                    186 ;	snake_game.c: 172: SET_CS;
      0080C4 AE 50 0A         [ 2]  187 	ldw	x, #0x500a
      0080C7 F6               [ 1]  188 	ld	a, (x)
      0080C8 A4 F7            [ 1]  189 	and	a, #0xf7
      0080CA F7               [ 1]  190 	ld	(x), a
                                    191 ;	snake_game.c: 173: SET_COMMAND;
      0080CB AE 50 0A         [ 2]  192 	ldw	x, #0x500a
      0080CE F6               [ 1]  193 	ld	a, (x)
      0080CF A4 EF            [ 1]  194 	and	a, #0xef
      0080D1 F7               [ 1]  195 	ld	(x), a
                                    196 ;	snake_game.c: 128: for(i = 0; i < delay; i++)
      0080D2 5F               [ 1]  197 	clrw	x
      0080D3                        198 00123$:
      0080D3 A3 09 EC         [ 2]  199 	cpw	x, #0x09ec
      0080D6 24 04            [ 1]  200 	jrnc	00140$
                                    201 ;	snake_game.c: 129: __asm__("nop");
      0080D8 9D               [ 1]  202 	nop
                                    203 ;	snake_game.c: 128: for(i = 0; i < delay; i++)
      0080D9 5C               [ 2]  204 	incw	x
      0080DA 20 F7            [ 2]  205 	jra	00123$
                                    206 ;	snake_game.c: 176: while(init_sequence[i] != 0x00){
      0080DC                        207 00140$:
      0080DC AE 8D 26         [ 2]  208 	ldw	x, #_init_sequence+0
      0080DF 1F 08            [ 2]  209 	ldw	(0x08, sp), x
      0080E1 0F 01            [ 1]  210 	clr	(0x01, sp)
      0080E3                        211 00101$:
      0080E3 5F               [ 1]  212 	clrw	x
      0080E4 7B 01            [ 1]  213 	ld	a, (0x01, sp)
      0080E6 97               [ 1]  214 	ld	xl, a
      0080E7 72 FB 08         [ 2]  215 	addw	x, (0x08, sp)
      0080EA F6               [ 1]  216 	ld	a, (x)
      0080EB 4D               [ 1]  217 	tnz	a
      0080EC 27 15            [ 1]  218 	jreq	00103$
                                    219 ;	snake_game.c: 159: while(*reg & mask)
      0080EE                        220 00112$:
      0080EE 90 AE 52 03      [ 2]  221 	ldw	y, #0x5203
      0080F2 90 F6            [ 1]  222 	ld	a, (y)
      0080F4 48               [ 1]  223 	sll	a
      0080F5 24 03            [ 1]  224 	jrnc	00115$
                                    225 ;	snake_game.c: 160: __asm__("nop");
      0080F7 9D               [ 1]  226 	nop
      0080F8 20 F4            [ 2]  227 	jra	00112$
                                    228 ;	snake_game.c: 177: waitForLo(&SPI->SR, 0x80);  /* Wait while SPI is busy transmitting data */
      0080FA                        229 00115$:
                                    230 ;	snake_game.c: 178: SPI->DR = init_sequence[i];
      0080FA F6               [ 1]  231 	ld	a, (x)
      0080FB AE 52 04         [ 2]  232 	ldw	x, #0x5204
      0080FE F7               [ 1]  233 	ld	(x), a
                                    234 ;	snake_game.c: 179: i++;
      0080FF 0C 01            [ 1]  235 	inc	(0x01, sp)
      008101 20 E0            [ 2]  236 	jra	00101$
      008103                        237 00103$:
                                    238 ;	snake_game.c: 182: gotoX(0);
      008103 4B 00            [ 1]  239 	push	#0x00
      008105 CD 81 4E         [ 4]  240 	call	_gotoX
      008108 84               [ 1]  241 	pop	a
                                    242 ;	snake_game.c: 183: gotoY(0);
      008109 4B 00            [ 1]  243 	push	#0x00
      00810B CD 81 6D         [ 4]  244 	call	_gotoY
      00810E 84               [ 1]  245 	pop	a
                                    246 ;	snake_game.c: 184: for(i = 0; i < 6; i++){
      00810F 4F               [ 1]  247 	clr	a
      008110                        248 00127$:
                                    249 ;	snake_game.c: 185: gotoY(i);
      008110 88               [ 1]  250 	push	a
      008111 88               [ 1]  251 	push	a
      008112 CD 81 6D         [ 4]  252 	call	_gotoY
      008115 84               [ 1]  253 	pop	a
      008116 84               [ 1]  254 	pop	a
                                    255 ;	snake_game.c: 186: for(x=0; x < 84; x++){
      008117 5F               [ 1]  256 	clrw	x
      008118 1F 02            [ 2]  257 	ldw	(0x02, sp), x
      00811A 5F               [ 1]  258 	clrw	x
      00811B 1F 06            [ 2]  259 	ldw	(0x06, sp), x
      00811D                        260 00125$:
                                    261 ;	snake_game.c: 187: writeData(0);
      00811D 88               [ 1]  262 	push	a
      00811E 4B 00            [ 1]  263 	push	#0x00
      008120 CD 81 A6         [ 4]  264 	call	_writeData
      008123 84               [ 1]  265 	pop	a
      008124 84               [ 1]  266 	pop	a
                                    267 ;	snake_game.c: 188: LCD_RAM[x][i] = 0;
      008125 AE 00 01         [ 2]  268 	ldw	x, #_LCD_RAM+0
      008128 72 FB 06         [ 2]  269 	addw	x, (0x06, sp)
      00812B 1F 04            [ 2]  270 	ldw	(0x04, sp), x
      00812D 5F               [ 1]  271 	clrw	x
      00812E 97               [ 1]  272 	ld	xl, a
      00812F 72 FB 04         [ 2]  273 	addw	x, (0x04, sp)
      008132 7F               [ 1]  274 	clr	(x)
                                    275 ;	snake_game.c: 186: for(x=0; x < 84; x++){
      008133 1E 06            [ 2]  276 	ldw	x, (0x06, sp)
      008135 1C 00 06         [ 2]  277 	addw	x, #0x0006
      008138 1F 06            [ 2]  278 	ldw	(0x06, sp), x
      00813A 1E 02            [ 2]  279 	ldw	x, (0x02, sp)
      00813C 5C               [ 2]  280 	incw	x
      00813D 1F 02            [ 2]  281 	ldw	(0x02, sp), x
      00813F 1E 02            [ 2]  282 	ldw	x, (0x02, sp)
      008141 A3 00 54         [ 2]  283 	cpw	x, #0x0054
      008144 25 D7            [ 1]  284 	jrc	00125$
                                    285 ;	snake_game.c: 184: for(i = 0; i < 6; i++){
      008146 4C               [ 1]  286 	inc	a
      008147 A1 06            [ 1]  287 	cp	a, #0x06
      008149 25 C5            [ 1]  288 	jrc	00127$
      00814B 5B 09            [ 2]  289 	addw	sp, #9
      00814D 81               [ 4]  290 	ret
                                    291 ;	snake_game.c: 193: void gotoX(uint8_t X_address)
                                    292 ;	-----------------------------------------
                                    293 ;	 function gotoX
                                    294 ;	-----------------------------------------
      00814E                        295 _gotoX:
                                    296 ;	snake_game.c: 195: LCD_X = X_address;
      00814E 7B 03            [ 1]  297 	ld	a, (0x03, sp)
      008150 C7 01 F9         [ 1]  298 	ld	_LCD_X+0, a
                                    299 ;	snake_game.c: 159: while(*reg & mask)
      008153                        300 00101$:
      008153 AE 52 03         [ 2]  301 	ldw	x, #0x5203
      008156 F6               [ 1]  302 	ld	a, (x)
      008157 48               [ 1]  303 	sll	a
      008158 24 03            [ 1]  304 	jrnc	00104$
                                    305 ;	snake_game.c: 160: __asm__("nop");
      00815A 9D               [ 1]  306 	nop
      00815B 20 F6            [ 2]  307 	jra	00101$
                                    308 ;	snake_game.c: 196: waitForLo(&SPI->SR, 0x80);  /* Wait while SPI is busy transmitting data */
      00815D                        309 00104$:
                                    310 ;	snake_game.c: 197: SET_COMMAND;
      00815D AE 50 0A         [ 2]  311 	ldw	x, #0x500a
      008160 F6               [ 1]  312 	ld	a, (x)
      008161 A4 EF            [ 1]  313 	and	a, #0xef
      008163 F7               [ 1]  314 	ld	(x), a
                                    315 ;	snake_game.c: 198: SPI->DR = X_address | 0x80;
      008164 7B 03            [ 1]  316 	ld	a, (0x03, sp)
      008166 AA 80            [ 1]  317 	or	a, #0x80
      008168 AE 52 04         [ 2]  318 	ldw	x, #0x5204
      00816B F7               [ 1]  319 	ld	(x), a
      00816C 81               [ 4]  320 	ret
                                    321 ;	snake_game.c: 201: void gotoY(uint8_t Y_address)
                                    322 ;	-----------------------------------------
                                    323 ;	 function gotoY
                                    324 ;	-----------------------------------------
      00816D                        325 _gotoY:
                                    326 ;	snake_game.c: 203: LCD_Y = Y_address;
      00816D 7B 03            [ 1]  327 	ld	a, (0x03, sp)
      00816F C7 01 FA         [ 1]  328 	ld	_LCD_Y+0, a
                                    329 ;	snake_game.c: 159: while(*reg & mask)
      008172                        330 00101$:
      008172 AE 52 03         [ 2]  331 	ldw	x, #0x5203
      008175 F6               [ 1]  332 	ld	a, (x)
      008176 48               [ 1]  333 	sll	a
      008177 24 03            [ 1]  334 	jrnc	00104$
                                    335 ;	snake_game.c: 160: __asm__("nop");
      008179 9D               [ 1]  336 	nop
      00817A 20 F6            [ 2]  337 	jra	00101$
                                    338 ;	snake_game.c: 204: waitForLo(&SPI->SR, 0x80);  /* Wait while SPI is busy transmitting data */
      00817C                        339 00104$:
                                    340 ;	snake_game.c: 205: SET_COMMAND;
      00817C AE 50 0A         [ 2]  341 	ldw	x, #0x500a
      00817F F6               [ 1]  342 	ld	a, (x)
      008180 A4 EF            [ 1]  343 	and	a, #0xef
      008182 F7               [ 1]  344 	ld	(x), a
                                    345 ;	snake_game.c: 206: SPI->DR = (Y_address & 0x07) | 0x40;
      008183 7B 03            [ 1]  346 	ld	a, (0x03, sp)
      008185 A4 07            [ 1]  347 	and	a, #0x07
      008187 AA 40            [ 1]  348 	or	a, #0x40
      008189 AE 52 04         [ 2]  349 	ldw	x, #0x5204
      00818C F7               [ 1]  350 	ld	(x), a
      00818D 81               [ 4]  351 	ret
                                    352 ;	snake_game.c: 209: void writeDataFast(uint8_t data)
                                    353 ;	-----------------------------------------
                                    354 ;	 function writeDataFast
                                    355 ;	-----------------------------------------
      00818E                        356 _writeDataFast:
                                    357 ;	snake_game.c: 159: while(*reg & mask)
      00818E                        358 00101$:
      00818E AE 52 03         [ 2]  359 	ldw	x, #0x5203
      008191 F6               [ 1]  360 	ld	a, (x)
      008192 48               [ 1]  361 	sll	a
      008193 24 03            [ 1]  362 	jrnc	00104$
                                    363 ;	snake_game.c: 160: __asm__("nop");
      008195 9D               [ 1]  364 	nop
      008196 20 F6            [ 2]  365 	jra	00101$
                                    366 ;	snake_game.c: 211: waitForLo(&SPI->SR, 0x80);  /* Wait while SPI is busy transmitting data */
      008198                        367 00104$:
                                    368 ;	snake_game.c: 212: SET_DATA;
      008198 AE 50 0A         [ 2]  369 	ldw	x, #0x500a
      00819B F6               [ 1]  370 	ld	a, (x)
      00819C AA 10            [ 1]  371 	or	a, #0x10
      00819E F7               [ 1]  372 	ld	(x), a
                                    373 ;	snake_game.c: 213: SPI->DR = data;
      00819F AE 52 04         [ 2]  374 	ldw	x, #0x5204
      0081A2 7B 03            [ 1]  375 	ld	a, (0x03, sp)
      0081A4 F7               [ 1]  376 	ld	(x), a
      0081A5 81               [ 4]  377 	ret
                                    378 ;	snake_game.c: 216: void writeData(uint8_t data)
                                    379 ;	-----------------------------------------
                                    380 ;	 function writeData
                                    381 ;	-----------------------------------------
      0081A6                        382 _writeData:
      0081A6 52 04            [ 2]  383 	sub	sp, #4
                                    384 ;	snake_game.c: 218: LCD_RAM[LCD_X][LCD_Y] = data;
      0081A8 AE 00 01         [ 2]  385 	ldw	x, #_LCD_RAM+0
      0081AB 1F 01            [ 2]  386 	ldw	(0x01, sp), x
      0081AD C6 01 F9         [ 1]  387 	ld	a, _LCD_X+0
      0081B0 97               [ 1]  388 	ld	xl, a
      0081B1 A6 06            [ 1]  389 	ld	a, #0x06
      0081B3 42               [ 4]  390 	mul	x, a
      0081B4 72 FB 01         [ 2]  391 	addw	x, (0x01, sp)
      0081B7 1F 03            [ 2]  392 	ldw	(0x03, sp), x
      0081B9 C6 01 FA         [ 1]  393 	ld	a, _LCD_Y+0
      0081BC 5F               [ 1]  394 	clrw	x
      0081BD 97               [ 1]  395 	ld	xl, a
      0081BE 72 FB 03         [ 2]  396 	addw	x, (0x03, sp)
      0081C1 7B 07            [ 1]  397 	ld	a, (0x07, sp)
      0081C3 F7               [ 1]  398 	ld	(x), a
                                    399 ;	snake_game.c: 219: LCD_X++;
      0081C4 72 5C 01 F9      [ 1]  400 	inc	_LCD_X+0
                                    401 ;	snake_game.c: 220: if( LCD_X > 83 ){
      0081C8 C6 01 F9         [ 1]  402 	ld	a, _LCD_X+0
      0081CB A1 53            [ 1]  403 	cp	a, #0x53
      0081CD 23 13            [ 2]  404 	jrule	00105$
                                    405 ;	snake_game.c: 221: LCD_X = 0;
      0081CF 72 5F 01 F9      [ 1]  406 	clr	_LCD_X+0
                                    407 ;	snake_game.c: 222: LCD_Y++;
      0081D3 72 5C 01 FA      [ 1]  408 	inc	_LCD_Y+0
                                    409 ;	snake_game.c: 223: if( LCD_Y > 5)
      0081D7 C6 01 FA         [ 1]  410 	ld	a, _LCD_Y+0
      0081DA A1 05            [ 1]  411 	cp	a, #0x05
      0081DC 23 04            [ 2]  412 	jrule	00105$
                                    413 ;	snake_game.c: 224: LCD_Y = 0;
      0081DE 72 5F 01 FA      [ 1]  414 	clr	_LCD_Y+0
                                    415 ;	snake_game.c: 159: while(*reg & mask)
      0081E2                        416 00105$:
      0081E2 AE 52 03         [ 2]  417 	ldw	x, #0x5203
      0081E5 F6               [ 1]  418 	ld	a, (x)
      0081E6 48               [ 1]  419 	sll	a
      0081E7 24 03            [ 1]  420 	jrnc	00108$
                                    421 ;	snake_game.c: 160: __asm__("nop");
      0081E9 9D               [ 1]  422 	nop
      0081EA 20 F6            [ 2]  423 	jra	00105$
                                    424 ;	snake_game.c: 226: waitForLo(&SPI->SR, 0x80);  /* Wait while SPI is busy transmitting data */
      0081EC                        425 00108$:
                                    426 ;	snake_game.c: 227: SET_DATA;
      0081EC AE 50 0A         [ 2]  427 	ldw	x, #0x500a
      0081EF F6               [ 1]  428 	ld	a, (x)
      0081F0 AA 10            [ 1]  429 	or	a, #0x10
      0081F2 F7               [ 1]  430 	ld	(x), a
                                    431 ;	snake_game.c: 228: SPI->DR = data;
      0081F3 AE 52 04         [ 2]  432 	ldw	x, #0x5204
      0081F6 7B 07            [ 1]  433 	ld	a, (0x07, sp)
      0081F8 F7               [ 1]  434 	ld	(x), a
      0081F9 5B 04            [ 2]  435 	addw	sp, #4
      0081FB 81               [ 4]  436 	ret
                                    437 ;	snake_game.c: 231: void refreshBlock(uint8_t x, uint8_t y)
                                    438 ;	-----------------------------------------
                                    439 ;	 function refreshBlock
                                    440 ;	-----------------------------------------
      0081FC                        441 _refreshBlock:
      0081FC 52 04            [ 2]  442 	sub	sp, #4
                                    443 ;	snake_game.c: 233: gotoX(x);
      0081FE 7B 07            [ 1]  444 	ld	a, (0x07, sp)
      008200 88               [ 1]  445 	push	a
      008201 CD 81 4E         [ 4]  446 	call	_gotoX
      008204 84               [ 1]  447 	pop	a
                                    448 ;	snake_game.c: 234: gotoY(y);
      008205 7B 08            [ 1]  449 	ld	a, (0x08, sp)
      008207 88               [ 1]  450 	push	a
      008208 CD 81 6D         [ 4]  451 	call	_gotoY
      00820B 84               [ 1]  452 	pop	a
                                    453 ;	snake_game.c: 235: writeDataFast(LCD_RAM[LCD_X][LCD_Y]);
      00820C AE 00 01         [ 2]  454 	ldw	x, #_LCD_RAM+0
      00820F 1F 03            [ 2]  455 	ldw	(0x03, sp), x
      008211 C6 01 F9         [ 1]  456 	ld	a, _LCD_X+0
      008214 97               [ 1]  457 	ld	xl, a
      008215 A6 06            [ 1]  458 	ld	a, #0x06
      008217 42               [ 4]  459 	mul	x, a
      008218 72 FB 03         [ 2]  460 	addw	x, (0x03, sp)
      00821B 1F 01            [ 2]  461 	ldw	(0x01, sp), x
      00821D C6 01 FA         [ 1]  462 	ld	a, _LCD_Y+0
      008220 5F               [ 1]  463 	clrw	x
      008221 97               [ 1]  464 	ld	xl, a
      008222 72 FB 01         [ 2]  465 	addw	x, (0x01, sp)
      008225 F6               [ 1]  466 	ld	a, (x)
      008226 88               [ 1]  467 	push	a
      008227 CD 81 8E         [ 4]  468 	call	_writeDataFast
      00822A 84               [ 1]  469 	pop	a
      00822B 5B 04            [ 2]  470 	addw	sp, #4
      00822D 81               [ 4]  471 	ret
                                    472 ;	snake_game.c: 238: void refreshSnakeTile(uint8_t x, uint8_t y)
                                    473 ;	-----------------------------------------
                                    474 ;	 function refreshSnakeTile
                                    475 ;	-----------------------------------------
      00822E                        476 _refreshSnakeTile:
      00822E 52 05            [ 2]  477 	sub	sp, #5
                                    478 ;	snake_game.c: 241: uint8_t lcd_tmp_x = x<<2;
      008230 7B 08            [ 1]  479 	ld	a, (0x08, sp)
      008232 48               [ 1]  480 	sll	a
      008233 48               [ 1]  481 	sll	a
      008234 6B 02            [ 1]  482 	ld	(0x02, sp), a
                                    483 ;	snake_game.c: 242: uint8_t lcd_tmp_y = y>>1;
      008236 7B 09            [ 1]  484 	ld	a, (0x09, sp)
      008238 44               [ 1]  485 	srl	a
      008239 6B 01            [ 1]  486 	ld	(0x01, sp), a
                                    487 ;	snake_game.c: 243: gotoX(lcd_tmp_x);
      00823B 7B 02            [ 1]  488 	ld	a, (0x02, sp)
      00823D 88               [ 1]  489 	push	a
      00823E CD 81 4E         [ 4]  490 	call	_gotoX
      008241 84               [ 1]  491 	pop	a
                                    492 ;	snake_game.c: 244: gotoY(lcd_tmp_y);
      008242 7B 01            [ 1]  493 	ld	a, (0x01, sp)
      008244 88               [ 1]  494 	push	a
      008245 CD 81 6D         [ 4]  495 	call	_gotoY
      008248 84               [ 1]  496 	pop	a
                                    497 ;	snake_game.c: 245: for(i = 0; i < 4; i++)
      008249 0F 03            [ 1]  498 	clr	(0x03, sp)
      00824B                        499 00102$:
                                    500 ;	snake_game.c: 246: writeDataFast(LCD_RAM[lcd_tmp_x + i][lcd_tmp_y]);
      00824B AE 00 01         [ 2]  501 	ldw	x, #_LCD_RAM+0
      00824E 1F 04            [ 2]  502 	ldw	(0x04, sp), x
      008250 7B 02            [ 1]  503 	ld	a, (0x02, sp)
      008252 1B 03            [ 1]  504 	add	a, (0x03, sp)
      008254 97               [ 1]  505 	ld	xl, a
      008255 A6 06            [ 1]  506 	ld	a, #0x06
      008257 42               [ 4]  507 	mul	x, a
      008258 72 FB 04         [ 2]  508 	addw	x, (0x04, sp)
      00825B 9F               [ 1]  509 	ld	a, xl
      00825C 1B 01            [ 1]  510 	add	a, (0x01, sp)
      00825E 97               [ 1]  511 	ld	xl, a
      00825F 9E               [ 1]  512 	ld	a, xh
      008260 A9 00            [ 1]  513 	adc	a, #0x00
      008262 95               [ 1]  514 	ld	xh, a
      008263 F6               [ 1]  515 	ld	a, (x)
      008264 88               [ 1]  516 	push	a
      008265 CD 81 8E         [ 4]  517 	call	_writeDataFast
      008268 84               [ 1]  518 	pop	a
                                    519 ;	snake_game.c: 245: for(i = 0; i < 4; i++)
      008269 0C 03            [ 1]  520 	inc	(0x03, sp)
      00826B 7B 03            [ 1]  521 	ld	a, (0x03, sp)
      00826D A1 04            [ 1]  522 	cp	a, #0x04
      00826F 25 DA            [ 1]  523 	jrc	00102$
      008271 5B 05            [ 2]  524 	addw	sp, #5
      008273 81               [ 4]  525 	ret
                                    526 ;	snake_game.c: 249: void setPixel(uint8_t x, uint8_t y)
                                    527 ;	-----------------------------------------
                                    528 ;	 function setPixel
                                    529 ;	-----------------------------------------
      008274                        530 _setPixel:
      008274 52 04            [ 2]  531 	sub	sp, #4
                                    532 ;	snake_game.c: 251: uint8_t row = y >> 3;
      008276 7B 08            [ 1]  533 	ld	a, (0x08, sp)
      008278 44               [ 1]  534 	srl	a
      008279 44               [ 1]  535 	srl	a
      00827A 44               [ 1]  536 	srl	a
      00827B 6B 02            [ 1]  537 	ld	(0x02, sp), a
                                    538 ;	snake_game.c: 252: uint8_t bit = 0x01 << (y & 0x07);
      00827D 7B 08            [ 1]  539 	ld	a, (0x08, sp)
      00827F A4 07            [ 1]  540 	and	a, #0x07
      008281 95               [ 1]  541 	ld	xh, a
      008282 A6 01            [ 1]  542 	ld	a, #0x01
      008284 6B 01            [ 1]  543 	ld	(0x01, sp), a
      008286 9E               [ 1]  544 	ld	a, xh
      008287 4D               [ 1]  545 	tnz	a
      008288 27 05            [ 1]  546 	jreq	00104$
      00828A                        547 00103$:
      00828A 08 01            [ 1]  548 	sll	(0x01, sp)
      00828C 4A               [ 1]  549 	dec	a
      00828D 26 FB            [ 1]  550 	jrne	00103$
      00828F                        551 00104$:
                                    552 ;	snake_game.c: 253: gotoX(x);
      00828F 7B 07            [ 1]  553 	ld	a, (0x07, sp)
      008291 88               [ 1]  554 	push	a
      008292 CD 81 4E         [ 4]  555 	call	_gotoX
      008295 84               [ 1]  556 	pop	a
                                    557 ;	snake_game.c: 254: gotoY(row);
      008296 7B 02            [ 1]  558 	ld	a, (0x02, sp)
      008298 88               [ 1]  559 	push	a
      008299 CD 81 6D         [ 4]  560 	call	_gotoY
      00829C 84               [ 1]  561 	pop	a
                                    562 ;	snake_game.c: 255: writeData( LCD_RAM[x][row] | bit );
      00829D AE 00 01         [ 2]  563 	ldw	x, #_LCD_RAM+0
      0082A0 1F 03            [ 2]  564 	ldw	(0x03, sp), x
      0082A2 7B 07            [ 1]  565 	ld	a, (0x07, sp)
      0082A4 97               [ 1]  566 	ld	xl, a
      0082A5 A6 06            [ 1]  567 	ld	a, #0x06
      0082A7 42               [ 4]  568 	mul	x, a
      0082A8 72 FB 03         [ 2]  569 	addw	x, (0x03, sp)
      0082AB 9F               [ 1]  570 	ld	a, xl
      0082AC 1B 02            [ 1]  571 	add	a, (0x02, sp)
      0082AE 97               [ 1]  572 	ld	xl, a
      0082AF 9E               [ 1]  573 	ld	a, xh
      0082B0 A9 00            [ 1]  574 	adc	a, #0x00
      0082B2 95               [ 1]  575 	ld	xh, a
      0082B3 F6               [ 1]  576 	ld	a, (x)
      0082B4 1A 01            [ 1]  577 	or	a, (0x01, sp)
      0082B6 88               [ 1]  578 	push	a
      0082B7 CD 81 A6         [ 4]  579 	call	_writeData
      0082BA 84               [ 1]  580 	pop	a
      0082BB 5B 04            [ 2]  581 	addw	sp, #4
      0082BD 81               [ 4]  582 	ret
                                    583 ;	snake_game.c: 258: void clrPixel(uint8_t x, uint8_t y)
                                    584 ;	-----------------------------------------
                                    585 ;	 function clrPixel
                                    586 ;	-----------------------------------------
      0082BE                        587 _clrPixel:
      0082BE 52 07            [ 2]  588 	sub	sp, #7
                                    589 ;	snake_game.c: 260: uint8_t row = y >> 3;
      0082C0 7B 0B            [ 1]  590 	ld	a, (0x0b, sp)
      0082C2 44               [ 1]  591 	srl	a
      0082C3 44               [ 1]  592 	srl	a
      0082C4 44               [ 1]  593 	srl	a
      0082C5 6B 02            [ 1]  594 	ld	(0x02, sp), a
                                    595 ;	snake_game.c: 261: uint8_t bit = 1 << (y & 0x07);
      0082C7 7B 0B            [ 1]  596 	ld	a, (0x0b, sp)
      0082C9 A4 07            [ 1]  597 	and	a, #0x07
      0082CB 95               [ 1]  598 	ld	xh, a
      0082CC A6 01            [ 1]  599 	ld	a, #0x01
      0082CE 6B 01            [ 1]  600 	ld	(0x01, sp), a
      0082D0 9E               [ 1]  601 	ld	a, xh
      0082D1 4D               [ 1]  602 	tnz	a
      0082D2 27 05            [ 1]  603 	jreq	00104$
      0082D4                        604 00103$:
      0082D4 08 01            [ 1]  605 	sll	(0x01, sp)
      0082D6 4A               [ 1]  606 	dec	a
      0082D7 26 FB            [ 1]  607 	jrne	00103$
      0082D9                        608 00104$:
                                    609 ;	snake_game.c: 262: gotoX(x);
      0082D9 7B 0A            [ 1]  610 	ld	a, (0x0a, sp)
      0082DB 88               [ 1]  611 	push	a
      0082DC CD 81 4E         [ 4]  612 	call	_gotoX
      0082DF 84               [ 1]  613 	pop	a
                                    614 ;	snake_game.c: 263: gotoY(row);
      0082E0 7B 02            [ 1]  615 	ld	a, (0x02, sp)
      0082E2 88               [ 1]  616 	push	a
      0082E3 CD 81 6D         [ 4]  617 	call	_gotoY
      0082E6 84               [ 1]  618 	pop	a
                                    619 ;	snake_game.c: 264: writeData( LCD_RAM[LCD_X][LCD_Y] & ~bit );
      0082E7 AE 00 01         [ 2]  620 	ldw	x, #_LCD_RAM+0
      0082EA 1F 03            [ 2]  621 	ldw	(0x03, sp), x
      0082EC C6 01 F9         [ 1]  622 	ld	a, _LCD_X+0
      0082EF 97               [ 1]  623 	ld	xl, a
      0082F0 A6 06            [ 1]  624 	ld	a, #0x06
      0082F2 42               [ 4]  625 	mul	x, a
      0082F3 72 FB 03         [ 2]  626 	addw	x, (0x03, sp)
      0082F6 1F 06            [ 2]  627 	ldw	(0x06, sp), x
      0082F8 C6 01 FA         [ 1]  628 	ld	a, _LCD_Y+0
      0082FB 5F               [ 1]  629 	clrw	x
      0082FC 97               [ 1]  630 	ld	xl, a
      0082FD 72 FB 06         [ 2]  631 	addw	x, (0x06, sp)
      008300 7B 01            [ 1]  632 	ld	a, (0x01, sp)
      008302 43               [ 1]  633 	cpl	a
      008303 6B 05            [ 1]  634 	ld	(0x05, sp), a
      008305 F6               [ 1]  635 	ld	a, (x)
      008306 14 05            [ 1]  636 	and	a, (0x05, sp)
      008308 88               [ 1]  637 	push	a
      008309 CD 81 A6         [ 4]  638 	call	_writeData
      00830C 84               [ 1]  639 	pop	a
      00830D 5B 07            [ 2]  640 	addw	sp, #7
      00830F 81               [ 4]  641 	ret
                                    642 ;	snake_game.c: 267: uint8_t ADCread(uint8_t channel)
                                    643 ;	-----------------------------------------
                                    644 ;	 function ADCread
                                    645 ;	-----------------------------------------
      008310                        646 _ADCread:
      008310 88               [ 1]  647 	push	a
                                    648 ;	snake_game.c: 269: ADC1->CSR &=~ 0x0F;
      008311 AE 54 00         [ 2]  649 	ldw	x, #0x5400
      008314 F6               [ 1]  650 	ld	a, (x)
      008315 A4 F0            [ 1]  651 	and	a, #0xf0
      008317 F7               [ 1]  652 	ld	(x), a
                                    653 ;	snake_game.c: 270: ADC1->CSR |= channel & 0x0F;
      008318 AE 54 00         [ 2]  654 	ldw	x, #0x5400
      00831B F6               [ 1]  655 	ld	a, (x)
      00831C 6B 01            [ 1]  656 	ld	(0x01, sp), a
      00831E 7B 04            [ 1]  657 	ld	a, (0x04, sp)
      008320 A4 0F            [ 1]  658 	and	a, #0x0f
      008322 1A 01            [ 1]  659 	or	a, (0x01, sp)
      008324 AE 54 00         [ 2]  660 	ldw	x, #0x5400
      008327 F7               [ 1]  661 	ld	(x), a
                                    662 ;	snake_game.c: 271: ADC1->CR1 |= (1<<0);  /* initiate conversion */
      008328 72 10 54 01      [ 1]  663 	bset	0x5401, #0
                                    664 ;	snake_game.c: 147: while(!(*reg & mask))
      00832C                        665 00101$:
      00832C AE 54 00         [ 2]  666 	ldw	x, #0x5400
      00832F F6               [ 1]  667 	ld	a, (x)
      008330 48               [ 1]  668 	sll	a
      008331 25 03            [ 1]  669 	jrc	00104$
                                    670 ;	snake_game.c: 148: __asm__("nop");
      008333 9D               [ 1]  671 	nop
      008334 20 F6            [ 2]  672 	jra	00101$
                                    673 ;	snake_game.c: 272: waitForHi( &ADC1->CSR, 1 << 7 );
      008336                        674 00104$:
                                    675 ;	snake_game.c: 273: ADC1->CSR &= ~(1<<7); /* Clear conversion-done flag */
      008336 72 17 54 00      [ 1]  676 	bres	0x5400, #7
                                    677 ;	snake_game.c: 274: return ADC1->DRH;
      00833A AE 54 04         [ 2]  678 	ldw	x, #0x5404
      00833D F6               [ 1]  679 	ld	a, (x)
      00833E 5B 01            [ 2]  680 	addw	sp, #1
      008340 81               [ 4]  681 	ret
                                    682 ;	snake_game.c: 295: void setSnakeTile(uint8_t x, uint8_t y, enum Snake_tile tileID)
                                    683 ;	-----------------------------------------
                                    684 ;	 function setSnakeTile
                                    685 ;	-----------------------------------------
      008341                        686 _setSnakeTile:
      008341 52 42            [ 2]  687 	sub	sp, #66
                                    688 ;	snake_game.c: 297: uint8_t tmp_x = x << 2;
      008343 7B 45            [ 1]  689 	ld	a, (0x45, sp)
      008345 48               [ 1]  690 	sll	a
      008346 48               [ 1]  691 	sll	a
      008347 6B 42            [ 1]  692 	ld	(0x42, sp), a
                                    693 ;	snake_game.c: 298: uint8_t tmp_y = y >> 1;
      008349 7B 46            [ 1]  694 	ld	a, (0x46, sp)
      00834B 44               [ 1]  695 	srl	a
      00834C 6B 01            [ 1]  696 	ld	(0x01, sp), a
                                    697 ;	snake_game.c: 300: Snake_array[x][y] = tileID;
      00834E AE 01 FC         [ 2]  698 	ldw	x, #_Snake_array+0
      008351 1F 25            [ 2]  699 	ldw	(0x25, sp), x
      008353 7B 45            [ 1]  700 	ld	a, (0x45, sp)
      008355 97               [ 1]  701 	ld	xl, a
      008356 A6 0A            [ 1]  702 	ld	a, #0x0a
      008358 42               [ 4]  703 	mul	x, a
      008359 72 FB 25         [ 2]  704 	addw	x, (0x25, sp)
      00835C 7B 46            [ 1]  705 	ld	a, (0x46, sp)
      00835E 6B 2C            [ 1]  706 	ld	(0x2c, sp), a
      008360 9F               [ 1]  707 	ld	a, xl
      008361 1B 2C            [ 1]  708 	add	a, (0x2c, sp)
      008363 97               [ 1]  709 	ld	xl, a
      008364 9E               [ 1]  710 	ld	a, xh
      008365 A9 00            [ 1]  711 	adc	a, #0x00
      008367 95               [ 1]  712 	ld	xh, a
      008368 7B 47            [ 1]  713 	ld	a, (0x47, sp)
      00836A F7               [ 1]  714 	ld	(x), a
                                    715 ;	snake_game.c: 303: LCD_RAM[tmp_x][tmp_y] &= ~0xF0;
      00836B 7B 42            [ 1]  716 	ld	a, (0x42, sp)
      00836D 97               [ 1]  717 	ld	xl, a
      00836E A6 06            [ 1]  718 	ld	a, #0x06
      008370 42               [ 4]  719 	mul	x, a
      008371 1F 2E            [ 2]  720 	ldw	(0x2e, sp), x
                                    721 ;	snake_game.c: 304: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][0] & 0xF0;
      008373 5F               [ 1]  722 	clrw	x
      008374 7B 47            [ 1]  723 	ld	a, (0x47, sp)
      008376 97               [ 1]  724 	ld	xl, a
                                    725 ;	snake_game.c: 305: tmp_x++;
      008377 7B 42            [ 1]  726 	ld	a, (0x42, sp)
      008379 4C               [ 1]  727 	inc	a
      00837A 6B 2D            [ 1]  728 	ld	(0x2d, sp), a
                                    729 ;	snake_game.c: 304: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][0] & 0xF0;
      00837C 58               [ 2]  730 	sllw	x
      00837D 1F 2A            [ 2]  731 	ldw	(0x2a, sp), x
                                    732 ;	snake_game.c: 302: if( y & 0x01 ){ /* Top tile */
      00837F 7B 2C            [ 1]  733 	ld	a, (0x2c, sp)
      008381 44               [ 1]  734 	srl	a
      008382 25 03            [ 1]  735 	jrc	00110$
      008384 CC 85 02         [ 2]  736 	jp	00102$
      008387                        737 00110$:
                                    738 ;	snake_game.c: 303: LCD_RAM[tmp_x][tmp_y] &= ~0xF0;
      008387 AE 00 01         [ 2]  739 	ldw	x, #_LCD_RAM+0
      00838A 72 FB 2E         [ 2]  740 	addw	x, (0x2e, sp)
      00838D 9F               [ 1]  741 	ld	a, xl
      00838E 1B 01            [ 1]  742 	add	a, (0x01, sp)
      008390 90 97            [ 1]  743 	ld	yl, a
      008392 9E               [ 1]  744 	ld	a, xh
      008393 A9 00            [ 1]  745 	adc	a, #0x00
      008395 90 95            [ 1]  746 	ld	yh, a
      008397 AE 00 01         [ 2]  747 	ldw	x, #_LCD_RAM+0
      00839A 72 FB 2E         [ 2]  748 	addw	x, (0x2e, sp)
      00839D 9F               [ 1]  749 	ld	a, xl
      00839E 1B 01            [ 1]  750 	add	a, (0x01, sp)
      0083A0 97               [ 1]  751 	ld	xl, a
      0083A1 9E               [ 1]  752 	ld	a, xh
      0083A2 A9 00            [ 1]  753 	adc	a, #0x00
      0083A4 95               [ 1]  754 	ld	xh, a
      0083A5 F6               [ 1]  755 	ld	a, (x)
      0083A6 A4 0F            [ 1]  756 	and	a, #0x0f
      0083A8 90 F7            [ 1]  757 	ld	(y), a
                                    758 ;	snake_game.c: 304: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][0] & 0xF0;
      0083AA AE 00 01         [ 2]  759 	ldw	x, #_LCD_RAM+0
      0083AD 72 FB 2E         [ 2]  760 	addw	x, (0x2e, sp)
      0083B0 9F               [ 1]  761 	ld	a, xl
      0083B1 1B 01            [ 1]  762 	add	a, (0x01, sp)
      0083B3 6B 29            [ 1]  763 	ld	(0x29, sp), a
      0083B5 9E               [ 1]  764 	ld	a, xh
      0083B6 A9 00            [ 1]  765 	adc	a, #0x00
      0083B8 6B 28            [ 1]  766 	ld	(0x28, sp), a
      0083BA AE 00 01         [ 2]  767 	ldw	x, #_LCD_RAM+0
      0083BD 72 FB 2E         [ 2]  768 	addw	x, (0x2e, sp)
      0083C0 9F               [ 1]  769 	ld	a, xl
      0083C1 1B 01            [ 1]  770 	add	a, (0x01, sp)
      0083C3 97               [ 1]  771 	ld	xl, a
      0083C4 9E               [ 1]  772 	ld	a, xh
      0083C5 A9 00            [ 1]  773 	adc	a, #0x00
      0083C7 95               [ 1]  774 	ld	xh, a
      0083C8 90 AE 8D 2D      [ 2]  775 	ldw	y, #_snake_tiles+0
      0083CC 72 F9 2A         [ 2]  776 	addw	y, (0x2a, sp)
      0083CF 90 F6            [ 1]  777 	ld	a, (y)
      0083D1 A4 F0            [ 1]  778 	and	a, #0xf0
      0083D3 6B 27            [ 1]  779 	ld	(0x27, sp), a
      0083D5 F6               [ 1]  780 	ld	a, (x)
      0083D6 1A 27            [ 1]  781 	or	a, (0x27, sp)
      0083D8 1E 28            [ 2]  782 	ldw	x, (0x28, sp)
      0083DA F7               [ 1]  783 	ld	(x), a
                                    784 ;	snake_game.c: 305: tmp_x++;
      0083DB 7B 2D            [ 1]  785 	ld	a, (0x2d, sp)
      0083DD 6B 41            [ 1]  786 	ld	(0x41, sp), a
                                    787 ;	snake_game.c: 306: LCD_RAM[tmp_x][tmp_y] &= ~0xF0;
      0083DF AE 00 01         [ 2]  788 	ldw	x, #_LCD_RAM+0
      0083E2 89               [ 2]  789 	pushw	x
      0083E3 7B 43            [ 1]  790 	ld	a, (0x43, sp)
      0083E5 97               [ 1]  791 	ld	xl, a
      0083E6 A6 06            [ 1]  792 	ld	a, #0x06
      0083E8 42               [ 4]  793 	mul	x, a
      0083E9 1F 41            [ 2]  794 	ldw	(0x41, sp), x
      0083EB 85               [ 2]  795 	popw	x
      0083EC 72 FB 3F         [ 2]  796 	addw	x, (0x3f, sp)
      0083EF 9F               [ 1]  797 	ld	a, xl
      0083F0 1B 01            [ 1]  798 	add	a, (0x01, sp)
      0083F2 6B 3E            [ 1]  799 	ld	(0x3e, sp), a
      0083F4 9E               [ 1]  800 	ld	a, xh
      0083F5 A9 00            [ 1]  801 	adc	a, #0x00
      0083F7 6B 3D            [ 1]  802 	ld	(0x3d, sp), a
      0083F9 AE 00 01         [ 2]  803 	ldw	x, #_LCD_RAM+0
      0083FC 72 FB 3F         [ 2]  804 	addw	x, (0x3f, sp)
      0083FF 9F               [ 1]  805 	ld	a, xl
      008400 1B 01            [ 1]  806 	add	a, (0x01, sp)
      008402 97               [ 1]  807 	ld	xl, a
      008403 9E               [ 1]  808 	ld	a, xh
      008404 A9 00            [ 1]  809 	adc	a, #0x00
      008406 95               [ 1]  810 	ld	xh, a
      008407 F6               [ 1]  811 	ld	a, (x)
      008408 A4 0F            [ 1]  812 	and	a, #0x0f
      00840A 1E 3D            [ 2]  813 	ldw	x, (0x3d, sp)
      00840C F7               [ 1]  814 	ld	(x), a
                                    815 ;	snake_game.c: 307: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][0] << 4;
      00840D AE 00 01         [ 2]  816 	ldw	x, #_LCD_RAM+0
      008410 72 FB 3F         [ 2]  817 	addw	x, (0x3f, sp)
      008413 9F               [ 1]  818 	ld	a, xl
      008414 1B 01            [ 1]  819 	add	a, (0x01, sp)
      008416 6B 3C            [ 1]  820 	ld	(0x3c, sp), a
      008418 9E               [ 1]  821 	ld	a, xh
      008419 A9 00            [ 1]  822 	adc	a, #0x00
      00841B 6B 3B            [ 1]  823 	ld	(0x3b, sp), a
      00841D AE 00 01         [ 2]  824 	ldw	x, #_LCD_RAM+0
      008420 72 FB 3F         [ 2]  825 	addw	x, (0x3f, sp)
      008423 9F               [ 1]  826 	ld	a, xl
      008424 1B 01            [ 1]  827 	add	a, (0x01, sp)
      008426 97               [ 1]  828 	ld	xl, a
      008427 9E               [ 1]  829 	ld	a, xh
      008428 A9 00            [ 1]  830 	adc	a, #0x00
      00842A 95               [ 1]  831 	ld	xh, a
      00842B 90 F6            [ 1]  832 	ld	a, (y)
      00842D 48               [ 1]  833 	sll	a
      00842E 48               [ 1]  834 	sll	a
      00842F 48               [ 1]  835 	sll	a
      008430 48               [ 1]  836 	sll	a
      008431 6B 3A            [ 1]  837 	ld	(0x3a, sp), a
      008433 F6               [ 1]  838 	ld	a, (x)
      008434 1A 3A            [ 1]  839 	or	a, (0x3a, sp)
      008436 1E 3B            [ 2]  840 	ldw	x, (0x3b, sp)
      008438 F7               [ 1]  841 	ld	(x), a
                                    842 ;	snake_game.c: 308: tmp_x++;
      008439 7B 41            [ 1]  843 	ld	a, (0x41, sp)
      00843B 4C               [ 1]  844 	inc	a
      00843C 6B 39            [ 1]  845 	ld	(0x39, sp), a
      00843E 7B 39            [ 1]  846 	ld	a, (0x39, sp)
      008440 6B 38            [ 1]  847 	ld	(0x38, sp), a
                                    848 ;	snake_game.c: 309: LCD_RAM[tmp_x][tmp_y] &= ~0xF0;
      008442 AE 00 01         [ 2]  849 	ldw	x, #_LCD_RAM+0
      008445 89               [ 2]  850 	pushw	x
      008446 7B 3A            [ 1]  851 	ld	a, (0x3a, sp)
      008448 97               [ 1]  852 	ld	xl, a
      008449 A6 06            [ 1]  853 	ld	a, #0x06
      00844B 42               [ 4]  854 	mul	x, a
      00844C 1F 38            [ 2]  855 	ldw	(0x38, sp), x
      00844E 85               [ 2]  856 	popw	x
      00844F 72 FB 36         [ 2]  857 	addw	x, (0x36, sp)
      008452 9F               [ 1]  858 	ld	a, xl
      008453 1B 01            [ 1]  859 	add	a, (0x01, sp)
      008455 6B 35            [ 1]  860 	ld	(0x35, sp), a
      008457 9E               [ 1]  861 	ld	a, xh
      008458 A9 00            [ 1]  862 	adc	a, #0x00
      00845A 6B 34            [ 1]  863 	ld	(0x34, sp), a
      00845C AE 00 01         [ 2]  864 	ldw	x, #_LCD_RAM+0
      00845F 72 FB 36         [ 2]  865 	addw	x, (0x36, sp)
      008462 9F               [ 1]  866 	ld	a, xl
      008463 1B 01            [ 1]  867 	add	a, (0x01, sp)
      008465 97               [ 1]  868 	ld	xl, a
      008466 9E               [ 1]  869 	ld	a, xh
      008467 A9 00            [ 1]  870 	adc	a, #0x00
      008469 95               [ 1]  871 	ld	xh, a
      00846A F6               [ 1]  872 	ld	a, (x)
      00846B A4 0F            [ 1]  873 	and	a, #0x0f
      00846D 1E 34            [ 2]  874 	ldw	x, (0x34, sp)
      00846F F7               [ 1]  875 	ld	(x), a
                                    876 ;	snake_game.c: 310: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][1] & 0xF0;
      008470 AE 00 01         [ 2]  877 	ldw	x, #_LCD_RAM+0
      008473 72 FB 36         [ 2]  878 	addw	x, (0x36, sp)
      008476 9F               [ 1]  879 	ld	a, xl
      008477 1B 01            [ 1]  880 	add	a, (0x01, sp)
      008479 6B 33            [ 1]  881 	ld	(0x33, sp), a
      00847B 9E               [ 1]  882 	ld	a, xh
      00847C A9 00            [ 1]  883 	adc	a, #0x00
      00847E 6B 32            [ 1]  884 	ld	(0x32, sp), a
      008480 AE 00 01         [ 2]  885 	ldw	x, #_LCD_RAM+0
      008483 72 FB 36         [ 2]  886 	addw	x, (0x36, sp)
      008486 9F               [ 1]  887 	ld	a, xl
      008487 1B 01            [ 1]  888 	add	a, (0x01, sp)
      008489 97               [ 1]  889 	ld	xl, a
      00848A 9E               [ 1]  890 	ld	a, xh
      00848B A9 00            [ 1]  891 	adc	a, #0x00
      00848D 95               [ 1]  892 	ld	xh, a
      00848E 90 5C            [ 2]  893 	incw	y
      008490 90 F6            [ 1]  894 	ld	a, (y)
      008492 A4 F0            [ 1]  895 	and	a, #0xf0
      008494 6B 31            [ 1]  896 	ld	(0x31, sp), a
      008496 F6               [ 1]  897 	ld	a, (x)
      008497 1A 31            [ 1]  898 	or	a, (0x31, sp)
      008499 1E 32            [ 2]  899 	ldw	x, (0x32, sp)
      00849B F7               [ 1]  900 	ld	(x), a
                                    901 ;	snake_game.c: 311: tmp_x++;    
      00849C 7B 38            [ 1]  902 	ld	a, (0x38, sp)
      00849E 4C               [ 1]  903 	inc	a
      00849F 6B 30            [ 1]  904 	ld	(0x30, sp), a
      0084A1 7B 30            [ 1]  905 	ld	a, (0x30, sp)
      0084A3 6B 02            [ 1]  906 	ld	(0x02, sp), a
                                    907 ;	snake_game.c: 312: LCD_RAM[tmp_x][tmp_y] &= ~0xF0;
      0084A5 AE 00 01         [ 2]  908 	ldw	x, #_LCD_RAM+0
      0084A8 89               [ 2]  909 	pushw	x
      0084A9 7B 04            [ 1]  910 	ld	a, (0x04, sp)
      0084AB 97               [ 1]  911 	ld	xl, a
      0084AC A6 06            [ 1]  912 	ld	a, #0x06
      0084AE 42               [ 4]  913 	mul	x, a
      0084AF 1F 25            [ 2]  914 	ldw	(0x25, sp), x
      0084B1 85               [ 2]  915 	popw	x
      0084B2 72 FB 23         [ 2]  916 	addw	x, (0x23, sp)
      0084B5 9F               [ 1]  917 	ld	a, xl
      0084B6 1B 01            [ 1]  918 	add	a, (0x01, sp)
      0084B8 6B 22            [ 1]  919 	ld	(0x22, sp), a
      0084BA 9E               [ 1]  920 	ld	a, xh
      0084BB A9 00            [ 1]  921 	adc	a, #0x00
      0084BD 6B 21            [ 1]  922 	ld	(0x21, sp), a
      0084BF AE 00 01         [ 2]  923 	ldw	x, #_LCD_RAM+0
      0084C2 72 FB 23         [ 2]  924 	addw	x, (0x23, sp)
      0084C5 9F               [ 1]  925 	ld	a, xl
      0084C6 1B 01            [ 1]  926 	add	a, (0x01, sp)
      0084C8 97               [ 1]  927 	ld	xl, a
      0084C9 9E               [ 1]  928 	ld	a, xh
      0084CA A9 00            [ 1]  929 	adc	a, #0x00
      0084CC 95               [ 1]  930 	ld	xh, a
      0084CD F6               [ 1]  931 	ld	a, (x)
      0084CE A4 0F            [ 1]  932 	and	a, #0x0f
      0084D0 1E 21            [ 2]  933 	ldw	x, (0x21, sp)
      0084D2 F7               [ 1]  934 	ld	(x), a
                                    935 ;	snake_game.c: 313: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][1] << 4;
      0084D3 AE 00 01         [ 2]  936 	ldw	x, #_LCD_RAM+0
      0084D6 72 FB 23         [ 2]  937 	addw	x, (0x23, sp)
      0084D9 9F               [ 1]  938 	ld	a, xl
      0084DA 1B 01            [ 1]  939 	add	a, (0x01, sp)
      0084DC 6B 20            [ 1]  940 	ld	(0x20, sp), a
      0084DE 9E               [ 1]  941 	ld	a, xh
      0084DF A9 00            [ 1]  942 	adc	a, #0x00
      0084E1 6B 1F            [ 1]  943 	ld	(0x1f, sp), a
      0084E3 AE 00 01         [ 2]  944 	ldw	x, #_LCD_RAM+0
      0084E6 72 FB 23         [ 2]  945 	addw	x, (0x23, sp)
      0084E9 9F               [ 1]  946 	ld	a, xl
      0084EA 1B 01            [ 1]  947 	add	a, (0x01, sp)
      0084EC 97               [ 1]  948 	ld	xl, a
      0084ED 9E               [ 1]  949 	ld	a, xh
      0084EE A9 00            [ 1]  950 	adc	a, #0x00
      0084F0 95               [ 1]  951 	ld	xh, a
      0084F1 90 F6            [ 1]  952 	ld	a, (y)
      0084F3 48               [ 1]  953 	sll	a
      0084F4 48               [ 1]  954 	sll	a
      0084F5 48               [ 1]  955 	sll	a
      0084F6 48               [ 1]  956 	sll	a
      0084F7 6B 1E            [ 1]  957 	ld	(0x1e, sp), a
      0084F9 F6               [ 1]  958 	ld	a, (x)
      0084FA 1A 1E            [ 1]  959 	or	a, (0x1e, sp)
      0084FC 1E 1F            [ 2]  960 	ldw	x, (0x1f, sp)
      0084FE F7               [ 1]  961 	ld	(x), a
      0084FF CC 86 71         [ 2]  962 	jp	00103$
      008502                        963 00102$:
                                    964 ;	snake_game.c: 316: LCD_RAM[tmp_x][tmp_y] &= ~0x0F;
      008502 AE 00 01         [ 2]  965 	ldw	x, #_LCD_RAM+0
      008505 72 FB 2E         [ 2]  966 	addw	x, (0x2e, sp)
      008508 9F               [ 1]  967 	ld	a, xl
      008509 1B 01            [ 1]  968 	add	a, (0x01, sp)
      00850B 90 97            [ 1]  969 	ld	yl, a
      00850D 9E               [ 1]  970 	ld	a, xh
      00850E A9 00            [ 1]  971 	adc	a, #0x00
      008510 90 95            [ 1]  972 	ld	yh, a
      008512 AE 00 01         [ 2]  973 	ldw	x, #_LCD_RAM+0
      008515 72 FB 2E         [ 2]  974 	addw	x, (0x2e, sp)
      008518 9F               [ 1]  975 	ld	a, xl
      008519 1B 01            [ 1]  976 	add	a, (0x01, sp)
      00851B 97               [ 1]  977 	ld	xl, a
      00851C 9E               [ 1]  978 	ld	a, xh
      00851D A9 00            [ 1]  979 	adc	a, #0x00
      00851F 95               [ 1]  980 	ld	xh, a
      008520 F6               [ 1]  981 	ld	a, (x)
      008521 A4 F0            [ 1]  982 	and	a, #0xf0
      008523 90 F7            [ 1]  983 	ld	(y), a
                                    984 ;	snake_game.c: 317: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][0] >> 4;
      008525 AE 00 01         [ 2]  985 	ldw	x, #_LCD_RAM+0
      008528 72 FB 2E         [ 2]  986 	addw	x, (0x2e, sp)
      00852B 9F               [ 1]  987 	ld	a, xl
      00852C 1B 01            [ 1]  988 	add	a, (0x01, sp)
      00852E 6B 1D            [ 1]  989 	ld	(0x1d, sp), a
      008530 9E               [ 1]  990 	ld	a, xh
      008531 A9 00            [ 1]  991 	adc	a, #0x00
      008533 6B 1C            [ 1]  992 	ld	(0x1c, sp), a
      008535 AE 00 01         [ 2]  993 	ldw	x, #_LCD_RAM+0
      008538 72 FB 2E         [ 2]  994 	addw	x, (0x2e, sp)
      00853B 9F               [ 1]  995 	ld	a, xl
      00853C 1B 01            [ 1]  996 	add	a, (0x01, sp)
      00853E 97               [ 1]  997 	ld	xl, a
      00853F 9E               [ 1]  998 	ld	a, xh
      008540 A9 00            [ 1]  999 	adc	a, #0x00
      008542 95               [ 1] 1000 	ld	xh, a
      008543 90 AE 8D 2D      [ 2] 1001 	ldw	y, #_snake_tiles+0
      008547 72 F9 2A         [ 2] 1002 	addw	y, (0x2a, sp)
      00854A 90 F6            [ 1] 1003 	ld	a, (y)
      00854C 4E               [ 1] 1004 	swap	a
      00854D A4 0F            [ 1] 1005 	and	a, #0x0f
      00854F 6B 1B            [ 1] 1006 	ld	(0x1b, sp), a
      008551 F6               [ 1] 1007 	ld	a, (x)
      008552 1A 1B            [ 1] 1008 	or	a, (0x1b, sp)
      008554 1E 1C            [ 2] 1009 	ldw	x, (0x1c, sp)
      008556 F7               [ 1] 1010 	ld	(x), a
                                   1011 ;	snake_game.c: 318: tmp_x++;
      008557 7B 2D            [ 1] 1012 	ld	a, (0x2d, sp)
      008559 6B 1A            [ 1] 1013 	ld	(0x1a, sp), a
                                   1014 ;	snake_game.c: 319: LCD_RAM[tmp_x][tmp_y] &= ~0x0F;
      00855B AE 00 01         [ 2] 1015 	ldw	x, #_LCD_RAM+0
      00855E 89               [ 2] 1016 	pushw	x
      00855F 7B 1C            [ 1] 1017 	ld	a, (0x1c, sp)
      008561 97               [ 1] 1018 	ld	xl, a
      008562 A6 06            [ 1] 1019 	ld	a, #0x06
      008564 42               [ 4] 1020 	mul	x, a
      008565 1F 1A            [ 2] 1021 	ldw	(0x1a, sp), x
      008567 85               [ 2] 1022 	popw	x
      008568 72 FB 18         [ 2] 1023 	addw	x, (0x18, sp)
      00856B 9F               [ 1] 1024 	ld	a, xl
      00856C 1B 01            [ 1] 1025 	add	a, (0x01, sp)
      00856E 6B 17            [ 1] 1026 	ld	(0x17, sp), a
      008570 9E               [ 1] 1027 	ld	a, xh
      008571 A9 00            [ 1] 1028 	adc	a, #0x00
      008573 6B 16            [ 1] 1029 	ld	(0x16, sp), a
      008575 AE 00 01         [ 2] 1030 	ldw	x, #_LCD_RAM+0
      008578 72 FB 18         [ 2] 1031 	addw	x, (0x18, sp)
      00857B 9F               [ 1] 1032 	ld	a, xl
      00857C 1B 01            [ 1] 1033 	add	a, (0x01, sp)
      00857E 97               [ 1] 1034 	ld	xl, a
      00857F 9E               [ 1] 1035 	ld	a, xh
      008580 A9 00            [ 1] 1036 	adc	a, #0x00
      008582 95               [ 1] 1037 	ld	xh, a
      008583 F6               [ 1] 1038 	ld	a, (x)
      008584 A4 F0            [ 1] 1039 	and	a, #0xf0
      008586 1E 16            [ 2] 1040 	ldw	x, (0x16, sp)
      008588 F7               [ 1] 1041 	ld	(x), a
                                   1042 ;	snake_game.c: 320: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][0] & 0x0F;
      008589 AE 00 01         [ 2] 1043 	ldw	x, #_LCD_RAM+0
      00858C 72 FB 18         [ 2] 1044 	addw	x, (0x18, sp)
      00858F 9F               [ 1] 1045 	ld	a, xl
      008590 1B 01            [ 1] 1046 	add	a, (0x01, sp)
      008592 6B 15            [ 1] 1047 	ld	(0x15, sp), a
      008594 9E               [ 1] 1048 	ld	a, xh
      008595 A9 00            [ 1] 1049 	adc	a, #0x00
      008597 6B 14            [ 1] 1050 	ld	(0x14, sp), a
      008599 AE 00 01         [ 2] 1051 	ldw	x, #_LCD_RAM+0
      00859C 72 FB 18         [ 2] 1052 	addw	x, (0x18, sp)
      00859F 9F               [ 1] 1053 	ld	a, xl
      0085A0 1B 01            [ 1] 1054 	add	a, (0x01, sp)
      0085A2 97               [ 1] 1055 	ld	xl, a
      0085A3 9E               [ 1] 1056 	ld	a, xh
      0085A4 A9 00            [ 1] 1057 	adc	a, #0x00
      0085A6 95               [ 1] 1058 	ld	xh, a
      0085A7 90 F6            [ 1] 1059 	ld	a, (y)
      0085A9 A4 0F            [ 1] 1060 	and	a, #0x0f
      0085AB 6B 13            [ 1] 1061 	ld	(0x13, sp), a
      0085AD F6               [ 1] 1062 	ld	a, (x)
      0085AE 1A 13            [ 1] 1063 	or	a, (0x13, sp)
      0085B0 1E 14            [ 2] 1064 	ldw	x, (0x14, sp)
      0085B2 F7               [ 1] 1065 	ld	(x), a
                                   1066 ;	snake_game.c: 321: tmp_x++;
      0085B3 7B 1A            [ 1] 1067 	ld	a, (0x1a, sp)
      0085B5 4C               [ 1] 1068 	inc	a
      0085B6 6B 12            [ 1] 1069 	ld	(0x12, sp), a
      0085B8 7B 12            [ 1] 1070 	ld	a, (0x12, sp)
      0085BA 6B 11            [ 1] 1071 	ld	(0x11, sp), a
                                   1072 ;	snake_game.c: 322: LCD_RAM[tmp_x][tmp_y] &= ~0x0F;
      0085BC AE 00 01         [ 2] 1073 	ldw	x, #_LCD_RAM+0
      0085BF 89               [ 2] 1074 	pushw	x
      0085C0 7B 13            [ 1] 1075 	ld	a, (0x13, sp)
      0085C2 97               [ 1] 1076 	ld	xl, a
      0085C3 A6 06            [ 1] 1077 	ld	a, #0x06
      0085C5 42               [ 4] 1078 	mul	x, a
      0085C6 1F 11            [ 2] 1079 	ldw	(0x11, sp), x
      0085C8 85               [ 2] 1080 	popw	x
      0085C9 72 FB 0F         [ 2] 1081 	addw	x, (0x0f, sp)
      0085CC 9F               [ 1] 1082 	ld	a, xl
      0085CD 1B 01            [ 1] 1083 	add	a, (0x01, sp)
      0085CF 6B 0E            [ 1] 1084 	ld	(0x0e, sp), a
      0085D1 9E               [ 1] 1085 	ld	a, xh
      0085D2 A9 00            [ 1] 1086 	adc	a, #0x00
      0085D4 6B 0D            [ 1] 1087 	ld	(0x0d, sp), a
      0085D6 AE 00 01         [ 2] 1088 	ldw	x, #_LCD_RAM+0
      0085D9 72 FB 0F         [ 2] 1089 	addw	x, (0x0f, sp)
      0085DC 9F               [ 1] 1090 	ld	a, xl
      0085DD 1B 01            [ 1] 1091 	add	a, (0x01, sp)
      0085DF 97               [ 1] 1092 	ld	xl, a
      0085E0 9E               [ 1] 1093 	ld	a, xh
      0085E1 A9 00            [ 1] 1094 	adc	a, #0x00
      0085E3 95               [ 1] 1095 	ld	xh, a
      0085E4 F6               [ 1] 1096 	ld	a, (x)
      0085E5 A4 F0            [ 1] 1097 	and	a, #0xf0
      0085E7 1E 0D            [ 2] 1098 	ldw	x, (0x0d, sp)
      0085E9 F7               [ 1] 1099 	ld	(x), a
                                   1100 ;	snake_game.c: 323: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][1] >> 4;
      0085EA AE 00 01         [ 2] 1101 	ldw	x, #_LCD_RAM+0
      0085ED 72 FB 0F         [ 2] 1102 	addw	x, (0x0f, sp)
      0085F0 9F               [ 1] 1103 	ld	a, xl
      0085F1 1B 01            [ 1] 1104 	add	a, (0x01, sp)
      0085F3 6B 0C            [ 1] 1105 	ld	(0x0c, sp), a
      0085F5 9E               [ 1] 1106 	ld	a, xh
      0085F6 A9 00            [ 1] 1107 	adc	a, #0x00
      0085F8 6B 0B            [ 1] 1108 	ld	(0x0b, sp), a
      0085FA AE 00 01         [ 2] 1109 	ldw	x, #_LCD_RAM+0
      0085FD 72 FB 0F         [ 2] 1110 	addw	x, (0x0f, sp)
      008600 9F               [ 1] 1111 	ld	a, xl
      008601 1B 01            [ 1] 1112 	add	a, (0x01, sp)
      008603 97               [ 1] 1113 	ld	xl, a
      008604 9E               [ 1] 1114 	ld	a, xh
      008605 A9 00            [ 1] 1115 	adc	a, #0x00
      008607 95               [ 1] 1116 	ld	xh, a
      008608 90 5C            [ 2] 1117 	incw	y
      00860A 90 F6            [ 1] 1118 	ld	a, (y)
      00860C 4E               [ 1] 1119 	swap	a
      00860D A4 0F            [ 1] 1120 	and	a, #0x0f
      00860F 6B 0A            [ 1] 1121 	ld	(0x0a, sp), a
      008611 F6               [ 1] 1122 	ld	a, (x)
      008612 1A 0A            [ 1] 1123 	or	a, (0x0a, sp)
      008614 1E 0B            [ 2] 1124 	ldw	x, (0x0b, sp)
      008616 F7               [ 1] 1125 	ld	(x), a
                                   1126 ;	snake_game.c: 324: tmp_x++;    
      008617 7B 11            [ 1] 1127 	ld	a, (0x11, sp)
      008619 4C               [ 1] 1128 	inc	a
                                   1129 ;	snake_game.c: 325: LCD_RAM[tmp_x][tmp_y] &= ~0x0F;
      00861A AE 00 01         [ 2] 1130 	ldw	x, #_LCD_RAM+0
      00861D 89               [ 2] 1131 	pushw	x
      00861E 41               [ 1] 1132 	exg	a, xl
      00861F A6 06            [ 1] 1133 	ld	a, #0x06
      008621 41               [ 1] 1134 	exg	a, xl
      008622 42               [ 4] 1135 	mul	x, a
      008623 1F 0A            [ 2] 1136 	ldw	(0x0a, sp), x
      008625 85               [ 2] 1137 	popw	x
      008626 72 FB 08         [ 2] 1138 	addw	x, (0x08, sp)
      008629 9F               [ 1] 1139 	ld	a, xl
      00862A 1B 01            [ 1] 1140 	add	a, (0x01, sp)
      00862C 6B 07            [ 1] 1141 	ld	(0x07, sp), a
      00862E 9E               [ 1] 1142 	ld	a, xh
      00862F A9 00            [ 1] 1143 	adc	a, #0x00
      008631 6B 06            [ 1] 1144 	ld	(0x06, sp), a
      008633 AE 00 01         [ 2] 1145 	ldw	x, #_LCD_RAM+0
      008636 72 FB 08         [ 2] 1146 	addw	x, (0x08, sp)
      008639 9F               [ 1] 1147 	ld	a, xl
      00863A 1B 01            [ 1] 1148 	add	a, (0x01, sp)
      00863C 97               [ 1] 1149 	ld	xl, a
      00863D 9E               [ 1] 1150 	ld	a, xh
      00863E A9 00            [ 1] 1151 	adc	a, #0x00
      008640 95               [ 1] 1152 	ld	xh, a
      008641 F6               [ 1] 1153 	ld	a, (x)
      008642 A4 F0            [ 1] 1154 	and	a, #0xf0
      008644 1E 06            [ 2] 1155 	ldw	x, (0x06, sp)
      008646 F7               [ 1] 1156 	ld	(x), a
                                   1157 ;	snake_game.c: 326: LCD_RAM[tmp_x][tmp_y] |= snake_tiles[tileID][1] & 0x0F;
      008647 AE 00 01         [ 2] 1158 	ldw	x, #_LCD_RAM+0
      00864A 72 FB 08         [ 2] 1159 	addw	x, (0x08, sp)
      00864D 9F               [ 1] 1160 	ld	a, xl
      00864E 1B 01            [ 1] 1161 	add	a, (0x01, sp)
      008650 6B 05            [ 1] 1162 	ld	(0x05, sp), a
      008652 9E               [ 1] 1163 	ld	a, xh
      008653 A9 00            [ 1] 1164 	adc	a, #0x00
      008655 6B 04            [ 1] 1165 	ld	(0x04, sp), a
      008657 AE 00 01         [ 2] 1166 	ldw	x, #_LCD_RAM+0
      00865A 72 FB 08         [ 2] 1167 	addw	x, (0x08, sp)
      00865D 9F               [ 1] 1168 	ld	a, xl
      00865E 1B 01            [ 1] 1169 	add	a, (0x01, sp)
      008660 97               [ 1] 1170 	ld	xl, a
      008661 9E               [ 1] 1171 	ld	a, xh
      008662 A9 00            [ 1] 1172 	adc	a, #0x00
      008664 95               [ 1] 1173 	ld	xh, a
      008665 90 F6            [ 1] 1174 	ld	a, (y)
      008667 A4 0F            [ 1] 1175 	and	a, #0x0f
      008669 6B 03            [ 1] 1176 	ld	(0x03, sp), a
      00866B F6               [ 1] 1177 	ld	a, (x)
      00866C 1A 03            [ 1] 1178 	or	a, (0x03, sp)
      00866E 1E 04            [ 2] 1179 	ldw	x, (0x04, sp)
      008670 F7               [ 1] 1180 	ld	(x), a
      008671                       1181 00103$:
                                   1182 ;	snake_game.c: 329: refreshSnakeTile(x,y);
      008671 7B 2C            [ 1] 1183 	ld	a, (0x2c, sp)
      008673 88               [ 1] 1184 	push	a
      008674 7B 46            [ 1] 1185 	ld	a, (0x46, sp)
      008676 88               [ 1] 1186 	push	a
      008677 CD 82 2E         [ 4] 1187 	call	_refreshSnakeTile
      00867A 5B 02            [ 2] 1188 	addw	sp, #2
      00867C 5B 42            [ 2] 1189 	addw	sp, #66
      00867E 81               [ 4] 1190 	ret
                                   1191 ;	snake_game.c: 342: void iterateSnakeHead()
                                   1192 ;	-----------------------------------------
                                   1193 ;	 function iterateSnakeHead
                                   1194 ;	-----------------------------------------
      00867F                       1195 _iterateSnakeHead:
      00867F 88               [ 1] 1196 	push	a
                                   1197 ;	snake_game.c: 345: switch(snake.head.direction){
      008680 AE 02 D6         [ 2] 1198 	ldw	x, #_snake+5
      008683 F6               [ 1] 1199 	ld	a, (x)
      008684 6B 01            [ 1] 1200 	ld	(0x01, sp), a
      008686 7B 01            [ 1] 1201 	ld	a, (0x01, sp)
      008688 A1 05            [ 1] 1202 	cp	a, #0x05
      00868A 23 03            [ 2] 1203 	jrule	00146$
      00868C CC 87 F1         [ 2] 1204 	jp	00124$
      00868F                       1205 00146$:
      00868F 5F               [ 1] 1206 	clrw	x
      008690 7B 01            [ 1] 1207 	ld	a, (0x01, sp)
      008692 97               [ 1] 1208 	ld	xl, a
      008693 58               [ 2] 1209 	sllw	x
      008694 DE 86 98         [ 2] 1210 	ldw	x, (#00147$, x)
      008697 FC               [ 2] 1211 	jp	(x)
      008698                       1212 00147$:
      008698 86 A4                 1213 	.dw	#00101$
      00869A 86 FD                 1214 	.dw	#00102$
      00869C 87 3C                 1215 	.dw	#00105$
      00869E 87 79                 1216 	.dw	#00108$
      0086A0 87 B7                 1217 	.dw	#00111$
      0086A2 87 F1                 1218 	.dw	#00114$
                                   1219 ;	snake_game.c: 346: case INITIAL:
      0086A4                       1220 00101$:
                                   1221 ;	snake_game.c: 347: setSnakeTile(12, 6, S_TD);
      0086A4 4B 0D            [ 1] 1222 	push	#0x0d
      0086A6 4B 06            [ 1] 1223 	push	#0x06
      0086A8 4B 0C            [ 1] 1224 	push	#0x0c
      0086AA CD 83 41         [ 4] 1225 	call	_setSnakeTile
      0086AD 5B 03            [ 2] 1226 	addw	sp, #3
                                   1227 ;	snake_game.c: 348: setSnakeTile(12, 7, S_V);
      0086AF 4B 01            [ 1] 1228 	push	#0x01
      0086B1 4B 07            [ 1] 1229 	push	#0x07
      0086B3 4B 0C            [ 1] 1230 	push	#0x0c
      0086B5 CD 83 41         [ 4] 1231 	call	_setSnakeTile
      0086B8 5B 03            [ 2] 1232 	addw	sp, #3
                                   1233 ;	snake_game.c: 349: setSnakeTile(12, 8, S_V);
      0086BA 4B 01            [ 1] 1234 	push	#0x01
      0086BC 4B 08            [ 1] 1235 	push	#0x08
      0086BE 4B 0C            [ 1] 1236 	push	#0x0c
      0086C0 CD 83 41         [ 4] 1237 	call	_setSnakeTile
      0086C3 5B 03            [ 2] 1238 	addw	sp, #3
                                   1239 ;	snake_game.c: 350: setSnakeTile(12, 9, S_HD);
      0086C5 4B 09            [ 1] 1240 	push	#0x09
      0086C7 4B 09            [ 1] 1241 	push	#0x09
      0086C9 4B 0C            [ 1] 1242 	push	#0x0c
      0086CB CD 83 41         [ 4] 1243 	call	_setSnakeTile
      0086CE 5B 03            [ 2] 1244 	addw	sp, #3
                                   1245 ;	snake_game.c: 352: snake.tail.x = 12;
      0086D0 AE 02 D1         [ 2] 1246 	ldw	x, #_snake+0
      0086D3 A6 0C            [ 1] 1247 	ld	a, #0x0c
      0086D5 F7               [ 1] 1248 	ld	(x), a
                                   1249 ;	snake_game.c: 353: snake.tail.y = 6;
      0086D6 AE 02 D2         [ 2] 1250 	ldw	x, #_snake+1
      0086D9 A6 06            [ 1] 1251 	ld	a, #0x06
      0086DB F7               [ 1] 1252 	ld	(x), a
                                   1253 ;	snake_game.c: 355: snake.head.x = 12;
      0086DC AE 02 D4         [ 2] 1254 	ldw	x, #_snake+3
      0086DF A6 0C            [ 1] 1255 	ld	a, #0x0c
      0086E1 F7               [ 1] 1256 	ld	(x), a
                                   1257 ;	snake_game.c: 356: snake.head.y = 9;
      0086E2 AE 02 D5         [ 2] 1258 	ldw	x, #_snake+4
      0086E5 A6 09            [ 1] 1259 	ld	a, #0x09
      0086E7 F7               [ 1] 1260 	ld	(x), a
                                   1261 ;	snake_game.c: 358: snake.length = 4;
      0086E8 AE 02 D7         [ 2] 1262 	ldw	x, #_snake+6
      0086EB A6 04            [ 1] 1263 	ld	a, #0x04
      0086ED F7               [ 1] 1264 	ld	(x), a
                                   1265 ;	snake_game.c: 359: snake.head.direction = DOWN;
      0086EE AE 02 D6         [ 2] 1266 	ldw	x, #_snake+5
      0086F1 A6 04            [ 1] 1267 	ld	a, #0x04
      0086F3 F7               [ 1] 1268 	ld	(x), a
                                   1269 ;	snake_game.c: 360: snake.tail.direction = DOWN;
      0086F4 AE 02 D3         [ 2] 1270 	ldw	x, #_snake+2
      0086F7 A6 04            [ 1] 1271 	ld	a, #0x04
      0086F9 F7               [ 1] 1272 	ld	(x), a
                                   1273 ;	snake_game.c: 361: return; /* Quit function, everything is set up*/
      0086FA CC 87 F1         [ 2] 1274 	jp	00124$
                                   1275 ;	snake_game.c: 363: case LEFT:
      0086FD                       1276 00102$:
                                   1277 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      0086FD AE 02 D5         [ 2] 1278 	ldw	x, #_snake+4
      008700 F6               [ 1] 1279 	ld	a, (x)
      008701 AE 02 D4         [ 2] 1280 	ldw	x, #_snake+3
      008704 88               [ 1] 1281 	push	a
      008705 F6               [ 1] 1282 	ld	a, (x)
      008706 97               [ 1] 1283 	ld	xl, a
      008707 84               [ 1] 1284 	pop	a
      008708 4B 00            [ 1] 1285 	push	#0x00
      00870A 88               [ 1] 1286 	push	a
      00870B 9F               [ 1] 1287 	ld	a, xl
      00870C 88               [ 1] 1288 	push	a
      00870D CD 83 41         [ 4] 1289 	call	_setSnakeTile
      008710 5B 03            [ 2] 1290 	addw	sp, #3
                                   1291 ;	snake_game.c: 365: snake.head.x--;
      008712 AE 02 D4         [ 2] 1292 	ldw	x, #_snake+3
      008715 7A               [ 1] 1293 	dec	(x)
                                   1294 ;	snake_game.c: 366: if(snake.head.x > 20)
      008716 AE 02 D4         [ 2] 1295 	ldw	x, #_snake+3
      008719 F6               [ 1] 1296 	ld	a, (x)
      00871A A1 14            [ 1] 1297 	cp	a, #0x14
      00871C 23 06            [ 2] 1298 	jrule	00104$
                                   1299 ;	snake_game.c: 367: snake.head.x = 20;
      00871E AE 02 D4         [ 2] 1300 	ldw	x, #_snake+3
      008721 A6 14            [ 1] 1301 	ld	a, #0x14
      008723 F7               [ 1] 1302 	ld	(x), a
      008724                       1303 00104$:
                                   1304 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008724 AE 02 D5         [ 2] 1305 	ldw	x, #_snake+4
      008727 F6               [ 1] 1306 	ld	a, (x)
      008728 AE 02 D4         [ 2] 1307 	ldw	x, #_snake+3
      00872B 88               [ 1] 1308 	push	a
      00872C F6               [ 1] 1309 	ld	a, (x)
      00872D 97               [ 1] 1310 	ld	xl, a
      00872E 84               [ 1] 1311 	pop	a
      00872F 4B 07            [ 1] 1312 	push	#0x07
      008731 88               [ 1] 1313 	push	a
      008732 9F               [ 1] 1314 	ld	a, xl
      008733 88               [ 1] 1315 	push	a
      008734 CD 83 41         [ 4] 1316 	call	_setSnakeTile
      008737 5B 03            [ 2] 1317 	addw	sp, #3
                                   1318 ;	snake_game.c: 369: break;
      008739 CC 87 F1         [ 2] 1319 	jp	00124$
                                   1320 ;	snake_game.c: 371: case RIGHT: 
      00873C                       1321 00105$:
                                   1322 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      00873C AE 02 D5         [ 2] 1323 	ldw	x, #_snake+4
      00873F F6               [ 1] 1324 	ld	a, (x)
      008740 AE 02 D4         [ 2] 1325 	ldw	x, #_snake+3
      008743 88               [ 1] 1326 	push	a
      008744 F6               [ 1] 1327 	ld	a, (x)
      008745 97               [ 1] 1328 	ld	xl, a
      008746 84               [ 1] 1329 	pop	a
      008747 4B 00            [ 1] 1330 	push	#0x00
      008749 88               [ 1] 1331 	push	a
      00874A 9F               [ 1] 1332 	ld	a, xl
      00874B 88               [ 1] 1333 	push	a
      00874C CD 83 41         [ 4] 1334 	call	_setSnakeTile
      00874F 5B 03            [ 2] 1335 	addw	sp, #3
                                   1336 ;	snake_game.c: 373: snake.head.x++;
      008751 AE 02 D4         [ 2] 1337 	ldw	x, #_snake+3
      008754 7C               [ 1] 1338 	inc	(x)
                                   1339 ;	snake_game.c: 374: if(snake.head.x > 20)
      008755 AE 02 D4         [ 2] 1340 	ldw	x, #_snake+3
      008758 F6               [ 1] 1341 	ld	a, (x)
      008759 A1 14            [ 1] 1342 	cp	a, #0x14
      00875B 23 04            [ 2] 1343 	jrule	00107$
                                   1344 ;	snake_game.c: 375: snake.head.x = 0;
      00875D AE 02 D4         [ 2] 1345 	ldw	x, #_snake+3
      008760 7F               [ 1] 1346 	clr	(x)
      008761                       1347 00107$:
                                   1348 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008761 AE 02 D5         [ 2] 1349 	ldw	x, #_snake+4
      008764 F6               [ 1] 1350 	ld	a, (x)
      008765 AE 02 D4         [ 2] 1351 	ldw	x, #_snake+3
      008768 88               [ 1] 1352 	push	a
      008769 F6               [ 1] 1353 	ld	a, (x)
      00876A 97               [ 1] 1354 	ld	xl, a
      00876B 84               [ 1] 1355 	pop	a
      00876C 4B 06            [ 1] 1356 	push	#0x06
      00876E 88               [ 1] 1357 	push	a
      00876F 9F               [ 1] 1358 	ld	a, xl
      008770 88               [ 1] 1359 	push	a
      008771 CD 83 41         [ 4] 1360 	call	_setSnakeTile
      008774 5B 03            [ 2] 1361 	addw	sp, #3
                                   1362 ;	snake_game.c: 377: break;
      008776 CC 87 F1         [ 2] 1363 	jp	00124$
                                   1364 ;	snake_game.c: 379: case UP:
      008779                       1365 00108$:
                                   1366 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008779 AE 02 D5         [ 2] 1367 	ldw	x, #_snake+4
      00877C F6               [ 1] 1368 	ld	a, (x)
      00877D AE 02 D4         [ 2] 1369 	ldw	x, #_snake+3
      008780 88               [ 1] 1370 	push	a
      008781 F6               [ 1] 1371 	ld	a, (x)
      008782 97               [ 1] 1372 	ld	xl, a
      008783 84               [ 1] 1373 	pop	a
      008784 4B 01            [ 1] 1374 	push	#0x01
      008786 88               [ 1] 1375 	push	a
      008787 9F               [ 1] 1376 	ld	a, xl
      008788 88               [ 1] 1377 	push	a
      008789 CD 83 41         [ 4] 1378 	call	_setSnakeTile
      00878C 5B 03            [ 2] 1379 	addw	sp, #3
                                   1380 ;	snake_game.c: 381: snake.head.y--;
      00878E AE 02 D5         [ 2] 1381 	ldw	x, #_snake+4
      008791 7A               [ 1] 1382 	dec	(x)
                                   1383 ;	snake_game.c: 382: if(snake.head.y > 9)
      008792 AE 02 D5         [ 2] 1384 	ldw	x, #_snake+4
      008795 F6               [ 1] 1385 	ld	a, (x)
      008796 A1 09            [ 1] 1386 	cp	a, #0x09
      008798 23 06            [ 2] 1387 	jrule	00110$
                                   1388 ;	snake_game.c: 383: snake.head.y = 9;
      00879A AE 02 D5         [ 2] 1389 	ldw	x, #_snake+4
      00879D A6 09            [ 1] 1390 	ld	a, #0x09
      00879F F7               [ 1] 1391 	ld	(x), a
      0087A0                       1392 00110$:
                                   1393 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      0087A0 AE 02 D5         [ 2] 1394 	ldw	x, #_snake+4
      0087A3 F6               [ 1] 1395 	ld	a, (x)
      0087A4 AE 02 D4         [ 2] 1396 	ldw	x, #_snake+3
      0087A7 88               [ 1] 1397 	push	a
      0087A8 F6               [ 1] 1398 	ld	a, (x)
      0087A9 97               [ 1] 1399 	ld	xl, a
      0087AA 84               [ 1] 1400 	pop	a
      0087AB 4B 08            [ 1] 1401 	push	#0x08
      0087AD 88               [ 1] 1402 	push	a
      0087AE 9F               [ 1] 1403 	ld	a, xl
      0087AF 88               [ 1] 1404 	push	a
      0087B0 CD 83 41         [ 4] 1405 	call	_setSnakeTile
      0087B3 5B 03            [ 2] 1406 	addw	sp, #3
                                   1407 ;	snake_game.c: 385: break;
      0087B5 20 3A            [ 2] 1408 	jra	00124$
                                   1409 ;	snake_game.c: 387: case DOWN: 
      0087B7                       1410 00111$:
                                   1411 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      0087B7 AE 02 D5         [ 2] 1412 	ldw	x, #_snake+4
      0087BA F6               [ 1] 1413 	ld	a, (x)
      0087BB AE 02 D4         [ 2] 1414 	ldw	x, #_snake+3
      0087BE 88               [ 1] 1415 	push	a
      0087BF F6               [ 1] 1416 	ld	a, (x)
      0087C0 97               [ 1] 1417 	ld	xl, a
      0087C1 84               [ 1] 1418 	pop	a
      0087C2 4B 01            [ 1] 1419 	push	#0x01
      0087C4 88               [ 1] 1420 	push	a
      0087C5 9F               [ 1] 1421 	ld	a, xl
      0087C6 88               [ 1] 1422 	push	a
      0087C7 CD 83 41         [ 4] 1423 	call	_setSnakeTile
      0087CA 5B 03            [ 2] 1424 	addw	sp, #3
                                   1425 ;	snake_game.c: 389: snake.head.y++;
      0087CC AE 02 D5         [ 2] 1426 	ldw	x, #_snake+4
      0087CF 7C               [ 1] 1427 	inc	(x)
                                   1428 ;	snake_game.c: 390: if(snake.head.y > 9)
      0087D0 AE 02 D5         [ 2] 1429 	ldw	x, #_snake+4
      0087D3 F6               [ 1] 1430 	ld	a, (x)
      0087D4 A1 09            [ 1] 1431 	cp	a, #0x09
      0087D6 23 04            [ 2] 1432 	jrule	00113$
                                   1433 ;	snake_game.c: 391: snake.head.y = 0;
      0087D8 AE 02 D5         [ 2] 1434 	ldw	x, #_snake+4
      0087DB 7F               [ 1] 1435 	clr	(x)
      0087DC                       1436 00113$:
                                   1437 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      0087DC AE 02 D5         [ 2] 1438 	ldw	x, #_snake+4
      0087DF F6               [ 1] 1439 	ld	a, (x)
      0087E0 AE 02 D4         [ 2] 1440 	ldw	x, #_snake+3
      0087E3 88               [ 1] 1441 	push	a
      0087E4 F6               [ 1] 1442 	ld	a, (x)
      0087E5 97               [ 1] 1443 	ld	xl, a
      0087E6 84               [ 1] 1444 	pop	a
      0087E7 4B 09            [ 1] 1445 	push	#0x09
      0087E9 88               [ 1] 1446 	push	a
      0087EA 9F               [ 1] 1447 	ld	a, xl
      0087EB 88               [ 1] 1448 	push	a
      0087EC CD 83 41         [ 4] 1449 	call	_setSnakeTile
      0087EF 5B 03            [ 2] 1450 	addw	sp, #3
                                   1451 ;	snake_game.c: 393: break;
                                   1452 ;	snake_game.c: 395: case DEAD:
                                   1453 ;	snake_game.c: 397: }
      0087F1                       1454 00114$:
      0087F1                       1455 00124$:
      0087F1 84               [ 1] 1456 	pop	a
      0087F2 81               [ 4] 1457 	ret
                                   1458 ;	snake_game.c: 400: void iterateSnakeTail()
                                   1459 ;	-----------------------------------------
                                   1460 ;	 function iterateSnakeTail
                                   1461 ;	-----------------------------------------
      0087F3                       1462 _iterateSnakeTail:
      0087F3 52 12            [ 2] 1463 	sub	sp, #18
                                   1464 ;	snake_game.c: 339: setSnakeTile(snake.tail.x, snake.tail.y, tileID);
      0087F5 AE 02 D2         [ 2] 1465 	ldw	x, #_snake+1
      0087F8 F6               [ 1] 1466 	ld	a, (x)
      0087F9 AE 02 D1         [ 2] 1467 	ldw	x, #_snake+0
      0087FC 88               [ 1] 1468 	push	a
      0087FD F6               [ 1] 1469 	ld	a, (x)
      0087FE 97               [ 1] 1470 	ld	xl, a
      0087FF 84               [ 1] 1471 	pop	a
      008800 4B 11            [ 1] 1472 	push	#0x11
      008802 88               [ 1] 1473 	push	a
      008803 9F               [ 1] 1474 	ld	a, xl
      008804 88               [ 1] 1475 	push	a
      008805 CD 83 41         [ 4] 1476 	call	_setSnakeTile
      008808 5B 03            [ 2] 1477 	addw	sp, #3
                                   1478 ;	snake_game.c: 404: switch(snake.tail.direction){
      00880A AE 02 D3         [ 2] 1479 	ldw	x, #_snake+2
      00880D F6               [ 1] 1480 	ld	a, (x)
      00880E 6B 12            [ 1] 1481 	ld	(0x12, sp), a
      008810 7B 12            [ 1] 1482 	ld	a, (0x12, sp)
      008812 A1 01            [ 1] 1483 	cp	a, #0x01
      008814 26 03            [ 1] 1484 	jrne	00223$
      008816 CC 88 83         [ 2] 1485 	jp	00108$
      008819                       1486 00223$:
      008819 7B 12            [ 1] 1487 	ld	a, (0x12, sp)
      00881B A1 02            [ 1] 1488 	cp	a, #0x02
      00881D 27 15            [ 1] 1489 	jreq	00101$
      00881F 7B 12            [ 1] 1490 	ld	a, (0x12, sp)
      008821 A1 03            [ 1] 1491 	cp	a, #0x03
      008823 26 03            [ 1] 1492 	jrne	00229$
      008825 CC 88 D4         [ 2] 1493 	jp	00115$
      008828                       1494 00229$:
      008828 7B 12            [ 1] 1495 	ld	a, (0x12, sp)
      00882A A1 04            [ 1] 1496 	cp	a, #0x04
      00882C 26 03            [ 1] 1497 	jrne	00232$
      00882E CC 89 24         [ 2] 1498 	jp	00122$
      008831                       1499 00232$:
      008831 CC 89 70         [ 2] 1500 	jp	00129$
                                   1501 ;	snake_game.c: 405: case RIGHT:
      008834                       1502 00101$:
                                   1503 ;	snake_game.c: 406: snake.tail.x++;
      008834 AE 02 D1         [ 2] 1504 	ldw	x, #_snake+0
      008837 7C               [ 1] 1505 	inc	(x)
                                   1506 ;	snake_game.c: 407: if(snake.tail.x > 20)
      008838 AE 02 D1         [ 2] 1507 	ldw	x, #_snake+0
      00883B F6               [ 1] 1508 	ld	a, (x)
      00883C A1 14            [ 1] 1509 	cp	a, #0x14
      00883E 23 04            [ 2] 1510 	jrule	00103$
                                   1511 ;	snake_game.c: 408: snake.tail.x = 0;
      008840 AE 02 D1         [ 2] 1512 	ldw	x, #_snake+0
      008843 7F               [ 1] 1513 	clr	(x)
      008844                       1514 00103$:
                                   1515 ;	snake_game.c: 410: switch(Snake_array[snake.tail.x][snake.tail.y]){
      008844 AE 01 FC         [ 2] 1516 	ldw	x, #_Snake_array+0
      008847 1F 10            [ 2] 1517 	ldw	(0x10, sp), x
      008849 AE 02 D1         [ 2] 1518 	ldw	x, #_snake+0
      00884C F6               [ 1] 1519 	ld	a, (x)
      00884D 97               [ 1] 1520 	ld	xl, a
      00884E A6 0A            [ 1] 1521 	ld	a, #0x0a
      008850 42               [ 4] 1522 	mul	x, a
      008851 72 FB 10         [ 2] 1523 	addw	x, (0x10, sp)
      008854 1F 01            [ 2] 1524 	ldw	(0x01, sp), x
      008856 AE 02 D2         [ 2] 1525 	ldw	x, #_snake+1
      008859 F6               [ 1] 1526 	ld	a, (x)
      00885A 5F               [ 1] 1527 	clrw	x
      00885B 97               [ 1] 1528 	ld	xl, a
      00885C 72 FB 01         [ 2] 1529 	addw	x, (0x01, sp)
      00885F F6               [ 1] 1530 	ld	a, (x)
      008860 A1 02            [ 1] 1531 	cp	a, #0x02
      008862 27 0D            [ 1] 1532 	jreq	00105$
      008864 A1 03            [ 1] 1533 	cp	a, #0x03
      008866 26 12            [ 1] 1534 	jrne	00106$
                                   1535 ;	snake_game.c: 411: case(S_LU): snake.tail.direction = UP;    break;
      008868 AE 02 D3         [ 2] 1536 	ldw	x, #_snake+2
      00886B A6 03            [ 1] 1537 	ld	a, #0x03
      00886D F7               [ 1] 1538 	ld	(x), a
      00886E CC 89 70         [ 2] 1539 	jp	00129$
                                   1540 ;	snake_game.c: 412: case(S_LD): snake.tail.direction = DOWN;  break;
      008871                       1541 00105$:
      008871 AE 02 D3         [ 2] 1542 	ldw	x, #_snake+2
      008874 A6 04            [ 1] 1543 	ld	a, #0x04
      008876 F7               [ 1] 1544 	ld	(x), a
      008877 CC 89 70         [ 2] 1545 	jp	00129$
                                   1546 ;	snake_game.c: 413: default:    snake.tail.direction = RIGHT; break;
      00887A                       1547 00106$:
      00887A AE 02 D3         [ 2] 1548 	ldw	x, #_snake+2
      00887D A6 02            [ 1] 1549 	ld	a, #0x02
      00887F F7               [ 1] 1550 	ld	(x), a
                                   1551 ;	snake_game.c: 415: break;
      008880 CC 89 70         [ 2] 1552 	jp	00129$
                                   1553 ;	snake_game.c: 417: case LEFT:
      008883                       1554 00108$:
                                   1555 ;	snake_game.c: 418: snake.tail.x--;
      008883 AE 02 D1         [ 2] 1556 	ldw	x, #_snake+0
      008886 7A               [ 1] 1557 	dec	(x)
                                   1558 ;	snake_game.c: 419: if(snake.tail.x > 20)
      008887 AE 02 D1         [ 2] 1559 	ldw	x, #_snake+0
      00888A F6               [ 1] 1560 	ld	a, (x)
      00888B A1 14            [ 1] 1561 	cp	a, #0x14
      00888D 23 06            [ 2] 1562 	jrule	00110$
                                   1563 ;	snake_game.c: 420: snake.tail.x = 20;
      00888F AE 02 D1         [ 2] 1564 	ldw	x, #_snake+0
      008892 A6 14            [ 1] 1565 	ld	a, #0x14
      008894 F7               [ 1] 1566 	ld	(x), a
      008895                       1567 00110$:
                                   1568 ;	snake_game.c: 422: switch(Snake_array[snake.tail.x][snake.tail.y]){
      008895 AE 01 FC         [ 2] 1569 	ldw	x, #_Snake_array+0
      008898 1F 09            [ 2] 1570 	ldw	(0x09, sp), x
      00889A AE 02 D1         [ 2] 1571 	ldw	x, #_snake+0
      00889D F6               [ 1] 1572 	ld	a, (x)
      00889E 97               [ 1] 1573 	ld	xl, a
      00889F A6 0A            [ 1] 1574 	ld	a, #0x0a
      0088A1 42               [ 4] 1575 	mul	x, a
      0088A2 72 FB 09         [ 2] 1576 	addw	x, (0x09, sp)
      0088A5 1F 0D            [ 2] 1577 	ldw	(0x0d, sp), x
      0088A7 AE 02 D2         [ 2] 1578 	ldw	x, #_snake+1
      0088AA F6               [ 1] 1579 	ld	a, (x)
      0088AB 5F               [ 1] 1580 	clrw	x
      0088AC 97               [ 1] 1581 	ld	xl, a
      0088AD 72 FB 0D         [ 2] 1582 	addw	x, (0x0d, sp)
      0088B0 F6               [ 1] 1583 	ld	a, (x)
      0088B1 A1 04            [ 1] 1584 	cp	a, #0x04
      0088B3 27 0D            [ 1] 1585 	jreq	00112$
      0088B5 A1 05            [ 1] 1586 	cp	a, #0x05
      0088B7 26 12            [ 1] 1587 	jrne	00113$
                                   1588 ;	snake_game.c: 423: case(S_RU): snake.tail.direction = UP;    break;
      0088B9 AE 02 D3         [ 2] 1589 	ldw	x, #_snake+2
      0088BC A6 03            [ 1] 1590 	ld	a, #0x03
      0088BE F7               [ 1] 1591 	ld	(x), a
      0088BF CC 89 70         [ 2] 1592 	jp	00129$
                                   1593 ;	snake_game.c: 424: case(S_RD): snake.tail.direction = DOWN;  break;
      0088C2                       1594 00112$:
      0088C2 AE 02 D3         [ 2] 1595 	ldw	x, #_snake+2
      0088C5 A6 04            [ 1] 1596 	ld	a, #0x04
      0088C7 F7               [ 1] 1597 	ld	(x), a
      0088C8 CC 89 70         [ 2] 1598 	jp	00129$
                                   1599 ;	snake_game.c: 425: default:    snake.tail.direction = LEFT;  break;
      0088CB                       1600 00113$:
      0088CB AE 02 D3         [ 2] 1601 	ldw	x, #_snake+2
      0088CE A6 01            [ 1] 1602 	ld	a, #0x01
      0088D0 F7               [ 1] 1603 	ld	(x), a
                                   1604 ;	snake_game.c: 427: break;
      0088D1 CC 89 70         [ 2] 1605 	jp	00129$
                                   1606 ;	snake_game.c: 429: case UP:
      0088D4                       1607 00115$:
                                   1608 ;	snake_game.c: 430: snake.tail.y--;
      0088D4 AE 02 D2         [ 2] 1609 	ldw	x, #_snake+1
      0088D7 7A               [ 1] 1610 	dec	(x)
                                   1611 ;	snake_game.c: 431: if(snake.tail.y > 9)
      0088D8 AE 02 D2         [ 2] 1612 	ldw	x, #_snake+1
      0088DB F6               [ 1] 1613 	ld	a, (x)
      0088DC A1 09            [ 1] 1614 	cp	a, #0x09
      0088DE 23 06            [ 2] 1615 	jrule	00117$
                                   1616 ;	snake_game.c: 432: snake.tail.y = 9;
      0088E0 AE 02 D2         [ 2] 1617 	ldw	x, #_snake+1
      0088E3 A6 09            [ 1] 1618 	ld	a, #0x09
      0088E5 F7               [ 1] 1619 	ld	(x), a
      0088E6                       1620 00117$:
                                   1621 ;	snake_game.c: 434: switch(Snake_array[snake.tail.x][snake.tail.y]){
      0088E6 AE 01 FC         [ 2] 1622 	ldw	x, #_Snake_array+0
      0088E9 1F 05            [ 2] 1623 	ldw	(0x05, sp), x
      0088EB AE 02 D1         [ 2] 1624 	ldw	x, #_snake+0
      0088EE F6               [ 1] 1625 	ld	a, (x)
      0088EF 97               [ 1] 1626 	ld	xl, a
      0088F0 A6 0A            [ 1] 1627 	ld	a, #0x0a
      0088F2 42               [ 4] 1628 	mul	x, a
      0088F3 72 FB 05         [ 2] 1629 	addw	x, (0x05, sp)
      0088F6 1F 03            [ 2] 1630 	ldw	(0x03, sp), x
      0088F8 AE 02 D2         [ 2] 1631 	ldw	x, #_snake+1
      0088FB F6               [ 1] 1632 	ld	a, (x)
      0088FC 5F               [ 1] 1633 	clrw	x
      0088FD 97               [ 1] 1634 	ld	xl, a
      0088FE 72 FB 03         [ 2] 1635 	addw	x, (0x03, sp)
      008901 F6               [ 1] 1636 	ld	a, (x)
      008902 A1 02            [ 1] 1637 	cp	a, #0x02
      008904 27 06            [ 1] 1638 	jreq	00118$
      008906 A1 04            [ 1] 1639 	cp	a, #0x04
      008908 27 0A            [ 1] 1640 	jreq	00119$
      00890A 20 10            [ 2] 1641 	jra	00120$
                                   1642 ;	snake_game.c: 435: case(S_LD): snake.tail.direction = LEFT;  break;
      00890C                       1643 00118$:
      00890C AE 02 D3         [ 2] 1644 	ldw	x, #_snake+2
      00890F A6 01            [ 1] 1645 	ld	a, #0x01
      008911 F7               [ 1] 1646 	ld	(x), a
      008912 20 5C            [ 2] 1647 	jra	00129$
                                   1648 ;	snake_game.c: 436: case(S_RD): snake.tail.direction = RIGHT; break;
      008914                       1649 00119$:
      008914 AE 02 D3         [ 2] 1650 	ldw	x, #_snake+2
      008917 A6 02            [ 1] 1651 	ld	a, #0x02
      008919 F7               [ 1] 1652 	ld	(x), a
      00891A 20 54            [ 2] 1653 	jra	00129$
                                   1654 ;	snake_game.c: 437: default:    snake.tail.direction = UP;    break;
      00891C                       1655 00120$:
      00891C AE 02 D3         [ 2] 1656 	ldw	x, #_snake+2
      00891F A6 03            [ 1] 1657 	ld	a, #0x03
      008921 F7               [ 1] 1658 	ld	(x), a
                                   1659 ;	snake_game.c: 439: break;
      008922 20 4C            [ 2] 1660 	jra	00129$
                                   1661 ;	snake_game.c: 441: case DOWN:
      008924                       1662 00122$:
                                   1663 ;	snake_game.c: 442: snake.tail.y++;
      008924 AE 02 D2         [ 2] 1664 	ldw	x, #_snake+1
      008927 7C               [ 1] 1665 	inc	(x)
                                   1666 ;	snake_game.c: 443: if(snake.tail.y > 9)
      008928 AE 02 D2         [ 2] 1667 	ldw	x, #_snake+1
      00892B F6               [ 1] 1668 	ld	a, (x)
      00892C A1 09            [ 1] 1669 	cp	a, #0x09
      00892E 23 04            [ 2] 1670 	jrule	00124$
                                   1671 ;	snake_game.c: 444: snake.tail.y = 0;
      008930 AE 02 D2         [ 2] 1672 	ldw	x, #_snake+1
      008933 7F               [ 1] 1673 	clr	(x)
      008934                       1674 00124$:
                                   1675 ;	snake_game.c: 446: switch(Snake_array[snake.tail.x][snake.tail.y]){
      008934 AE 01 FC         [ 2] 1676 	ldw	x, #_Snake_array+0
      008937 1F 0B            [ 2] 1677 	ldw	(0x0b, sp), x
      008939 AE 02 D1         [ 2] 1678 	ldw	x, #_snake+0
      00893C F6               [ 1] 1679 	ld	a, (x)
      00893D 97               [ 1] 1680 	ld	xl, a
      00893E A6 0A            [ 1] 1681 	ld	a, #0x0a
      008940 42               [ 4] 1682 	mul	x, a
      008941 72 FB 0B         [ 2] 1683 	addw	x, (0x0b, sp)
      008944 1F 07            [ 2] 1684 	ldw	(0x07, sp), x
      008946 AE 02 D2         [ 2] 1685 	ldw	x, #_snake+1
      008949 F6               [ 1] 1686 	ld	a, (x)
      00894A 5F               [ 1] 1687 	clrw	x
      00894B 97               [ 1] 1688 	ld	xl, a
      00894C 72 FB 07         [ 2] 1689 	addw	x, (0x07, sp)
      00894F F6               [ 1] 1690 	ld	a, (x)
      008950 A1 03            [ 1] 1691 	cp	a, #0x03
      008952 27 06            [ 1] 1692 	jreq	00125$
      008954 A1 05            [ 1] 1693 	cp	a, #0x05
      008956 27 0A            [ 1] 1694 	jreq	00126$
      008958 20 10            [ 2] 1695 	jra	00127$
                                   1696 ;	snake_game.c: 447: case(S_LU): snake.tail.direction = LEFT;  break;
      00895A                       1697 00125$:
      00895A AE 02 D3         [ 2] 1698 	ldw	x, #_snake+2
      00895D A6 01            [ 1] 1699 	ld	a, #0x01
      00895F F7               [ 1] 1700 	ld	(x), a
      008960 20 0E            [ 2] 1701 	jra	00129$
                                   1702 ;	snake_game.c: 448: case(S_RU): snake.tail.direction = RIGHT; break;
      008962                       1703 00126$:
      008962 AE 02 D3         [ 2] 1704 	ldw	x, #_snake+2
      008965 A6 02            [ 1] 1705 	ld	a, #0x02
      008967 F7               [ 1] 1706 	ld	(x), a
      008968 20 06            [ 2] 1707 	jra	00129$
                                   1708 ;	snake_game.c: 449: default:    snake.tail.direction = DOWN;  break;
      00896A                       1709 00127$:
      00896A AE 02 D3         [ 2] 1710 	ldw	x, #_snake+2
      00896D A6 04            [ 1] 1711 	ld	a, #0x04
      00896F F7               [ 1] 1712 	ld	(x), a
                                   1713 ;	snake_game.c: 452: }
      008970                       1714 00129$:
                                   1715 ;	snake_game.c: 454: switch(snake.tail.direction){
      008970 AE 02 D3         [ 2] 1716 	ldw	x, #_snake+2
      008973 F6               [ 1] 1717 	ld	a, (x)
      008974 6B 0F            [ 1] 1718 	ld	(0x0f, sp), a
      008976 7B 0F            [ 1] 1719 	ld	a, (0x0f, sp)
      008978 A1 01            [ 1] 1720 	cp	a, #0x01
      00897A 27 2B            [ 1] 1721 	jreq	00131$
      00897C 7B 0F            [ 1] 1722 	ld	a, (0x0f, sp)
      00897E A1 02            [ 1] 1723 	cp	a, #0x02
      008980 27 0E            [ 1] 1724 	jreq	00130$
      008982 7B 0F            [ 1] 1725 	ld	a, (0x0f, sp)
      008984 A1 03            [ 1] 1726 	cp	a, #0x03
      008986 27 36            [ 1] 1727 	jreq	00132$
      008988 7B 0F            [ 1] 1728 	ld	a, (0x0f, sp)
      00898A A1 04            [ 1] 1729 	cp	a, #0x04
      00898C 27 47            [ 1] 1730 	jreq	00133$
      00898E 20 5A            [ 2] 1731 	jra	00140$
                                   1732 ;	snake_game.c: 455: case(RIGHT): setSnakeTailTile(S_TR); break;
      008990                       1733 00130$:
                                   1734 ;	snake_game.c: 339: setSnakeTile(snake.tail.x, snake.tail.y, tileID);
      008990 AE 02 D2         [ 2] 1735 	ldw	x, #_snake+1
      008993 F6               [ 1] 1736 	ld	a, (x)
      008994 AE 02 D1         [ 2] 1737 	ldw	x, #_snake+0
      008997 88               [ 1] 1738 	push	a
      008998 F6               [ 1] 1739 	ld	a, (x)
      008999 97               [ 1] 1740 	ld	xl, a
      00899A 84               [ 1] 1741 	pop	a
      00899B 4B 0A            [ 1] 1742 	push	#0x0a
      00899D 88               [ 1] 1743 	push	a
      00899E 9F               [ 1] 1744 	ld	a, xl
      00899F 88               [ 1] 1745 	push	a
      0089A0 CD 83 41         [ 4] 1746 	call	_setSnakeTile
      0089A3 5B 03            [ 2] 1747 	addw	sp, #3
                                   1748 ;	snake_game.c: 455: case(RIGHT): setSnakeTailTile(S_TR); break;
      0089A5 20 43            [ 2] 1749 	jra	00140$
                                   1750 ;	snake_game.c: 456: case(LEFT):  setSnakeTailTile(S_TL); break;
      0089A7                       1751 00131$:
                                   1752 ;	snake_game.c: 339: setSnakeTile(snake.tail.x, snake.tail.y, tileID);
      0089A7 AE 02 D2         [ 2] 1753 	ldw	x, #_snake+1
      0089AA F6               [ 1] 1754 	ld	a, (x)
      0089AB AE 02 D1         [ 2] 1755 	ldw	x, #_snake+0
      0089AE 88               [ 1] 1756 	push	a
      0089AF F6               [ 1] 1757 	ld	a, (x)
      0089B0 97               [ 1] 1758 	ld	xl, a
      0089B1 84               [ 1] 1759 	pop	a
      0089B2 4B 0B            [ 1] 1760 	push	#0x0b
      0089B4 88               [ 1] 1761 	push	a
      0089B5 9F               [ 1] 1762 	ld	a, xl
      0089B6 88               [ 1] 1763 	push	a
      0089B7 CD 83 41         [ 4] 1764 	call	_setSnakeTile
      0089BA 5B 03            [ 2] 1765 	addw	sp, #3
                                   1766 ;	snake_game.c: 456: case(LEFT):  setSnakeTailTile(S_TL); break;
      0089BC 20 2C            [ 2] 1767 	jra	00140$
                                   1768 ;	snake_game.c: 457: case(UP):    setSnakeTailTile(S_TU); break;
      0089BE                       1769 00132$:
                                   1770 ;	snake_game.c: 339: setSnakeTile(snake.tail.x, snake.tail.y, tileID);
      0089BE AE 02 D2         [ 2] 1771 	ldw	x, #_snake+1
      0089C1 F6               [ 1] 1772 	ld	a, (x)
      0089C2 AE 02 D1         [ 2] 1773 	ldw	x, #_snake+0
      0089C5 88               [ 1] 1774 	push	a
      0089C6 F6               [ 1] 1775 	ld	a, (x)
      0089C7 97               [ 1] 1776 	ld	xl, a
      0089C8 84               [ 1] 1777 	pop	a
      0089C9 4B 0C            [ 1] 1778 	push	#0x0c
      0089CB 88               [ 1] 1779 	push	a
      0089CC 9F               [ 1] 1780 	ld	a, xl
      0089CD 88               [ 1] 1781 	push	a
      0089CE CD 83 41         [ 4] 1782 	call	_setSnakeTile
      0089D1 5B 03            [ 2] 1783 	addw	sp, #3
                                   1784 ;	snake_game.c: 457: case(UP):    setSnakeTailTile(S_TU); break;
      0089D3 20 15            [ 2] 1785 	jra	00140$
                                   1786 ;	snake_game.c: 458: case(DOWN):  setSnakeTailTile(S_TD); break;
      0089D5                       1787 00133$:
                                   1788 ;	snake_game.c: 339: setSnakeTile(snake.tail.x, snake.tail.y, tileID);
      0089D5 AE 02 D2         [ 2] 1789 	ldw	x, #_snake+1
      0089D8 F6               [ 1] 1790 	ld	a, (x)
      0089D9 AE 02 D1         [ 2] 1791 	ldw	x, #_snake+0
      0089DC 88               [ 1] 1792 	push	a
      0089DD F6               [ 1] 1793 	ld	a, (x)
      0089DE 97               [ 1] 1794 	ld	xl, a
      0089DF 84               [ 1] 1795 	pop	a
      0089E0 4B 0D            [ 1] 1796 	push	#0x0d
      0089E2 88               [ 1] 1797 	push	a
      0089E3 9F               [ 1] 1798 	ld	a, xl
      0089E4 88               [ 1] 1799 	push	a
      0089E5 CD 83 41         [ 4] 1800 	call	_setSnakeTile
      0089E8 5B 03            [ 2] 1801 	addw	sp, #3
                                   1802 ;	snake_game.c: 459: }
      0089EA                       1803 00140$:
      0089EA 5B 12            [ 2] 1804 	addw	sp, #18
      0089EC 81               [ 4] 1805 	ret
                                   1806 ;	snake_game.c: 462: void moveSnake(enum snake_orientation move_direction)
                                   1807 ;	-----------------------------------------
                                   1808 ;	 function moveSnake
                                   1809 ;	-----------------------------------------
      0089ED                       1810 _moveSnake:
      0089ED 52 04            [ 2] 1811 	sub	sp, #4
                                   1812 ;	snake_game.c: 464: switch(move_direction){
      0089EF 7B 07            [ 1] 1813 	ld	a, (0x07, sp)
      0089F1 A1 01            [ 1] 1814 	cp	a, #0x01
      0089F3 26 03            [ 1] 1815 	jrne	00213$
      0089F5 CC 8A 92         [ 2] 1816 	jp	00108$
      0089F8                       1817 00213$:
      0089F8 7B 07            [ 1] 1818 	ld	a, (0x07, sp)
      0089FA A1 02            [ 1] 1819 	cp	a, #0x02
      0089FC 27 15            [ 1] 1820 	jreq	00101$
      0089FE 7B 07            [ 1] 1821 	ld	a, (0x07, sp)
      008A00 A1 03            [ 1] 1822 	cp	a, #0x03
      008A02 26 03            [ 1] 1823 	jrne	00219$
      008A04 CC 8B 13         [ 2] 1824 	jp	00115$
      008A07                       1825 00219$:
      008A07 7B 07            [ 1] 1826 	ld	a, (0x07, sp)
      008A09 A1 04            [ 1] 1827 	cp	a, #0x04
      008A0B 26 03            [ 1] 1828 	jrne	00222$
      008A0D CC 8B 92         [ 2] 1829 	jp	00122$
      008A10                       1830 00222$:
      008A10 CC 8C 0C         [ 2] 1831 	jp	00129$
                                   1832 ;	snake_game.c: 465: case RIGHT:
      008A13                       1833 00101$:
                                   1834 ;	snake_game.c: 466: switch(snake.head.direction){
      008A13 AE 02 D6         [ 2] 1835 	ldw	x, #_snake+5
      008A16 F6               [ 1] 1836 	ld	a, (x)
      008A17 6B 02            [ 1] 1837 	ld	(0x02, sp), a
      008A19 7B 02            [ 1] 1838 	ld	a, (0x02, sp)
      008A1B A1 03            [ 1] 1839 	cp	a, #0x03
      008A1D 27 08            [ 1] 1840 	jreq	00102$
      008A1F 7B 02            [ 1] 1841 	ld	a, (0x02, sp)
      008A21 A1 04            [ 1] 1842 	cp	a, #0x04
      008A23 27 19            [ 1] 1843 	jreq	00103$
      008A25 20 2E            [ 2] 1844 	jra	00104$
                                   1845 ;	snake_game.c: 467: case UP:    setSnakeHeadTile(S_RD); break;
      008A27                       1846 00102$:
                                   1847 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008A27 AE 02 D5         [ 2] 1848 	ldw	x, #_snake+4
      008A2A F6               [ 1] 1849 	ld	a, (x)
      008A2B AE 02 D4         [ 2] 1850 	ldw	x, #_snake+3
      008A2E 88               [ 1] 1851 	push	a
      008A2F F6               [ 1] 1852 	ld	a, (x)
      008A30 97               [ 1] 1853 	ld	xl, a
      008A31 84               [ 1] 1854 	pop	a
      008A32 4B 04            [ 1] 1855 	push	#0x04
      008A34 88               [ 1] 1856 	push	a
      008A35 9F               [ 1] 1857 	ld	a, xl
      008A36 88               [ 1] 1858 	push	a
      008A37 CD 83 41         [ 4] 1859 	call	_setSnakeTile
      008A3A 5B 03            [ 2] 1860 	addw	sp, #3
                                   1861 ;	snake_game.c: 467: case UP:    setSnakeHeadTile(S_RD); break;
      008A3C 20 2C            [ 2] 1862 	jra	00105$
                                   1863 ;	snake_game.c: 468: case DOWN:  setSnakeHeadTile(S_RU); break;  
      008A3E                       1864 00103$:
                                   1865 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008A3E AE 02 D5         [ 2] 1866 	ldw	x, #_snake+4
      008A41 F6               [ 1] 1867 	ld	a, (x)
      008A42 AE 02 D4         [ 2] 1868 	ldw	x, #_snake+3
      008A45 88               [ 1] 1869 	push	a
      008A46 F6               [ 1] 1870 	ld	a, (x)
      008A47 97               [ 1] 1871 	ld	xl, a
      008A48 84               [ 1] 1872 	pop	a
      008A49 4B 05            [ 1] 1873 	push	#0x05
      008A4B 88               [ 1] 1874 	push	a
      008A4C 9F               [ 1] 1875 	ld	a, xl
      008A4D 88               [ 1] 1876 	push	a
      008A4E CD 83 41         [ 4] 1877 	call	_setSnakeTile
      008A51 5B 03            [ 2] 1878 	addw	sp, #3
                                   1879 ;	snake_game.c: 468: case DOWN:  setSnakeHeadTile(S_RU); break;  
      008A53 20 15            [ 2] 1880 	jra	00105$
                                   1881 ;	snake_game.c: 469: default:    setSnakeHeadTile(S_H);  break;
      008A55                       1882 00104$:
                                   1883 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008A55 AE 02 D5         [ 2] 1884 	ldw	x, #_snake+4
      008A58 F6               [ 1] 1885 	ld	a, (x)
      008A59 AE 02 D4         [ 2] 1886 	ldw	x, #_snake+3
      008A5C 88               [ 1] 1887 	push	a
      008A5D F6               [ 1] 1888 	ld	a, (x)
      008A5E 97               [ 1] 1889 	ld	xl, a
      008A5F 84               [ 1] 1890 	pop	a
      008A60 4B 00            [ 1] 1891 	push	#0x00
      008A62 88               [ 1] 1892 	push	a
      008A63 9F               [ 1] 1893 	ld	a, xl
      008A64 88               [ 1] 1894 	push	a
      008A65 CD 83 41         [ 4] 1895 	call	_setSnakeTile
      008A68 5B 03            [ 2] 1896 	addw	sp, #3
                                   1897 ;	snake_game.c: 470: }
      008A6A                       1898 00105$:
                                   1899 ;	snake_game.c: 471: snake.head.x++;
      008A6A AE 02 D4         [ 2] 1900 	ldw	x, #_snake+3
      008A6D 7C               [ 1] 1901 	inc	(x)
                                   1902 ;	snake_game.c: 472: if(snake.head.x > 20)
      008A6E AE 02 D4         [ 2] 1903 	ldw	x, #_snake+3
      008A71 F6               [ 1] 1904 	ld	a, (x)
      008A72 A1 14            [ 1] 1905 	cp	a, #0x14
      008A74 23 04            [ 2] 1906 	jrule	00107$
                                   1907 ;	snake_game.c: 473: snake.head.x = 0;
      008A76 AE 02 D4         [ 2] 1908 	ldw	x, #_snake+3
      008A79 7F               [ 1] 1909 	clr	(x)
      008A7A                       1910 00107$:
                                   1911 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008A7A AE 02 D5         [ 2] 1912 	ldw	x, #_snake+4
      008A7D F6               [ 1] 1913 	ld	a, (x)
      008A7E AE 02 D4         [ 2] 1914 	ldw	x, #_snake+3
      008A81 88               [ 1] 1915 	push	a
      008A82 F6               [ 1] 1916 	ld	a, (x)
      008A83 97               [ 1] 1917 	ld	xl, a
      008A84 84               [ 1] 1918 	pop	a
      008A85 4B 06            [ 1] 1919 	push	#0x06
      008A87 88               [ 1] 1920 	push	a
      008A88 9F               [ 1] 1921 	ld	a, xl
      008A89 88               [ 1] 1922 	push	a
      008A8A CD 83 41         [ 4] 1923 	call	_setSnakeTile
      008A8D 5B 03            [ 2] 1924 	addw	sp, #3
                                   1925 ;	snake_game.c: 475: break;
      008A8F CC 8C 0C         [ 2] 1926 	jp	00129$
                                   1927 ;	snake_game.c: 477: case LEFT:
      008A92                       1928 00108$:
                                   1929 ;	snake_game.c: 478: switch(snake.head.direction){
      008A92 AE 02 D6         [ 2] 1930 	ldw	x, #_snake+5
      008A95 F6               [ 1] 1931 	ld	a, (x)
      008A96 6B 01            [ 1] 1932 	ld	(0x01, sp), a
      008A98 7B 01            [ 1] 1933 	ld	a, (0x01, sp)
      008A9A A1 03            [ 1] 1934 	cp	a, #0x03
      008A9C 27 08            [ 1] 1935 	jreq	00109$
      008A9E 7B 01            [ 1] 1936 	ld	a, (0x01, sp)
      008AA0 A1 04            [ 1] 1937 	cp	a, #0x04
      008AA2 27 19            [ 1] 1938 	jreq	00110$
      008AA4 20 2E            [ 2] 1939 	jra	00111$
                                   1940 ;	snake_game.c: 479: case UP:    setSnakeHeadTile(S_LD); break;
      008AA6                       1941 00109$:
                                   1942 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008AA6 AE 02 D5         [ 2] 1943 	ldw	x, #_snake+4
      008AA9 F6               [ 1] 1944 	ld	a, (x)
      008AAA AE 02 D4         [ 2] 1945 	ldw	x, #_snake+3
      008AAD 88               [ 1] 1946 	push	a
      008AAE F6               [ 1] 1947 	ld	a, (x)
      008AAF 97               [ 1] 1948 	ld	xl, a
      008AB0 84               [ 1] 1949 	pop	a
      008AB1 4B 02            [ 1] 1950 	push	#0x02
      008AB3 88               [ 1] 1951 	push	a
      008AB4 9F               [ 1] 1952 	ld	a, xl
      008AB5 88               [ 1] 1953 	push	a
      008AB6 CD 83 41         [ 4] 1954 	call	_setSnakeTile
      008AB9 5B 03            [ 2] 1955 	addw	sp, #3
                                   1956 ;	snake_game.c: 479: case UP:    setSnakeHeadTile(S_LD); break;
      008ABB 20 2C            [ 2] 1957 	jra	00112$
                                   1958 ;	snake_game.c: 480: case DOWN:  setSnakeHeadTile(S_LU); break;
      008ABD                       1959 00110$:
                                   1960 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008ABD AE 02 D5         [ 2] 1961 	ldw	x, #_snake+4
      008AC0 F6               [ 1] 1962 	ld	a, (x)
      008AC1 AE 02 D4         [ 2] 1963 	ldw	x, #_snake+3
      008AC4 88               [ 1] 1964 	push	a
      008AC5 F6               [ 1] 1965 	ld	a, (x)
      008AC6 97               [ 1] 1966 	ld	xl, a
      008AC7 84               [ 1] 1967 	pop	a
      008AC8 4B 03            [ 1] 1968 	push	#0x03
      008ACA 88               [ 1] 1969 	push	a
      008ACB 9F               [ 1] 1970 	ld	a, xl
      008ACC 88               [ 1] 1971 	push	a
      008ACD CD 83 41         [ 4] 1972 	call	_setSnakeTile
      008AD0 5B 03            [ 2] 1973 	addw	sp, #3
                                   1974 ;	snake_game.c: 480: case DOWN:  setSnakeHeadTile(S_LU); break;
      008AD2 20 15            [ 2] 1975 	jra	00112$
                                   1976 ;	snake_game.c: 481: default:    setSnakeHeadTile(S_H);  break;
      008AD4                       1977 00111$:
                                   1978 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008AD4 AE 02 D5         [ 2] 1979 	ldw	x, #_snake+4
      008AD7 F6               [ 1] 1980 	ld	a, (x)
      008AD8 AE 02 D4         [ 2] 1981 	ldw	x, #_snake+3
      008ADB 88               [ 1] 1982 	push	a
      008ADC F6               [ 1] 1983 	ld	a, (x)
      008ADD 97               [ 1] 1984 	ld	xl, a
      008ADE 84               [ 1] 1985 	pop	a
      008ADF 4B 00            [ 1] 1986 	push	#0x00
      008AE1 88               [ 1] 1987 	push	a
      008AE2 9F               [ 1] 1988 	ld	a, xl
      008AE3 88               [ 1] 1989 	push	a
      008AE4 CD 83 41         [ 4] 1990 	call	_setSnakeTile
      008AE7 5B 03            [ 2] 1991 	addw	sp, #3
                                   1992 ;	snake_game.c: 482: }
      008AE9                       1993 00112$:
                                   1994 ;	snake_game.c: 483: snake.head.x--;
      008AE9 AE 02 D4         [ 2] 1995 	ldw	x, #_snake+3
      008AEC 7A               [ 1] 1996 	dec	(x)
                                   1997 ;	snake_game.c: 484: if(snake.head.x > 20)
      008AED AE 02 D4         [ 2] 1998 	ldw	x, #_snake+3
      008AF0 F6               [ 1] 1999 	ld	a, (x)
      008AF1 A1 14            [ 1] 2000 	cp	a, #0x14
      008AF3 23 06            [ 2] 2001 	jrule	00114$
                                   2002 ;	snake_game.c: 485: snake.head.x = 20;
      008AF5 AE 02 D4         [ 2] 2003 	ldw	x, #_snake+3
      008AF8 A6 14            [ 1] 2004 	ld	a, #0x14
      008AFA F7               [ 1] 2005 	ld	(x), a
      008AFB                       2006 00114$:
                                   2007 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008AFB AE 02 D5         [ 2] 2008 	ldw	x, #_snake+4
      008AFE F6               [ 1] 2009 	ld	a, (x)
      008AFF AE 02 D4         [ 2] 2010 	ldw	x, #_snake+3
      008B02 88               [ 1] 2011 	push	a
      008B03 F6               [ 1] 2012 	ld	a, (x)
      008B04 97               [ 1] 2013 	ld	xl, a
      008B05 84               [ 1] 2014 	pop	a
      008B06 4B 07            [ 1] 2015 	push	#0x07
      008B08 88               [ 1] 2016 	push	a
      008B09 9F               [ 1] 2017 	ld	a, xl
      008B0A 88               [ 1] 2018 	push	a
      008B0B CD 83 41         [ 4] 2019 	call	_setSnakeTile
      008B0E 5B 03            [ 2] 2020 	addw	sp, #3
                                   2021 ;	snake_game.c: 487: break;
      008B10 CC 8C 0C         [ 2] 2022 	jp	00129$
                                   2023 ;	snake_game.c: 489: case UP:
      008B13                       2024 00115$:
                                   2025 ;	snake_game.c: 490: switch(snake.head.direction){
      008B13 AE 02 D6         [ 2] 2026 	ldw	x, #_snake+5
      008B16 F6               [ 1] 2027 	ld	a, (x)
      008B17 6B 04            [ 1] 2028 	ld	(0x04, sp), a
      008B19 7B 04            [ 1] 2029 	ld	a, (0x04, sp)
      008B1B A1 01            [ 1] 2030 	cp	a, #0x01
      008B1D 27 1D            [ 1] 2031 	jreq	00117$
      008B1F 7B 04            [ 1] 2032 	ld	a, (0x04, sp)
      008B21 A1 02            [ 1] 2033 	cp	a, #0x02
      008B23 26 2E            [ 1] 2034 	jrne	00118$
                                   2035 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008B25 AE 02 D5         [ 2] 2036 	ldw	x, #_snake+4
      008B28 F6               [ 1] 2037 	ld	a, (x)
      008B29 AE 02 D4         [ 2] 2038 	ldw	x, #_snake+3
      008B2C 88               [ 1] 2039 	push	a
      008B2D F6               [ 1] 2040 	ld	a, (x)
      008B2E 97               [ 1] 2041 	ld	xl, a
      008B2F 84               [ 1] 2042 	pop	a
      008B30 4B 03            [ 1] 2043 	push	#0x03
      008B32 88               [ 1] 2044 	push	a
      008B33 9F               [ 1] 2045 	ld	a, xl
      008B34 88               [ 1] 2046 	push	a
      008B35 CD 83 41         [ 4] 2047 	call	_setSnakeTile
      008B38 5B 03            [ 2] 2048 	addw	sp, #3
                                   2049 ;	snake_game.c: 491: case RIGHT: setSnakeHeadTile(S_LU); break;
      008B3A 20 2C            [ 2] 2050 	jra	00119$
                                   2051 ;	snake_game.c: 492: case LEFT:  setSnakeHeadTile(S_RU); break;
      008B3C                       2052 00117$:
                                   2053 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008B3C AE 02 D5         [ 2] 2054 	ldw	x, #_snake+4
      008B3F F6               [ 1] 2055 	ld	a, (x)
      008B40 AE 02 D4         [ 2] 2056 	ldw	x, #_snake+3
      008B43 88               [ 1] 2057 	push	a
      008B44 F6               [ 1] 2058 	ld	a, (x)
      008B45 97               [ 1] 2059 	ld	xl, a
      008B46 84               [ 1] 2060 	pop	a
      008B47 4B 05            [ 1] 2061 	push	#0x05
      008B49 88               [ 1] 2062 	push	a
      008B4A 9F               [ 1] 2063 	ld	a, xl
      008B4B 88               [ 1] 2064 	push	a
      008B4C CD 83 41         [ 4] 2065 	call	_setSnakeTile
      008B4F 5B 03            [ 2] 2066 	addw	sp, #3
                                   2067 ;	snake_game.c: 492: case LEFT:  setSnakeHeadTile(S_RU); break;
      008B51 20 15            [ 2] 2068 	jra	00119$
                                   2069 ;	snake_game.c: 493: default:    setSnakeHeadTile(S_V);  break;
      008B53                       2070 00118$:
                                   2071 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008B53 AE 02 D5         [ 2] 2072 	ldw	x, #_snake+4
      008B56 F6               [ 1] 2073 	ld	a, (x)
      008B57 AE 02 D4         [ 2] 2074 	ldw	x, #_snake+3
      008B5A 88               [ 1] 2075 	push	a
      008B5B F6               [ 1] 2076 	ld	a, (x)
      008B5C 97               [ 1] 2077 	ld	xl, a
      008B5D 84               [ 1] 2078 	pop	a
      008B5E 4B 01            [ 1] 2079 	push	#0x01
      008B60 88               [ 1] 2080 	push	a
      008B61 9F               [ 1] 2081 	ld	a, xl
      008B62 88               [ 1] 2082 	push	a
      008B63 CD 83 41         [ 4] 2083 	call	_setSnakeTile
      008B66 5B 03            [ 2] 2084 	addw	sp, #3
                                   2085 ;	snake_game.c: 494: }
      008B68                       2086 00119$:
                                   2087 ;	snake_game.c: 495: snake.head.y--;
      008B68 AE 02 D5         [ 2] 2088 	ldw	x, #_snake+4
      008B6B 7A               [ 1] 2089 	dec	(x)
                                   2090 ;	snake_game.c: 496: if(snake.head.y > 9)
      008B6C AE 02 D5         [ 2] 2091 	ldw	x, #_snake+4
      008B6F F6               [ 1] 2092 	ld	a, (x)
      008B70 A1 09            [ 1] 2093 	cp	a, #0x09
      008B72 23 06            [ 2] 2094 	jrule	00121$
                                   2095 ;	snake_game.c: 497: snake.head.y = 9;
      008B74 AE 02 D5         [ 2] 2096 	ldw	x, #_snake+4
      008B77 A6 09            [ 1] 2097 	ld	a, #0x09
      008B79 F7               [ 1] 2098 	ld	(x), a
      008B7A                       2099 00121$:
                                   2100 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008B7A AE 02 D5         [ 2] 2101 	ldw	x, #_snake+4
      008B7D F6               [ 1] 2102 	ld	a, (x)
      008B7E AE 02 D4         [ 2] 2103 	ldw	x, #_snake+3
      008B81 88               [ 1] 2104 	push	a
      008B82 F6               [ 1] 2105 	ld	a, (x)
      008B83 97               [ 1] 2106 	ld	xl, a
      008B84 84               [ 1] 2107 	pop	a
      008B85 4B 08            [ 1] 2108 	push	#0x08
      008B87 88               [ 1] 2109 	push	a
      008B88 9F               [ 1] 2110 	ld	a, xl
      008B89 88               [ 1] 2111 	push	a
      008B8A CD 83 41         [ 4] 2112 	call	_setSnakeTile
      008B8D 5B 03            [ 2] 2113 	addw	sp, #3
                                   2114 ;	snake_game.c: 499: break;
      008B8F CC 8C 0C         [ 2] 2115 	jp	00129$
                                   2116 ;	snake_game.c: 501: case DOWN:
      008B92                       2117 00122$:
                                   2118 ;	snake_game.c: 502: switch(snake.head.direction){
      008B92 AE 02 D6         [ 2] 2119 	ldw	x, #_snake+5
      008B95 F6               [ 1] 2120 	ld	a, (x)
      008B96 6B 03            [ 1] 2121 	ld	(0x03, sp), a
      008B98 7B 03            [ 1] 2122 	ld	a, (0x03, sp)
      008B9A A1 01            [ 1] 2123 	cp	a, #0x01
      008B9C 27 1D            [ 1] 2124 	jreq	00124$
      008B9E 7B 03            [ 1] 2125 	ld	a, (0x03, sp)
      008BA0 A1 02            [ 1] 2126 	cp	a, #0x02
      008BA2 26 2E            [ 1] 2127 	jrne	00125$
                                   2128 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008BA4 AE 02 D5         [ 2] 2129 	ldw	x, #_snake+4
      008BA7 F6               [ 1] 2130 	ld	a, (x)
      008BA8 AE 02 D4         [ 2] 2131 	ldw	x, #_snake+3
      008BAB 88               [ 1] 2132 	push	a
      008BAC F6               [ 1] 2133 	ld	a, (x)
      008BAD 97               [ 1] 2134 	ld	xl, a
      008BAE 84               [ 1] 2135 	pop	a
      008BAF 4B 02            [ 1] 2136 	push	#0x02
      008BB1 88               [ 1] 2137 	push	a
      008BB2 9F               [ 1] 2138 	ld	a, xl
      008BB3 88               [ 1] 2139 	push	a
      008BB4 CD 83 41         [ 4] 2140 	call	_setSnakeTile
      008BB7 5B 03            [ 2] 2141 	addw	sp, #3
                                   2142 ;	snake_game.c: 503: case RIGHT: setSnakeHeadTile(S_LD); break;
      008BB9 20 2C            [ 2] 2143 	jra	00126$
                                   2144 ;	snake_game.c: 504: case LEFT:  setSnakeHeadTile(S_RD); break;
      008BBB                       2145 00124$:
                                   2146 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008BBB AE 02 D5         [ 2] 2147 	ldw	x, #_snake+4
      008BBE F6               [ 1] 2148 	ld	a, (x)
      008BBF AE 02 D4         [ 2] 2149 	ldw	x, #_snake+3
      008BC2 88               [ 1] 2150 	push	a
      008BC3 F6               [ 1] 2151 	ld	a, (x)
      008BC4 97               [ 1] 2152 	ld	xl, a
      008BC5 84               [ 1] 2153 	pop	a
      008BC6 4B 04            [ 1] 2154 	push	#0x04
      008BC8 88               [ 1] 2155 	push	a
      008BC9 9F               [ 1] 2156 	ld	a, xl
      008BCA 88               [ 1] 2157 	push	a
      008BCB CD 83 41         [ 4] 2158 	call	_setSnakeTile
      008BCE 5B 03            [ 2] 2159 	addw	sp, #3
                                   2160 ;	snake_game.c: 504: case LEFT:  setSnakeHeadTile(S_RD); break;
      008BD0 20 15            [ 2] 2161 	jra	00126$
                                   2162 ;	snake_game.c: 505: default:    setSnakeHeadTile(S_V);  break;
      008BD2                       2163 00125$:
                                   2164 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008BD2 AE 02 D5         [ 2] 2165 	ldw	x, #_snake+4
      008BD5 F6               [ 1] 2166 	ld	a, (x)
      008BD6 AE 02 D4         [ 2] 2167 	ldw	x, #_snake+3
      008BD9 88               [ 1] 2168 	push	a
      008BDA F6               [ 1] 2169 	ld	a, (x)
      008BDB 97               [ 1] 2170 	ld	xl, a
      008BDC 84               [ 1] 2171 	pop	a
      008BDD 4B 01            [ 1] 2172 	push	#0x01
      008BDF 88               [ 1] 2173 	push	a
      008BE0 9F               [ 1] 2174 	ld	a, xl
      008BE1 88               [ 1] 2175 	push	a
      008BE2 CD 83 41         [ 4] 2176 	call	_setSnakeTile
      008BE5 5B 03            [ 2] 2177 	addw	sp, #3
                                   2178 ;	snake_game.c: 506: }
      008BE7                       2179 00126$:
                                   2180 ;	snake_game.c: 507: snake.head.y++;
      008BE7 AE 02 D5         [ 2] 2181 	ldw	x, #_snake+4
      008BEA 7C               [ 1] 2182 	inc	(x)
                                   2183 ;	snake_game.c: 508: if(snake.head.y > 9)
      008BEB AE 02 D5         [ 2] 2184 	ldw	x, #_snake+4
      008BEE F6               [ 1] 2185 	ld	a, (x)
      008BEF A1 09            [ 1] 2186 	cp	a, #0x09
      008BF1 23 04            [ 2] 2187 	jrule	00128$
                                   2188 ;	snake_game.c: 509: snake.head.y = 0;
      008BF3 AE 02 D5         [ 2] 2189 	ldw	x, #_snake+4
      008BF6 7F               [ 1] 2190 	clr	(x)
      008BF7                       2191 00128$:
                                   2192 ;	snake_game.c: 334: setSnakeTile(snake.head.x, snake.head.y, tileID);
      008BF7 AE 02 D5         [ 2] 2193 	ldw	x, #_snake+4
      008BFA F6               [ 1] 2194 	ld	a, (x)
      008BFB AE 02 D4         [ 2] 2195 	ldw	x, #_snake+3
      008BFE 88               [ 1] 2196 	push	a
      008BFF F6               [ 1] 2197 	ld	a, (x)
      008C00 97               [ 1] 2198 	ld	xl, a
      008C01 84               [ 1] 2199 	pop	a
      008C02 4B 09            [ 1] 2200 	push	#0x09
      008C04 88               [ 1] 2201 	push	a
      008C05 9F               [ 1] 2202 	ld	a, xl
      008C06 88               [ 1] 2203 	push	a
      008C07 CD 83 41         [ 4] 2204 	call	_setSnakeTile
      008C0A 5B 03            [ 2] 2205 	addw	sp, #3
                                   2206 ;	snake_game.c: 512: }
      008C0C                       2207 00129$:
                                   2208 ;	snake_game.c: 514: snake.head.direction = move_direction;
      008C0C AE 02 D6         [ 2] 2209 	ldw	x, #_snake+5
      008C0F 7B 07            [ 1] 2210 	ld	a, (0x07, sp)
      008C11 F7               [ 1] 2211 	ld	(x), a
                                   2212 ;	snake_game.c: 516: iterateSnakeTail();
      008C12 CD 87 F3         [ 4] 2213 	call	_iterateSnakeTail
      008C15 5B 04            [ 2] 2214 	addw	sp, #4
      008C17 81               [ 4] 2215 	ret
                                   2216 ;	snake_game.c: 519: int main(void){
                                   2217 ;	-----------------------------------------
                                   2218 ;	 function main
                                   2219 ;	-----------------------------------------
      008C18                       2220 _main:
      008C18 52 03            [ 2] 2221 	sub	sp, #3
                                   2222 ;	snake_game.c: 520: uint8_t volatile j = 0, i = 0, k =0;
      008C1A 0F 03            [ 1] 2223 	clr	(0x03, sp)
      008C1C 0F 02            [ 1] 2224 	clr	(0x02, sp)
      008C1E 0F 01            [ 1] 2225 	clr	(0x01, sp)
                                   2226 ;	snake_game.c: 523: GPIOD->DDR |= LED;    /* Pin directions */
      008C20 72 10 50 11      [ 1] 2227 	bset	0x5011, #0
                                   2228 ;	snake_game.c: 524: GPIOD->CR1 |= LED;    /* Set pin to high speed push-pull */
      008C24 72 10 50 12      [ 1] 2229 	bset	0x5012, #0
                                   2230 ;	snake_game.c: 525: GPIOD->CR2 |= LED;
      008C28 72 10 50 13      [ 1] 2231 	bset	0x5013, #0
                                   2232 ;	snake_game.c: 527: GPIOC->DDR |= (1<<6)|(1<<5)|DC_PIN|RESET_PIN|CS_PIN;  /* SPI MOSI and SPI CLK */
      008C2C AE 50 0C         [ 2] 2233 	ldw	x, #0x500c
      008C2F F6               [ 1] 2234 	ld	a, (x)
      008C30 AA 7C            [ 1] 2235 	or	a, #0x7c
      008C32 F7               [ 1] 2236 	ld	(x), a
                                   2237 ;	snake_game.c: 528: GPIOC->CR1 |= (1<<6)|(1<<5)|DC_PIN|RESET_PIN|CS_PIN;  /* Fast push pull for quick SPI transmissions */
      008C33 AE 50 0D         [ 2] 2238 	ldw	x, #0x500d
      008C36 F6               [ 1] 2239 	ld	a, (x)
      008C37 AA 7C            [ 1] 2240 	or	a, #0x7c
      008C39 F7               [ 1] 2241 	ld	(x), a
                                   2242 ;	snake_game.c: 529: GPIOC->CR2 |= (1<<6)|(1<<5)|DC_PIN|RESET_PIN|CS_PIN;
      008C3A AE 50 0E         [ 2] 2243 	ldw	x, #0x500e
      008C3D F6               [ 1] 2244 	ld	a, (x)
      008C3E AA 7C            [ 1] 2245 	or	a, #0x7c
      008C40 F7               [ 1] 2246 	ld	(x), a
                                   2247 ;	snake_game.c: 531: GPIOB->DDR &=~ (BUTTON1 | BUTTON2 | BUTTON3 | BUTTON4); /* Set to input */
      008C41 AE 50 07         [ 2] 2248 	ldw	x, #0x5007
      008C44 F6               [ 1] 2249 	ld	a, (x)
      008C45 A4 F0            [ 1] 2250 	and	a, #0xf0
      008C47 F7               [ 1] 2251 	ld	(x), a
                                   2252 ;	snake_game.c: 532: GPIOB->CR1 |=  (BUTTON1 | BUTTON2 | BUTTON3 | BUTTON4); /* Pull-up without interrupts */
      008C48 AE 50 08         [ 2] 2253 	ldw	x, #0x5008
      008C4B F6               [ 1] 2254 	ld	a, (x)
      008C4C AA 0F            [ 1] 2255 	or	a, #0x0f
      008C4E F7               [ 1] 2256 	ld	(x), a
                                   2257 ;	snake_game.c: 534: CLR_CS;
      008C4F AE 50 0A         [ 2] 2258 	ldw	x, #0x500a
      008C52 F6               [ 1] 2259 	ld	a, (x)
      008C53 AA 08            [ 1] 2260 	or	a, #0x08
      008C55 F7               [ 1] 2261 	ld	(x), a
                                   2262 ;	snake_game.c: 537: CLK->SWCR  |= 1<<1;   /* Enable clock source switch */
      008C56 AE 50 C5         [ 2] 2263 	ldw	x, #0x50c5
      008C59 F6               [ 1] 2264 	ld	a, (x)
      008C5A AA 02            [ 1] 2265 	or	a, #0x02
      008C5C F7               [ 1] 2266 	ld	(x), a
                                   2267 ;	snake_game.c: 538: CLK->SWR    = 0xE1;   /* Switch to high speed internal clock */
      008C5D AE 50 C4         [ 2] 2268 	ldw	x, #0x50c4
      008C60 A6 E1            [ 1] 2269 	ld	a, #0xe1
      008C62 F7               [ 1] 2270 	ld	(x), a
                                   2271 ;	snake_game.c: 539: CLK->CKDIVR = 0x00;   /* Set CPU and HSI prescalers to 1 */
      008C63 AE 50 C6         [ 2] 2272 	ldw	x, #0x50c6
      008C66 7F               [ 1] 2273 	clr	(x)
                                   2274 ;	snake_game.c: 540: CLK->PCKENR1= (1<<1); /* Enable SPI clock */
      008C67 AE 50 C7         [ 2] 2275 	ldw	x, #0x50c7
      008C6A A6 02            [ 1] 2276 	ld	a, #0x02
      008C6C F7               [ 1] 2277 	ld	(x), a
                                   2278 ;	snake_game.c: 541: CLK->PCKENR2= (1<<3); /* Enable ADC clock */
      008C6D AE 50 CA         [ 2] 2279 	ldw	x, #0x50ca
      008C70 A6 08            [ 1] 2280 	ld	a, #0x08
      008C72 F7               [ 1] 2281 	ld	(x), a
                                   2282 ;	snake_game.c: 544: SPI->CR1  = (1<<6)|(1<<2)|(0x3<<3);   /* Enable SPI, set to master mode */
      008C73 AE 52 00         [ 2] 2283 	ldw	x, #0x5200
      008C76 A6 5C            [ 1] 2284 	ld	a, #0x5c
      008C78 F7               [ 1] 2285 	ld	(x), a
                                   2286 ;	snake_game.c: 545: SPI->CR2  = (1<<7)|(1<<6);            /* Transmit only */
      008C79 AE 52 01         [ 2] 2287 	ldw	x, #0x5201
      008C7C A6 C0            [ 1] 2288 	ld	a, #0xc0
      008C7E F7               [ 1] 2289 	ld	(x), a
                                   2290 ;	snake_game.c: 546: SPI->CR2 |= (1<<0)|(1<<1);
      008C7F AE 52 01         [ 2] 2291 	ldw	x, #0x5201
      008C82 F6               [ 1] 2292 	ld	a, (x)
      008C83 AA 03            [ 1] 2293 	or	a, #0x03
      008C85 F7               [ 1] 2294 	ld	(x), a
                                   2295 ;	snake_game.c: 549: ADC1->CSR = (0x7<<4); /* Prescaler fmaster/6 */
      008C86 AE 54 00         [ 2] 2296 	ldw	x, #0x5400
      008C89 A6 70            [ 1] 2297 	ld	a, #0x70
      008C8B F7               [ 1] 2298 	ld	(x), a
                                   2299 ;	snake_game.c: 551: ADC1->CR2 = 0; /* Data aligned to the left */
      008C8C AE 54 02         [ 2] 2300 	ldw	x, #0x5402
      008C8F 7F               [ 1] 2301 	clr	(x)
                                   2302 ;	snake_game.c: 552: initLCD();
      008C90 CD 80 A0         [ 4] 2303 	call	_initLCD
                                   2304 ;	snake_game.c: 554: while(1){
      008C93                       2305 00123$:
                                   2306 ;	snake_game.c: 555: GPIOD->ODR ^= LED;
      008C93 AE 50 0F         [ 2] 2307 	ldw	x, #0x500f
      008C96 F6               [ 1] 2308 	ld	a, (x)
      008C97 A8 01            [ 1] 2309 	xor	a, #0x01
      008C99 F7               [ 1] 2310 	ld	(x), a
                                   2311 ;	snake_game.c: 557: for(i = 0; i < 16; i++)
      008C9A 0F 02            [ 1] 2312 	clr	(0x02, sp)
      008C9C                       2313 00131$:
      008C9C 7B 02            [ 1] 2314 	ld	a, (0x02, sp)
      008C9E A1 10            [ 1] 2315 	cp	a, #0x10
      008CA0 24 11            [ 1] 2316 	jrnc	00101$
                                   2317 ;	snake_game.c: 128: for(i = 0; i < delay; i++)
      008CA2 5F               [ 1] 2318 	clrw	x
      008CA3                       2319 00128$:
      008CA3 A3 FD E8         [ 2] 2320 	cpw	x, #0xfde8
      008CA6 24 04            [ 1] 2321 	jrnc	00126$
                                   2322 ;	snake_game.c: 129: __asm__("nop");
      008CA8 9D               [ 1] 2323 	nop
                                   2324 ;	snake_game.c: 128: for(i = 0; i < delay; i++)
      008CA9 5C               [ 2] 2325 	incw	x
      008CAA 20 F7            [ 2] 2326 	jra	00128$
                                   2327 ;	snake_game.c: 558: delay16b(65000);
      008CAC                       2328 00126$:
                                   2329 ;	snake_game.c: 557: for(i = 0; i < 16; i++)
      008CAC 7B 02            [ 1] 2330 	ld	a, (0x02, sp)
      008CAE 4C               [ 1] 2331 	inc	a
      008CAF 6B 02            [ 1] 2332 	ld	(0x02, sp), a
      008CB1 20 E9            [ 2] 2333 	jra	00131$
      008CB3                       2334 00101$:
                                   2335 ;	snake_game.c: 561: if(!(GPIOB->IDR & BUTTON1)){
      008CB3 AE 50 06         [ 2] 2336 	ldw	x, #0x5006
      008CB6 F6               [ 1] 2337 	ld	a, (x)
      008CB7 44               [ 1] 2338 	srl	a
      008CB8 25 10            [ 1] 2339 	jrc	00120$
                                   2340 ;	snake_game.c: 562: if(snake.head.direction != DOWN)
      008CBA AE 02 D6         [ 2] 2341 	ldw	x, #_snake+5
      008CBD F6               [ 1] 2342 	ld	a, (x)
      008CBE A1 04            [ 1] 2343 	cp	a, #0x04
      008CC0 27 D1            [ 1] 2344 	jreq	00123$
                                   2345 ;	snake_game.c: 563: moveSnake(UP);
      008CC2 4B 03            [ 1] 2346 	push	#0x03
      008CC4 CD 89 ED         [ 4] 2347 	call	_moveSnake
      008CC7 84               [ 1] 2348 	pop	a
      008CC8 20 C9            [ 2] 2349 	jra	00123$
      008CCA                       2350 00120$:
                                   2351 ;	snake_game.c: 565: else if(!(GPIOB->IDR & BUTTON2)){
      008CCA AE 50 06         [ 2] 2352 	ldw	x, #0x5006
      008CCD F6               [ 1] 2353 	ld	a, (x)
      008CCE A5 02            [ 1] 2354 	bcp	a, #0x02
      008CD0 26 10            [ 1] 2355 	jrne	00117$
                                   2356 ;	snake_game.c: 566: if(snake.head.direction != UP)
      008CD2 AE 02 D6         [ 2] 2357 	ldw	x, #_snake+5
      008CD5 F6               [ 1] 2358 	ld	a, (x)
      008CD6 A1 03            [ 1] 2359 	cp	a, #0x03
      008CD8 27 B9            [ 1] 2360 	jreq	00123$
                                   2361 ;	snake_game.c: 567: moveSnake(DOWN);
      008CDA 4B 04            [ 1] 2362 	push	#0x04
      008CDC CD 89 ED         [ 4] 2363 	call	_moveSnake
      008CDF 84               [ 1] 2364 	pop	a
      008CE0 20 B1            [ 2] 2365 	jra	00123$
      008CE2                       2366 00117$:
                                   2367 ;	snake_game.c: 569: else if(!(GPIOB->IDR & BUTTON3)){
      008CE2 AE 50 06         [ 2] 2368 	ldw	x, #0x5006
      008CE5 F6               [ 1] 2369 	ld	a, (x)
      008CE6 A5 04            [ 1] 2370 	bcp	a, #0x04
      008CE8 26 14            [ 1] 2371 	jrne	00114$
                                   2372 ;	snake_game.c: 570: if(snake.head.direction != RIGHT)
      008CEA AE 02 D6         [ 2] 2373 	ldw	x, #_snake+5
      008CED F6               [ 1] 2374 	ld	a, (x)
      008CEE A1 02            [ 1] 2375 	cp	a, #0x02
      008CF0 26 03            [ 1] 2376 	jrne	00200$
      008CF2 CC 8C 93         [ 2] 2377 	jp	00123$
      008CF5                       2378 00200$:
                                   2379 ;	snake_game.c: 571: moveSnake(LEFT);
      008CF5 4B 01            [ 1] 2380 	push	#0x01
      008CF7 CD 89 ED         [ 4] 2381 	call	_moveSnake
      008CFA 84               [ 1] 2382 	pop	a
      008CFB CC 8C 93         [ 2] 2383 	jp	00123$
      008CFE                       2384 00114$:
                                   2385 ;	snake_game.c: 573: else if(!(GPIOB->IDR & BUTTON4)){
      008CFE AE 50 06         [ 2] 2386 	ldw	x, #0x5006
      008D01 F6               [ 1] 2387 	ld	a, (x)
      008D02 A5 08            [ 1] 2388 	bcp	a, #0x08
      008D04 26 14            [ 1] 2389 	jrne	00111$
                                   2390 ;	snake_game.c: 574: if(snake.head.direction != LEFT)
      008D06 AE 02 D6         [ 2] 2391 	ldw	x, #_snake+5
      008D09 F6               [ 1] 2392 	ld	a, (x)
      008D0A A1 01            [ 1] 2393 	cp	a, #0x01
      008D0C 26 03            [ 1] 2394 	jrne	00204$
      008D0E CC 8C 93         [ 2] 2395 	jp	00123$
      008D11                       2396 00204$:
                                   2397 ;	snake_game.c: 575: moveSnake(RIGHT);
      008D11 4B 02            [ 1] 2398 	push	#0x02
      008D13 CD 89 ED         [ 4] 2399 	call	_moveSnake
      008D16 84               [ 1] 2400 	pop	a
      008D17 CC 8C 93         [ 2] 2401 	jp	00123$
      008D1A                       2402 00111$:
                                   2403 ;	snake_game.c: 578: iterateSnakeHead();
      008D1A CD 86 7F         [ 4] 2404 	call	_iterateSnakeHead
                                   2405 ;	snake_game.c: 579: iterateSnakeTail();
      008D1D CD 87 F3         [ 4] 2406 	call	_iterateSnakeTail
      008D20 CC 8C 93         [ 2] 2407 	jp	00123$
      008D23 5B 03            [ 2] 2408 	addw	sp, #3
      008D25 81               [ 4] 2409 	ret
                                   2410 	.area CODE
      008D26                       2411 _init_sequence:
      008D26 21                    2412 	.db #0x21	; 33
      008D27 AF                    2413 	.db #0xAF	; 175
      008D28 04                    2414 	.db #0x04	; 4
      008D29 13                    2415 	.db #0x13	; 19
      008D2A 20                    2416 	.db #0x20	; 32
      008D2B 0C                    2417 	.db #0x0C	; 12
      008D2C 00                    2418 	.db #0x00	; 0
      008D2D                       2419 _snake_tiles:
      008D2D 64                    2420 	.db #0x64	; 100	'd'
      008D2E 26                    2421 	.db #0x26	; 38
      008D2F 0B                    2422 	.db #0x0B	; 11
      008D30 D0                    2423 	.db #0xD0	; 208
      008D31 6A                    2424 	.db #0x6A	; 106	'j'
      008D32 C0                    2425 	.db #0xC0	; 192
      008D33 65                    2426 	.db #0x65	; 101	'e'
      008D34 30                    2427 	.db #0x30	; 48	'0'
      008D35 0C                    2428 	.db #0x0C	; 12
      008D36 A6                    2429 	.db #0xA6	; 166
      008D37 03                    2430 	.db #0x03	; 3
      008D38 56                    2431 	.db #0x56	; 86	'V'
      008D39 56                    2432 	.db #0x56	; 86	'V'
      008D3A 60                    2433 	.db #0x60	; 96
      008D3B 06                    2434 	.db #0x06	; 6
      008D3C 65                    2435 	.db #0x65	; 101	'e'
      008D3D 0E                    2436 	.db #0x0E	; 14
      008D3E 68                    2437 	.db #0x68	; 104	'h'
      008D3F 16                    2438 	.db #0x16	; 22
      008D40 70                    2439 	.db #0x70	; 112	'p'
      008D41 44                    2440 	.db #0x44	; 68	'D'
      008D42 66                    2441 	.db #0x66	; 102	'f'
      008D43 66                    2442 	.db #0x66	; 102	'f'
      008D44 44                    2443 	.db #0x44	; 68	'D'
      008D45 0F                    2444 	.db #0x0F	; 15
      008D46 30                    2445 	.db #0x30	; 48	'0'
      008D47 0C                    2446 	.db #0x0C	; 12
      008D48 F0                    2447 	.db #0xF0	; 240
      008D49 6D                    2448 	.db #0x6D	; 109	'm'
      008D4A B6                    2449 	.db #0xB6	; 182
      008D4B 6B                    2450 	.db #0x6B	; 107	'k'
      008D4C D6                    2451 	.db #0xD6	; 214
      008D4D 4A                    2452 	.db #0x4A	; 74	'J'
      008D4E 40                    2453 	.db #0x40	; 64
      008D4F 00                    2454 	.db #0x00	; 0
      008D50 00                    2455 	.db #0x00	; 0
      008D51 00                    2456 	.db 0x00
      008D52 00                    2457 	.db 0x00
                                   2458 	.area INITIALIZER
      008D53                       2459 __xinit__LCD_X:
      008D53 00                    2460 	.db #0x00	; 0
      008D54                       2461 __xinit__LCD_Y:
      008D54 00                    2462 	.db #0x00	; 0
      008D55                       2463 __xinit__snake_heading:
      008D55 00                    2464 	.db #0x00	; 0
      008D56                       2465 __xinit__Snake_array:
      008D56 00                    2466 	.db #0x00	; 0
      008D57 00                    2467 	.db 0x00
      008D58 00                    2468 	.db 0x00
      008D59 00                    2469 	.db 0x00
      008D5A 00                    2470 	.db 0x00
      008D5B 00                    2471 	.db 0x00
      008D5C 00                    2472 	.db 0x00
      008D5D 00                    2473 	.db 0x00
      008D5E 00                    2474 	.db 0x00
      008D5F 00                    2475 	.db 0x00
      008D60 00                    2476 	.db 0x00
      008D61 00                    2477 	.db 0x00
      008D62 00                    2478 	.db 0x00
      008D63 00                    2479 	.db 0x00
      008D64 00                    2480 	.db 0x00
      008D65 00                    2481 	.db 0x00
      008D66 00                    2482 	.db 0x00
      008D67 00                    2483 	.db 0x00
      008D68 00                    2484 	.db 0x00
      008D69 00                    2485 	.db 0x00
      008D6A 00                    2486 	.db 0x00
      008D6B 00                    2487 	.db 0x00
      008D6C 00                    2488 	.db 0x00
      008D6D 00                    2489 	.db 0x00
      008D6E 00                    2490 	.db 0x00
      008D6F 00                    2491 	.db 0x00
      008D70 00                    2492 	.db 0x00
      008D71 00                    2493 	.db 0x00
      008D72 00                    2494 	.db 0x00
      008D73 00                    2495 	.db 0x00
      008D74 00                    2496 	.db 0x00
      008D75 00                    2497 	.db 0x00
      008D76 00                    2498 	.db 0x00
      008D77 00                    2499 	.db 0x00
      008D78 00                    2500 	.db 0x00
      008D79 00                    2501 	.db 0x00
      008D7A 00                    2502 	.db 0x00
      008D7B 00                    2503 	.db 0x00
      008D7C 00                    2504 	.db 0x00
      008D7D 00                    2505 	.db 0x00
      008D7E 00                    2506 	.db 0x00
      008D7F 00                    2507 	.db 0x00
      008D80 00                    2508 	.db 0x00
      008D81 00                    2509 	.db 0x00
      008D82 00                    2510 	.db 0x00
      008D83 00                    2511 	.db 0x00
      008D84 00                    2512 	.db 0x00
      008D85 00                    2513 	.db 0x00
      008D86 00                    2514 	.db 0x00
      008D87 00                    2515 	.db 0x00
      008D88 00                    2516 	.db 0x00
      008D89 00                    2517 	.db 0x00
      008D8A 00                    2518 	.db 0x00
      008D8B 00                    2519 	.db 0x00
      008D8C 00                    2520 	.db 0x00
      008D8D 00                    2521 	.db 0x00
      008D8E 00                    2522 	.db 0x00
      008D8F 00                    2523 	.db 0x00
      008D90 00                    2524 	.db 0x00
      008D91 00                    2525 	.db 0x00
      008D92 00                    2526 	.db 0x00
      008D93 00                    2527 	.db 0x00
      008D94 00                    2528 	.db 0x00
      008D95 00                    2529 	.db 0x00
      008D96 00                    2530 	.db 0x00
      008D97 00                    2531 	.db 0x00
      008D98 00                    2532 	.db 0x00
      008D99 00                    2533 	.db 0x00
      008D9A 00                    2534 	.db 0x00
      008D9B 00                    2535 	.db 0x00
      008D9C 00                    2536 	.db 0x00
      008D9D 00                    2537 	.db 0x00
      008D9E 00                    2538 	.db 0x00
      008D9F 00                    2539 	.db 0x00
      008DA0 00                    2540 	.db 0x00
      008DA1 00                    2541 	.db 0x00
      008DA2 00                    2542 	.db 0x00
      008DA3 00                    2543 	.db 0x00
      008DA4 00                    2544 	.db 0x00
      008DA5 00                    2545 	.db 0x00
      008DA6 00                    2546 	.db 0x00
      008DA7 00                    2547 	.db 0x00
      008DA8 00                    2548 	.db 0x00
      008DA9 00                    2549 	.db 0x00
      008DAA 00                    2550 	.db 0x00
      008DAB 00                    2551 	.db 0x00
      008DAC 00                    2552 	.db 0x00
      008DAD 00                    2553 	.db 0x00
      008DAE 00                    2554 	.db 0x00
      008DAF 00                    2555 	.db 0x00
      008DB0 00                    2556 	.db 0x00
      008DB1 00                    2557 	.db 0x00
      008DB2 00                    2558 	.db 0x00
      008DB3 00                    2559 	.db 0x00
      008DB4 00                    2560 	.db 0x00
      008DB5 00                    2561 	.db 0x00
      008DB6 00                    2562 	.db 0x00
      008DB7 00                    2563 	.db 0x00
      008DB8 00                    2564 	.db 0x00
      008DB9 00                    2565 	.db 0x00
      008DBA 00                    2566 	.db 0x00
      008DBB 00                    2567 	.db 0x00
      008DBC 00                    2568 	.db 0x00
      008DBD 00                    2569 	.db 0x00
      008DBE 00                    2570 	.db 0x00
      008DBF 00                    2571 	.db 0x00
      008DC0 00                    2572 	.db 0x00
      008DC1 00                    2573 	.db 0x00
      008DC2 00                    2574 	.db 0x00
      008DC3 00                    2575 	.db 0x00
      008DC4 00                    2576 	.db 0x00
      008DC5 00                    2577 	.db 0x00
      008DC6 00                    2578 	.db 0x00
      008DC7 00                    2579 	.db 0x00
      008DC8 00                    2580 	.db 0x00
      008DC9 00                    2581 	.db 0x00
      008DCA 00                    2582 	.db 0x00
      008DCB 00                    2583 	.db 0x00
      008DCC 00                    2584 	.db 0x00
      008DCD 00                    2585 	.db 0x00
      008DCE 00                    2586 	.db 0x00
      008DCF 00                    2587 	.db 0x00
      008DD0 00                    2588 	.db 0x00
      008DD1 00                    2589 	.db 0x00
      008DD2 00                    2590 	.db 0x00
      008DD3 00                    2591 	.db 0x00
      008DD4 00                    2592 	.db 0x00
      008DD5 00                    2593 	.db 0x00
      008DD6 00                    2594 	.db 0x00
      008DD7 00                    2595 	.db 0x00
      008DD8 00                    2596 	.db 0x00
      008DD9 00                    2597 	.db 0x00
      008DDA 00                    2598 	.db 0x00
      008DDB 00                    2599 	.db 0x00
      008DDC 00                    2600 	.db 0x00
      008DDD 00                    2601 	.db 0x00
      008DDE 00                    2602 	.db 0x00
      008DDF 00                    2603 	.db 0x00
      008DE0 00                    2604 	.db 0x00
      008DE1 00                    2605 	.db 0x00
      008DE2 00                    2606 	.db 0x00
      008DE3 00                    2607 	.db 0x00
      008DE4 00                    2608 	.db 0x00
      008DE5 00                    2609 	.db 0x00
      008DE6 00                    2610 	.db 0x00
      008DE7 00                    2611 	.db 0x00
      008DE8 00                    2612 	.db 0x00
      008DE9 00                    2613 	.db 0x00
      008DEA 00                    2614 	.db 0x00
      008DEB 00                    2615 	.db 0x00
      008DEC 00                    2616 	.db 0x00
      008DED 00                    2617 	.db 0x00
      008DEE 00                    2618 	.db 0x00
      008DEF 00                    2619 	.db 0x00
      008DF0 00                    2620 	.db 0x00
      008DF1 00                    2621 	.db 0x00
      008DF2 00                    2622 	.db 0x00
      008DF3 00                    2623 	.db 0x00
      008DF4 00                    2624 	.db 0x00
      008DF5 00                    2625 	.db 0x00
      008DF6 00                    2626 	.db 0x00
      008DF7 00                    2627 	.db 0x00
      008DF8 00                    2628 	.db 0x00
      008DF9 00                    2629 	.db 0x00
      008DFA 00                    2630 	.db 0x00
      008DFB 00                    2631 	.db 0x00
      008DFC 00                    2632 	.db 0x00
      008DFD 00                    2633 	.db 0x00
      008DFE 00                    2634 	.db 0x00
      008DFF 00                    2635 	.db 0x00
      008E00 00                    2636 	.db 0x00
      008E01 00                    2637 	.db 0x00
      008E02 00                    2638 	.db 0x00
      008E03 00                    2639 	.db 0x00
      008E04 00                    2640 	.db 0x00
      008E05 00                    2641 	.db 0x00
      008E06 00                    2642 	.db 0x00
      008E07 00                    2643 	.db 0x00
      008E08 00                    2644 	.db 0x00
      008E09 00                    2645 	.db 0x00
      008E0A 00                    2646 	.db 0x00
      008E0B 00                    2647 	.db 0x00
      008E0C 00                    2648 	.db 0x00
      008E0D 00                    2649 	.db 0x00
      008E0E 00                    2650 	.db 0x00
      008E0F 00                    2651 	.db 0x00
      008E10 00                    2652 	.db 0x00
      008E11 00                    2653 	.db 0x00
      008E12 00                    2654 	.db 0x00
      008E13 00                    2655 	.db 0x00
      008E14 00                    2656 	.db 0x00
      008E15 00                    2657 	.db 0x00
      008E16 00                    2658 	.db 0x00
      008E17 00                    2659 	.db 0x00
      008E18 00                    2660 	.db 0x00
      008E19 00                    2661 	.db 0x00
      008E1A 00                    2662 	.db 0x00
      008E1B 00                    2663 	.db 0x00
      008E1C 00                    2664 	.db 0x00
      008E1D 00                    2665 	.db 0x00
      008E1E 00                    2666 	.db 0x00
      008E1F 00                    2667 	.db 0x00
      008E20 00                    2668 	.db 0x00
      008E21 00                    2669 	.db 0x00
      008E22 00                    2670 	.db 0x00
      008E23 00                    2671 	.db 0x00
      008E24 00                    2672 	.db 0x00
      008E25 00                    2673 	.db 0x00
      008E26 00                    2674 	.db 0x00
      008E27 00                    2675 	.db 0x00
      008E28                       2676 __xinit__bait_pos:
      008E28 00                    2677 	.db #0x00	; 0
      008E29 00                    2678 	.db #0x00	; 0
      008E2A 00                    2679 	.db #0x00	; 0
      008E2B                       2680 __xinit__snake:
      008E2B 00                    2681 	.db #0x00	; 0
      008E2C 00                    2682 	.db #0x00	; 0
      008E2D 00                    2683 	.db #0x00	; 0
      008E2E 00                    2684 	.db #0x00	; 0
      008E2F 00                    2685 	.db #0x00	; 0
      008E30 00                    2686 	.db #0x00	; 0
      008E31 00                    2687 	.db #0x00	; 0
                                   2688 	.area CABS (ABS)
