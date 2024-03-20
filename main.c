#include "sg200x_regs.h"
#include "uart.h"
#include "led.h"
#include "key.h"
#include <stdint.h>

int main(void) {
  user_led_init();
  user_led_on();
  uart_puts(UART0_BASE, "HelloWorld\n\r");
  user_key_init();
  while (1) {
    if (user_key_read()) {
      user_led_on();
    } else {
      user_led_off();
    }
  }
}
