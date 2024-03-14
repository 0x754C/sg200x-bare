#include "io.h"
#include "sg200x_regs.h"

void user_key_init(void) {
  write32(PINMUX_BASE + PINMUX_AUX0, 0x3); // gpio mode
  // deassert reset
  write32(RSTC_BASE + RSTC_RSTN1,
	  read32(RSTC_BASE + RSTC_RSTN1) | RSTC_RSTN1_GPIO0);
  write32(GPIO0_BASE + GPIO_PA_DATADIR,
	  read32(GPIO0_BASE + GPIO_PA_DATADIR) & ~(1 << 30)); // input
}

uint32_t user_key_read(void) {
  return (read32(GPIO0_BASE + GPIO_PA_IN) & (1 << 30));
}
			 
