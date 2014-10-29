/*
 * GccApplication1.c
 *
 * Created: 01-Oct-14 22:07:47
 *  Author: Andrew
 */ 

//#define __AVR_ATtiny2313__ // MCU TYPE - Uncomment if running weird compiler

#include <avr/io.h>
#include <avr/interrupt.h>

//----------definitions
#define goal_light1 0x02	//PORTD1
#define BEAM1 0x04			//PORTD2
#define BEAM2 0x08			//PORTD3
#define goal_light2 0x20	//PORTD5
#define Data_to_reg 0x40	//PORTD6
#define write_in1 0x01		//PORTB0
#define write_in2 0x02		//PORTB1
#define write_out1 0x04		//PORTB2
#define write_out2 0x08		//PORTB3
#define out_en1 0x10		//PORTB4
#define out_en2 0x20		//PORTB5
#define Button 0x80			//PORTB7

//----------functions
void write_to_7seg(char goal_tens, char goal_ones, char comma, char out_en);
void dec_to_7seg(char digit, char comma);
void write_to_reg(char digit);
char goal(long timer_tick, char goals);
void check_button();

//----------global variables
const char goal_lim = 10;	//number of goals at which game ends
volatile long dark_time = 0, timer_tick = 0;
volatile char goals1 = 0, goals2 = 0, player = 0;

int main(void)
{
	//PORTs' configuration
	DDRB = 0x7F;	//PORTB [0 - 6] - out, 7 - in
	PORTB = 0x80;	//one input port with pull-up
	DDRD = 0x73;	//PORTD [0 - 1] - out, [2 - 3] - in, [4 - 6] - out
	PORTD = 0x80;	//input ports without pull-ups, all outputs set to 0
		
	//At the beginning of the game - write 0 : 0
	write_to_7seg(0, 0, 0, out_en1 | out_en2);

	//setting interrupts	
	TCCR1B |= (1 << CS10);	// 16bit counter prescaler = 1
	MCUCR |= (1 << ISC10) | (1 << ISC00);	//interrupts for both PORTD [2 & 3] on any logical change
	GIMSK |= (1 << INT1) | (1 << INT0);		//enable interrupts for both PORTD [2 & 3]
	sei();	//global interrupt enable
	
	while (1)
	{
		check_button();
		
		//when game is over blink digits and check for button
		if ((goals1 == goal_lim) || (goals2 == goal_lim)){
			cli();
			while(1){
				PORTB |= (out_en1 | out_en2);	//don't show buffer exit
				for (unsigned long j = 0; j < 40000; j++){
					if (!(PINB & Button))
						break;
				}
				PORTB &= ~(out_en1 | out_en2);	//show buffer exit
				for (unsigned long j = 0; j < 80000; j++){
					if (!(PINB & Button))
						break;
				}
				if (!(PINB & Button)){
					EIFR |= (1 << INTF1) | (1 << INTF0);	//clear accidental interrupts
					break;
				}
			}
			check_button();
		}
	}
}

void check_button()	//check if the button is pressed during all the game
{
	cli();
	if (!(PINB & Button)){
		for (unsigned int i = 0; i < 50001; i++){
			//if hold for a while, change goals
			if ((i > 10000) && (i < 50000)){
				//if button is released - decrease selected players goals
				if (PINB & Button){
					if (player == 1){
						if (goals1 > 0)	goals1--;
						write_to_7seg(goals1 / 10, goals1 % 10, 2, out_en1);
					}
					else{
						if (goals2 > 0)	goals2--;
						write_to_7seg(goals2 / 10, goals2 % 10, 2, out_en2);
					}
					break;
				}
			}
			//if hold button for a long time, reset the game
			else if ((i == 50000) && !(PINB & Button)){
				player = 0;
				goals1 = 0;
				goals2 = 0;
				write_to_7seg(0, 0, 0, (out_en1 | out_en2));
				while (!(PINB & Button)){};
				break;
			}
		}
	}
	sei();
}

void write_to_7seg(char goal_tens, char goal_ones, char comma, char out_en)	//sends 2 digits to be written on 7seg. Proceeds to dec_to_7seg()
{
	//comma - when 0 - no comma (xx), when 1 - after higher digit (x.x), when 2 - after lower digit (xx.)
	PORTB |= out_en; 	//turn off output buffer
	dec_to_7seg(goal_tens, comma & 1);
	dec_to_7seg(goal_ones, comma & 2);
	PORTB &= ~out_en; 	//turn on output buffer
}

void dec_to_7seg(char digit, char comma)	//converts decimal to 7seg (adds comma if necessary) and proceeds to write_to_reg()
{
	unsigned char leds = 0;
	
	//select correct digit for 7seg
	switch (digit)
	{							//MSB -> LSB
	case 1: leds = 0x06; break;	//0b01100000  
	case 2: leds = 0x5B; break;	//0b11011010	
	case 3: leds = 0x4F; break;	//0b11110010
	case 4: leds = 0x66; break;	//0b01100110
	case 5: leds = 0x6D; break;	//0b10110110
	case 6: leds = 0x7D; break;	//0b10111110
	case 7: leds = 0x07; break;	//0b11100000
	case 8: leds = 0x7F; break;	//0b11111110
	case 9: leds = 0x6F; break;	//0b11110110
	default: leds = 0x3F;break;	//0b11111100
	}
	
	//add comma if necessary
	if (comma)
		leds |= 0x80;
	write_to_reg(leds);
}

void write_to_reg(char digit)			//shifts one digit into 1st/2nd/both registers
{
	char mask = 0x80;		//helps to write digit to shift register
	char write_input = 0;	//clock for serial input data load
	char write_output = 0;	//clock for parallel output data load
	
	for (char i = 0; i < 8; i++)
	{
		//send "1" or "0" to register input
		if (digit & mask)
			PORTD |= Data_to_reg;
		else
			PORTD &= ~Data_to_reg;
		
		//chose, which player receive update
		if (player == 1){
			write_input = write_in1;
			write_output = write_out1;
		}
		else if (player == 2){
			write_input = write_in2;
			write_output = write_out2;
		}
		else{
			write_input = (write_in1 | write_in2);
			write_output = (write_out1 | write_out2);
		}
		
		PORTB ^= write_input;	//serial input load
		PORTB ^= write_input;
		
		mask /= 2;	//prepare mask for next use
	}
	
	PORTB ^= write_output;	//parallel output buffer load
	PORTB ^= write_output;
}

void blink_blink(char blink_diodes)		//blinks diodes of 1st/2nd player
{
	char k = 0;
	while (k < 10)	//blink diodes for 5 times on and 5 times off
	{
		for (unsigned int i = 0; i < 50000; i++);	//wait
		PORTD ^= blink_diodes;
		k++;
	}
}

char goal(long timer_tick, char goals)	//proceeds new goal occurrence
{
	TIMSK &= ~(1 << TOIE1);						//disable counter overflow interrupt
	GIMSK &= ~((1 << INT1) | (1 << INT0));		//disable interrupts for both PORTD [2 & 3]
	
	char output_on = 0, blink_diodes = 0;
	int speed;
		
	if (player == 1)
	{
		//clear dot from player 2, who missed goal
		player = 2;
		write_to_7seg(goals2 / 10, goals2 % 10, 0, out_en2);
		
		player = 1;
		output_on = out_en1;	//select port to enable/disable output
		blink_diodes = goal_light1;	//select port to turn diode strip on
	}
	else
	{		
		//clear dot from player 1, who missed goal
		player = 1;
		write_to_7seg(goals1 / 10, goals1 % 10, 0, out_en1);
		
		player = 2;
		output_on = out_en2;	//select port to enable/disable output
		blink_diodes = goal_light2;	//select port to turn diode strip on
	}
	
	dark_time += timer_tick;
	speed = (int)(1296000 / dark_time);	//12960000 = 0.036 * 3.6 * 1000000 * 10 [ball_diameter[m] / m/s * km/h * freq * 10] - one digit after dec.point
	
	//----------show speed
	if (speed / 100){
		write_to_7seg(speed / 100, (speed - speed / 100 * 100) / 10, 0, output_on);
	}
	else{
		write_to_7seg(speed / 10, (speed - speed / 10 * 10), 1, output_on);
	}
	blink_blink(blink_diodes);
			
	//----------calculate and show goals
	if (goals < goal_lim) goals++;
		
	write_to_7seg(goals / 10, goals % 10, 2, output_on);
	blink_blink(blink_diodes);
	
	EIFR |= (1 << INTF1) | (1 << INTF0);	//clear accidental interrupts
	GIMSK |= (1 << INT1) | (1 << INT0);		//enable interrupts for both PORTD [2 & 3]
	return goals;
}

ISR(INT0_vect) //external interrupt for player1
{
	if (PIND & BEAM1)
	{
		TCNT1 = 0x0000; //start 16bit counter
		dark_time = 0;	//reset time, when ball hides beam
		TIMSK |= (1 << TOIE1);	//enable counter overflow interrupt	
		player = 1;	
		GIMSK = 0x40;	//disable interrupts for 2nd player
	}
	else
	{
		timer_tick = TCNT1;	//read counter and pass value when ball frees beam;
		goals1 = goal(timer_tick, goals1);	//change display data and celebrate the goal 
	}
}

ISR(INT1_vect) //external interrupt for player2
{
	if (PIND & BEAM2)
	{
		TCNT1 = 0x0000; //start 16bit counter
		dark_time = 0;	//reset time, when ball hides beam
		TIMSK |= (1 << TOIE1);	//enable counter overflow interrupt
		player = 2;
		GIMSK = 0x80;	//disable interrupts for 1st player
	}
	else
	{	
		timer_tick = TCNT1;	//read counter, and pass value when ball frees beam;
		goals2 = goal(timer_tick, goals2); //change display data and celebrate the goal
	}
}

ISR(TIMER1_OVF_vect) //timer overflow interrupt
{
	dark_time += 65536;
}
