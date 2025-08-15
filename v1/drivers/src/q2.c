#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "q2.h"
#include "q3.h"
#include "hardware_config.h"
#include "punts.h"
#include "calc_moviment.h"
#include "moviment.h"

volatile int step_count_q2 = 0;
volatile uint8_t MOV_Q2 = 0;
volatile uint8_t HM_Q2 = 1;
volatile uint8_t ACABAT_Q2 = 0;
volatile uint8_t mov_acabat_q2 = 0;

// Afegit: índex propi de Q2 (coherent amb q2.h)
volatile int mov_index_q2 = 0;


ISR(TIMER1_COMPA_vect) {
    step_count_q2++;
    if (step_count_q2 >= llista_q2[mov_index_q2].passos) {
        TCCR1A &= ~(1 << COM1A1);   // para el toggle d'OC1A
        TIMSK1 &= ~(1 << OCIE1A);   // desactiva la INT de compare
        mov_acabat_q2 = 1;
        HM_Q2 = 3;
    }
}



void homing_q2(void){
    // Enable actiu LOW ? assegura que el driver Q2 està ON
    PORTD &= ~(1 << EN_q2);

    while(!ACABAT_Q2)
    {
        switch (HM_Q2){
            case 0:     // En moviment
                break;

            case 1:     // Config inici desplaçament
                step_count_q2 = 0;
                mov_index_q2 = 0;
                llista_q2[mov_index_q2].passos = 5766;   // valor que ja feies servir
                TCNT1 = 0;
                TCCR1A |= (1 << COM1A1);                 // activa PWM a OC1A
                HM_Q2  = 0;
                break;

            case 2:     // Config desplaçament a home (retrocés)
                PORTB &= ~(1 << DIR_q2);                 // Direcció CW (inverteix si cal)
                step_count_q2 = 0;
                llista_q2[mov_index_q2].passos = 1920;
                TCNT1 = 0;

                // Evita triggers mentre configures
                PCMSK1 &= ~(1 << PCINT8);
                HM_Q2  = 0;
                break;

            case 3:     // Home q2 acabat
                PCMSK1 |= (1 << PCINT8);                 // torna a habilitar PCINT de PE0
                ACABAT_Q2 = 1;
                step_count_q2 = 0;
                MOV_Q2 = 0;
                break;
        }
    }
}

void mou_q2(void){
    switch(MOV_Q2){
        case 0: // En repòs/esperant ordre
            break;

        case 1: // Preparar moviment cap a la posició demanada
            step_count_q2 = 0;
            TCNT1 = 0;

            if (llista_q2[mov_index_q2].dir == 1) {
                PORTB &= ~(1 << DIR_q2);   // Direcció CW
            } else {
                PORTB |= (1 << DIR_q2);    // Direcció CCW
            }

            MOV_Q2 = 0;

            TIMSK1 |= (1 << OCIE1A);       // INT Timer1 ON
            TCCR1A |= (1 << COM1A1);       // Reactiva PWM (toggle OC1A)
            break;

        case 2: // Control per polsador/FC en bucle (lectura directa)
            // Llegeix PE0 (FC_q2) amb pull-up: alt = no polsat, baix = polsat
            if (PINE & (1 << FC_q2)) {
                MOV_Q2 = 1;                 // no polsat ? continua
                TCCR1A |= (1 << COM1A1);    // assegura PWM actiu
            } else {
                TCCR1A &= ~(1 << COM1A1);   // para PWM si polsat
            }
            break;

        case 3: // Fi de moviment ? deshabilita driver si vols
            PORTD |= (1 << EN_q2);          // HIGH ? driver OFF (si EN és actiu LOW)
            break;
    }
}
/*
void moviment_loop_q2(void) {
	switch (MOV_Q2) {
		case 0: // En moviment
		break;

		case 1: // Atura PWM. Seq no acabada
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
		} 
		else 
		{
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

*/
