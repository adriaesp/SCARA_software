/*
 * moviment.c
 *
 * Created: 26/07/2025 12:30:47
 *  Author: adrie
 */ 



#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "calc_moviment.h"
#include "hardware_config.h"
#include "punts.h"
#include "USART.h"



int calcula_pasos_q2(float graus) {
	return (int)(5766.0 * (graus / 360.0));
}

int calcula_pasos_q3(float graus) {
	return (int)(10152.0 * (graus / 360.0));
}

int calcula_pasos_d1(float altura) {
	return (int32_t)(60000 * (altura / 15.5f));
}

int calcula_passos_moviments_q2(Moviment movs[]) {
	int i;
	for (i = 0;movs[i].graus != -1.0f; i++) {
		movs[i].passos = calcula_pasos_q2(movs[i].graus);
		}
		return i-1; //nombre màxim de movs
}

int calcula_passos_moviments_q3(Moviment movs[]) {
	int i;
	for (i = 0;movs[i].graus != -1.0f; i++) {
		movs[i].passos = calcula_pasos_q3(movs[i].graus);
		}
		return i-1; //nombre màxim de movs
}

int calcula_passos_moviments_d1(Moviment movs[]) {
	int i;
	for (i = 0;movs[i].altura != -1.0f; i++) {
		movs[i].passos = calcula_pasos_d1(movs[i].altura);
		}
		return i-1; //nombre màxim de movs
}



InversaResultat c_inversa(float px, float py, float pz, int elbow_up)
{
	InversaResultat result;
	result.ok = false;
	result.theta2_deg = 0.0f;
	result.theta3_deg = 0.0f;
	result.d1_mm = 0.0f;

	// D1
	float d1 = pz;
	result.d1_mm = d1;

	// s3 i c3
	float r2 = px * px + py * py;
	float c3 = (r2 - L3 * L3 - L2 * L2) / (2.0f * L3 * L2);
	c3 = fminf(fmaxf(c3, -1.0f), 1.0f);  // Clamp entre -1 i 1

	float s3_abs = sqrtf(fmaxf(0.0f, 1.0f - c3 * c3));
	float s3 = elbow_up ? s3_abs : -s3_abs;

	// theta3
	float theta3 = atan2f(s3, c3);
	result.theta3_deg = DEG(theta3);

	// theta2
	float k1 = L3 * c3 + L2;
	float k2 = L3 * s3;
	float num = k1 * py - k2 * px;
	float den = k1 * px + k2 * py;

	const float eps = 1e-7f;
	float theta2 = (fabsf(k1) < eps && fabsf(k2) < eps) ? atan2f(py, px) : atan2f(num, den);
	result.theta2_deg = DEG(theta2);

	//Normalitzar a [0, 360]
	// 	if (result.theta2_deg < 0.0f)
	// 	result.theta2_deg += 360.0f;
	// 	if (result.theta3_deg < 0.0f)
	// 	result.theta3_deg += 360.0f;

	// comprovació d’abast en XY
	float r = sqrtf(r2);
	float rmin = fabsf(L2 - L3);
	float rmax = L3 + L2;

	result.ok = (r >= (rmin - 1e-4f) && r <= (rmax + 1e-4f));
	return result;
}

/*
void genera_graus(const Taula coords[], Moviment llista_q2[], Moviment llista_q3[], Moviment llista_d1[], int max_items)
{
	float q2_anterior = 0.0f;
	float q3_anterior = 0.0f;
	float d1_anterior = 0.0f;

	int i;
	InversaResultat inv;

	for (i = 0; i < max_items; i++)
	{
		// Sentinella per final de coordenades
		if (coords[i].X == -1.0f && coords[i].Y == -1.0f && coords[i].Z == -1.0f)
		{
			break;
		}

		// Calcular la cinemàtica inversa
		inv = c_inversa(coords[i].X, coords[i].Y, coords[i].Z, ELBOW_UP);

		// Q2
		float delta_q2 = inv.theta2_deg - q2_anterior;
		if (delta_q2 > 180.0f) delta_q2 -= 360.0f;
		if (delta_q2 < -180.0f) delta_q2 += 360.0f;

		if(i==0){
			llista_q2[i].dir = 1;
		}else{
			llista_q2[i].dir = (delta_q2 >= 0.0f) ?llista_q2[i-1].dir : !llista_q2[i-1].dir ;
		}
		
		llista_q2[i].graus = fabsf(delta_q2);
		llista_q2[i].altura = 0.0f;
		llista_q2[i].passos = 0;

		
		q2_anterior = inv.theta2_deg;

		// Q3
		float delta_q3 = inv.theta3_deg - q3_anterior;
		if (delta_q3 > 180.0f) delta_q3 -= 360.0f;
		if (delta_q3 < -180.0f) delta_q3 += 360.0f;

		if(i==0){
			llista_q3[i].dir = 1;
		}else{
			llista_q3[i].dir = (delta_q3 >= 0.0f) ? llista_q3[i-1].dir : !llista_q3[i-1].dir;
		}
		
		llista_q3[i].graus = fabsf(delta_q3);
		llista_q3[i].altura = 0.0f;
		llista_q3[i].passos = 0;

		q3_anterior = inv.theta3_deg;

		// D1
		float delta_d1 = inv.d1_mm - d1_anterior;
		llista_d1[i].graus = 0.0f;
		llista_d1[i].altura = fabsf(delta_d1);
		llista_d1[i].passos = 0;
		llista_d1[i].dir = (delta_d1 >= 0.0f) ? 1 : 0;
		d1_anterior = inv.d1_mm;


		if (!inv.ok)
		{
			usart1_envias("Point NOT Achievable\r\n");
		}
	}

	if (i < max_items)
	{
		llista_q2[i] = (Moviment){.graus = -1.0f, .altura = 0.0f, .passos = 0, .dir = 0};
		llista_q3[i] = (Moviment){.graus = -1.0f, .altura = 0.0f, .passos = 0, .dir = 0};
		llista_d1[i] = (Moviment){.graus = 0.0f, .altura = -1.0f, .passos = 0, .dir = 0};
	}
}

*/

void genera_graus(const Taula coords[], Moviment llista_q2[], Moviment llista_q3[], Moviment llista_d1[], int max_items)
{
	InversaResultat resultat;
	
	int i;
	int elbow;
	
	float theta2_anterior = 0.0f;
	float theta3_anterior = 0.0f;
	float d1_anterior = 15.0f;  // o la teva posició base
	
	for (i = 0; i < max_items; i++)
	{
		// Sentinella per final de coordenades
		if (coords[i].X == -1.0f && coords[i].Y == -1.0f && coords[i].Z == -1.0f)
		{
			break;
		}
		
		elbow = (coords[i].Y < 0.0f) ? 0 : 1;
		
		resultat = c_inversa(coords[i].X,coords[i].Y,coords[i].Z, elbow);
		resultat.theta3_deg += resultat.theta2_deg;
		
		if (i==0)
		{
			//Q2
			llista_q2[i].dir = (resultat.theta2_deg < 0.0f) ? 0 : 1;
			llista_q2[i].graus= fabs(resultat.theta2_deg);
			llista_q2[i].passos = 0;
			llista_q2[i].altura = 0.0f;
			
			//Q3
			llista_q3[i].dir = (resultat.theta3_deg < 0.0f) ? 0 : 1;
			llista_q3[i].graus= fabs(resultat.theta3_deg);
			llista_q3[i].passos = 0;
			llista_q3[i].altura = 0.0f;
			
			//D1
			llista_d1[i].dir = (resultat.d1_mm < 15.0f) ? 1: 0;
			llista_d1[i].altura = resultat.d1_mm;
			llista_d1[i].passos = 0;
			llista_d1[i].graus = 0.0f;
			
		}else
		{
			// ?2
			float delta_q2 = resultat.theta2_deg - theta2_anterior;
			llista_q2[i].dir = (delta_q2 < 0.0f) ? 0 : 1;
			llista_q2[i].graus = fabsf(delta_q2);
			llista_q2[i].passos = 0;
			llista_q2[i].altura = 0.0f;

			// ?3
			float delta_q3 = resultat.theta3_deg - theta3_anterior;
			llista_q3[i].dir = (delta_q3 < 0.0f) ? 0 : 1;
			llista_q3[i].graus = fabsf(delta_q3);
			llista_q3[i].passos = 0;
			llista_q3[i].altura = 0.0f;

			// D1
			float delta_d1 = resultat.d1_mm - d1_anterior;
			llista_d1[i].dir = (delta_d1 < 0.0f) ? 0 : 1;
			llista_d1[i].altura = fabsf(delta_d1);
			llista_d1[i].passos = 0;
			llista_d1[i].graus = 0.0f;
			
			theta2_anterior = resultat.theta2_deg;
			theta3_anterior = resultat.theta3_deg;
			d1_anterior = resultat.d1_mm;
		}
		

	}

	if (!resultat.ok)
	{
	 	usart1_envias("Point NOT Achievable\r\n");
	}

	if (i < max_items)
	{
		llista_q2[i] = (Moviment){.graus = -1.0f, .altura = 0.0f, .passos = 0, .dir = 0};
		llista_q3[i] = (Moviment){.graus = -1.0f, .altura = 0.0f, .passos = 0, .dir = 0};
		llista_d1[i] = (Moviment){.graus = 0.0f, .altura = -1.0f, .passos = 0, .dir = 0};
	}
	
	
}


