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

	asm volatile("int $0x1");
	kprintf("After Itr\n");
	asm volatile("int $0x2");
	kprintf("After Itr\n");
}
