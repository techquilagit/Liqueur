#include <funqueur.h>
#include <kernel/kernel.h>
#include <shared.h>
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
int x = 0;
int y = 0;
Kernel core;
KeyEvent ev;
void startk(uint32_t magic, uint32_t address) {
    char* video = VIDEO;
    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) { printk(video, "Invalid magic.", RED, &x, &y); hlt(FLAG_REBOOT_AFTER_HALT); }
    clean(video, &x, &y);
    (void)address;
    core.keyev = &ev;
    InitIDT();
    InitPIC();
    InitPS2();
    EnableInterrupts();
    while(1) {
        if (core.keyev->pressed) {
            char c = core.keyev->key;
            if (c != 0) {
                char code[2]= {c, '\0'};
                printk(video, code, GREEN, &x, &y);
            }
            core.keyev->pressed = false;
        }
    }
}