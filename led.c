#include <stdint.h>

#include "sg200x_regs.h"
#include "io.h"


void user_led_init(void) {
  write32(PINMUX_BASE + PINMUX_SD0_PWR_EN, 0x03); // gpio mode
  // deassert reset
  write32(RSTC_BASE + RSTC_RSTN1,
	  read32(RSTC_BASE + RSTC_RSTN1) | RSTC_RSTN1_GPIO0);
  write32(GPIO0_BASE + GPIO_PA_DATADIR,
	  read32(GPIO0_BASE + GPIO_PA_DATADIR) | (1 << 14)); // output mode
};

void user_led_on(void) {
  write32(GPIO0_BASE + GPIO_PA_DATA,
	  read32(GPIO0_BASE + GPIO_PA_DATA) | (1 << 14));
}

void user_led_off(void) {
  write32(GPIO0_BASE + GPIO_PA_DATA,
	  read32(GPIO0_BASE + GPIO_PA_DATA) & ~(1 << 14));
}

void user_led_toggle(void) {
  write32(GPIO0_BASE + GPIO_PA_DATA,
	  read32(GPIO0_BASE + GPIO_PA_DATA) ^ (1 << 14));
}
