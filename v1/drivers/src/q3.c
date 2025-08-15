/*
 * q3.c
 *
 * Created: 31/07/2025 18:48:25
 *  Author: adrie
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "q3.h"
#include "q2.h"
#include "d1.h"
#include "hardware_config.h"
#include "punts.h"
#include "calc_moviment.h"
#include "moviment.h"

volatile uint16_t step_count_q3 = 0;
volatile uint8_t mov_index_q3 = 0;
volatile uint8_t MOV_Q3 = 0;
volatile uint8_t HM_Q3 = 1;
volatile uint8_t ACABAT_Q3 = 0;
volatile uint8_t mov_acabat_q3 = 0;

// ISR PWM. Genera steps (polsos) per al motor. Fq: 1Khz; Dty: 50%.
ISR(TIMER3_COMPA_vect) {
    step_count_q3++;
    if (step_count_q3 >= llista_q3[mov_index_q3].passos) {
        TCCR3A &= ~(1 << COM3A1);
        TIMSK3 &= ~(1 << OCIE3A);
        mov_acabat_q3 = 1;
        HM_Q3 = 3;
    }
}

/* PCINT de PORT E (PCINT[14:8]) ? FC_q2=PE0, FC_q3=PE1, FC_d1=PE2
   Amb pull-up activat, el final de cursa "premut" = nivell LOW ? !(PINE & (1<<PE*)) */
ISR(PCINT1_vect) {
    // FC Q2 (PE0)
    if (!(PINE & (1 << FC_q2))) {
        if (MOV_Q2 != 4) {
            MOV_Q2 = 2;
            HM_Q2  = 2;
        }
    }
    // FC Q3 (PE1)
    if (!(PINE & (1 << FC_q3))) {
        if (MOV_Q3 != 4) {
            MOV_Q3 = 3;
            HM_Q3  = 2;
        }
    }
    // FC D1 (PE2)
    if (!(PINE & (1 << FC_d1))) {
        if (MOV_D1 != 4) {
            MOV_D1 = 3;
            HM_D1  = 2;
        }
    }
}

void homing_q3(void) {
    while (!ACABAT_Q3) {
        switch (HM_Q3) {
            case 0: // Moviment
                break;

            case 1: // Config inici desplaçament
                step_count_q3 = 0;
                TCNT3 = 0;
                mov_index_q3 = 0;
                llista_q3[mov_index_q3].passos = 10152;
                TCCR3A |= (1 << COM3A1);
                HM_Q3 = 0;
                break;

            case 2: // Config desplaçament a home (canvi direcció i evita triggers)
                PORTD &= ~(1 << DIR_q3);          // CW (inverteix si cal)
                step_count_q3 = 0;
                TCNT3 = 0;
                llista_q3[mov_index_q3].passos = 3384;

                // Deshabilita PCINT de PE1 durant el moviment de homing
                PCMSK1 &= ~(1 << PCINT9);
                HM_Q3 = 0;
                break;

            case 3: // Home q3 acabat
                TIMSK3 &= ~(1 << OCIE3A);         // Timer3 INT OFF
                TCCR3A &= ~(1 << COM3A1);         // PWM OFF
                PCMSK1 |= (1 << PCINT9);          // Re-habilita PCINT de PE1
                ACABAT_Q3 = 1;
                MOV_Q3 = 0;
                step_count_q3 = 0;
                // PORTD |= (1 << EN_q3);         // opcional: deshabilitar driver (EN alt)
                break;
        }
    }
}

void mou_q3(void) {
    switch (MOV_Q3) {
        case 0: // En repòs / esperant
            break;

        case 1: // Preparar moviment
            step_count_q3 = 0;
            mov_acabat_q3 = 0;
            TCNT3 = 0;

            if (llista_q3[mov_index_q3].dir == 1) {
                PORTD &= ~(1 << DIR_q3); // CW
            } else {
                PORTD |=  (1 << DIR_q3); // CCW
            }

            MOV_Q3 = 0;
            TIMSK3 |= (1 << OCIE3A);
            TCCR3A |= (1 << COM3A1);
            break;

        case 2: // Lectura directa de FC/polsador (PE1)
            if (PINE & (1 << FC_q3)) {
                // pin alt ? no polsat ? continua
                MOV_Q3 = 1;
                TCCR3A |= (1 << COM3A1);
            } else {
                // pin baix ? FC actiu ? para
                TCCR3A &= ~(1 << COM3A1);
            }
            break;

        case 3: // Final de moviment
            PORTD |= (1 << EN_q3); // EN alt ? driver OFF (si EN és actiu LOW)
            break;
    }
}
/*

void moviment_loop_q3(void) {
	switch (MOV_Q3) {
		case 0: // En moviment
		break;

		case 1: // Atura PWM. Seq no acabada
		TCCR3A &= ~(1 << COM3A1);
		TIMSK3 &= ~(1 << OCIE3A);
		MOV_Q3 = 2;
		break;

		case 2:
		if (mov_index_q3 <= max_moves_q3) {
			mov_index_q3++;
			step_count_q3 = 0;
			TCNT3 = 0;
			TIMSK3 |= (1 << OCIE3A);		// Timer3 INT ON
			TCCR3A |= (1 << COM3A1);	// Reactiva PWM
			if (llista_q3[mov_index_q3].dir == 1) {
				PORTD &= ~(1 << DIR_q3);	// Direcció CW
				} else {
				PORTD |= (1 << DIR_q3);		// Direcció CCW
			}
			MOV_Q3 = 0;
			} else {
			MOV_Q3 = 4;
		}
		break;

		case 3:
		// Llegim quin pin polsat
		if (PINB & (1 << PINB3)) {
			MOV_Q3 = 2;						// botó no polsat (pull-up actiu, pin alt)
			TCCR3A |= (1 << COM3A1);		// Reactiva PWM
			} else {
			TCCR3A &= ~(1 << COM3A1);		// Para timer3
		}
		break;

		case 4:
		PORTD |= (1 << EN_q3);
		// Fi de moviment
		break;
	}
}
*/