/*
 * q3.h
 *
 * Created: 31/07/2025 19:06:25
 *  Author: adrie
 */

#ifndef Q3_H_
#define Q3_H_

#include <stdint.h>

// Variables globals definides a q3.c
extern volatile uint16_t step_count_q3;
extern volatile uint8_t mov_index_q3;

extern volatile uint8_t MOV_Q3;
extern volatile uint8_t HM_Q3;
extern volatile uint8_t ACABAT_Q3;
extern volatile uint8_t mov_acabat_q3;



// Funcions públiques
void homing_q3(void);
void mou_q3(void);

#endif /* Q3_H_ */
