	.section .boot
	.global _start

_start:
	li sp, 0x801FFFFC

	j main
