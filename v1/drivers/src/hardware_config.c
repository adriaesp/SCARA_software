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
	DDRD &= ~(1 << FC_q2);
	PORTD &= ~(1 << FC_q2);
	EICRA |= (1 << ISC00);
	EICRA &= ~(1 << ISC01);
	EIMSK |= (1 << INT0);
}

void setup_driver_q2(void) {
	DDRB |= (1 << DIR_q2) | (1 << STEP_q2);  // PB0, PB1 com a sortides
	DDRB &= ~(1 << FC_q2);	// PB2 com a entrada 

	DDRD |= (1 << EN_q2);   // PD4 com a sortida (Enable)

	PORTB |= (1 << DIR_q2);		// Direcció CCW
	PORTD &= ~(1 << EN_q2);		// Enable ON
	PORTB |= (1 << FC_q2);       // Activa la resistència pull-up interna (si interruptor a GND)
	

	DDRC |= (1 << MS2_q2) | (1 << MS1_q2);		// PC0 i PC1 com a sortides
	PORTC &= ~((1 << MS2_q2) | (1 << MS1_q2));	// 00: 1/8 -> microstepping

	// Configuració Timer1 per PWM (mode 14, Fast PWM amb ICR1 com a TOP)
	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8
	TIMSK1 |= (1 << OCIE1A); // INT output compare match OFF

	// Interrupció per canvi a PINB3 (FC_q2)
	PCMSK0 |= (1 << PCINT2);  // habilita interrupció a PB2
	PCICR |= (1 << PCIE0);    // habilita interrupcions per port B

	ICR1 = 1999;  // Freqüència: 1 kHz
	OCR1A = 999;  // Duty cycle: 50%
	
	sei(); // habilita interrupcions globals
}


void setup_driver_q3(void) {
	DDRB &= ~(1 << FC_q3);                   // PB4 com a entrada
	
	DDRD |= (1 << DIR_q3) | (1 << STEP_q3);  // PD2, PD0 com a sortides
	DDRD |= (1 << EN_q3);                    // PD5 com a sortida
	
	PORTB |= (1 << FC_q3);                   // Pull-up per a FC_q3 

	PORTD |= (1 << DIR_q3);                  // Direcció CCW (nivell alt)
	PORTD &= ~(1 << EN_q3);                  // Enable LOW (ON)

	DDRC |= (1 << MS2_q3) | (1 << MS1_q3);   // PC2 i PC3 com a sortides per microstepping
	PORTC &= ~((1 << MS2_q3) | (1 << MS1_q3)); // 00: 1/8 
	
	TCCR3A = (1 << COM3A1) | (1 << WGM31);       // Clear OC3A on compare match, mode Fast PWM bits 1
	TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS31);  // Mode bits 2 i 3 + prescaler 8
	TIMSK3 |= (1 << OCIE3A);                      //INT output compare match OFF

	// Interrupció per canvi a FC_q3 (PB3 == PCINT3)
	PCMSK0 |= (1 << PCINT3);                      // Habilita interrupció per PB3
	PCICR |= (1 << PCIE0);                        // Habilita interrupció per port B (PCINT[7:0])

	ICR3 = 1119;  // Freqüència: 1 kHz (TOP)
	OCR3A = 999;  // Duty cycle: 50%

	sei(); // Habilita interrupcions globals
}
