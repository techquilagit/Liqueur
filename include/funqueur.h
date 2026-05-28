#pragma once
#include <multiboot2.h>
#include <color.h>
#include <bool.h>
#include <stdint.h>
#include <isr.h>
#define VIDEO (char*)0xB8000
#define CLEAR ' '
#define FLAG_REBOOT_AFTER_HALT 1
#define NONE 0x0
#define SCREEN 80*25
enum Code;
void hlt(int key) {
    if (key == FLAG_REBOOT_AFTER_HALT) reboot();
    if (key != FLAG_REBOOT_AFTER_HALT) {
        __asm__ __volatile__(
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
void clean(char* vga, Color color, int* x, int* y) {
    for (int i = 0; i < SCREEN; i++) {
        vga[i*2] = CLEAR; vga[i*2+1] = color;
    }
    *x = 0;
    *y = 0;
}
void EnableInterrupts(void) {
    __asm__ __volatile__("sti");
}
void DisableInterrupts(void) {
    __asm__ __volatile__("cli");
}
void KernelPanic(int flag) {
    clean(VIDEO, BLUE, &x, &y);
    if (flag == FLAG_DOUBLE_FAULT) printk(VIDEO, DOUBLE_FAULT, WHITE, &x, &y);
    if (flag == FLAG_TRIPLE_FAULT) printk(VIDEO, TRIPLE_FAULT, WHITE, &x, &y);
    if (flag == FLAG_PAGE_FAULT)   printk(VIDEO, PAGE_FAULT, WHITE, &x, &y);
    hlt(NONE);
}