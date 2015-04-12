#include <msp430.h> 

////// Port 1
// Rotary encoder pins
#define A		0x01	// Rotary encoder's A pin connection (with external pull-up with debouncing RC circuit)
#define B		0x02	// Rotary encoder's B pin connection (with external pull-up with debouncing RC circuit)
#define SW1		0x40	// Rotary encoder's button pin connection (button press connects this pin to ground - should be pulled high)
// Shift register
#define STROBE 	0x80	// The strobe pin of the shift register. Upon high->low, loads the sent data into the register
#define DATA	0x04	// Data in of the shift register. SPI data channel
#define CLK		0x10	// CLK of the shift register. SPI clock channel
#define OE		0x08	// OE of the shift register (inverted) if low, output is enabled, if low, outputs are High-Z

// Scrolling animation sequences
const int light_up_anim[17] = {0xFFFF, 0xFF7F, 0xFE7F, 0xFC7F, 0xF87F, 0xF07F, 0xE07F, 0xC07F, 0x807F, 0x007F, 0x007E, 0x007C, 0x0078, 0x0070, 0x0060, 0x0040, 0x0000};
const int eye_anim[10] = { 0xFFFF, 0xFF7F, 0xFE3F, 0xFC1F, 0xF80F, 0xF007, 0xE003, 0xC001, 0x8000, 0x0000 };
const int spindle_anim[5] = { 0xFFFF, 0x7777, 0x6666, 0x4444, 0x0000 };

// SPI globals
unsigned char SPI_upload_state = 0;	// Flag to show that all packets have been sent
unsigned int  SPI_buffer = 0;		// Data to be sent via SPI
unsigned int  SPI_PWM_buffer[16] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}; // 4bits per LED (light intensity resolution - 16)
unsigned char SPI_PWM_frame = 0;	// SPI_PWM_Buffer current frame
unsigned char SPI_mode = 0;			// SPI_mode - on/off(0) or PWM-fading(1)
// Rotary encoder
unsigned char Rot_previous_state = 0;	// Temporarily stores the previous state of the encoder
unsigned int  Rot_value = 0x3FFF;		// Initial value of the encoder
unsigned int  SW_debouncer = 0;			// Software debouncer

// General
unsigned char Value_translator_mode = 0;// Value translation mode (LED light up mode)
unsigned char accelerate_scroll = 0;
unsigned int  Fast_detect = 0;

// Limit rotary encoder value to allowed region
void Rot_limit_value(unsigned int maximum_value){
	if(Rot_value > 0x0FFF)
		Rot_value = 0;					// In case of integer underflow (went below zero) set to zero
	else if(Rot_value>maximum_value)
		Rot_value = maximum_value;		// If over maximum_value set to maximum_value
}

// Translate rotary encoder value to SPI data packets
unsigned int Rot_value_translator(){
	unsigned int translated_value=0;
	/*switch(Value_translator_mode&0x03){
		case(0):	// Infinitely rotating point
			translated_value = ~(1 << (Rot_value & 0x0F));
			break;
		case(1):	// Light circle which fills up
			Rot_limit_value(16);
			translated_value = light_up_anim[Rot_value];
			break;
		case(2):	// Eye type indicator filling up
			Rot_limit_value(9);
			translated_value = eye_anim[Rot_value];
			break;
		case(3):	// Four point spindle
			Rot_limit_value(4);
			translated_value = spindle_anim[Rot_value];
			break;
	}*/
	if(accelerate_scroll)
		translated_value = light_up_anim[((Rot_value>>6)+1)];
	else
		translated_value = light_up_anim[(((Rot_value>>2)&0x0F)+1)];
	return translated_value;
}

int main(void) {
	// Initialisation
	WDTCTL = WDTPW | WDTHOLD;				// Stop watchdog timer
	// GPIO pin setup
	P1DIR = STROBE + OE;					// Set up output pins
	P1OUT &= ~0xFF;							// Turn off all outputs
	P1REN |= SW1; P1OUT|=SW1;				// Set pull-up resistor for switch pin
	// Port1 interrupt setup
	P1IE |= A|B|SW1|0x80;                        // Enable interrupt for pins connected to A and B
	P1IES |= A|B|SW1|0x80;                           // Configure interrupt to fire on transition from high to low
	P1IFG &= ~(A|B|SW1|0x80);                    // Clear interrupt flags for pins connected to A and B
	// Timer interrupt setup
    TACTL=TASSEL_2+MC_1;					// Up timer
    CCTL0=CCIE;								// Enable timer interrupt
    TACCR0=800;								// Interrupt every 800 clicks
    // Output timer setup
    TA1CTL=TASSEL_2 + MC_1;			// Timer A0 control setup for PWM-DAC for TA0.1
    TA1CCTL1= OUTMOD_7;
    TA1CCTL0 = CCIE;
    TA1CCR0=1024+40;
    TA1CCR1=40;
    P2SEL|=0x02; P2DIR|=0x02;
	// SPI peripheral configuration
	P1SEL = DATA + CLK;						// Set pin function selectors for SPI mode
	P1SEL2 = DATA + CLK;					// Set pin function selectors for SPI mode
	UCA0CTL1 = UCSWRST;   	            	// **Put USCI(SPI) state machine in reset**
	UCA0CTL0 |= UCMST|UCMSB|UCSYNC|UCCKPH; 	// Synchronous, MSB first, Master mode, Load data on pin going high
	UCA0CTL1 |= UCSSEL_2;					// Clock source is main clock
	UCA0BR0 |= 0x02;                   		// Clock=Clock_source/2
	UCA0BR1 = 0;                        	// Second clock divider register setup
	UCA0MCTL =  0;							// No modulation
	UCA0CTL1 &= ~UCSWRST;               	// **Initialize USCI(SPI) state machine**
	IE2 |= UCA0TXIE;						// Enable SPI interrupt on transmit
	// CPU setup
	__bis_SR_register(GIE);					// Enable CPU interrupt handling
    BCSCTL1 = CALBC1_16MHZ;         		// Set DCO to 16MHz factory calibration value
    DCOCTL  = CALDCO_16MHZ;

    char temp;
	// Main loop
	while(1){
		temp=!(P1IN&SW1);
		if( (!(accelerate_scroll)) != temp ){	// If switch has underwent a change
			accelerate_scroll = !temp;
			P1IFG|=0x80;	// Call interrupt but don't set any important pins
		}
	}
	return 0;
}


////// Interrupt routines
// Timer routine (push data to registers)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0 (void){
	__bis_SR_register(GIE);
	if(SPI_mode)
		SPI_buffer = SPI_PWM_buffer[(SPI_PWM_frame++)&0x0F];
	UCA0TXBUF = SPI_buffer&0xFF;	// Start the SPI routine by sending first packet
	if(P1IN&SW1){
		SW_debouncer=(SW_debouncer + 1) & 0x7FFF;	// Software debouncer counter, & 0x7FFF so that integer won't overflow
	}
	else
		SW_debouncer=0;
}
// SPI routine (push second data block or load the data)
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIA0TX_ISR(void){
	if(SPI_upload_state){	// Make the register load the data
		P1OUT |= STROBE;
		P1OUT &= ~STROBE;	// Load in freshly sent data
		SPI_upload_state = 0;
	}
	else{					// Send the second data packet of 8 bits
		SPI_upload_state = 1;
		UCA0TXBUF = SPI_buffer >> 8;
	}
	IFG2 &= ~UCA0TXIFG;		// Clear interrupt flag so that regular operation can resum
}
// Port1 interrupt (handles rotary encoder switching)
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
	// Remember when the rotary encoder closes the connection, the corresponding pin goes low. Everything is by default pulled high.
	switch(P1IFG & 0x43){
		case(A):	// If A went from high to low
			if(Rot_previous_state == B){  // And if previously B went from high to low (legal transition)
				if(Fast_detect<500)
					Rot_value=(Rot_value + (accelerate_scroll?32:4)) & 0x3FF;			// Increment the set value
				else
					Rot_value=(Rot_value + (accelerate_scroll?8:1)) & 0x3FF;			// Increment the set value
				Rot_previous_state = 0;	// Set the previous state to 0 (transition completed, ready for new one)
				Fast_detect = 0;
			}
			else	// If B didn't go low and B is low now, something's wrong, drop previous state, or if B is high set A as previous state
				Rot_previous_state = (P1IN & B) ? A : 0;
			break;
		case(B):	// If B went from high to low
			if(Rot_previous_state == A){	// And if previously A went from high to low (legal transition)
				if(Fast_detect<500)
					Rot_value=(Rot_value - (accelerate_scroll?32:4)) & 0x3FF;			// Decrement the set value
				else
					Rot_value=(Rot_value - (accelerate_scroll?8:1)) & 0x3FF;			// Decrement the set value
				Rot_previous_state = 0;	// Set the previous state to 0 (transition completed, ready for new one)
				Fast_detect = 0;
			}
			else 	// If A didn't go low and A is low now, something's wrong, drop previous state, or if A is high set B as previous state
				Rot_previous_state = (P1IN & A) ? B : 0;
			break;
		/*case(SW1):
			if(!(P1IN & SW1))
				if(SW_debouncer > 80){	// Software switch debouncer
					SW_debouncer = 0;
					Value_translator_mode++;
				}
			break;*/
		default: break;
	}
	P1IFG = 0;								// Clear interrupt flag so that regular operation can resume
	SPI_buffer = Rot_value_translator();	// Load current data to be sent to the registers
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0(void)
{
	TA1CCR1=40+Rot_value;
	Fast_detect= (Fast_detect+1)&0xFFF;
}
