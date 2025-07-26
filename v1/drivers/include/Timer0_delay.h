

#ifndef TIMER0_DELAY_H
#define TIMER0_DELAY_H

#include <stdbool.h>
#include <stdint.h>

void timer0_init(void);
bool delay_ms(uint16_t ms);

#endif