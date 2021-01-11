#include "io.h"
#include "uart_8250.h"

uint16_t PORT;

void
serial_init()
{
	/* Read Port from BIOS Data Area (BDA) */
	PORT = *((uint16_t *) 0x400);

	outb(PORT+LCR, 0x80);		/* DLAB = 1 */
	outb(PORT, 115200 / BAUD);
	outb(PORT+LCR, 0x0);		/* DLAB = 0 */
	//outb(PORT+IER, 0x0);		/* Enable no Interrupts */
	outb(PORT+IER, 0x1);		/* Enable data  available interrupt */
	outb(PORT+IIR, 0x0);		/* Disable FIFO */
	outb(PORT+MCR, 0x0);		/* Disable Loopback */
}

void
serial_putc(char c)
{
	while ((inb(PORT+LSR) & 0x20) == 0);

	outb(PORT, c);
}

void
serial_puts(char *s)
{
	while (*s != '\0')
	{
		serial_putc(*s);
		s++;
	}
}

char
serial_getc()
{
	while ((inb(PORT+LSR) & 1) == 0);

	return inb(PORT);
}
