
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer0_delay.h"
#include "calc_moviment.h"
#include "hardware_config.h"
#include "punts.h"
#include "q2.h"
#include "q3.h"

uint8_t max_moves_q2;
uint8_t max_moves_q3;

int main(void) {
	// Precalcula els passos per cada moviment
	max_moves_q2 = calcula_passos_moviments_q2(llista_q2);
	max_moves_q3 = calcula_passos_moviments_q3(llista_q3);
//	int0_init();
	timer0_init();
	
	setup_driver_q2();
	homing_q2();
	setup_driver_q3();
	homing_q3();
	_delay_ms(10000);
	max_moves_q3 = calcula_passos_moviments_q3(llista_q3);
	max_moves_q2 = calcula_passos_moviments_q2(llista_q2);
	setup_driver_q2();
	setup_driver_q3();

	while (1) {
 		moviment_loop_q2();
 		moviment_loop_q3();
	}
}