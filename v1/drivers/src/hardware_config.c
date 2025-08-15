/*
 * hardware_config.c
 *
 * Setup of pins and timer for three stepper motors.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "hardware_config.h"

<<<<<<< Updated upstream
// Hardware description for the three motors
const MotorHW motor_hw[3] = {
    { &PORTB, &DDRB, PB0, PB1, PB2 }, // Motor 1 on PORTB
    { &PORTC, &DDRC, PC0, PC1, PC2 }, // Motor 2 on PORTC
    { &PORTD, &DDRD, PD0, PD1, PD2 }  // Motor 3 on PORTD
};

void int0_init(void) {
        DDRD &= ~(1 << FC_Z);
        PORTD &= ~(1 << FC_Z);
        EICRA |= (1 << ISC00);
        EICRA &= ~(1 << ISC01);
        EIMSK |= (1 << INT0);
}

void setup_driver(void) {
        for (int i = 0; i < 3; i++) {
                *(motor_hw[i].ddr) |= (1 << motor_hw[i].dir) |
                                      (1 << motor_hw[i].step) |
                                      (1 << motor_hw[i].en);
                *(motor_hw[i].port) |= (1 << motor_hw[i].dir);
                *(motor_hw[i].port) &= ~(1 << motor_hw[i].en);
        }

        DDRD &= ~(1 << FC_Z);   // limit switch input
        PORTD |= (1 << FC_Z);

        TCCR1A = (1 << WGM11); // no hardware toggle, manual step
        TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8

        TIMSK1 |= (1 << OCIE1A); // enable compare match interrupt

        ICR1 = 1999;  // Fq: 1Khz
        OCR1A = 999;  // Dty: 50%
        sei();
}

=======
void setup_driver_q2(void) {
	UCSR1B = 0;     // UART1 OFF

	DDRB |= (1 << DIR_q2) | (1 << STEP_q2);  // PB0, PB1 com a sortides

	DDRE &= ~(1 << FC_q2);         // PE0 com a entrada
	PORTE |= (1 << FC_q2);         // Pull-up activat

	DDRD |= (1 << EN_q2);        // PD4 com a sortida (Enable)

	PORTB |= (1 << DIR_q2);		// Direcció CCW
	PORTD &= ~(1 << EN_q2);		// Enable ON

	DDRC |= (1 << MS2_q2) | (1 << MS1_q2);
	PORTC &= ~((1 << MS2_q2) | (1 << MS1_q2));	// 00: 1/8 microstepping

	// Configuració Timer1 per PWM
	TCCR1A = (1 << COM1A1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	TIMSK1 |= (1 << OCIE1A);

	PCMSK1 |= (1 << PCINT8);    // Habilita PE0
	PCICR |= (1 << PCIE1);      // Activa PCINT[14:8]

	ICR1 = 1999;
	OCR1A = 999;

	sei();
}

void setup_driver_q3(void) {
	DDRE &= ~(1 << FC_q3);         // PE1 com a entrada
	PORTE |= (1 << FC_q3);         // Pull-up activat

	DDRD |= (1 << DIR_q3) | (1 << STEP_q3);
	DDRD |= (1 << EN_q3);

	PORTD |= (1 << DIR_q3);
	PORTD &= ~(1 << EN_q3);

	DDRC |= (1 << MS2_q3) | (1 << MS1_q3);
	PORTC &= ~((1 << MS2_q3) | (1 << MS1_q3));

	TCCR3A = (1 << COM3A1) | (1 << WGM31);
	TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS31);
	TIMSK3 |= (1 << OCIE3A);

	PCMSK1 |= (1 << PCINT9);    // Habilita PE1
	PCICR |= (1 << PCIE1);      // Ja estava activada, no cal repetir si ja hi és

	ICR3 = 1119;
	OCR3A = 999;

	sei();
}

void setup_driver_d1(void) {
	DDRD |= (1 << DIR_d1) | (1 << STEP_d1);
	DDRD |= (1 << EN_d1);

	DDRE &= ~(1 << FC_d1);         // PE2 com a entrada
	PORTE |= (1 << FC_d1);         // Pull-up activat

	PORTD |= (1 << DIR_d1);
	PORTD &= ~(1 << EN_d1);

	DDRC |= (1 << MS2_d1) | (1 << MS1_d1);
	PORTC &= ~(1 << MS2_d1);
	PORTC |=  (1 << MS1_d1);   // 01: 1/2 microstepping

	TCCR4A = (1 << COM4A1) | (1 << WGM41);
	TCCR4B = (1 << WGM43) | (1 << WGM42) | (1 << CS41);
	TIMSK4 |= (1 << OCIE4A);

	ICR4 = 1000;
	OCR4A = 500;

	PCMSK1 |= (1 << PCINT10);   // Habilita PE2
	PCICR |= (1 << PCIE1);      // Port E

	sei();
}
>>>>>>> Stashed changes
