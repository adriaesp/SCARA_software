/*
 * steppers.c
 *
 * Created: 05/08/2025 16:26:19
 *  Author: adrie
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "steppers.h"


ISR(TIMER1_COMPA_vect) {
	for (uint8_t i = 0; i < num_motors; i++) {
		StepperMotor* m = &motors[i];

		// Si MOV = 0, motor en moviment
		if (*(m->MOV) == 0) {
			(*(m->step_count))++;

			// Generar pols de STEP
			*(m->port_step) |= (1 << m->step_pin);
			*(m->port_step) &= ~(1 << m->step_pin);

			if (*(m->step_count) >= m->movs[*(m->mov_index)].passos) {
				*(m->MOV) = 1;
				*(m->HM) = 3;
			}
		}
	}
}

void moviment_loop_motor(StepperMotor* m, uint8_t max_moves) {
	switch (*(m->MOV)) {
		case 0:
		break;

		case 1:
		*(m->tccr_a) &= ~(1 << m->pwm_enable_bit);
		*(m->timsk) &= ~(1 << m->timer_int_bit);
		*(m->MOV) = 2;
		break;

		case 2:
		if (*(m->mov_index) <= max_moves) {
			(*(m->mov_index))++;
			*(m->step_count) = 0;
			*(m->tcnt) = 0;

			*(m->timsk) |= (1 << m->timer_int_bit);
			*(m->tccr_a) |= (1 << m->pwm_enable_bit);

			if (m->movs[*(m->mov_index)].dir == 1)
			*(m->port_dir) &= ~(1 << m->dir_pin);
			else
			*(m->port_dir) |= (1 << m->dir_pin);

			*(m->MOV) = 0;
			} else {
			*(m->MOV) = 4;
		}
		break;

		case 3:
		if (PINB & (1 << m->limit_switch_pinb_bit)) {
			*(m->MOV) = 2;
			*(m->tccr_a) |= (1 << m->pwm_enable_bit);
			} else {
			*(m->tccr_a) &= ~(1 << m->pwm_enable_bit);
		}
		break;

		case 4:
		*(m->port_en) |= (1 << m->en_pin);
		break;
	}
}
