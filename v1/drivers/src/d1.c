/*
 * d1.c
 *
 * Created: 07/08/2025 11:23:44
 *  Author: adrie
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "d1.h"
#include "hardware_config.h"
#include "punts.h"
#include "calc_moviment.h"
#include "moviment.h"

volatile uint16_t step_count_d1 = 0;
volatile uint8_t  mov_index_d1  = 0;
volatile uint8_t  MOV_D1        = 0;
volatile uint8_t  HM_D1         = 1;
volatile uint8_t  ACABAT_D1     = 0;
volatile uint8_t  mov_acabat_d1 = 0;


ISR(TIMER4_COMPA_vect) {
	step_count_d1++;
	if (step_count_d1 >= llista_d1[mov_index_d1].passos) {
		TCCR4A &= ~(1 << COM4A1);
		TIMSK4 &= ~(1 << OCIE4A);
		mov_acabat_d1 = 1;
		HM_D1 = 3;
	}
}

void homing_d1(void) {
	while (!ACABAT_D1) {
		switch (HM_D1) {
			case 0:
			break;

			case 1: // inici desplaçament
			step_count_d1 = 0;
			TCNT4 = 0;
			llista_d1[mov_index_d1].passos = 65000;
			TCCR4A |= (1 << COM4A1);
			HM_D1 = 0;
			break;

			case 2: // tornar enrere cap a home
			PORTD &= ~(1 << DIR_d1);   // CW (inverteix si cal)
			step_count_d1 = 0;
			TCNT4 = 0;
			llista_d1[mov_index_d1].passos = 30000;

			// Desactiva la PCINT de PE2 (PCINT10) durant el moviment
			PCMSK1 &= ~(1 << PCINT10);
			HM_D1 = 0;
			break;

			case 3: // home assolit
			TIMSK4 &= ~(1 << OCIE4A);
			TCCR4A &= ~(1 << COM4A1);

			// Reactiva la PCINT de PE2 (PCINT10)
			PCMSK1 |= (1 << PCINT10);
			ACABAT_D1 = 1;
			MOV_D1 = 0;
			step_count_d1 = 0;
			break;
		}
	}
}

void mou_d1(void) {
	switch (MOV_D1) {
		case 0: // en repòs/esperant
		break;

		case 1: // inicia moviment
		step_count_d1 = 0;
		TCNT4 = 0;

		if (llista_d1[mov_index_d1].dir == 1) {
			PORTD &= ~(1 << DIR_d1);   // CW
			} else {
			PORTD |=  (1 << DIR_d1);   // CCW
		}

		MOV_D1 = 0;
		TIMSK4 |= (1 << OCIE4A);
		TCCR4A |= (1 << COM4A1);
		break;

		case 2: // lectura directa de FC (PE2 amb pull-up)
		if (PINE & (1 << FC_d1)) {
			// pin ALT ? FC NO polsat ? continua
			MOV_D1 = 1;
			TCCR4A |= (1 << COM4A1);
			} else {
			// pin BAIX ? FC polsat ? para PWM
			TCCR4A &= ~(1 << COM4A1);
		}
		break;

		case 3: // final de moviment
		PORTD |= (1 << EN_d1); // EN alt ? driver OFF (actiu en LOW)
		break;
	}
}
