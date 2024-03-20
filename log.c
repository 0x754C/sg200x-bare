#include <stdio.h>

#include "sg200x_regs.h"
#include "uart.h"

void log_printf(char *msg, ...) {
  // TODO: use printf
  uart_puts(CONSOLE, msg);
  return;
}
