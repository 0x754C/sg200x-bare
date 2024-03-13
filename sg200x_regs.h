#ifndef _SG200X_REGS_H_
#define _SG200X_REGS_H_

#define UART0_BASE 0x04140000

enum {
  UART_THR = 0x00,
  UART_LSR = 0x14,
};

enum {
  UART_LSR_THRE = (1 << 6),
};

#endif
