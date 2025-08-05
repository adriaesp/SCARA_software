#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "moviment_q2.h"
#include "hardware_config.h"

Moviment movs_q2[] = {
    {90, 0, 1},
    {90, 0, 1},
    {90, 0, 1},
    {90, 0, 0},
    {90, 0, 0},
    {95, 0, 1},
    {-1.0f, 0}
};

volatile int step_count_q2 = 0;
volatile int mov_index_q2 = 0;
volatile uint8_t MOV_q2 = 0;
volatile uint8_t HM_q2 = 1;
volatile uint8_t ACABAT_q2 = 0;

int calcula_pasos_q2(float graus) {
    return (int)(5766.0 * (graus / 360.0));
}

void calcula_passos_moviments_q2(void) {
    for (int i = 0; movs_q2[i].graus != -1.0f; i++) {
        movs_q2[i].passos = calcula_pasos_q2(movs_q2[i].graus);
    }
}

ISR(TIMER1_COMPA_vect) {
    step_count_q2++;
    if (step_count_q2 >= movs_q2[mov_index_q2].passos) {
        MOV_q2 = 1;
        HM_q2 = 3;
    }
}

ISR(PCINT0_vect) {
    if (MOV_q2 != 4) {
        MOV_q2 = 3;
        HM_q2 = 2;
    }
}

void homing_q2(void) {
    while (!ACABAT_q2) {
        switch (HM_q2) {
            case 0:
                break;
            case 1:
                TCNT1 = 0;
                mov_index_q2 = 0;
                movs_q2[mov_index_q2].passos = 5766;
                TCCR1A |= (1 << COM1A1);
                HM_q2 = 0;
                break;
            case 2:
                PORTB &= ~(1 << DIR_Q2);
                step_count_q2 = 0;
                TCNT1 = 0;
                movs_q2[mov_index_q2].passos = 1920;
                PCMSK0 &= ~(1 << PCINT3);
                HM_q2 = 0;
                break;
            case 3:
                TIMSK1 &= ~(1 << OCIE1A);
                cli();
                TCCR1A &= ~(1 << COM1A1);
                PCMSK0 |= (1 << PCINT3);
                ACABAT_q2 = 1;
                PORTB |= (1 << EN_Q2);
                _delay_ms(1000);
                MOV_q2 = 0;
                step_count_q2 = 0;
                break;
        }
    }
}

void moviment_loop_q2(void) {
    switch (MOV_q2) {
        case 0:
            break;
        case 1:
            TCCR1A &= ~(1 << COM1A1);
            TIMSK1 &= ~(1 << OCIE1A);
            MOV_q2 = 2;
            break;
        case 2:
            mov_index_q2++;
            step_count_q2 = 0;
            TCNT1 = 0;
            TIMSK1 |= (1 << OCIE1A);
            TCCR1A |= (1 << COM1A1);
            if (movs_q2[mov_index_q2].dir == 1) {
                PORTB &= ~(1 << DIR_Q2);
            } else {
                PORTB |= (1 << DIR_Q2);
            }
            MOV_q2 = 0;
            break;
        case 3:
            if (PINB & (1 << PINB3)) {
                MOV_q2 = 2;
                TCCR1A |= (1 << COM1A1);
            } else {
                TCCR1A &= ~(1 << COM1A1);
            }
            break;
        case 4:
            PORTB |= (1 << EN_Q2);
            break;
    }
}
