/*
 * UART.c
 *
 * Created: 19/08/2025 20:04:37
 *  Author: adrie
 */ 
#include "USART.h"




void usart1_init(void) {
	UBRR1H = (uint8_t)(UBRR1_VAL >> 8);
	UBRR1L = (uint8_t)(UBRR1_VAL & 0xFF);
	UCSR1B = (1 << RXEN1) | (1 << TXEN1);
	UCSR1C = (1 << UCSZ11) | (1 << UCSZ10); // 8N1
}

uint8_t usart1_lligc(void) {
	while (!(UCSR1A & (1 << RXC1)));
	return UDR1;
}

void usart1_enviac(uint8_t c) {
	while (!(UCSR1A & (1 << UDRE1)));
	UDR1 = c;
}

void usart1_envias(const char* s) {
	while (*s) {
		if (*s == '\n') usart1_enviac('\r');
		usart1_enviac(*s++);
	}
}

int uart1_lligs(char *buf, int maxlen) {
	int i = 0;
	while (1) {
		uint8_t c = usart1_lligc();
		//usart1_enviac(c);

		if (c == '\r' || c == '\n') {
			buf[i] = '\0';         // final de cadena
			return i;              // retorna longitud
		}
		if (i < maxlen - 1) {
			buf[i++] = (char)c;
		}
	}
}