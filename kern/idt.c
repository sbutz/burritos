#include <stdint.h>

#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "pic_8259.h"
#include "system.h"
#include "uart_8250.h"
#include "schedule.h"

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
static void handle_exception(struct cpu_state *cpu);
static struct cpu_state *handle_irq(struct cpu_state *cpu);
static void handle_syscall(struct cpu_state *cpu);

void idt_init()
{
	idtp.limit = sizeof(struct idt_entry) * IDT_ENTRIES - 1;
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
	idt_set_entry(3, (uintptr_t) &intr_stub_3, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(4, (uintptr_t) &intr_stub_4, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(5, (uintptr_t) &intr_stub_5, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(6, (uintptr_t) &intr_stub_6, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(7, (uintptr_t) &intr_stub_7, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(8, (uintptr_t) &intr_stub_8, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(9, (uintptr_t) &intr_stub_9, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(10, (uintptr_t) &intr_stub_10, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(11, (uintptr_t) &intr_stub_11, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(12, (uintptr_t) &intr_stub_12, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(13, (uintptr_t) &intr_stub_13, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(14, (uintptr_t) &intr_stub_14, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(15, (uintptr_t) &intr_stub_15, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(16, (uintptr_t) &intr_stub_16, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(17, (uintptr_t) &intr_stub_17, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);

	/* Hardware-Interrupts (IRQs) */
	idt_set_entry(32, (uintptr_t) &intr_stub_32, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(33, (uintptr_t) &intr_stub_33, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(34, (uintptr_t) &intr_stub_34, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(35, (uintptr_t) &intr_stub_35, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(36, (uintptr_t) &intr_stub_36, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(37, (uintptr_t) &intr_stub_37, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(38, (uintptr_t) &intr_stub_38, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(39, (uintptr_t) &intr_stub_39, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(40, (uintptr_t) &intr_stub_40, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(41, (uintptr_t) &intr_stub_41, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(42, (uintptr_t) &intr_stub_42, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(43, (uintptr_t) &intr_stub_43, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(44, (uintptr_t) &intr_stub_44, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(45, (uintptr_t) &intr_stub_45, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(46, (uintptr_t) &intr_stub_46, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);
	idt_set_entry(47, (uintptr_t) &intr_stub_47, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING0 | IDT_FLAG_32_BIT);

	/* Syscalls */
	idt_set_entry(48, (uintptr_t) &intr_stub_48, 0x8, IDT_FLAG_INTERRUPT_GATE |
		IDT_FLAG_PRESENT | IDT_FLAG_RING3 | IDT_FLAG_32_BIT);

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

struct cpu_state *handle_intr(struct cpu_state *cpu)
{
	/* Exception */
	if (cpu->intr < 0x20)
		handle_exception(cpu);
	/* IRQ */
	else if (cpu->intr < 0x30)
		return handle_irq(cpu);
	/* Syscalls */
	else
		handle_syscall(cpu);

	return cpu;
}

void handle_exception(struct cpu_state *cpu)
{
	kprintf("Exception %x, Error %x, halting Kernel\n", cpu->intr,
		cpu->error_code);


	cpu_state_dump(cpu);

	disable_irqs();
	while (1)
		cpu_relax();
}

struct cpu_state *handle_irq(struct cpu_state *cpu)
{
	struct cpu_state *ret = cpu;

	pic_mask_irq(cpu->intr - IRQ_OFFSET);

	switch (cpu->intr - IRQ_OFFSET) {
	case 0x0:
		ret = schedule(cpu);
		tss_set_kernel_stack((uint32_t) (ret + 1));
		break;
	case 0x4:
		serial_putc(serial_getc());
		break;
	default:
		kprintf("IRQ %x\n", cpu->intr);
		break;
	}

	pic_send_eoi(cpu->intr - IRQ_OFFSET);
	pic_unmask_irq(cpu->intr - IRQ_OFFSET);

	return ret;
}

void handle_syscall(struct cpu_state *cpu)
{
	kprintf("Interrupt %x\n", cpu->intr);
}

void cpu_state_dump(struct cpu_state *cpu)
{
	kprintf("\n");
	kprintf("EAX %x\n", cpu->eax);
	kprintf("EBX %x\n", cpu->ebx);
	kprintf("ECX %x\n", cpu->ecx);
	kprintf("EDX %x\n", cpu->edx);
	kprintf("ESI %x\n", cpu->esi);
	kprintf("EDI %x\n", cpu->edi);
	kprintf("EBP %x\n", cpu->ebp);
	kprintf("Instruction Pointer %x\n", cpu->eip);
	kprintf("Code Segment %x\n", cpu->cs);
	kprintf("Flags %x\n", cpu->eflags);
	kprintf("Stack Pointer %x\n", cpu->esp);
	kprintf("Stack Segment %x\n", cpu->ss);
	kprintf("\n");
}
