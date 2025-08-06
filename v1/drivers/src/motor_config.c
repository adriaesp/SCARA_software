/*
 * motor_config.c
 *
 * Created: 05/08/2025 16:32:47
 *  Author: adrie
 */ 


#include <avr/io.h>
#include "steppers.h"
#include "hardware_config.h"
#include "punts.h"


// Variables globals del sistema
extern StepperMotor motor_q2;
extern StepperMotor motor_q3;

extern volatile int step_count_q2, step_count_q3;
extern volatile int mov_index_q2, mov_index_q3;
extern volatile uint8_t MOV_Q2, HM_Q2, ACABAT_Q2;
extern volatile uint8_t MOV_Q3, HM_Q3, ACABAT_Q3;

StepperMotor motors[] = { motor_q2, motor_q3 };
uint8_t num_motors = 2;

StepperMotor motor_q2 = {
	.movs = llista_q2,
	.step_count = &step_count_q2,
	.mov_index = &mov_index_q2,
	.MOV = &MOV_Q2,
	.HM = &HM_Q2,
	.ACABAT = &ACABAT_Q2,
	.dir_pin = DIR_q2,
	.en_pin = EN_q2,
	.port_dir = &PORTB,
	.port_en = &PORTD,
	.tccr_a = &TCCR1A,
	.timsk = &TIMSK1,
	.tcnt = &TCNT1,
	.pwm_enable_bit = COM1A1,
	.timer_int_bit = OCIE1A,
	.limit_switch_pinb_bit = PINB2
};

StepperMotor motor_q3 = {
	.movs = llista_q3,
	.step_count = &step_count_q3,
	.mov_index = &mov_index_q3,
	.MOV = &MOV_Q3,
	.HM = &HM_Q3,
	.ACABAT = &ACABAT_Q3,
	.dir_pin = DIR_q3,
	.en_pin = EN_q3,
	.port_dir = &PORTD,
	.port_en = &PORTD,
	.tccr_a = &TCCR1A,
	.timsk = &TIMSK1,
	.tcnt = &TCNT1,
	.pwm_enable_bit = COM1A1,
	.timer_int_bit = OCIE1A,
	.limit_switch_pinb_bit = PINB3
};