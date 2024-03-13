#include "io.h"
#include "sg200x_regs.h"

int uart_tx_ready(unsigned int base) {
	return ((read32(base + UART_IIR) & UART_INT_ID_MASK) == UART_INT_ID_TXOK);
}

void uart_putc(unsigned int base, char c) {
	while (!uart_tx_ready(base));
	write32((base + UART_THR), c);
	while (!uart_tx_ready(base));
}

void uart_puts(unsigned int base, char *s) {
	while (*s != '\0') {
		uart_putc(base, *s);
		s++;
	}
}
