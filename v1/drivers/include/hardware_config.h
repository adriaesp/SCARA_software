/*
 * hardware_config.h
 *
 * General hardware description for three stepper motors.
 */

#ifndef HARDWARE_H
#define HARDWARE_H

#include <avr/io.h>

<<<<<<< Updated upstream
typedef struct {
    volatile uint8_t *port;   // PORT register for the motor
    volatile uint8_t *ddr;    // DDR register for the motor
    uint8_t dir;              // direction pin bit
    uint8_t step;             // step pin bit
    uint8_t en;               // enable pin bit
} MotorHW;

extern const MotorHW motor_hw[3];
=======
// Driver Q2
#define DIR_q2 PB0
#define STEP_q2 PB1
#define EN_q2 PD4
#define MS2_q2 PC1
#define MS1_q2 PC0
#define FC_q2 PE0
                                                   
// Driver Q3
#define DIR_q3 PD2
#define STEP_q3 PD0
#define EN_q3 PD5
#define MS2_q3 PC3
#define MS1_q3 PC2
#define FC_q3  PE1

// Driver D1
#define DIR_d1 PD3
#define STEP_d1 PD1
#define EN_d1 PD6
#define MS2_d1 PC6
#define MS1_d1 PC5
#define FC_d1  PE2
>>>>>>> Stashed changes

void int0_init(void);
void setup_driver(void);

#endif

