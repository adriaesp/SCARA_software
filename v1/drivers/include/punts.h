/*
 * punts.h
 *
 * Created: 31/07/2025 18:09:51
 *  Author: adrie
 */ 

#ifndef PUNTS_H_
#define PUNTS_H_

typedef struct {
	float graus;
	int passos;
	int dir;
} Moviment;

extern Moviment llista_q2[];
extern Moviment llista_q3[];

#endif /* PUNTS_H_ */