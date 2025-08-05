/*
 * moviment.h
 *
 * Generic movement control for multiple stepper motors.
 */

#ifndef MOVIMENT_H
#define MOVIMENT_H

#include <stdint.h>
#include "hardware_config.h"

typedef struct {
        float graus;   // desired rotation in degrees
        int passos;    // steps calculated from graus
        int dir;       // direction flag
} Moviment;

typedef struct {
        Moviment *movs;
        uint8_t max_moves;
        volatile int step_count;
        volatile int mov_index;
        volatile uint8_t MOV; // state machine variable
        const MotorHW *hw;    // hardware pins
} Motor;

extern Motor motors[3];

void init_motors(void);
void moviment_loop(void);

#endif

