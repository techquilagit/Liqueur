#pragma once
#include <stdint.h>
#include <kernel/kernel.h>
#include <color.h>
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
extern void clean(char* vga, int* x, int* y);
extern void InitPIC(void);
extern void PICSendEOI(uint8_t irq);
extern void InitIDT(void);
extern void SetGateIDT(uint8_t, uint32_t handler, uint8_t flags);
extern void KeyboardStub(void);
extern void KeyboardMain(void);
extern void EnableInterrupts(void);