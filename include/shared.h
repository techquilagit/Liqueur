#pragma once
#include <stdint.h>
#include <kernel/kernel.h>
#include <color.h>
extern int x;
extern int y;
extern Kernel core;
extern uint8_t inb(uint16_t scan);
extern void outb(uint16_t scan, uint8_t val);
extern void WriteWaitPS2(void);
extern void ReadWaitPS2(void);
extern void InitPS2(void);
extern uint8_t KbdReadP_oll(void);
extern void reboot(void);
extern void CheckKeyEvent(KeyEvent* ev);
extern char TranslateCode(uint8_t scancode);
extern void KeyboardMain(void);
extern void hlt(int key);
extern void printk(char* vga, const char* word, Color color, int* x, int* y);
extern void clean(char* vga, Color color, int *x, int* y);
extern void InitPIC(void);
extern void PICSendEOI(uint8_t irq);
extern void InitIDT(void);
extern void SetGateIDT(uint8_t, uint32_t handler, uint8_t flags);
extern void KeyboardStub(void);
extern void KeyboardMain(void);
extern void EnableInterrupts(void);
extern void DisableInterrupts(void);
extern void InitTimer(uint32_t frequency);
extern void TimerMain(void);
extern void TimerStub(void);