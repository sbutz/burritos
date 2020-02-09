#ifndef ASM_H
#define ASM_H

#include <stdint.h>

extern void relax();
extern void disable_irqs();
extern uint8_t inb(uint16_t port);
extern void outb(uint16_t port, uint8_t data);

#endif
