/*
 * moviment.c
 *
 * Movement handling for three stepper motors.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "moviment.h"
#include "timer0_delay.h"

// Example movement tables for each motor
static Moviment movs_m1[] = {
        {720.0, 0, 0},
        {720.0, 0, 1}
};

static Moviment movs_m2[] = {
        {360.0, 0, 0},
        {360.0, 0, 1}
};

static Moviment movs_m3[] = {
        {180.0, 0, 0},
        {180.0, 0, 1}
};

Motor motors[3];

static int calcula_pasos(float graus) {
        return (int)(1600.0 * (graus / 360.0));
}

static void calcula_passos_moviments(Motor *m) {
        for (int i = 0; i < m->max_moves; i++) {
                m->movs[i].passos = calcula_pasos(m->movs[i].graus);
        }
}

void init_motors(void) {
        motors[0].movs = movs_m1;
        motors[0].max_moves = sizeof(movs_m1) / sizeof(movs_m1[0]);
        motors[0].hw = &motor_hw[0];
        motors[0].step_count = 0;
        motors[0].mov_index = 0;
        motors[0].MOV = 0;
        calcula_passos_moviments(&motors[0]);

        motors[1].movs = movs_m2;
        motors[1].max_moves = sizeof(movs_m2) / sizeof(movs_m2[0]);
        motors[1].hw = &motor_hw[1];
        motors[1].step_count = 0;
        motors[1].mov_index = 0;
        motors[1].MOV = 0;
        calcula_passos_moviments(&motors[1]);

        motors[2].movs = movs_m3;
        motors[2].max_moves = sizeof(movs_m3) / sizeof(movs_m3[0]);
        motors[2].hw = &motor_hw[2];
        motors[2].step_count = 0;
        motors[2].mov_index = 0;
        motors[2].MOV = 0;
        calcula_passos_moviments(&motors[2]);
}

// Timer interrupt toggles step pins and counts steps for each motor
ISR(TIMER1_COMPA_vect) {
        static uint8_t toggle = 0;
        toggle ^= 1;

        for (int i = 0; i < 3; i++) {
                Motor *m = &motors[i];
                if (m->MOV != 0) {
                        continue; // motor not moving
                }
                if (toggle) {
                        *(m->hw->port) |= (1 << m->hw->step);
                        m->step_count++;
                        if (m->step_count >= m->movs[m->mov_index].passos) {
                                m->MOV = 1;
                        }
                } else {
                        *(m->hw->port) &= ~(1 << m->hw->step);
                }
        }
}

// Core movement state machine for one motor
static void moviment_loop_motor(Motor *m) {
        switch (m->MOV) {
                case 0:
                        break;
                case 1:
                        if (delay_ms(1000)) {
                                m->mov_index++;
                                m->MOV = 2;
                        }
                        break;
                case 2:
                        if (m->mov_index < m->max_moves) {
                                m->step_count = 0;
                                if (m->movs[m->mov_index].dir == 1) {
                                        *(m->hw->port) &= ~(1 << m->hw->dir);
                                } else {
                                        *(m->hw->port) |= (1 << m->hw->dir);
                                }
                                m->MOV = 0;
                        } else {
                                m->MOV = 4;
                        }
                        break;
                case 4:
                        *(m->hw->port) |= (1 << m->hw->en);
                        break;
        }
}

void moviment_loop(void) {
        for (int i = 0; i < 3; i++) {
                moviment_loop_motor(&motors[i]);
        }
}

