	.global _c906_slave_start
	.option norvc
_c906_slave_start:
	j reset

reset:
	li sp, 0x0C0007FC

	j c906_slave_main
