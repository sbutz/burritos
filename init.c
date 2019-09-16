#include "console.h"
#include "gdt.h"

void init()
{
	kclear();
	kprintf("sButz OS v1.0\n\n");

	kprintf("[*] Init GDT\n");
	gdt_init();
}
