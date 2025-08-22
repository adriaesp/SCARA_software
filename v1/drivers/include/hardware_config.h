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
#define MS2_q2 PC1
#define MS1_q2 PC0
#define FC_q2 PE2
                                                   
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
#define FC_d1  PE0

void setup_driver_q2(void); 
void setup_driver_q3(void);
void setup_driver_d1(void);

#endif