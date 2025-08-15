/*
 * punts.h
 *
 * Created: 31/07/2025 18:09:51
 *  Author: adrie
 */ 


#include <stdio.h>
#include <stdlib.h>

#ifndef PUNTS_H_
#define PUNTS_H_
#define MAX_PUNTS 100

typedef struct {
	float graus;
	float altura;
	int passos;
	int dir;
} Moviment;

double punts [MAX_PUNTS][3];

extern Moviment llista_q2[];
extern Moviment llista_q3[];
extern Moviment llista_d1[];

int llegir_punts(const char* nom_fitxer, double punts[][3]);

#endif /* PUNTS_H_ */