#pragma once
#include <bool.h>
#include <stdint.h>
typedef struct {
    char key;
    uint8_t keycode;
    bool pressed;
    bool extended;
} __attribute__((packed)) KeyEvent;
typedef struct {
    uint32_t ticks;
    uint32_t seconds;
    uint32_t frequency;
    bool triggered;
} __attribute__((packed)) TimerEvent;
void CheckKeyEvent(KeyEvent* ev);