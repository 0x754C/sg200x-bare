	.section .boot
	.global _start

_start:
	li sp, 0x801FFFFC
.equ PINMUX_BASE,0x03001000
.equ FMUX_SD0_PWR_EN,0x38
.equ GPIO0_BASE,0x03020000
.equ PA_DATA,0x0
.equ PA_DATA_DIR,0x4
	li t0, PINMUX_BASE
	li t1, 0x03 /* gpio mode */
	sw t1, FMUX_SD0_PWR_EN(t0)

	li t0, GPIO0_BASE
	lw t1, PA_DATA_DIR(t0)
	li t2, (1 << 14)
	or t1, t1, t2 /* output */
	sw t1, PA_DATA_DIR(t0)

	lw t1, PA_DATA(t0)
	or t1, t1, t2 /* led on */
	sw t1, PA_DATA(t0)

	j main
