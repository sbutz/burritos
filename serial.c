#include "io.h"
#include "serial.h"

uint16_t PORT;

void serial_init()
{
	PORT = *((uint16_t *) 0x400);

	outb(PORT+LCR, 0x80); /* DLAB = 1 */
	outb(PORT, 115200 / BAUD);
	outb(PORT+LCR, 0x0); /* DLAB = 0 */
	outb(PORT+IER, 0x0); /* Enable no Interrupts */
	outb(PORT+IIR, 0x0); /* Disable FIFO */
	outb(PORT+MCR, 0x0); /* Disable Loopback */
}

void serial_putc(char c)
{
	while ((inb(PORT+LSR) & 0x20) == 0);
		outb(PORT, c);
}

void serial_puts(char *s)
{
	while (*s != '\0')
	{
		serial_putc(*s);
		s++;
	}
}

char serial_getc();
