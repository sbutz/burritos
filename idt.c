#include "idt.h"

#include "console.h"

extern void idt_load();

static void idt_set_entry(unsigned int n, uint32_t offset, uint16_t selector,
	uint8_t flags) {

	idt[n].offset_lower = offset & 0xffff;
	idt[n].selector = selector;
	idt[n].unused = 0x0;
	idt[n].flags = flags;
	idt[n].offset_higher = offset >> 16;
}

void int_handler() {
	kprintf("Interrupt\n");
	while(1);
}

void idt_init() {
	idtp.limit = sizeof(struct idt_entry) * 8 - 1;
	idtp.pointer = idt;

	//TODO: Generischer Interrupt Handler, der die Nummer des Interrupts ausgibt

	/* 0x8 ist das Kernelcodesegment in der GDT */
	/* Jeder Eintrag ist 8 Byte gross + nulldeskriptor => offset 0x8 */
	idt_set_entry(0, (uintptr_t) &int_handler, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);

	idt_load();
}
