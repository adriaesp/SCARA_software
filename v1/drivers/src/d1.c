/*
 * d1.c
 *
 * Created: 07/08/2025 11:23:44
 *  Author: adrie
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

#include "d1.h"
#include "hardware_config.h"
#include "punts.h"
#include "calc_moviment.h"
#include "moviment.h"

volatile uint16_t step_count_d1 = 0;
volatile uint8_t mov_index_d1 = 0;
volatile uint8_t MOV_D1 = 0;
volatile uint8_t HM_D1 = 1;
volatile uint8_t ACABAT_D1 = 0;
volatile uint8_t mov_acabat_d1 = 0;

// ISR PWM. Genera steps per al motor D1 (Fq: 1kHz)
ISR(TIMER4_COMPA_vect) {
	step_count_d1++;
	if (step_count_d1 >= llista_d1[mov_index].passos) {
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

			case 1:
			step_count_d1 = 0;
			TCNT4 = 0;
			llista_d1[mov_index].passos = 65000;
			TCCR4A |= (1 << COM4A1);
			HM_D1 = 0;
			break;

			case 2:  // Tornar enrere
			PORTD &= ~(1 << DIR_d1); // CW
			step_count_d1 = 0;
			TCNT4 = 0;
			llista_d1[mov_index].passos = 30000;

			PCMSK2 &= ~(1 << PCINT23);  // ? Desactiva interrupció per PD7
			HM_D1 = 0;
			break;

			case 3:
			TIMSK4 &= ~(1 << OCIE4A);
			TCCR4A &= ~(1 << COM4A1);

			PCMSK2 |= (1 << PCINT23);   // ? Reactiva interrupció
			ACABAT_D1 = 1;
			MOV_D1 = 0;
			step_count_d1 = 0;
			break;
		}
	}
}

void mou_d1(void) {
	switch (MOV_D1) {
		case 0: // En moviment
		break;

		case 1:	// Inicia moviment
		step_count_d1 = 0;
		TCNT4 = 0;

		if (llista_d1[mov_index].dir == 1) {
			PORTD &= ~(1 << DIR_d1); // CW
			} else {
			PORTD |= (1 << DIR_d1); // CCW
		}

		MOV_D1 = 0;
		TIMSK4 |= (1 << OCIE4A);
		TCCR4A |= (1 << COM4A1);
		break;

		case 2: // Botó deixat anar
		if (PINE & (1 << FC_d1)) {
			MOV_D1 = 1;
			TCCR4A |= (1 << COM4A1);
			} else {
			TCCR4A &= ~(1 << COM4A1);
		}
		break;

		case 3: // Final de moviment
		PORTD |= (1 << EN_d1);
		break;
	}
}
