/*
 * motr_config.h
 *
 * Created: 05/08/2025 16:30:34
 *  Author: adrie
 */ 


#ifndef MOTORS_CONFIG_H_
#define MOTORS_CONFIG_H_

#include "steppers.h"

// Declaració de motors com a externs
extern StepperMotor motor_q2;
extern StepperMotor motor_q3;

extern volatile int step_count_q2, step_count_q3;
extern volatile int mov_index_q2, mov_index_q3;
extern volatile uint8_t MOV_Q2, HM_Q2, ACABAT_Q2;
extern volatile uint8_t MOV_Q3, HM_Q3, ACABAT_Q3;

extern StepperMotor motors[];
extern uint8_t num_motors;

#endif