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

all: $(FW_NAME).elf $(FW_NAME).bin $(FW_NAME).asm
	$(SZ) $(FW_NAME).elf

clean:
	rm -f *.out $(FW_NAME).asm $(FW_NAME).elf $(FW_NAME).bin

format:
	clang-format -i *.c *.h

$(FW_NAME).elf:
	$(CC) $(CFLAGS) $(INCS) $(SRCS) $(LIBS) -o $(FW_NAME).elf

$(FW_NAME).asm: $(FW_NAME).elf
	$(OD) -S -D $(FW_NAME).elf > $(FW_NAME).asm

$(FW_NAME).bin: $(FW_NAME).elf
	$(OC) -O binary $(FW_NAME).elf $(FW_NAME).bin
