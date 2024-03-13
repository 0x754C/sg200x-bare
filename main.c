#include <stdint.h>
#include "sg200x_regs.h"
#include "uart.h"

int main(void) {
	while(1) {
		uart_puts(UART0_BASE, "HelloWorld\n\r");
	}
}
