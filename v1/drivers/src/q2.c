/*
 * q2.c
 *
 * Created: 31/07/2025 18:48:25
 *  Author: adrie
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "q2.h"
#include "q3.h"
#include "hardware_config.h"
#include "punts.h"
#include "calc_moviment.h"

volatile int step_count_q2 = 0;
volatile int mov_index_q2 = 0;
volatile uint8_t MOV_Q2 = 0;
volatile uint8_t HM_Q2 = 1;
volatile uint8_t ACABAT_Q2 = 0;

extern uint8_t max_moves_q2;


// ISR PWM. Genera steps (polsos) per al motor. Fq: 1Khz; Dty: 50%.
ISR(TIMER1_COMPA_vect) {
	step_count_q2++;
	if (step_count_q2 >= llista_q2[mov_index_q2].passos) {
		MOV_Q2 = 1;
		HM_Q2 = 3;
	}
}

/*
ISR(PCINT0_vect) {
	if(MOV_Q2 != 4)
	{
		MOV_Q2 = 3;
		HM_Q2 = 2;
	}

}
*/


void homing_q2(void){
	PORTD |= (1 << EN_q3);
	while(!ACABAT_Q2)
	{
		switch (HM_Q2){
			case 0:		// Moviment
			break;

			case 1:		// Config inici desplaçament
 			step_count_q2 = 0;
			mov_index_q2 = 0;
			llista_q2[mov_index_q2].passos = 5766;
			TCNT1 = 0;
			TCCR1A |= (1<<COM1A1);
			HM_Q2  = 0;
			break;

			case 2:									// Config desplaçament a home
			PORTB &= ~(1<<DIR_q2);					// Canvi direcció
			step_count_q2 = 0;
			llista_q2[mov_index_q2].passos = 1920;
			TCNT1 = 0;
			PCMSK0 &= ~(1 << PCINT2);
			HM_Q2  = 0;
			break;

			case 3:							// Home q2 acabat
			TIMSK1 &= ~(1 << OCIE1A);		// Timer1 INT OFF
			TCCR1A &= ~(1<<COM1A1);			// PWM OFF
			PCMSK0 |= (1 << PCINT2);
			ACABAT_Q2 = 1; 
			mov_index_q2 ++;
			step_count_q2 = 0;
			MOV_Q2 = 0;
			break;
		}
	}
}



void moviment_loop_q2(void) {
	switch (MOV_Q2) {
		case 0: // En moviment
		break;

		case 1: // Atura PWM. Seq no acabada
		TCCR1A &= ~(1 << COM1A1);
		TIMSK1 &= ~(1 << OCIE1A);
		if (mov_index_q2 <= max_moves_q2) {
			mov_index_q2++;
			step_count_q2 = 0;
			TCNT1 = 0;
			TIMSK1 |= (1 << OCIE1A);		// Timer1 INT ON
			TCCR1A |= (1 << COM1A1);		// Reactiva PWM
			if(llista_q2[mov_index_q2].dir == 1)
			{
				PORTB &= ~(1 << DIR_q2);		// Direcció CW
			}
			else
			{
				PORTB |= (1 << DIR_q2);		// Direcció CCW
			}
			MOV_Q2 = 0;
			} else {
			MOV_Q2 = 3;
		}
		break;

		case 2:
		// Llegim quin pin polsat
		if (PINB & (1 << PINB2)) {
			MOV_Q2 = 2;						// botó no polsat (pull-up actiu, pin alt)
			TCCR1A |= (1 << COM1A1);		// Reactiva PWM
			} else {
			TCCR1A &= ~(1 << COM1A1);		// Para timer1
		}
		break;

		case 3:
		PORTD |= (1 << EN_q2);
		// Fi de moviment
		break;
	}
}


