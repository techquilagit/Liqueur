#include "funqueur.h"
__attribute__((section(".multiboot2"), used))
const struct {
    unsigned int magic;
    unsigned int architecture;
    unsigned int header_length;
    unsigned int checksum;
    unsigned short tag_type;
    unsigned short tag_flags;
    unsigned int tag_size;
} multiboot_header = {
    MULTIBOOT2_HEADER_MAGIC,
    0,
    24,
    (unsigned int)-(MULTIBOOT2_HEADER_MAGIC + 0 + 24),
    0,
    0,
    8
};
extern void dmain(char* kb, int *index);
int x = 0;
int y = 0;
void startk(unsigned int magic, unsigned long address) {
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {}
    char* video = VIDEO;
    char kb = 0;
    int index = 256;
    clean(video, &x, &y);
    (void)address;
    while(1) {
        dmain(&kb, &index);
        hlt(NONE);
    }
}
