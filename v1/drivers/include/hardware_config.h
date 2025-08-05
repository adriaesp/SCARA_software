/*
 * hardware_config.h
 *
 * General hardware description for three stepper motors.
 */

#ifndef HARDWARE_H
#define HARDWARE_H

#include <avr/io.h>

typedef struct {
    volatile uint8_t *port;   // PORT register for the motor
    volatile uint8_t *ddr;    // DDR register for the motor
    uint8_t dir;              // direction pin bit
    uint8_t step;             // step pin bit
    uint8_t en;               // enable pin bit
} MotorHW;

extern const MotorHW motor_hw[3];

void int0_init(void);
void setup_driver(void);

#endif

