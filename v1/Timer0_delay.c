
// Configura delay amb timer 0

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
	uint16_t start = timer0_millis;
	if ((uint16_t)(timer0_millis) >= ms) {
		timer0_millis = 0;
		return true;
	}
	return false;
}