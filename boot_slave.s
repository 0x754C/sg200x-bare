	.global _c906_slave_start
	.option norvc
_c906_slave_start:
	j reset

reset:
	li sp, 0x0C00EFFC /* TPU_BASE + (60 * 1024 - 4) */

	j c906_slave_main
