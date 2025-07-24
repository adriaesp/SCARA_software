
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "Timer0_delay.h"


typedef struct {
	float graus;
	int passos;
} Moviment;

Moviment movs[] = {
	{90.0, 0},
	{180.0, 0},
	{45.0, 0},
	{720.0, 0}
};

#define MAX_MOVES (sizeof(movs) / sizeof(movs[0]))



volatile int step_obj[MAX_MOVES];   // Passos per a cada moviment
volatile int step_count = 0;
volatile int mov_index = 0;

volatile uint8_t MOV = 0;

#define DIR PB0
#define STEP PB1
#define EN PB2
#define MS2 PC4
#define MS1 PC5

#define FC_Z PD0

void int0_init(void) {
	DDRD &= ~(1 << FC_Z);      // PD0 entrada
	PORTD &= ~(1 << FC_Z);

	EICRA |= (1 << ISC00);    // Interrupt on any logical change
	EICRA &= ~(1 << ISC01);

	EIMSK |= (1 << INT0);     // Habilita INT0
}

void setup() {
	// Configura OC1A (PB1, pin 9 Arduino UNO) com a sortida
	DDRB |= (1 << DIR) | (1 << STEP) | (1 << EN); 
	PORTB |= (1 << DIR); // Direcció = HIGH, CCKW
	PORTB &= ~(1<<EN);  // EN = LOW -> Driver = 0n
	
	// Configura microsteping
	DDRC |= (1<<MS2) | (1<<MS1);
	PORTC &= ~((1<<MS2) | (1<<MS1)); // MS2, MS1: 00: 1/8, 01: 1/2, 10: 1/4 11: 1/16 
	
	// Timer1 ? Fast PWM, TOP = ICR1, prescaler = 8
	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	TIMSK1 |= (1 << OCIE1A);  // Habilita interrupció per OCR1A

	ICR1 = 1999;      // TOP ? Freq = 1kHz
	OCR1A = 999;      // 50% cicle de treball
	sei();
}


int calcula_pasos(float graus)
{
	return (int)(1600.0 *( graus / 360.0));
}

ISR(TIMER1_COMPA_vect) {		
	step_count++;
	if (step_count >= movs[mov_index].passos) {
		MOV = 1;
	}
}

ISR(INT0_vect) {
	if (MOV != 4){
		MOV = 3;	
	}

}

int main(void) {
	
	// Precalcula els passos per cada moviment
	for (int i = 0; i < MAX_MOVES; i++) {
		movs[i].passos = calcula_pasos(movs[i].graus);
	}
	
	int0_init();
	timer0_init();
	setup();

while (1) {
	switch (MOV) {
		case 0:
		// En moviment
		break;

		case 1:
		TCCR1A &= ~(1<<COM1A1); // Atura PWM
		if (delay_ms(1000))
		{
			mov_index++;
			MOV = 2;
		}

		break;

		case 2:	
		if (mov_index < MAX_MOVES) {
			step_count = 0;
			TCNT1 = 0;
			TCCR1A |= (1 << COM1A1); // Reactiva PWM
			MOV = 0;
			} else { 
			// Hem acabat
			MOV = 4;
			//PORTB |= (1 << EN); // Desactiva driver si vols
		}
		break;
		
		case 3: // Final de carrera detectat
		if (PIND & !(1 << FC_Z)) {      // PD0 és LOW -> botó no premut
			TCCR1A &= ~(1<<COM1A1);		// Atura PWM

			}else{
			DDRB &= ~(1 << DIR);
			MOV = 2;
		}
		break;
				
		case 4:
		//Finito
		break;
		

	}
}
}