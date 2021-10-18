#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "pic_8259.h"
#include "pit_825x.h"
#include "schedule.h"
#include "system.h"

void
main()
{
	console_init();
	kprintf("\n\nBurritos v1.0\n\n");

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
