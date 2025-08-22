/*
 * USART.h
 *
 * Creat per: adrie
 * Descripció: Capçalera per a la comunicació UART mitjançant USART1.
 */

#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include <stdint.h>

#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR1_VAL ((F_CPU / (16UL * BAUD)) - 1)


void usart1_init(void);                       // Inicialitza USART1
void usart1_enviac(uint8_t c);                  // Envia un caràcter per UART
uint8_t usart1_lligc(void);                    // Rep un caràcter per UART (bloquejant)
void usart1_envias(const char* s);              // Envia una cadena de caràcters per UART
int uart1_lligs(char *buf, int maxlen);    // Llegeix una línia (fins \n)

#endif /* USART_H_ */