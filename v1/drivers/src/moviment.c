/*
 * moviment.c
 *
 * Created: 26/07/2025 12:30:47
 *  Author: adrie
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "moviment.h"
#include "timer0_delay.h"
#include "hardware_config.h"

Moviment movs[] = {
	{110.0, 0, 1},
	{110.0, 0, 0},
	{110, 0, 0},
	{110, 0, 1},
	{50, 0, 0},
	{50, 0, 1},
	{50, 0, 1},
	{50, 0, 0},
	{-1.0f, 0}
};



volatile int step_count = 0;
volatile int mov_index = 0;
volatile uint8_t MOV = 0;

uint8_t max_moves = 0;

int calcula_pasos(float graus) {
	return (int)(5766.0 * (graus / 360.0));
}

void calcula_passos_moviments(void) {
	for (int i = 0;movs[i].graus != -1.0f; i++) {
		movs[i].passos = calcula_pasos(movs[i].graus);
		max_moves = i;
	}
	
	
}


// ISR PWM. Genera steps (polsos) per al motor. Fq: 1Khz; Dty: 50%.
ISR(TIMER1_COMPA_vect) {
	step_count++;
	if (step_count >= movs[mov_index].passos) {
		MOV = 1;
	}
}

ISR(PCINT0_vect) {
 	if(MOV != 4)
	{
		MOV = 3;
	}
	
}



void homing(void){
	if (PINB & (1 << PINB3)) // Homing de q2
	{
		TCNT1 = 0;
		mov_index = 0;
		movs[mov_index].passos = 5766;		// posem un limit de 360º de gir del q2 (no arribarà mai)
		TCCR1A |= (1 << COM1A1); 
	
		while(MOV !=3){}
			
		// Hem topat FC_q2
		
		PORTB ^= (1 << DIR);  // Invertir gir
		step_count = 0;
		TCNT1 = 0;
		
		movs[mov_index].passos = 1920;	// 1stp = 0,0625º de q2. 120 = 1920. 
		while (MOV != 1){}
		TCCR1A &= ~(1 << COM1A1);		// Para timer1
		_delay_ms(1000);
		TCNT1 = 0;
		//TCCR1A |= (1 << COM1A1);
	}
}


void moviment_loop(void) {
	switch (MOV) {
		case 0: // En moviment
		break;

		case 1: // Atura PWM. Seq no acabada
		TCCR1A &= ~(1 << COM1A1); 
		if (delay_ms(1000)) {
			mov_index++;
			MOV = 2;
		}
		break;

		case 2:
		if (mov_index <= max_moves) {
			step_count = 0;
			TCNT1 = 0;
			TCCR1A |= (1 << COM1A1); // Reactiva PWM
			if(movs[mov_index].dir == 1)
			{
				PORTB &= ~(1 << DIR);		// Direcció CW				
			}
			else 
			{
				PORTB |= (1 << DIR);		// Direcció CCW	
			}
			MOV = 0;
			} else {
			MOV = 4;
		}
		break;

		case 3:
		// Llegim quin pin polsat
		if (PINB & (1 << PINB3)) {
			MOV = 2;						// botó no polsat (pull-up actiu, pin alt)
			TCCR1A |= (1 << COM1A1);		// Reactiva PWM
			} else {
			TCCR1A &= ~(1 << COM1A1);		// Para timer1
		}
		break;

		case 4:
		PORTB |= (1 << EN);
		// Fi de moviment
		break;
	}
}