#pragma once
#include <shared.h>
#define DOUBLE_FAULT     "The system has been faulted. DOUBLE FAULT"
#define TRIPLE_FAULT     "The system has been faulted. TRIPLE FAULT"
#define PAGE_FAULT       "The system has been faulted. PAGE FAULT"
#define FLAG_DOUBLE_FAULT 1
#define FLAG_TRIPLE_FAULT 2
#define FLAG_PAGE_FAULT   3
#define IRQ1_TIMER        0
#define IRQ1_KEYBOARD     1
#define IRQ1_CASCADE      2
#define IRQ1_COM2_COM4    3
#define IRQ1_COM1_COM3    4
#define IRQ1_SOUND        5
#define IRQ1_FLOPPY       6
#define IRQ1_PRINTER      7
#define IRQ2_RTC          8
#define IRQ2_ACPI         9
#define IRQ2_RESERVED1    10
#define IRQ2_RESERVED2    11
#define IRQ2_TOUCHPAD     12
#define IRQ2_FPU          13
#define IRQ2_ATA1         14
#define IRQ2_ATA2         15