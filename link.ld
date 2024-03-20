ENTRY(_start)
MEMORY {
	TPU_SRAM (rwx): ORIGIN = 0x0C00000, LENGTH = 0x20000
	RTCSYS_SRAM (rwx): ORIGIN = 0x0520000, LENGTH = 0x2000
	DRAM (rwx): ORIGIN = 0x80000000, LENGTH = 0x10000000
}

SECTIONS {
	.boot : {
		. = ALIGN(8);
		*(.boot)
		. = ALIGN(8);
	} > TPU_SRAM

	.text : {
		. = ALIGN(8);
		*(.text*)
		*(.rodata*)
		. = ALIGN(8);
	} > TPU_SRAM

	.data : {
		. = ALIGN(8);
		*(.data*)
		. = ALIGN(8);
	} > TPU_SRAM

	.bss (NOLOAD) : {
		. = ALIGN(8);
		PROVIDE(__bss_start = .);
		*(.bss*)
		*(.sbss*)
		PROVIDE(__bss_end = .);
		. = ALIGN(8);
	} > TPU_SRAM

	.stack ORIGIN(TPU_SRAM)+LENGTH(TPU_SRAM) : {
		. = ALIGN(8);
		PROVIDE(__stack_end = . );
	} > TPU_SRAM
}
