#ifndef _SG200X_REGS_H_
#define _SG200X_REGS_H_

#define UART0_BASE 0x04140000

enum {
	UART_THR = 0x0,
	UART_IIR = 0x8,
};

enum {
	UART_INT_ID_MASK = 0xF,
	UART_INT_ID_TXOK = 0x2,
};

#endif
