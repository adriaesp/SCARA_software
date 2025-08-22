
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
#include "USART.h"

uint8_t max_moves;
char test[] = "Hola món!\r\n";
char buffer[128];
char c;
uint8_t val = 5;


int main(void) {
	// Precalcula els passos per cada moviment
	usart1_init();

	max_moves = calcula_passos_moviments_q2(llista_q2);
	calcula_passos_moviments_q3(llista_q3);
	calcula_passos_moviments_d1(llista_d1);
	
	usart1_envias("-------------ROBOT INIT-------------\r\n");
	usart1_envias("---------------HOMING---------------\r\n");
	setup_driver_q2();
	homing_q2();
	usart1_envias("Q2 CHECK\r\n");
	setup_driver_q3();
	homing_q3();
	usart1_envias("Q3 CHECK\r\n");
	setup_driver_d1();
	homing_d1();
	usart1_envias("D1 CHECK\r\n");
	_delay_ms(2000);
	usart1_envias("PRESS \"ENTER\" TO INITIALIZE MOV\r\n");
	uart1_lligs(buffer,sizeof(buffer));
	usart1_envias("---------------INITIALAIZING---------------\r\n");
// 	max_moves = calcula_passos_moviments_q3(llista_q3);
// 	calcula_passos_moviments_q2(llista_q2);
	setup_driver_q2();
	setup_driver_q3();
	setup_driver_d1();

	while (1) {
		uart1_lligs(buffer,sizeof(buffer));
		//usart1_envias("\r\nHas escrit:\r\n");
		usart1_envias(buffer);
		usart1_envias("\r");
//	  	moviment();
// 		moviment_loop_q3();

	}
}