#include "uart.h"
#include "cvitek_regs.h"
#include "io.h"

void uart_reset(unsigned int n) {
  uint32_t val;
  uint32_t mask;
  switch (n) {
  case 0:
    mask = SOFT_UART0_RESET;
    break;
  case 1:
    mask = SOFT_UART1_RESET;
    break;
  case 2:
    mask = SOFT_UART2_RESET;
    break;
  case 3:
    mask = SOFT_UART3_RESET;
    break;
  default:
    mask = 0;
    break;
  }
  val = read32(RSTN_BASE + SOFT_RSTN_0);
  val &= ~(mask);
  write32(RSTN_BASE + SOFT_RSTN_0, val);
  val = read32(RSTN_BASE + SOFT_RSTN_0);
  val |= mask;
  write32(RSTN_BASE + SOFT_RSTN_0, val);
}

uint64_t uart_sclk_get(unsigned int n) {
  uint32_t val;
  val = read32(CLKGEN_BASE + CLKSEL0);
  uint32_t mask;
  switch (n) {
  case 0:
    mask = CLKSEL_UART0;
    break;
  case 1:
    mask = CLKSEL_UART1;
    break;
  case 2:
    mask = CLKSEL_UART2;
    break;
  case 3:
    mask = CLKSEL_UART3;
    break;
  default:
    mask = 0;
    break;
  }
  val &= mask;
  if (val) {
    return (25 * 1000 * 1000); // 25Mhz xtal
  } else {
    // todo, clock source is div_clk_187p5m */
    // default is 187.5Mhz
    return 187500000;
  }
}

void uart_txs(unsigned int n, char *s) {
  while (*s != '\0') {
    uart_txc(n, *s);
    s++;
  }
}

void uart_txa(unsigned int n, uint8_t *buf, uint64_t len) {
  while (len) {
    uart_txc(n, *buf);
    buf++;
    len--;
  }
}

void uart_rxa(unsigned int n, uint8_t *buf, uint64_t len) {
  while (len) {
    *buf = uart_rxc(n);
    buf++;
    len--;
  }
}
