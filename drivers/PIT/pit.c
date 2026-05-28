#include <kernel/kernel.h>
#include <shared.h>
#define PIT_COMMAND 0x43
#define PIT_DATA 0x40
void InitTimer(uint32_t frequency) {
    core.timev->frequency = frequency;
    uint32_t divisor = 1193182 / frequency;
    outb(PIT_COMMAND, 0x36);
    outb(PIT_DATA, (uint8_t)(divisor & 0xFF));
    outb(PIT_DATA, (uint8_t)((divisor >> 8) & 0xFF));
}
void TimerMain(void) {
    core.timev->ticks++;
    if (core.timev->ticks % 100 == 0) {
        core.timev->seconds++;
    }
    core.timev->triggered = true;
    PICSendEOI(0);
}