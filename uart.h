#ifndef _UART_H_
#define _UART_H_

#include "sg200x_regs.h"

#define CONSOLE UART0_BASE

void uart_putc(unsigned int base, char c);
void uart_puts(unsigned int base, char *s);

#endif
