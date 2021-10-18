#include "io.h"

uint8_t inb(uint16_t port)
{
	uint8_t tmp;
	asm volatile ("inb %w1, %b0": "=a"(tmp) : "d"(port));
	return tmp;
}

void outb(uint16_t port, uint8_t val)
{
	asm volatile ("outb %b0, %w1": : "a"(val), "d"(port));
}
