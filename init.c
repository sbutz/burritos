#include "console.h"
#include "gdt.h"
#include "idt.h"

void init()
{
	kclear();
	kprintf("sButz OS v1.0\n\n");

	kprintf("[*] Init Global Descriptor Table\n");
	gdt_init();

	kprintf("[*] Init Interrupt Descriptor Table\n");
	idt_init();

	int x, y, z;
	x = 1;
	y = 0;
	z = x/y;
	//asm volatile("int $0x0");

	/* Interrupts aktivieren */
	asm volatile("sti");
}
