#ifndef MOVIMENT_Q2_H
#define MOVIMENT_Q2_H

#include <stdint.h>

typedef struct {
    float graus;
    int passos;
    int dir;
} Moviment;

extern Moviment movs_q2[];

extern volatile int step_count_q2;
extern volatile int mov_index_q2;
extern volatile uint8_t MOV_q2;
extern volatile uint8_t HM_q2;
extern volatile uint8_t ACABAT_q2;

void calcula_passos_moviments_q2(void);
void homing_q2(void);
void moviment_loop_q2(void);

#endif
