ENTRY(_start)
MEMORY {
	TPU_SRAM (rwx): ORIGIN = 0x0C000000, LENGTH = 0x20000
}

SECTIONS {
	.text : {
		*(.text*)
		*(.rodata*)
	} > TPU_SRAM

	.data : {
		. = ALIGN(16);
		*(.data*)
		. = ALIGN(16);
	} > TPU_SRAM

	.bss (NOLOAD) : {
		. = ALIGN(16);
		PROVIDE(__bss_start = .);
		*(.bss*)
		*(.sbss*)
		PROVIDE(__bss_end = .);
		. = ALIGN(16);
	} > TPU_SRAM
}
