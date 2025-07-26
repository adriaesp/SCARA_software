/*
 * hardware_config.c
 *
 * Created: 26/07/2025 12:40:52
 *  Author: adrie
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "hardware_config.h"

#define DIR PB0
#define STEP PB1
#define EN PB2
#define MS2 PC4
#define MS1 PC5
#define FC_Z PD0

void int0_init(void) {
	DDRD &= ~(1 << FC_Z);
	PORTD &= ~(1 << FC_Z);
	EICRA |= (1 << ISC00);
	EICRA &= ~(1 << ISC01);
	EIMSK |= (1 << INT0);
}

void setup_driver(void) {
	DDRB |= (1 << DIR) | (1 << STEP) | (1 << EN);
	PORTB |= (1 << DIR);
	PORTB &= ~(1 << EN);

	DDRC |= (1 << MS2) | (1 << MS1);
	PORTC &= ~((1 << MS2) | (1 << MS1));

	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	TIMSK1 |= (1 << OCIE1A);

	ICR1 = 1999;
	OCR1A = 999;
	sei();
}
