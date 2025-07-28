/*
 * hradware_config.h
 *
 * Created: 26/07/2025 12:40:36
 *  Author: adrie
 */ 


#ifndef HARDWARE_H
#define HARDWARE_H

#define DIR PB0
#define STEP PB1
#define EN PB2
#define MS2 PC4
#define MS1 PC5
#define FC_q2 PB3

void int0_init(void);
void setup_driver(void);

#endif