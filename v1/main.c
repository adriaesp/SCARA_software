
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer0_delay.h"
#include "moviment.h"
#include "hardware_config.h"

int main(void) {
        int0_init();
        timer0_init();
        setup_driver();
        init_motors();

        while (1) {
                moviment_loop();
        }
}