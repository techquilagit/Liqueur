#include "multiboot2.h"
#define MULTIBOOT2_CHECKSUM (0x100000000 - (MULTIBOOT2_HEADER_MAGIC + MULTIBOOT2_ARCHITECTURE_I386 + 24))
__attribute__((section(".multiboot"))) 
__attribute__((aligned(8)))
struct {
    struct multiboot_header header;
    struct multiboot_header_tag end_tag;
} my_grub_header = {
    .header = {
        .magic = MULTIBOOT2_HEADER_MAGIC,
        .architecture = MULTIBOOT2_ARCHITECTURE_I386,
        .header_length = 24, 
        .checksum = MULTIBOOT2_CHECKSUM
    },
        .end_tag =
        .type = MULTIBOOT2_HEADER_TAG_END,
        .flags = 0,
        .size = 8
    };
enum Color {
    RED = 0x0C,
    GREEN = 0x0A,
    BLUE = 0x09
};
char* video = VIDEO;
void printk(char* vga, char* word, Color color) {
    for (int i = 0; word[i] != '\0'; i++) {
        vga[i*2] = word[i]; vga[i*2+1] = (char)color;
    }
}
extern "C" void startk(unsigned int magic, unsigned long address) {
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) printk(&video, "INVALID MAGIC!!!", RED); return;
    printk(&video, "Everything's OK!", GREEN);
    (void)address;
    while(1) {
        asm __volatile (
            "hlt"
        )
    }
}