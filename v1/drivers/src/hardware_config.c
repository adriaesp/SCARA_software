/*
 * hardware_config.c
 *
 * Setup of pins and timer for three stepper motors.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "hardware_config.h"

// Hardware description for the three motors
const MotorHW motor_hw[3] = {
    { &PORTB, &DDRB, PB0, PB1, PB2 }, // Motor 1 on PORTB
    { &PORTC, &DDRC, PC0, PC1, PC2 }, // Motor 2 on PORTC
    { &PORTD, &DDRD, PD0, PD1, PD2 }  // Motor 3 on PORTD
};

void int0_init(void) {
        DDRD &= ~(1 << FC_Z);
        PORTD &= ~(1 << FC_Z);
        EICRA |= (1 << ISC00);
        EICRA &= ~(1 << ISC01);
        EIMSK |= (1 << INT0);
}

void setup_driver(void) {
        for (int i = 0; i < 3; i++) {
                *(motor_hw[i].ddr) |= (1 << motor_hw[i].dir) |
                                      (1 << motor_hw[i].step) |
                                      (1 << motor_hw[i].en);
                *(motor_hw[i].port) |= (1 << motor_hw[i].dir);
                *(motor_hw[i].port) &= ~(1 << motor_hw[i].en);
        }

        DDRD &= ~(1 << FC_Z);   // limit switch input
        PORTD |= (1 << FC_Z);

        TCCR1A = (1 << WGM11); // no hardware toggle, manual step
        TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8

        TIMSK1 |= (1 << OCIE1A); // enable compare match interrupt

        ICR1 = 1999;  // Fq: 1Khz
        OCR1A = 999;  // Dty: 50%
        sei();
}

