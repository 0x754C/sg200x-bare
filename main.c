#include "sg200x_regs.h"
#include "uart.h"
#include <stdint.h>

int main(void) {
  uart_puts(UART0_BASE, "HelloWorld\n\r");
  while (1)
    ;
}
