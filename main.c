#include "cvitek_regs.h"
#include "gpio.h"
#include "str.h"
#include "uart.h"

void c906_slave_reset(uint64_t address) {
  uint32_t val;
  val = read32(RSTN_BASE + SOFT_CPU_RSTN);
  val &= ~(CPUSYS2_RESET);
  write32(RSTN_BASE + SOFT_CPU_RSTN, val);

  val = read32(SEC_SYS_BASE + 0x04);
  val |= (1 << 13);
  write32(SEC_SYS_BASE + 0x04, val);

  write32(SEC_SYS_BASE + 0x20, address);       // low 32bit
  write32(SEC_SYS_BASE + 0x24, address >> 32); // high 32bit

  val = read32(RSTN_BASE + SOFT_CPU_RSTN);
  val |= CPUSYS2_RESET;
  write32(RSTN_BASE + SOFT_CPU_RSTN, val);
}

int c906_slave_main(void) {
  uart_txs(0, "\n\rHELLO\n\r");
  uart_txs(0, "I'M SLAVE\n\r");
  // setup pinmux
  write32(PINMUX_BASE + PINMUX_AUX0, 0x3); // gpio mode
  // setup gpio direction
  gpio_bank_set_pindir(GPIO_BANK_PA, GPIO_MODE_IN, GPIO30);

  uint32_t prev = gpio_bank_readpin(GPIO_BANK_PA, GPIO30);
  uint32_t cur;
  while (1) {
    cur = gpio_bank_readpin(GPIO_BANK_PA, GPIO30);
    if (cur != prev) {
      if (cur) {
        uart_txc(0, '-');
      } else {
        uart_txc(0, '_');
      }
    }
    prev = cur;
  }
}

extern unsigned char _c906_slave_start[];

int c906_master_main(void) {
  /* UART0 is init by bootrom, so we can use it without init
   * baud is 128000 */
  uart_txs(0, "\n\rHELLO\n\r");
  uart_txs(0, "I'M MASTER\n\r");
  uint64_t hex;
  hex = num32tohexstr(0x01234567);
  uart_txa(0, (uint8_t *)&hex, sizeof(hex));
  hex = num32tohexstr(0x89ABCDEF);
  uart_txa(0, (uint8_t *)&hex, sizeof(hex));
  uart_txs(0, "\n\r");
  uart_txs(0, "CLKEN1 REG: ");
  hex = num32tohexstr(read32(CLKGEN_BASE + CLKEN1));
  uart_txa(0, (uint8_t *)&hex, sizeof(hex));
  uart_txs(0, "\n\r");
  uart_txs(0, "CLKSEL0 REG: ");
  hex = num32tohexstr(read32(CLKGEN_BASE + CLKSEL0));
  uart_txa(0, (uint8_t *)&hex, sizeof(hex));
  uart_txs(0, "\n\r");
  uart_txs(0, "UART0 SCLK: ");
  hex = num32tohexstr(uart_sclk_get(0));
  uart_txa(0, (uint8_t *)&hex, sizeof(hex));
  uart_txs(0, "\n\r");
  uart_txs(0, "UART0 FCR: ");
  hex = num32tohexstr(read32(uart_get_base(0) + UART_FCR));
  uart_txa(0, (uint8_t *)&hex, sizeof(hex));
  uart_txs(0, "\n\r");
  uart_txs(0, "UART0 LCR: ");
  hex = num32tohexstr(read32(uart_get_base(0) + UART_LCR));
  uart_txa(0, (uint8_t *)&hex, sizeof(hex));
  uart_txs(0, "\n\r");
  uart_txs(0, "BOOT CONF REG: ");
  hex = num32tohexstr(read32(SYSC_BASE + SYSC_CONF_INFO));
  uart_txa(0, (uint8_t *)&hex, sizeof(hex));
  uart_txs(0, "\n\r");

  uart_txs(0, "C906 SLAVE BOOTUP\n\r");
  uart_txs(0, "C906 SLAVE ADDRESS:");
  uint32_t val;
  val = ((uint64_t)_c906_slave_start) >> 32;
  hex = num32tohexstr(val);
  uart_txa(0, (uint8_t *)&hex, sizeof(hex));
  val = ((uint64_t)_c906_slave_start);
  hex = num32tohexstr(val);
  uart_txa(0, (uint8_t *)&hex, sizeof(hex));
  uart_txs(0, "\n\r");
  c906_slave_reset((uint64_t)_c906_slave_start);

  // setup pinmux
  write32(PINMUX_BASE + PINMUX_SD0_PWR_EN, 0x3); // gpio mode
  // setup gpio direction
  gpio_bank_set_pindir(GPIO_BANK_PA, GPIO_MODE_OUT, GPIO14);

  while (1) {
    uart_txc(0, uart_rxc(0));
    gpio_bank_invertpin(GPIO_BANK_PA, GPIO14);
  }
}
