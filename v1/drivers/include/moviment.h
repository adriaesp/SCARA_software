/*
 * moviment.h
 *
 * Created: 26/07/2025 12:28:27
 *  Author: adrie
 */ 


#ifndef MOVIMENT_H
#define MOVIMENT_H

#include <stdint.h>
#include <util/delay.h> 

typedef struct {
	float graus;
	int passos;
	int dir;
} Moviment;

extern Moviment movs[];

extern uint8_t max_moves;

extern volatile int step_count;
extern volatile int mov_index;
extern volatile uint8_t MOV;

void calcula_passos_moviments(void);
void homing(void);
void moviment_loop(void);


#endif