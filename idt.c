#include <stdint.h>

#include "idt.h"
#include "console.h"

extern void idt_load();
extern void intr_handler_1();
extern void intr_handler_2();

static void idt_set_entry(unsigned int n, uint32_t offset, uint16_t selector,
	uint8_t flags);

void idt_init() {
	idtp.limit = sizeof(struct idt_entry) * 8 - 1;
	idtp.pointer = idt;

	/* 0x8 ist das Kernelcodesegment in der GDT */
	/* Jeder Eintrag ist 8 Byte gross + nulldeskriptor => offset 0x8 */
	idt_set_entry(0, (uintptr_t) &intr_handler, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(1, (uintptr_t) &intr_handler_1, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_handler_2, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);

	idt_load();
}

static void idt_set_entry(unsigned int n, uint32_t offset, uint16_t selector,
	uint8_t flags) {

	idt[n].offset_lower = offset & 0xffff;
	idt[n].selector = selector;
	idt[n].unused = 0x0;
	idt[n].flags = flags;
	idt[n].offset_higher = offset >> 16;
}

void intr_handler(struct stack_state stack) {
	#if 0
	kprintf("EAX %x\n", stack.eax);
	kprintf("EBX %x\n", stack.ebx);
	kprintf("ECX %x\n", stack.ecx);
	kprintf("EDX %x\n", stack.edx);
	kprintf("ESI %x\n", stack.esi);
	kprintf("EDI %x\n", stack.edi);
	kprintf("EBP %x\n", stack.ebp);
	#endif
	kprintf("Interrupt %x\n", stack.intr);
	kprintf("Error Code %x\n", stack.error_code);
	#if 0
	kprintf("Instruction Pointer %x\n", stack.eip);
	kprintf("Code Segment %x\n", stack.cs);
	kprintf("Flags %x\n", stack.eflags);
	kprintf("Stack Pointer %x\n", stack.esp);
	kprintf("Stack Segment %x\n", stack.ss);
	#endif
}
