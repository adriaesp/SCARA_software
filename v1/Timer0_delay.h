

#ifndef TIMER0_DELAY_H
#define TIMER0_DELAY_H

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

// Inicialitza el Timer0 per generar una interrupció cada 1 ms
void timer0_init(void);

// Retarda el programa el nombre de mil·lisegons especificat (basat en Timer0)
bool delay_ms(uint16_t ms);

#endif // TIMER0_DELAY_H