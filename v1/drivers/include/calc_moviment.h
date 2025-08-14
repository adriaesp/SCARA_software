/*
 * moviment.h
 *
 * Created: 26/07/2025 12:28:27
 *  Author: adrie
 */ 


#ifndef CALC_MOVIMENT_H
#define CALC_MOVIMENT_H

#include <stdint.h>
#include <util/delay.h> 

#include "punts.h"


int calcula_passos_moviments_q2(Moviment movs[]);
int calcula_pasos_q2(float graus);

int calcula_passos_moviments_q3(Moviment movs[]);
int calcula_pasos_q3(float graus);

int calcula_passos_moviments_d1(Moviment movs[]);
int calcula_pasos_d1(float altura);

#endif

/*

extern volatile int step_count;
extern volatile int mov_index;


extern volatile uint8_t MOV;
extern volatile uint8_t HM;


void homing(void);
void moviment_loop(void);
*/