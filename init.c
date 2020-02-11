#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "io.h"
#include "pic.h"
#include "system.h"

void init()
{
	kclear();
	kprintf("sButz OS v1.0\n\n");

	kprintf("[*] Init Global Descriptor Table\n");
	gdt_init();

	kprintf("[*] Init Interrupt Descriptor Table\n");
	idt_init();

	kprintf("[*] Init Programmable Interrupt Controller\n");
	pic_init();
	pic_mask_irq(IRQ_TIMER);

	uint16_t PORT = *((uint16_t *) 0x400);
	kprintf("X: %x\n", PORT);

	uint16_t EQUIPMENT_WORD = *((uint16_t *) 0x410);
	kprintf("X: %x\n", EQUIPMENT_WORD & 0xe00);

	#define TB 0
	#define IER 1
	#define LCR 3
	#define LSR 5

	outb(0x3FB, 0x83); /* DLAB = 1 */
	outb(0x3F8, 0x0C); /* 9600 Baud */
	outb(0x3F9, 0x00);
	outb(0x3FB, 0x03); /* DLAB = 0 */
	outb(0x3F9, 0x00); /* keine Interrupts auslösen */
	outb(0x3FA, 0x00); /* FIFOs deaktiviert (8250, 16450) */
	outb(0x3FC, 0x00); /* Loopback deaktivieren, Aux1 & Aux2 deaktivieren */


	while ((inb(PORT+LSR) & 0x20) == 0);
	outb(PORT, 'H');
	outb(PORT, 'E');
	outb(PORT, 'L');
	outb(PORT, 'L');
	outb(PORT, 'O');
	kprintf("INB: %x\n", inb(PORT+LSR));

	/* Hardware-Interrupts aktivieren */
	asm volatile("sti");

	while (1)
		cpu_relax();
}
