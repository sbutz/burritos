#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_ENTRIES 256

#define IDT_FLAG_INTERRUPT_GATE 0x06
#define IDT_FLAG_TRAP_GATE 0x07
#define IDT_FLAG_TASK_GATE 0x05
#define IDT_FLAG_32_BIT 0x08
#define IDT_FLAG_RING0 0x00
#define IDT_FLAG_RING3 0x60
#define IDT_FLAG_PRESENT 0x80

struct idt_entry {
	uint16_t offset_lower;
	uint16_t selector;
	uint8_t unused;
	uint8_t flags;
	uint16_t offset_higher;
} __attribute__((packed));

struct idt_description {
	uint16_t limit;
	void *pointer;
} __attribute__((packed));

void idt_init();

struct idt_entry idt[IDT_ENTRIES];
struct idt_description idtp;

#endif
