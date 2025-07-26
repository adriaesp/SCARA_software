/*
 * hardware_config.c
 *
 * Created: 26/07/2025 12:40:52
 *  Author: adrie
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "hardware_config.h"



void int0_init(void) {
	DDRD &= ~(1 << FC_Z);
	PORTD &= ~(1 << FC_Z);
	EICRA |= (1 << ISC00);
	EICRA &= ~(1 << ISC01);
	EIMSK |= (1 << INT0);
}

void setup_driver(void) {
	DDRB |= (1 << DIR) | (1 << STEP) | (1 << EN);  // PB0, PB1 i PB2 com a sortides 
	DDRB &= ~(1 << FC_Z);	// PB3 com a entrada

	PORTB |= (1 << DIR) | (1<<FC_Z);		// Direcció CCW; Resist Pull Up PINB3
	PORTB &= ~(1 << EN);					// Enable LOW

	DDRC |= (1 << MS2) | (1 << MS1);		// PC5 i PC4 com a sortides 
	PORTC &= ~((1 << MS2) | (1 << MS1));	// 00: 1/8 -> microstepping

	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	// Clear OC1A on compare match, set at BOTTOM
	// WGM11 = 1 alta res
	
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	// Prescaler 8
	
	TIMSK1 |= (1 << OCIE1A);
	// INT output compare match ENABLE
	
	PCMSK0 |= (1 << PCINT3);
	// Habilita interrupció per PB3 (PCINT3)
    PCICR |= (1 << PCIE0);
	// Habilita interrupció per port B (PCIE0)
		
	ICR1 = 1999;  // Fq: 1Khz 
	OCR1A = 999;  // Dty: 50%
	sei();
}
