/*
 * q2.h
 *
 * Created: 31/07/2025 19:06:25
 *  Author: adrie
 */ 

#ifndef Q2_H_
#define Q2_H_

extern volatile int step_count_q2;
extern volatile int mov_index_q2;

extern volatile uint8_t MOV_Q2;
extern volatile uint8_t HM_Q2;

void homing_q2(void);
void moviment_loop_q2(void);

#endif /* Q2_H_ */