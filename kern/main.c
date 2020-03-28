#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "pic_8259.h"
#include "pit_825x.h"
#include "uart_8250.h"
#include "system.h"

void main()
{
	console_init();
	kprintf("sButz OS v1.0\n\n");

	kprintf("[*] Init Global Descriptor Table\n");
	gdt_init();

	kprintf("[*] Init Interrupt Descriptor Table\n");
	idt_init();

	kprintf("[*] Init Programmable Interrupt Controller\n");
	pic_init();
	pic_mask_irq(IRQ_TIMER);

	kprintf("[*] Init Programmable Interval Timer\n");
	pit_init(100);

	kprintf("[*] Init Serial Port\n");
	serial_init();

	serial_puts("Booting...");

	enable_irqs();

	while (1)
		cpu_relax();
}
