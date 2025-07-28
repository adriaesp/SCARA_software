
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer0_delay.h"
#include "moviment.h"
#include "hardware_config.h"

int main(void) {
	// Precalcula els passos per cada moviment
	calcula_passos_moviments();

	int0_init();
	timer0_init();
	setup_driver();
	homing();

	while (1) {
		moviment_loop();
	}
}