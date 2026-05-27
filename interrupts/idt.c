#include <stdint.h>
struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed));
struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
struct idt_entry idt_table[256];
struct idt_ptr idtr;
void SetGateIDT(uint8_t vector, uint32_t handler, uint8_t flags) {
    idt_table[vector].offset_low  = (uint16_t)(handler & 0xFFFF);
    idt_table[vector].selector    = 0x08;
    idt_table[vector].zero        = 0;
    idt_table[vector].type_attr   = flags;
    idt_table[vector].offset_high = (uint16_t)((handler >> 16) & 0xFFFF);
}
__attribute__((interrupt)) void DBZIDT(void* frame) {
    (void)frame;
    while(1);
}
__attribute__((interrupt)) void DefaultStubISR(void *frame) {
    (void)frame;
    outb(0x20, 0x20);
};
void InitIDT(void) {
    for (int i = 0; i < 256; i++) {
        SetGateIDT(i, (uint32_t)DefaultStubISR, 0x8E);
    }
    SetGateIDT(0, (uint32_t)DBZIDT, 0x8E);
    idtr.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtr.base = (uint32_t)&idt_table;
    __asm__ volatile (
        "lidt %0"
        :
        : "m"(idtr)
    );
}