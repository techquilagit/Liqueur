#include <stdint.h>
#include "../../bool.h"
#include "../../color.h"
enum Code {
    KEY_A = 0x1E,
    KEY_B = 0x30,
    KEY_C = 0x2E,
    KEY_D = 0x20,
    KEY_E = 0x12,
    KEY_F = 0x21,
    KEY_G = 0x22,
    KEY_H = 0x23,
    KEY_I = 0x17,
    KEY_J = 0x24,
    KEY_K = 0x25,
    KEY_L = 0x26,
    KEY_M = 0x32,
    KEY_N = 0x31,
    KEY_O = 0x18,
    KEY_P = 0x19,
    KEY_Q = 0x10,
    KEY_R = 0x13,
    KEY_S = 0x1F,
    KEY_T = 0x14,
    KEY_U = 0x16,
    KEY_V = 0x2F,
    KEY_W = 0x11,
    KEY_X = 0x2D,
    KEY_Y = 0x15,
    KEY_Z = 0x2C,
    KEY_ESCAPE = 0x1,
    KEY_L_ALT = 0x38,
    KEY_L_SHIFT = 0x2A,
    KEY_L_CTRL = 0x1D,
    KEY_R_ALT = 0x138,
    KEY_R_SHIFT = 0x36,
    KEY_R_CTRL = 0x11D,
    KEY_TAB = 0x0F,
    KEY_ENTER = 0x1C,
    KEY_CAPSLOCK = 0xA3,
    KEY_BACKSPACE = 0x0E,
    KEY_SPACE = 0x39
};
uint8_t inb(uint16_t scan) {
    uint8_t ret;
    __asm__ __volatile ("inb %w1, %0" : "=a" (ret): "Nd" (scan));
    return ret;
}
void outb(uint16_t scan, uint8_t val) {
    __asm__ __volatile ("outb %0, %w1" : : "a" (val), "Nd" (scan));
}
void ps2_write_wait(void) {
    while (inb(0x64) & 0x02);
}
void ps2_read_wait(void) {
    while ((inb(0x64) & 0x01) == 0);
}
void ps2_init(void) {
    while (inb(0x64) & 0x01) inb(0x60);
    ps2_write_wait();
    outb(0x64, 0xAE);
    ps2_write_wait();
    outb(0x60, 0xFF);
    ps2_read_wait();
    if (inb(0x60) == 0xFA) {ps2_read_wait(); inb(0x60);}
}
uint8_t kbd_read_poll(void) {
    if ((inb(0x64) & 0x01) == 0) {
        return 0;
    }
    return inb(0x60);
}
void reboot(void) { 
    outb(0xFE, 0x64);
}
#define VIDEO (char*)0xB8000
extern void printk(char* vga, const char* word, Color color, int* x, int* y);
extern int x;
extern int y;
char TranslateCode() {
    while ((inb(0x64) & 0x01) == 0) {};
    unsigned char scancode = inb(0x60);
    if (scancode >= 0x80) return 0;
    switch (scancode) {
        case KEY_A: return 'A';
        case KEY_B: return 'B';
        case KEY_C: return 'C';
        case KEY_D: return 'D';
        case KEY_E: return 'E';
        case KEY_F: return 'F';
        case KEY_G: return 'G';
        case KEY_H: return 'H';
        case KEY_I: return 'I';
        case KEY_J: return 'J';
        case KEY_K: return 'K';
        case KEY_L: return 'L';
        case KEY_M: return 'M';
        case KEY_N: return 'N';
        case KEY_O: return 'O';
        case KEY_P: return 'P';
        case KEY_Q: return 'Q';
        case KEY_R: return 'R';
        case KEY_S: return 'S';
        case KEY_T: return 'T';
        case KEY_U: return 'U';
        case KEY_V: return 'V';
        case KEY_W: return 'W';
        case KEY_X: return 'X';
        case KEY_Y: return 'Y';
        case KEY_Z: return 'Z';
        case KEY_SPACE: return ' ';
        case KEY_ENTER: return '\n';
        default: return 0;
    }
}
void dmain(char* kb, int* index) {
    char c = TranslateCode();
    if (c == 0) return;
    if (*index < 255) {
        kb[(*index)++] = c;
        kb[*index] = '\0';
    }
    char echo[2] = {c, '\0'};
    printk(VIDEO, echo, WHITE, &x, &y);
}