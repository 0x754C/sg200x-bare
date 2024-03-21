ARCH ?= riscv64

SRCS += boot_$(ARCH).s

INCS += -I./

FW_NAME ?= sg2002

ifeq ($(ARCH),aarch64)
	CROSS_COMPILE ?= aarch64-none-elf-
	CFLAGS += -march=armv8-a -mlittle-endian -mabi=lp64
endif

ifeq ($(ARCH),riscv64)
	CROSS_COMPILE ?= riscv64-none-elf-
	CFLAGS += -march=rv64imac_zicsr -mabi=lp64 -mcmodel=medany
	CFLAGS += -mstrict-align
endif


CC = $(CROSS_COMPILE)gcc
OD = $(CROSS_COMPILE)objdump
OC = $(CROSS_COMPILE)objcopy
SZ = $(CROSS_COMPILE)size

LINK_SCRIPT ?= link.ld

CFLAGS += -Wall -Wextra -Wno-int-to-pointer-cast \
	-nostartfiles \
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

flash:
	python3 cv181x_dl.py
