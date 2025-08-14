/*
 * q2.h
 *
 * Created: 31/07/2025 19:06:25
 *  Author: adrie
 */

#ifndef Q2_H_
#define Q2_H_

#include <stdint.h>

// Variables externes definides a q2.c
extern volatile int step_count_q2;
extern volatile int mov_index_q2;
extern volatile uint8_t MOV_Q2;
extern volatile uint8_t HM_Q2;
extern volatile uint8_t ACABAT_Q2;
extern volatile uint8_t mov_acabat_q2;


// Funcions públiques
void homing_q2(void);
void mou_q2(void);

#endif /* Q2_H_ */
