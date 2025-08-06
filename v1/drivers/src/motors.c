/*
 * motors.c
 *
 * Created: 05/08/2025 17:11:32
 *  Author: adrie
 */ 


#include "motors.h"
#include "moviment.h"
#include "timer0_delay.h"

Moviment movs_q2[] = { {720.0, 0, 0}, {720.0, 0, 1} };
Moviment movs_q3[] = { {360.0, 0, 1}, {360.0, 0, 0} };

Motor motors[] = {
	{ movs_q2, 2, 0, 0, 0, PB0, PB2, &PORTB, &PORTB },
	{ movs_q3, 2, 0, 0, 0, PD2, PD3, &PORTD, &PORTD }
};

const uint8_t num_motors = sizeof(motors) / sizeof(motors[0]);

void moviment_loop_motor(Motor* m) {

	switch (m->MOV) {
		case 0:
		break;
		case 1:
		TCCR1A &= ~(1 << COM1A1);
		if (delay_ms(1000)) {
			m->mov_index++;
			m->MOV = 2;
		}
		break;
		case 2:
		if (m->mov_index < m->num_movs) {
			m->step_count = 0;
			TCNT1 = 0;
			TCCR1A |= (1 << COM1A1);
			if (m->movs[m->mov_index].dir)
			*(m->port_dir) &= ~(1 << m->dir_pin);
			else
			*(m->port_dir) |= (1 << m->dir_pin);
			m->MOV = 0;
			} else {
			m->MOV = 4;
		}
		break;
		case 4:
		*(m->port_en) |= (1 << m->en_pin);
		break;
	}
}
