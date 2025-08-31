/*
 * punts.h
 *
 * Created: 31/07/2025 18:09:51
 *  Author: adrie
 */ 

#ifndef PUNTS_H_
#define PUNTS_H_

#include <stdio.h>
#define MAX_PUNTS 20

typedef struct {
	float graus;
	float altura;
	long int passos;
	int dir;
} Moviment;

typedef struct {
	float X;
	float Y;
	float Z;
} Taula;


extern Moviment llista_q2[];
extern Moviment llista_q3[];
extern Moviment llista_d1[];
extern Taula coordenades[];

#endif /* PUNTS_H_ */