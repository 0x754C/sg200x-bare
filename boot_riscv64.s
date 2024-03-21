	.equ PINMUX_BASE,0x03001000
	.equ PINMUX_SD0_PWR_EN,0x38
	.equ PINMUX_AUX0,0x78

	.equ GPIO0_BASE,0x03020000
	.equ GPIO_PA_DATA,0x0
	.equ GPIO_PA_DATADIR,0x04
	.equ GPIO_PA_IN,0x50

	.equ UART0_BASE,0x04140000
	.equ UART_THR,0x00
	.equ UART_LSR,0x14
	.equ UART_LSR_THRE,(1 << 6)

	.global _start

	.option norvc
_start:
	j reset
	.word 0
	.word 0 /* BL2 MSID */
	.word 0 /* BL2 version */
	.word 0
	.word 0
	.word 0
	.word 0

reset:
	li t0, PINMUX_BASE
	li t1, 0x3 /* gpio mode */
	sw t1, PINMUX_SD0_PWR_EN(t0)
	li t1, 0x3 /* gpio mode */
	sw t1, PINMUX_AUX0(t0)

	li t0, GPIO0_BASE
	lw t1, GPIO_PA_DATADIR(t0)
	li t2, (1 << 14)
	or t1, t1, t2 /* PA 14 out */
	li t2, ~(1 << 30)
	and t1, t1, t2 /* PA 30 in */
	sw t1, GPIO_PA_DATADIR(t0)

	call led_off

	li a0, '\n'
	call uart_putc
	li a0, '\r'
	call uart_putc
	li a0, 'B'
	call uart_putc
	li a0, 'L'
	call uart_putc
	li a0, '2'
	call uart_putc
	li a0, '\n'
	call uart_putc
	li a0, '\r'
	call uart_putc
	li a0, 'R'
	call uart_putc
	li a0, 'I'
	call uart_putc
	li a0, 'S'
	call uart_putc
	li a0, 'C'
	call uart_putc
	li a0, 'V'
	call uart_putc
	li a0, '\n'
	call uart_putc
	li a0, '\r'
	call uart_putc

loop:
	call btn_read
	beq zero, a0, 1f
	call led_on
	j loop
1:
	call led_off
	j loop

btn_read:
	li a0, GPIO0_BASE
	lw a1, GPIO_PA_IN(a0)
	li a2, (1 << 30)
	and a0, a1, a2
	ret

led_on:
	li a0, GPIO0_BASE
	lw a1, GPIO_PA_DATA(a0)
	li a2, (1 << 14)
	or a1, a1, a2
	sw a1, GPIO_PA_DATA(a0)
	ret

led_off:
	li a0, GPIO0_BASE
	lw a1, GPIO_PA_DATA(a0)
	li a2, ~(1 << 14)
	and a1, a1, a2
	sw a1, GPIO_PA_DATA(a0)
	ret

led_toggle:
	li a0, GPIO0_BASE
	lw a1, GPIO_PA_DATA(a0)
	li a2, (1 << 14)
	xor a1, a1, a2
	sw a1, GPIO_PA_DATA(a0)
	ret

uart_putc:
	li a1, UART0_BASE
	lw a2, UART_LSR(a1)
	andi a2, a2, UART_LSR_THRE
	beq zero, a2, uart_putc
	sw a0, UART_THR(a1)
	ret
