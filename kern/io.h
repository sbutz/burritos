#ifndef _IO_H
#define _IO_H

#include <stdint.h>

extern uint8_t inb(uint16_t);
extern void outb(uint16_t, uint8_t);

#endif
