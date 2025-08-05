#include <avr/io.h>
#include <avr/interrupt.h>
#include "moviment_q3.h"
#include "hardware_config.h"

Moviment movs_q3[] = {
    {90, 0, 1},
    {90, 0, 0},
    {-1.0f, 0}
};

volatile int step_count_q3 = 0;
volatile int mov_index_q3 = 0;
volatile uint8_t MOV_q3 = 0;
volatile uint8_t HM_q3 = 1;
volatile uint8_t ACABAT_q3 = 0;

void calcula_passos_moviments_q3(void) {
    for (int i = 0; movs_q3[i].graus != -1.0f; i++) {
        movs_q3[i].passos = calcula_pasos(movs_q3[i].graus);
    }
}

ISR(TIMER3_COMPA_vect) {
    step_count_q3++;
    if (step_count_q3 >= movs_q3[mov_index_q3].passos) {
        MOV_q3 = 1;
        HM_q3 = 3;
    }
}

void homing_q3(void) {
    while (!ACABAT_q3) {
        switch (HM_q3) {
            case 0:
                break;
            case 1:
                TCNT3 = 0;
                mov_index_q3 = 0;
                movs_q3[mov_index_q3].passos = 5766;
                TCCR3A |= (1 << COM3A1);
                HM_q3 = 0;
                break;
            case 2:
                PORTB &= ~(1 << DIR_Q3);
                step_count_q3 = 0;
                TCNT3 = 0;
                movs_q3[mov_index_q3].passos = 1920;
                PCMSK0 &= ~(1 << PCINT4);
                HM_q3 = 0;
                break;
            case 3:
                TIMSK3 &= ~(1 << OCIE3A);
                cli();
                TCCR3A &= ~(1 << COM3A1);
                PCMSK0 |= (1 << PCINT4);
                ACABAT_q3 = 1;
                PORTB |= (1 << EN_Q3);
                _delay_ms(1000);
                MOV_q3 = 0;
                step_count_q3 = 0;
                break;
        }
    }
}

void moviment_loop_q3(void) {
    switch (MOV_q3) {
        case 0:
            break;
        case 1:
            TCCR3A &= ~(1 << COM3A1);
            TIMSK3 &= ~(1 << OCIE3A);
            MOV_q3 = 2;
            break;
        case 2:
            if (mov_index_q3 <= 2) {
                mov_index_q3++;
                step_count_q3 = 0;
                TCNT3 = 0;
                TIMSK3 |= (1 << OCIE3A);
                TCCR3A |= (1 << COM3A1);
                if (movs_q3[mov_index_q3].dir == 1)
                    PORTB &= ~(1 << DIR_Q3);
                else
                    PORTB |= (1 << DIR_Q3);
                MOV_q3 = 0;
            } else {
                MOV_q3 = 4;
            }
            break;
        case 3:
            if (PINB & (1 << PINB4)) {
                MOV_q3 = 2;
                TCCR3A |= (1 << COM3A1);
            } else {
                TCCR3A &= ~(1 << COM3A1);
            }
            break;
        case 4:
            PORTB |= (1 << EN_Q3);
            break;
    }
}
