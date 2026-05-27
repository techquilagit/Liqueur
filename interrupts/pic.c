#include <stdint.h>
#include <shared.h>
#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1
#define ICW1_INIT    0x10
#define ICW1_ICW4    0x01
#define ICW4_8086    0x01
#define PIC_EOI      0x20
static inline void WaitIO(void) {
    outb(0x80, 0);
}

void InitPIC(void) {
    uint8_t a1 = inb(PIC1_DATA);
    uint8_t a2 = inb(PIC2_DATA);
    (void)a1;
    (void)a2;
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); WaitIO();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4); WaitIO();
    outb(PIC1_DATA, 0x20); WaitIO();
    outb(PIC2_DATA, 0x28); WaitIO();
    outb(PIC1_DATA, 4); WaitIO();
    outb(PIC2_DATA, 2); WaitIO();
    outb(PIC1_DATA, ICW4_8086); WaitIO();
    outb(PIC2_DATA, ICW4_8086); WaitIO();
    outb(PIC1_DATA, 0x00); WaitIO();
    outb(PIC2_DATA, 0x00); WaitIO();
}
void PICSendEOI(uint8_t irq) {
    if (irq >= 8) {
        outb(PIC2_COMMAND, PIC_EOI);
    }
    outb(PIC1_COMMAND, PIC_EOI);
}