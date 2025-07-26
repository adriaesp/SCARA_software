
// Configura delay amb timer 0

#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#include "timer0_delay.h"


volatile uint16_t timer0_millis = 0;

void timer0_init(void) {
	// Mode CTC
	TCCR0A = (1 << WGM01);                  // Mode CTC (WGM01 = 1)
	TCCR0B = (1 << CS01) | (1 << CS00);     // Prescaler = 64
	OCR0A = 249;                            // 1 ms amb F_CPU = 16 MHz i prescaler 64
	TIMSK0 |= (1 << OCIE0A);                // Activa interrupció per Compare Match A
	sei();                                  // Activa interrupcions globals
}

ISR(TIMER0_COMPA_vect) {
	timer0_millis++; // S'incrementa cada 1 ms
}

bool delay_ms(uint16_t ms) {
	if ((uint16_t)(timer0_millis) >= ms) {
		timer0_millis = 0;					// Retorna True quan ms <= nº milisegons
		return true;
	}
	return false;
}