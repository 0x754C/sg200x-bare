#include "cvitek_regs.h"
#include "uart.h"
#include "str.h"

void c906_slave_reset(uint64_t address) {
	uint32_t val;
	val = read32(RSTN_BASE + SOFT_CPU_RSTN);
	val &= ~(CPUSYS2_RESET);
	write32(RSTN_BASE + SOFT_CPU_RSTN, val);

	val = read32(SEC_SYS_BASE + 0x04);
	val |= (1 << 13);
	write32(SEC_SYS_BASE + 0x04, val);

	write32(SEC_SYS_BASE + 0x20, address); // low 32bit
	write32(SEC_SYS_BASE + 0x24, address >> 32); // high 32bit

	
	val = read32(RSTN_BASE + SOFT_CPU_RSTN);
	val |= CPUSYS2_RESET;
	write32(RSTN_BASE + SOFT_CPU_RSTN, val);
}

int c906_slave_main(void) {
	uart_txs(0, "\n\rHELLO\n\r");
	uart_txs(0, "I'M SLAVE\n\r");
	while(1);
}

extern unsigned char _c906_slave_start[];

int c906_master_main(void) {
	/* UART0 is init by bootrom, so we can use it without init
	 * baud is 128000 */
	uart_txs(0, "\n\rHELLO\n\r");
	uart_txs(0, "I'M MASTER\n\r");
	uint64_t hex;
	hex = num32tohexstr(0x01234567);
	uart_txa(0, (uint8_t *)&hex, sizeof(hex));
	hex = num32tohexstr(0x89ABCDEF);
	uart_txa(0, (uint8_t *)&hex, sizeof(hex));
	uart_txs(0, "\n\r");
	uart_txs(0, "BOOT CONF REG: ");
	hex = num32tohexstr(read32(SYSC_BASE + SYSC_CONF_INFO));
	uart_txa(0, (uint8_t *)&hex, sizeof(hex));
	uart_txs(0, "\n\r");
	uart_txs(0, "AXI SRAM RTOS OFS REG: ");
	hex = num32tohexstr(read32(AXI_SRAM_BASE + AXI_SRAM_RTOS_OFS));
	uart_txa(0, (uint8_t *)&hex, sizeof(hex));
	uart_txs(0, "\n\r");
	uart_txs(0, "CVI RTOS MAGIC CODE: ");
	hex = num32tohexstr(0xABC0DEF);
	uart_txa(0, (uint8_t *)&hex, sizeof(hex));
	uart_txs(0, "\n\r");

	uart_txs(0, "C906 SLAVE BOOTUP\n\r");
	uart_txs(0, "C906 SLAVE ADDRESS:");
	uint32_t val;
	val = ((uint64_t)_c906_slave_start) >> 32;
	hex = num32tohexstr(val);
        uart_txa(0, (uint8_t *)&hex, sizeof(hex));
	val = ((uint64_t)_c906_slave_start);
	hex = num32tohexstr(val);
        uart_txa(0, (uint8_t *)&hex, sizeof(hex));
	uart_txs(0, "\n\r");
	c906_slave_reset((uint64_t)_c906_slave_start);

	while(1);
}
