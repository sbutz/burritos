#include <stdint.h>

#include "asm.h"
#include "console.h"
#include "idt.h"

extern void idt_load();

/* Exceptions */
extern void intr_stub_0();
extern void intr_stub_1();
extern void intr_stub_2();
extern void intr_stub_3();
extern void intr_stub_4();
extern void intr_stub_5();
extern void intr_stub_6();
extern void intr_stub_7();
extern void intr_stub_8();
extern void intr_stub_9();
extern void intr_stub_10();
extern void intr_stub_11();
extern void intr_stub_12();
extern void intr_stub_13();
extern void intr_stub_14();
extern void intr_stub_15();
extern void intr_stub_16();
extern void intr_stub_17();
extern void intr_stub_18();

/* Hardware-Interrupts (IRQs) */
extern void intr_stub_32();
extern void intr_stub_33();
extern void intr_stub_34();
extern void intr_stub_35();
extern void intr_stub_36();
extern void intr_stub_37();
extern void intr_stub_38();
extern void intr_stub_39();
extern void intr_stub_40();
extern void intr_stub_41();
extern void intr_stub_42();
extern void intr_stub_43();
extern void intr_stub_44();
extern void intr_stub_45();
extern void intr_stub_46();
extern void intr_stub_47();

/* Syscalls */
extern void intr_stub_48();


static void idt_set_entry(unsigned int n, uint32_t offset, uint16_t selector,
	uint8_t flags);
static void pic_init();


void idt_init()
{
	pic_init();

	idtp.limit = sizeof(struct idt_entry) * 8 - 1;
	idtp.pointer = idt;

	/* 0x8 ist das Kernelcodesegment in der GDT */
	/* Jeder Eintrag ist 8 Byte gross + nulldeskriptor => offset 0x8 */

	/* Exceptions */
	idt_set_entry(0, (uintptr_t) &intr_stub_0, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(1, (uintptr_t) &intr_stub_1, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_2, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_3, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_4, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_5, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_6, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_7, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_8, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_9, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_10, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_11, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_12, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_13, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_14, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_15, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_16, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_17, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);

	/* Hardware-Interrupts (IRQs) */
	idt_set_entry(2, (uintptr_t) &intr_stub_32, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_33, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_34, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_35, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_36, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_37, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_38, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_39, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_40, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_41, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_42, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_43, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_44, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_45, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_46, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(2, (uintptr_t) &intr_stub_47, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);

	/* Syscalls */
	idt_set_entry(2, (uintptr_t) &intr_stub_48, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);

	idt_load();
}

static void idt_set_entry(unsigned int n, uint32_t offset, uint16_t selector,
	uint8_t flags)
{

	idt[n].offset_lower = offset & 0xffff;
	idt[n].selector = selector;
	idt[n].unused = 0x0;
	idt[n].flags = flags;
	idt[n].offset_higher = offset >> 16;
}

static void pic_init()
{
	/*
	 * PIC ist der Programmable Interrupt Controller.
	 * Der PIC besteht aus Master PIC und Slave PIC mit je 8 Kanaelen.
	 * Der Slave wird am IRQ2 des Master angeschlossen.
	 *
	 * Auf den ersten Interuptnummer liegen Exceptions und Hardware-Interrupts.
	 * Zur Unterscheidung werden die Hardware-Interrupts verschoben. Exceptions
	 * koennen nicht verschoben werden. Verschiebe Hardware-Interrupts auf 0x20.
	 *
	 * Vorgehensweise:
	 * 1. Schicke Init-Befehl an Befehlsport (0x20 bzw. 0xa0)
	 * 2. Schicke Interrupt-Nummer fuer IRQ bzw IRQ8
	 * 3. Schicke fuer Master 0x04, fuer Slave den IRQ an welchem er am Master
	 * angeschlossen ist.
	 * 4. Schicke Flags (0x01).
	 */
	outb(0x20, 0x11);
	outb(0x21, 0x20);
	outb(0x21, 0x04);
	outb(0x21, 0x01);

	outb(0xa0, 0x11);
	outb(0xa1, 0x28);
	outb(0xa1, 0x02);
	outb(0xa1, 0x01);

	outb(0x21, 0x0);
	outb(0xa1, 0x0);
}

void intr_handler(struct cpu_state cpu)
{
	#if 0
	kprintf("EAX %x\n", stack.eax);
	kprintf("EBX %x\n", stack.ebx);
	kprintf("ECX %x\n", stack.ecx);
	kprintf("EDX %x\n", stack.edx);
	kprintf("ESI %x\n", stack.esi);
	kprintf("EDI %x\n", stack.edi);
	kprintf("EBP %x\n", stack.ebp);
	kprintf("Instruction Pointer %x\n", stack.eip);
	kprintf("Code Segment %x\n", stack.cs);
	kprintf("Flags %x\n", stack.eflags);
	kprintf("Stack Pointer %x\n", stack.esp);
	kprintf("Stack Segment %x\n", stack.ss);
	#endif

	/* Exception */
	if (cpu.intr < 0x20)
	{
		kprintf("Exception %x, halt Kernel\n", cpu.error_code);

		while (1)
			halt();
	}
	/* IRQ */
	else if (cpu.intr < 0x30)
	{
		kprintf("IRQ %x\n", cpu.intr);

		if (cpu.intr > 0x27)
			outb(0xa0, 0x20);
		outb(0x20, 0x20);
	}
	/* Syscalls */
	else
	{
		kprintf("Interrupt %x\n", cpu.intr);
	}
}
