#ifndef _UART_H_
#define _UART_H_

#include "cvitek_regs.h"
#include "io.h"

static inline __attribute__((__always_inline__)) uint32_t long
uart_get_base(unsigned int n) {
  if (n < 4) {
    return ((n * (UART1_BASE - UART0_BASE)) + UART0_BASE);
  }
  return UART4_BASE;
}

static inline __attribute__((__always_inline__)) unsigned int
uart_tx_is_ready(unsigned int n) {
  uint32_t long base;
  base = uart_get_base(n);
  return (read32(base + UART_LSR) & UART_LSR_THRE);
}

static inline __attribute__((__always_inline__)) void
uart_wait_tx_ready(unsigned int n) {
  while (!uart_tx_is_ready(n))
    ;
}

static inline __attribute__((__always_inline__)) void uart_txc(unsigned int n,
                                                               uint8_t data) {
  uart_wait_tx_ready(n);
  uint32_t long base;
  base = uart_get_base(n);
  write32(base + UART_THR, (unsigned int)data);
}

static inline __attribute__((__always_inline__)) unsigned int
uart_rx_is_ready(unsigned int n) {
  uint32_t long base;
  base = uart_get_base(n);
  return (read32(base + UART_LSR) & UART_LSR_DR);
}

static inline __attribute__((__always_inline__)) void
uart_wait_rx_ready(unsigned int n) {
  while (!uart_rx_is_ready(n))
    ;
}

static inline __attribute__((__always_inline__)) uint8_t
uart_rxc(unsigned int n) {
  uart_wait_rx_ready(n);
  uint32_t long base;
  base = uart_get_base(n);
  return read32(base + UART_RBR) & 0xFF;
}

uint64_t uart_sclk_get(unsigned int n);
void uart_txs(unsigned int n, char *s);
void uart_txa(unsigned int n, uint8_t *buf, uint64_t len);
void uart_rxa(unsigned int n, uint8_t *buf, uint64_t len);

#endif
