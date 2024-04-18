ARCH ?= riscv64

SRCS += boot_master.s boot_slave.s

SRCS += gpio.c uart.c str.c main.c

FW_NAME ?= fw

ifeq ($(ARCH),aarch64)
	TARGET ?= aarch64-unknown-elf
	CFLAGS += -march=armv8-a -mlittle-endian -mabi=lp64
endif

ifeq ($(ARCH),riscv64)
	TARGET ?= riscv64-unknown-elf
	CFLAGS += -march=rv64imac -mabi=lp64
endif

CFLAGS += -Wall -Wextra -Os -g3

CFLAGS += -nostdlib

CFLAGS += -mno-relax

CFLAGS += -T link.ld

all: bin genfip dis
	llvm-size $(FW_NAME).elf

clean:
	rm -f *.out $(FW_NAME).dis $(FW_NAME).elf $(FW_NAME).bin
	rm -f chip_conf.bin blcp.bin fip.bin

format:
	clang-format -i *.c *.h

elf:
	clang -target ${TARGET} $(CFLAGS) $(INCS) $(SRCS) $(LIBS) -o $(FW_NAME).elf

dis: elf
	llvm-objdump -D -S $(FW_NAME).elf > $(FW_NAME).dis

bin: elf
	llvm-objcopy -O binary $(FW_NAME).elf $(FW_NAME).bin

chip_conf:
	python3 chip_conf.py chip_conf.bin

blcp:
	touch blcp.bin

genfip: bin chip_conf blcp
	python3 fiptool.py -v genfip \
		--CHIP_CONF=chip_conf.bin \
		--BL2=$(FW_NAME).bin \
		--BLCP_IMG_RUNADDR=0x05200200 \
		--BLCP_PARAM_LOADADDR=0 \
		--BLCP=blcp.bin \
		fip.bin

flash-acm:
	python3 cv181x_dl.py --serial

flash-libusb:
	python3 cv181x_dl.py --libusb
