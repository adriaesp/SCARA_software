/*
 * motors.h
 *
 * Created: 05/08/2025 17:12:25
 *  Author: adrie
 */ 


#ifndef MOTORS_H
#define MOTORS_H

#include <avr/io.h>
#include <stdint.h>
#include "moviment.h"

typedef struct {
	Moviment* movs;
	int num_movs;

	volatile int step_count;
	volatile int mov_index;
	volatile uint8_t MOV;

	uint8_t dir_pin;
	uint8_t en_pin;
	volatile uint8_t* port_dir;
	volatile uint8_t* port_en;
} Motor;

extern Motor motors[];
extern const uint8_t num_motors;
void moviment_loop_motor(Motor* m);

#endif