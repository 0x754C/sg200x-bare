#ifndef _SG200X_REGS_H_
#define _SG200X_REGS_H_

enum {
  PINMUX_BASE = 0x03001000,
  GPIO0_BASE = 0x03020000,
  UART0_BASE = 0x04140000,
};

enum {
  PINMUX_SD0_PWR_EN = 0x38,
  PINMUX_AUX0 = 0x78,
};

enum {
  GPIO_PA_DATA = 0x00,
  GPIO_PA_DATADIR = 0x04,
  GPIO_PA_IN = 0X50,
};

enum {
  UART_THR = 0x00,
  UART_LSR = 0x14,
};

enum {
  UART_LSR_THRE = (1 << 6),
};

#endif
