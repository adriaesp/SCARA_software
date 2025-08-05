#include <avr/io.h>
#include <avr/interrupt.h>
#include "moviment_d1.h"
#include "moviment.h"
#include "hardware_config.h"

Moviment movs_d1[] = {
    {90, 0, 1},
    {90, 0, 0},
    {-1.0f, 0}
};

volatile int step_count_d1 = 0;
volatile int mov_index_d1 = 0;
volatile uint8_t MOV_d1 = 0;
volatile uint8_t HM_d1 = 1;
volatile uint8_t ACABAT_d1 = 0;

void calcula_passos_moviments_d1(void) {
    for (int i = 0; movs_d1[i].graus != -1.0f; i++) {
        movs_d1[i].passos = calcula_pasos(movs_d1[i].graus);
    }
}

ISR(TIMER4_COMPA_vect) {
    step_count_d1++;
    if (step_count_d1 >= movs_d1[mov_index_d1].passos) {
        MOV_d1 = 1;
        HM_d1 = 3;
    }
}

void homing_d1(void) {
    while (!ACABAT_d1) {
        switch (HM_d1) {
            case 0:
                break;
            case 1:
                TCNT4 = 0;
                mov_index_d1 = 0;
                movs_d1[mov_index_d1].passos = 5766;
                TCCR4A |= (1 << COM4A1);
                HM_d1 = 0;
                break;
            case 2:
                PORTB &= ~(1 << DIR_D1);
                step_count_d1 = 0;
                TCNT4 = 0;
                movs_d1[mov_index_d1].passos = 1920;
                PCMSK0 &= ~(1 << PCINT5);
                HM_d1 = 0;
                break;
            case 3:
                TIMSK4 &= ~(1 << OCIE4A);
                cli();
                TCCR4A &= ~(1 << COM4A1);
                PCMSK0 |= (1 << PCINT5);
                ACABAT_d1 = 1;
                PORTB |= (1 << EN_D1);
                _delay_ms(1000);
                MOV_d1 = 0;
                step_count_d1 = 0;
                break;
        }
    }
}

void moviment_loop_d1(void) {
    switch (MOV_d1) {
        case 0:
            break;
        case 1:
            TCCR4A &= ~(1 << COM4A1);
            TIMSK4 &= ~(1 << OCIE4A);
            MOV_d1 = 2;
            break;
        case 2:
            if (mov_index_d1 <= 2) {
                mov_index_d1++;
                step_count_d1 = 0;
                TCNT4 = 0;
                TIMSK4 |= (1 << OCIE4A);
                TCCR4A |= (1 << COM4A1);
                if (movs_d1[mov_index_d1].dir == 1)
                    PORTB &= ~(1 << DIR_D1);
                else
                    PORTB |= (1 << DIR_D1);
                MOV_d1 = 0;
            } else {
                MOV_d1 = 4;
            }
            break;
        case 3:
            if (PINB & (1 << PINB5)) {
                MOV_d1 = 2;
                TCCR4A |= (1 << COM4A1);
            } else {
                TCCR4A &= ~(1 << COM4A1);
            }
            break;
        case 4:
            PORTB |= (1 << EN_D1);
            break;
    }
}
