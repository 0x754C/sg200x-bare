#ifndef _UART_H_
#define _UART_H_

int uart_tx_ready(unsigned int base);
void uart_putc(unsigned int base, char c);
void uart_puts(unsigned int base, char *s);

#endif
