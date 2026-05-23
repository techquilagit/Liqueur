#pragma once
#include "multiboot2.h"
#include "color.h"
#include "bool.h"
#include <stdint.h>
#define VIDEO (char*)0xB8000
#define INVMAG (char*)"Invalid magic address"
#define EVRISOK (char*)"Everything's okay. For now."
#define CLEAR ' '
#define FLAG_REBOOT_AFTER_HALT 1
#define NONE 0x0
#define SCREEN 80*25
enum Code;
uint8_t inb(uint16_t scan);
void outb(uint16_t scan, uint8_t val);
void ps2_write_wait();
void ps2_read_wait(void);
void ps2_init(void);
uint8_t kbd_read_poll(void);
void reboot(void);
void hlt(int key) {
    if (key == FLAG_REBOOT_AFTER_HALT) reboot();
    if (key != FLAG_REBOOT_AFTER_HALT) {
        __asm__ __volatile (
            "hlt"
            :
            :
            : "memory"
        );
    }
}
    
void printk(char* vga, const char* word, Color color, int* x, int* y) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == '\n') {
            *x = 0;
            (*y)++;
            continue;
        }
        int index = ((*y) * 80 + (*x)) * 2;
        vga[index] = word[i]; vga[index+1] = (char)color;
        (*x)++;
        if (*x >= 80) {
            *x = 0;
            (*y)++;
        }
        if (*y >= 25) {
            *x = 0;
            (*y) = 0;
        }
    }
}
void clean(char* vga, int* x, int* y) {
    for (int i = 0; i < SCREEN; i++) {
        vga[i*2] = CLEAR; vga[i*2+1] = BLACK;
    }
    *x = 0;
    *y = 0;
}