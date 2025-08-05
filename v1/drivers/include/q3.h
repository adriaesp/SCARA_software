/*
 * q3.h
 *
 * Created: 31/07/2025 19:06:25
 *  Author: adrie
 */ 

#ifndef Q3_H_
#define Q3_H_

extern volatile int step_count_q3;
extern volatile int mov_index_q3;

extern volatile uint8_t MOV_Q3;
extern volatile uint8_t HM_Q3;

void homing_q3(void);
void moviment_loop_q3(void);

#endif /* Q3_H_ */