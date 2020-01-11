#ifndef ASM_H
#define ASM_H

#include <stdint.h>

extern void halt();
extern uint8_t inb(uint16_t port);
extern void outb(uint16_t port, uint8_t data);

#endif
