/*
 * hradware_config.h
 *
 * Created: 26/07/2025 12:40:36
 *  Author: adrie
 */ 


#ifndef HARDWARE_H
#define HARDWARE_H


// Driver Q2
#define DIR_q2 PB0
#define STEP_q2 PB1
#define EN_q2 PD4
#define MS2_q2 PC0
#define MS1_q2 PC1
#define FC_q2 PB2

// Driver Q3
#define DIR_q3 PD2
#define STEP_q3 PD0
#define EN_q3 PD5
#define MS2_q3 PC2
#define MS1_q3 PC3
#define FC_q3  PB3

void int0_init(void);
void setup_driver_q2(void); 
void setup_driver_q3(void);

#endif