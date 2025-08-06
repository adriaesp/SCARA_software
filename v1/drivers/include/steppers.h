/*
 * steppers.h
 *
 * Created: 05/08/2025 16:26:54
 *  Author: adrie
 */ 


// steppers.h
#ifndef STEPPERS_H_
#define STEPPERS_H_

#include <avr/io.h>
#include "punts.h"

typedef struct {
	Moviment* movs;
	volatile int* step_count;
	volatile int* mov_index;
	volatile uint8_t* MOV;
	volatile uint8_t* HM;
	volatile uint8_t* ACABAT;

	uint8_t dir_pin;
	uint8_t step_pin;
	uint8_t en_pin;
	volatile uint8_t* port_dir;
	volatile uint8_t* port_step;
	volatile uint8_t* port_en;

	volatile uint8_t* tccr_a;
	volatile uint8_t* timsk;
	volatile uint16_t* tcnt;
	uint8_t pwm_enable_bit;
	uint8_t timer_int_bit;

	uint8_t limit_switch_pinb_bit;
} StepperMotor;

void moviment_loop_motor(StepperMotor* m, uint8_t max_moves);
void homing_motor(StepperMotor* m, uint16_t passos_inici, uint16_t passos_retrocés);

#endif /* STEPPERS_H_ */