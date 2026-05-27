#pragma once
#define KEY_DBZ_ERROR 0xDBZ
#include <bool.h>
#include <stdint.h>
extern void outb(uint16_t scan, uint8_t val);
extern uint8_t inb(uint16_t scan);
extern char TranslateCode(uint8_t scancode);
typedef struct {
    char key;
    uint8_t keycode;
    bool pressed;
    bool extended;
    int dbz;
} __attribute__((packed)) KeyEvent;
void CheckKeyEvent(KeyEvent* ev);