#include "io.h"
#include "sg200x_regs.h"

void uart_putc(unsigned int base, char c) {
  while (read32(base + UART_LSR) & UART_LSR_THRE)
    ;
  write32((base + UART_THR), c);
}

void uart_puts(unsigned int base, char *s) {
  while (*s != '\0') {
    uart_putc(base, *s);
    s++;
  }
}
