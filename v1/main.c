
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer0_delay.h"
#include "calc_moviment.h"
#include "hardware_config.h"
#include "punts.h"
#include "q2.h"
#include "q3.h"
#include "d1.h"
#include "moviment.h"

uint8_t max_moves;


int main(void) {
	// Precalcula els passos per cada moviment
	max_moves = calcula_passos_moviments_q2(llista_q2);
	 calcula_passos_moviments_q3(llista_q3);
	 calcula_passos_moviments_d1(llista_d1);
	
	setup_driver_q2();
	homing_q2();
	setup_driver_q3();
	homing_q3();
	setup_driver_d1();
	homing_d1();
	_delay_ms(2000);
	
// 	max_moves = calcula_passos_moviments_q3(llista_q3);
// 	calcula_passos_moviments_q2(llista_q2);
	setup_driver_q2();
	setup_driver_q3();
	setup_driver_d1();

	while (1) {
	  	moviment();
// 		moviment_loop_q3();

	}
}