#include "io.h"
#include "pic.h"

/*
 * PIC ist der Programmable Interrupt Controller.
 * Der PIC besteht aus Master PIC und Slave PIC mit je 8 Kanaelen.
 * Der Slave wird am IRQ2 des Master angeschlossen.
 *
 * Auf den ersten Interuptnummer liegen Exceptions und Hardware-Interrupts.
 * Zur Unterscheidung werden die Hardware-Interrupts verschoben. Exceptions
 * koennen nicht verschoben werden. Verschiebe Hardware-Interrupts auf 0x20.
 *
 * Vorgehensweise:
 * 1. Schicke Init-Befehl an Befehlsport (0x20 bzw. 0xa0)
 * 2. Schicke Interrupt-Nummer fuer IRQ bzw IRQ8
 * 3. Schicke fuer Master 0x04, fuer Slave den IRQ an welchem er am Master
 * angeschlossen ist.
 * 4. Schicke Flags (0x01).
 */
void pic_init()
{
	outb(MASTER_PORT_CMD, 0x11);
	outb(SLAVE_PORT_CMD, 0x11);

	outb(MASTER_PORT_DATA, IRQ_OFFSET);
	outb(SLAVE_PORT_DATA, IRQ_OFFSET + 8);

	outb(MASTER_PORT_DATA, 0x04);
	outb(SLAVE_PORT_DATA, 0x02);

	outb(MASTER_PORT_DATA, 0x01);
	outb(SLAVE_PORT_DATA, 0x01);

	outb(MASTER_PORT_DATA, 0x0);
	outb(SLAVE_PORT_DATA, 0x0);
}

void pic_send_eoi(uint8_t irq)
{
	if (irq >= 0x8)
		outb(SLAVE_PORT_CMD, PIC_EOI);
	outb(MASTER_PORT_CMD, PIC_EOI);
}

void pic_mask_irq(uint8_t irq)
{
	uint8_t mask;
	uint16_t port;

	if (irq < 8)
	{
		port = MASTER_PORT_DATA;
	}
	else
	{
		port = SLAVE_PORT_DATA;
		irq -= 8;
	}

	mask = inb(port) | (0x1 << irq);
	outb(port, mask);
}

void pic_unmask_irq(uint8_t irq)
{
	uint8_t mask;
	uint16_t port;

	if (irq < 8)
	{
		port = MASTER_PORT_DATA;
	}
	else
	{
		port = SLAVE_PORT_DATA;
		irq -= 8;
	}

	mask = inb(port) & ~ (0x1 << irq);
	outb(port, mask);
}
