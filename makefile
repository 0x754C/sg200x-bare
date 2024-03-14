SRCS += boot.s

SRCS += main.c led.c key.c uart.c

FW_NAME ?= sg2002
CROSS_COMPILE ?= riscv64-unknown-elf-
CC = $(CROSS_COMPILE)gcc
OD = $(CROSS_COMPILE)objdump
OC = $(CROSS_COMPILE)objcopy
SZ = $(CROSS_COMPILE)size

LINK_SCRIPT ?= link.ld

PICOLIBC_ROOT ?= /usr/lib/picolibc/riscv64-unknown-elf/

CFLAGS += -Wall -Wextra -Wno-int-to-pointer-cast \
	-march=rv64imac -mabi=lp64 -mcmodel=medany -Os -g3 \
	-fdata-sections -ffunction-sections -Wl,--gc-sections \
	-nostartfiles \
	-I$(PICOLIBC_ROOT)/include \
	-L$(PICOLIBC_ROOT)/lib \
	--specs=$(PICOLIBC_ROOT)/picolibc.specs \
	-T $(LINK_SCRIPT)

all: gen_fip $(FW_NAME).asm
	$(SZ) $(FW_NAME).elf

clean:
	rm -f *.out $(FW_NAME).asm $(FW_NAME).elf $(FW_NAME).bin
	rm -f chip_conf.bin blcp.bin fip.bin

format:
	clang-format -i *.c *.h

$(FW_NAME).elf:
	$(CC) $(CFLAGS) $(INCS) $(SRCS) $(LIBS) -o $(FW_NAME).elf

$(FW_NAME).asm: $(FW_NAME).elf
	$(OD) -S -D $(FW_NAME).elf > $(FW_NAME).asm

$(FW_NAME).bin: $(FW_NAME).elf
	$(OC) -O binary $(FW_NAME).elf $(FW_NAME).bin

chip_conf:
	python3 chip_conf.py chip_conf.bin

blcp:
	touch blcp.bin

gen_fip: $(FW_NAME).bin chip_conf blcp
	python3 fiptool.py -v genfip \
		--CHIP_CONF=chip_conf.bin \
		--BL2=$(FW_NAME).bin \
		--BLCP_IMG_RUNADDR=0x05200200 \
		--BLCP_PARAM_LOADADDR=0 \
		--BLCP=blcp.bin \
		fip.bin
