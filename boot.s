	.section .boot
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
	la sp, __stack_end

	j main
