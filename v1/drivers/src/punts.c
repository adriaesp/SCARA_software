/*
 * punts.c
 *
 * Created: 31/07/2025 18:15:36
 *  Author: adrie
 */ 


#include "punts.h"


Moviment llista_q2[] = {
	{10, 0, 0, 1},
	{90, 0, 0, 0},
	{90, 0, 0, 1},
 	{90, 0, 0, 1},
// 	{45, 0, 0, 0},
// 	{45, 0, 0, 1},
// 	{50, 0, 0, 1},
	{-1.0f, 0, 0, 0}
};

Moviment llista_q3[] = {
	{10, 0, 0, 1},
	{0.1, 0, 0, 0},
	{0.1, 0, 0, 0},
	{0.1, 0, 0, 0},
// 	{90, 0, 0, 1},
// 	{90, 0, 0, 0},
// 	{90, 0, 0, 0},
// 	{90, 0, 0, 1},
// 	{50, 0, 0, 1},
	{-1.0f, 0, 0, 0}
};

Moviment llista_d1[] = {
	{0, 5, 0, 1},
	{0, 5, 0, 1},
	{0, 10, 0, 0},
 	{0, 5	, 0, 1},
	// 	{90, 0, 1},
	// 	{90, 0, 0},
	// 	{90, 0, 0},
	// 	{90, 0, 1},
	// 	{50, 0, 1},
	{0, -1.0f, 0, 0}
};



int llegir_punts(const char* nom_fitxer, double pos[][3]) {
	FILE* fitxer = fopen(nom_fitxer, "r");
	if (!fitxer) {
		perror("No s'ha pogut obrir el fitxer");
		return -1;
	}

	int i = 0;
	while (fscanf(fitxer, " { %lf , %lf , %lf } ,", &pos[i][0], &pos[i][1], &pos[i][2]) == 3) {
	i++;
	if (i >= MAX_PUNTS) break;
}

fclose(fitxer);
return i;  // retorna el nombre de punts llegits
}