#include "cvitek_regs.h"
#include "uart.h"
#include "io.h"

void uart_txs(unsigned int n, char *s) {
	while(*s != '\0') {
		uart_txc(n, *s);
		s++;
	}
}

void uart_txa(unsigned int n, uint8_t *buf, uint64_t len) {
	while(len) {
		uart_txc(n, *buf);
		buf++;
		len--;
	}
}
