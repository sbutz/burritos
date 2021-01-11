#include "io.h"
#include "pic_8259.h"

/*
 * The Programmable Interrupt Controller (PIC) consists of a Master and a Slave.
 * Each of them has 8 Channels. The Slave is connected to the Mastsers IRQ 2.
 *
 * The first Interrupts numbers are reserved for Exceptions.They cannot be
 * remapped.
 * To distinct between Exceptions and Hardware Interrupts (IRQs), the IRQs have
 * to be remapped. Map them to 0x20.
 *
 * Remapping the IRQs:
 * 1. Send Init Command to the Command Port (0x20 or 0xa0).
 * 2. Send Interrupt Number for IRQ 0 or 8.
 * 3. Send the Master's Port where the Slave is connected to the Slave. Send
 *    0x04 to the Master.
 * 4. Send Flags (0x01).
 */
void
pic_init()
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

void
pic_send_eoi(uint8_t irq)
{
	if (irq >= 0x8)
		outb(SLAVE_PORT_CMD, PIC_EOI);
	outb(MASTER_PORT_CMD, PIC_EOI);
}

void
pic_mask_irq(uint8_t irq)
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

void
pic_unmask_irq(uint8_t irq)
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
