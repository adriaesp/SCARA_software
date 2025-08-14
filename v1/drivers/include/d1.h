/*
 * d1.h
 *
 * Created: 07/08/2025 11:23:58
 *  Author: adrie
 */ 


#ifndef D1_H
#define D1_H

#include <stdint.h>

extern volatile uint16_t step_count_d1;
extern volatile uint8_t mov_index_d1;
extern volatile uint8_t MOV_D1;
extern volatile uint8_t HM_D1;
extern volatile uint8_t ACABAT_D1;
extern volatile uint8_t mov_acabat_d1;

void homing_d1(void);
void mou_d1(void);

#endif
