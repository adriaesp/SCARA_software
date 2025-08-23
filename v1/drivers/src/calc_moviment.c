/*
 * moviment.c
 *
 * Created: 26/07/2025 12:30:47
 *  Author: adrie
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

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
	return (int)(60000 * (altura / 15.5));
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


static bool c_inversa(float px, float py, float pz, int elbow_up, float *theta2_deg, float *theta3_deg, float *d1_out)
{
	/* D1 */
	float d1 = (pz - L3) / L2;
	if (d1_out != NULL)
	{
		*d1_out = d1;
	}

	/* s3 i c3 */
	float r2 = px * px + py * py;
	float c3 = (r2 - L1 * L1 - L2 * L2) / (2.0f * L1 * L2);

	if (c3 > 1.0f)
	{
		c3 = 1.0f;
	}
	if (c3 < -1.0f)
	{
		c3 = -1.0f;
	}

	/* sqrt argument segur */
	float one_minus_c3sq = 1.0f - c3 * c3;
	if (one_minus_c3sq < 0.0f)
	{
		one_minus_c3sq = 0.0f;
	}

	float s3_abs = sqrtf(one_minus_c3sq);
	float s3;
	if (elbow_up)
	{
		s3 = s3_abs;
	}
	else
	{
		s3 = -s3_abs;
	}

	/* theta3 */
	float theta3 = atan2f(s3, c3);
	if (theta3_deg != NULL)
	{
		*theta3_deg = DEG(theta3);
	}

	/* theta2 */
	float k1 = L1 + L2 * c3;
	float k2 = L2 * s3;
	float num = k1 * py - k2 * px;
	float den = k1 * px + k2 * py;
	float theta2 = atan2f(num, den);
	if (theta2_deg != NULL)
	{
		*theta2_deg = DEG(theta2);
	}

	/* comprovació d’abast en XY: |L1-L2| <= r <= L1+L2 */
	float r = sqrtf(r2);
	float rmin = fabsf(L1 - L2);
	float rmax = L1 + L2;

	if (r >= (rmin - 1e-4f) && r <= (rmax + 1e-4f))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void genera_graus(const Taula coords[], Moviment llista_q2[], Moviment llista_q3[], Moviment llista_d1[], int max_items)
{
	int i;
	for (i = 0; i < max_items; i++)
	{
		/* comprovem si hem arribat al final amb el sentinella */
		if (coords[i].X == -1.0f && coords[i].Y == -1.0f && coords[i].Z == -1.0f)
		{
			break;
		}

		float q2_deg = 0.0f;
		float q3_deg = 0.0f;
		float d1_mm = 0.0f;

		int ok = c_inversa(coords[i].X, coords[i].Y, coords[i].Z, ELBOW_UP, &q2_deg, &q3_deg, &d1_mm);

		/* Q2 */
		llista_q2[i].graus = q2_deg;
		llista_q2[i].altura = 0.0f;
		llista_q2[i].passos = 0;
		if (q2_deg >= 0.0f)
		{
			llista_q2[i].dir = 1;
		}
		else
		{
			llista_q2[i].dir = 0;
		}

		/* Q3 */
		llista_q3[i].graus = q3_deg;
		llista_q3[i].altura = 0.0f;
		llista_q3[i].passos = 0;
		if (q3_deg >= 0.0f)
		{
			llista_q3[i].dir = 1;
		}
		else
		{
			llista_q3[i].dir = 0;
		}

		/* D1 */
		llista_d1[i].graus = 0.0f;
		llista_d1[i].altura = d1_mm;
		llista_d1[i].passos = 0;
		if (d1_mm >= 0.0f)
		{
			llista_d1[i].dir = 1;
		}
		else
		{
			llista_d1[i].dir = 0;
		}

		/* si el punt no és assolible marquem error */
		if (!ok)
		{
			usart1_enviac('0'+i);
			usart1_envias("Pint NOT Achivable");
			llista_q2[i].passos = -1;
			llista_q3[i].passos = -1;
			llista_d1[i].passos = -1;
		}
	}

	/* afegim el sentinella de final */
	if (i < max_items)
	{
		llista_q2[i].graus = -1.0f;
		llista_q2[i].altura = 0.0f;
		llista_q2[i].passos = 0;
		llista_q2[i].dir = 0;

		llista_q3[i].graus = -1.0f;
		llista_q3[i].altura = 0.0f;
		llista_q3[i].passos = 0;
		llista_q3[i].dir = 0;

		llista_d1[i].graus = 0.0f;
		llista_d1[i].altura = -1.0f;
		llista_d1[i].passos = 0;
		llista_d1[i].dir = 0;
	}

	/* ara calculem els passos amb les funcions que ja tens */
	calcula_passos_moviments_q2(llista_q2);
	calcula_passos_moviments_q3(llista_q3);
	calcula_passos_moviments_d1(llista_d1);
}
