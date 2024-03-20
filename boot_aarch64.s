	.section .boot
	.global _start

_start:
	b reset
	.word 0
	.word 0 /* BL2 MSID */
	.word 0 /* BL2 version */
	.word 0
	.word 0
	.word 0
	.word 0

reset:
	/* sync icache */
	ic iallu
	isb

	ldr x0, =__stack_end
	mov sp, x0

	b main
