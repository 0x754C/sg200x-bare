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
	li sp, 0x0C00FFFC /* TPU_BASE + (64 * 1024) - 4 */

	j c906_master_main
