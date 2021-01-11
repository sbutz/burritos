#ifndef _PIC_H
#define _PIC_H

#include <stdint.h>

#define MASTER_PORT_CMD		0x20
#define MASTER_PORT_DATA	0x21
#define SLAVE_PORT_CMD		0xa0
#define SLAVE_PORT_DATA		0xa1

#define ICW1_ICW4	0x01
#define ICW1_NO_SLAVE	0x02
#define ICW1_INIT	0x10

#define ICW3_MASTER	0x04
#define ICW3_SLAVE	0x02

#define ICW4_PC		0x01
#define ICW4_AUTO	0x02

#define PIC_EOI	0x20

#define IRQ_OFFSET	0x20

#define IRQ_TIMER	0x0

void pic_init();
void pic_send_eoi(uint8_t);
void pic_mask_irq(uint8_t);
void pic_unmask_irq(uint8_t);

#endif
