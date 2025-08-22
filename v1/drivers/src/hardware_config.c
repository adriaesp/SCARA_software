/*
 * hardware_config.c
 *
 * Created: 26/07/2025 12:40:52
 *  Author: adrie
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "hardware_config.h"


void setup_driver_q2(void) {
	
	DDRB |= (1 << DIR_q2) | (1 << STEP_q2);  // PB0, PB1 com a sortides
	DDRE &= ~(1 << FC_q2);	// PB2 com a entrada 

	DDRD |= (1 << EN_q2);   // PD4 com a sortida (Enable)

	PORTB |= (1 << DIR_q2);		// Direcció CCW
	PORTD &= ~(1 << EN_q2);		// Enable ON
	PORTE |= (1 << FC_q2);       // Activa la resistència pull-up interna (si interruptor a GND)
	

	DDRC |= (1 << MS2_q2) | (1 << MS1_q2);		// PC0 i PC1 com a sortides
	PORTC &= ~((1 << MS2_q2) | (1 << MS1_q2));	// 00: 1/8 -> microstepping

	// Configuració Timer1 per PWM (mode 14, Fast PWM amb ICR1 com a TOP)
	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8
	TIMSK1 |= (1 << OCIE1A); // INT output compare match OFF

	// Interrupció per canvi a PINE2 (FC_q2)
	PCIFR |= (1<<PCIF3);
	PCMSK3 |= (1<<FC_q2);
	PCICR  |= (1<<PCIE3);

	ICR1 = 1999;  // Freqüència: 1 kHz
	OCR1A = 999;  // Duty cycle: 50%
	
	sei(); // habilita interrupcions globals
}


void setup_driver_q3(void) {
	DDRE &= ~(1 << FC_q3);                   // PE1 com a entrada
	
	DDRD |= (1 << DIR_q3) | (1 << STEP_q3);  // PD2, PD0 com a sortides
	DDRD |= (1 << EN_q3);                    // PD5 com a sortida
	
	PORTE |= (1 << FC_q3);                   // Pull-up per a FC_q3 

	PORTD |= (1 << DIR_q3);                  // Direcció CCW (nivell alt)
	PORTD &= ~(1 << EN_q3);                  // Enable LOW (ON)

	DDRC |= (1 << MS2_q3) | (1 << MS1_q3);   // PC2 i PC3 com a sortides per microstepping
	PORTC &= ~((1 << MS2_q3) | (1 << MS1_q3)); // 00: 1/8 
	
	TCCR3A = (1 << COM3A1) | (1 << WGM31);       // Clear OC3A on compare match, mode Fast PWM bits 1
	TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS31);  // Mode bits 2 i 3 + prescaler 8
	TIMSK3 |= (1 << OCIE3A);                      //INT output compare match OFF

	// Interrupció per canvi a PINE1 (FC_q3)
	PCIFR |= (1<<PCIF3);
	PCMSK3 |= (1<<FC_q3);
	PCICR  |= (1<<PCIE3);

	ICR3 = 1119;  // Freqüència: 1 kHz (TOP)
	OCR3A = 999;  // Duty cycle: 50%

	sei(); // Habilita interrupcions globals
}


void setup_driver_d1(void) {
	// Direcció i step com a sortides
	DDRD |= (1 << DIR_d1) | (1 << STEP_d1);

	// Enable com a sortida
	DDRD |= (1 << EN_d1);

	// Final de carrera com entrada amb pull-up (PD7)
	DDRE &= ~(1 << FC_d1);     // FC_d1 = PD7
	PORTE |= (1 << FC_d1);     // Pull-up activada (interruptor NC a GND)

	// Direcció per defecte
	PORTD |= (1 << DIR_d1);
	PORTD &= ~(1 << EN_d1);    // Enable actiu (LOW)

	// Microstepping
	DDRC |= (1 << MS2_d1) | (1 << MS1_d1);
	PORTC &= ~(1 << MS2_d1);
	PORTC |=  (1 << MS1_d1);   // 01: 1/2 microstepping

	// Timer 4 config
	TCCR4A = (1 << COM4A1) | (1 << WGM41);
	TCCR4B = (1 << WGM43) | (1 << WGM42) | (1 << CS41);
	TIMSK4 |= (1 << OCIE4A);
	ICR4 = 1000;
	OCR4A = 500;

	// Interrupció per canvi a PINE0 (FC_d1)
	PCIFR |= (1<<PCIF3);
	PCMSK3 |= (1<<FC_d1);
	PCICR  |= (1<<PCIE3);

	sei();                     // Habilita interrupcions globals
}