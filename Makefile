CC = gcc
LD = ld

BIN_DIR = /home/artem/bin
ISO_IMAGE = Liqueur.iso
ISO_DIR = /home/artem/iso

TARGET = $(BIN_DIR)/kernel

CFLAGS =i386-pc-none-elf -m32 -nostdlib -ffreestanding -O2 -fno-builtin -fno-stack-protector -Wall -Wextra -mno-sse -mno-mmx

OBJS = ps2.o main.o

.PHONY: all clean iso

all: iso

ps2.o: drivers/keyboard/ps2.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(LD) -T linker.ld -m elf_i386 $(OBJS) -o $(TARGET)

iso: $(TARGET)
	@cp $(TARGET) $(ISO_DIR)/boot/
	grub-mkrescue -o $(ISO_IMAGE) $(ISO_DIR)

clean:
	rm -rf $(OBJS) $(ISO_IMAGE)