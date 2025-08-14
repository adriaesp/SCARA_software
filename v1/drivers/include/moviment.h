/*
 * moviment.h
 *
 * Created: 06/08/2025 12:25:36
 *  Author: adrie
 */

#ifndef MOVIMENT_H_
#define MOVIMENT_H_

#include <stdint.h>

// Variables globals compartides entre Q2 i Q3
extern volatile uint8_t mov_acabat_q2;
extern volatile uint8_t mov_acabat_q3;

extern volatile uint8_t MOV_Q2;
extern volatile uint8_t MOV_Q3;

extern volatile uint8_t mov_index;
extern uint8_t max_moves;

// Funció del bucle de sincronització
void moviment(void);

#endif /* MOVIMENT_H_ */