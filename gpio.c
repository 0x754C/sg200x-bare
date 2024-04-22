#include "gpio.h"
#include "cvitek_regs.h"
#include "io.h"

void gpio_bank_set_pindir(unsigned bank, unsigned mode, unsigned pin) {
  uint32_t reg_dir, val;
  reg_dir = gpio_get_base(bank) + GPIO_DATADIR;
  val = read32(reg_dir);
  switch (mode) {
  case GPIO_MODE_IN:
    val &= ~(1 << pin);
    break;
  case GPIO_MODE_OUT:
    val |= (1 << pin);
    break;
  default:
    break;
  }
  write32(reg_dir, val);
}
