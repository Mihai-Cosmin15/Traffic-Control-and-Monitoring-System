#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include <stdio.h>

/*
 * Functie de initializare a controllerului USART
 */
void USART0_init(unsigned int ubrr);

/*
 * Functie ce transmite un caracter prin USART
 *
 * @param data - caracterul de transmis
 */
void USART0_transmit(char data);

/*
 * Functie ce primeste un caracter prin USART
 *
 * @return - caracterul primit
 */
char USART0_receive();

bool USART0_receive_nonblocking(char &data);

/*
 * Functie ce transmite un sir de caractere prin USART
 *
 * @param data - sirul (terminat cu '\0') de transmis
 */
void USART0_print(const char *data);

void USART0_println(const char *data);

#endif // USART_H_
