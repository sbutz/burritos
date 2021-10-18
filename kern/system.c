#include "console.h"
#include "system.h"

void halt()
{
	asm volatile ("hlt");
}

void enable_irqs()
{
	asm volatile ("sti");
}

void disable_irqs()
{
	asm volatile ("cli");
}

void panic(char *msg)
{
	disable_irqs();
	kprintf("PANIC: %s\n", msg);
	halt();
}
