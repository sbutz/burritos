#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "multiboot.h"
#include "pic_8259.h"
#include "pit_825x.h"
#include "pmm.h"
#include "schedule.h"
#include "system.h"

void
main(struct multiboot_info *mbs)
{
	console_init();
	kprintf("Burritos\n");
	kprintf("Version 1.0\n");

	if (mbs->flags & MULTIBOOT_INFO_CMDLINE)
		kprintf("Cmdline: %s\n", mbs->cmdline);

	kprintf("[*] Init Physical Memory Manager\n");
	pmm_init(mbs);

	kprintf("[*] Init Global Descriptor Table\n");
	gdt_init();

	kprintf("[*] Init Interrupt Descriptor Table\n");
	idt_init();

	kprintf("[*] Init Programmable Interrupt Controller\n");
	pic_init();
	pic_mask_irq(IRQ_TIMER);

	kprintf("[*] Init Programmable Interval Timer\n");
	pit_init(100);

	kprintf("[*] Init Scheduler\n");
	schedule_init();

	pic_unmask_irq(IRQ_TIMER);
	enable_irqs();

	halt();
}
