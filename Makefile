CC = gcc
LD = ld
ASM = nasm

BIN_DIR = /home/artem/bin
ISO_IMAGE = Liqueur.iso
ISO_DIR = /home/artem/iso

TARGET = $(BIN_DIR)/kernel

CFLAGS = -m32 -nostdlib -ffreestanding -O2 -fno-builtin -fno-stack-protector -Wall -Wextra -mno-sse -mno-mmx -mno-80387 -mgeneral-regs-only -I./include
ASMFLAGS = -f elf32

CSOURCES = $(shell find . -name "*.c")
ASMSOURCES = $(shell find . -name "*.asm")

OBJS = $(CSOURCES:.c=.o) $(ASMSOURCES:.asm=.o)

.PHONY: all clean iso

all: iso

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
%.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(TARGET): $(OBJS)
	$(LD) -T linker.ld -m elf_i386 $(OBJS) -o $(TARGET)

iso: $(TARGET)
	@cp $(TARGET) $(ISO_DIR)/boot/
	grub-mkrescue -o $(ISO_IMAGE) $(ISO_DIR)

clean:
	rm -rf $(OBJS) $(ISO_IMAGE)