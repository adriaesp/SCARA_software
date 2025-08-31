/*
 *
 * calc_moviment.h
 */

#ifndef CALC_MOVIMENT_H
#define CALC_MOVIMENT_H

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "punts.h"

#define L1 0.0f     // mm, offset vertical
#define L2 7.7f    // mm, Proximal
#define L3 12.6f    // mm, Distal
#define ELBOW_UP 1  // 1 = elbow-up

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef DEG
#define DEG(x) ((x) * 180.0f / (float)M_PI)
#endif

// Nova estructura per al resultat de c_inversa
typedef struct {
    float theta2_deg;
    float theta3_deg;
    float d1_mm;
    bool ok;
} InversaResultat;

int elbow;

int calcula_pasos_q2(float graus);
int calcula_pasos_q3(float graus);
int calcula_pasos_d1(float altura);

int calcula_passos_moviments_q2(Moviment movs[]);
int calcula_passos_moviments_q3(Moviment movs[]);
int calcula_passos_moviments_d1(Moviment movs[]);

InversaResultat c_inversa(float px, float py, float pz, int elbow_up);
void genera_graus(const Taula coords[], Moviment llista_q2[], Moviment llista_q3[], Moviment llista_d1[], int max_items);

#endif /* CALC_MOVIMENT_H */
