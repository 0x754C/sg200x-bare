#ifndef _GPIO_H_
#define _GPIO_H_

#include "cvitek_regs.h"
enum {
  GPIO_BANK_PA = 0,
  GPIO_BANK_PB,
  GPIO_BANK_PC,
  GPIO_BANK_PD,
};
enum {
  GPIO0 = 0,
  GPIO1,
  GPIO2,
  GPIO3,
  GPIO4,
  GPIO5,
  GPIO6,
  GPIO7,
  GPIO8,
  GPIO9,
  GPIO10,
  GPIO11,
  GPIO12,
  GPIO13,
  GPIO14,
  GPIO15,
  GPIO16,
  GPIO17,
  GPIO18,
  GPIO19,
  GPIO20,
  GPIO21,
  GPIO22,
  GPIO23,
  GPIO24,
  GPIO25,
  GPIO26,
  GPIO27,
  GPIO28,
  GPIO29,
  GPIO30,
  GPIO31,

  /* todo: support pwr gpio */
};

enum {
  GPIO_MODE_OUT,
  GPIO_MODE_IN,
};

#include "io.h"
#include "types.h"

static inline __attribute__((__always_inline__)) uint32_t
gpio_get_base(unsigned int n) {
  if (n < 4) {
    return (n * (GPIO1_BASE - GPIO0_BASE) + GPIO0_BASE);
  }
  return 0;
}

static inline __attribute__((__always_inline__)) void
gpio_bank_setpin(unsigned bank, unsigned int pin, unsigned level) {
  uint32_t base;
  base = gpio_get_base(bank);
  uint32_t val;
  val = read32(base + GPIO_DATA);
  if (level) {
    val |= (1 << pin);
  } else {
    val &= ~(1 << pin);
  }
  write32(base + GPIO_DATA, val);
}

static inline __attribute__((__always_inline__)) void
gpio_bank_invertpin(unsigned bank, unsigned int pin) {
  uint32_t base;
  base = gpio_get_base(bank);
  uint32_t val;
  val = read32(base + GPIO_DATA);
  val ^= (1 << pin);
  write32(base + GPIO_DATA, val);
}

static inline __attribute__((__always_inline__)) uint32_t
gpio_bank_readpin(unsigned bank, unsigned int pin) {
  uint32_t base;
  base = gpio_get_base(bank);
  uint32_t val;
  val = read32(base + GPIO_IN) & (1 << pin);
  return !!val;
}
void gpio_bank_set_pindir(unsigned bank, unsigned mode, unsigned pin);

#endif
