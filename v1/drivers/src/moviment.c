/*
 * moviment.c
 *
 * Created: 06/08/2025 9:38:33
 *  Author: adrie
 */ 

#include "q2.h"
#include "q3.h"
#include "d1.h"
#include "moviment.h"

volatile uint8_t mov_index = 0;

void moviment(void) {
	if (mov_acabat_q2 && mov_acabat_q3 && mov_acabat_d1) {
		if (mov_index < max_moves) {
			mov_index++;
			MOV_Q2 = 1;
			MOV_Q3 = 1;
			MOV_D1 = 1;
			} else {
			MOV_Q2 = 3;
			MOV_Q3 = 3;
			MOV_D1 = 3;
		}
		mov_acabat_q2 = 0;
		mov_acabat_q3 = 0;
		mov_acabat_d1 = 0;
	}
	mou_q2();
	mou_q3();
	mou_d1();
}