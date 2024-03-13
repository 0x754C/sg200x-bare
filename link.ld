OUTPUT_FORMAT("elf64-littleriscv")
OUTPUT_ARCH(riscv)
ENTRY(_start)
MEMORY {
	DRAM (rwx): ORIGIN = 0x80080000, LENGTH = 0x200000
}

SECTIONS {
	.boot : {
		. = ALIGN(8);
		*(.boot)
		. = ALIGN(8);
	} > DRAM

	.text : {
		. = ALIGN(8);
		*(.text*)
		*(.rodata*)
		. = ALIGN(8);
	} > DRAM

	.data : {
		. = ALIGN(8);
		*(.data*)
		. = ALIGN(8);
	} > DRAM

	.bss (NOLOAD) : {
		. = ALIGN(8);
		*(.bss*)
		*(.sbss*)
		. = ALIGN(8);
	} > DRAM
}
