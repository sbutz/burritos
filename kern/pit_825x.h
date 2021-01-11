#ifndef _PIT_H
#define _PIT_H

#include <stdint.h>

#define PIT_PORT_0	0x40
#define PIT_PORT_1	0x41
#define PIT_PORT_2	0x42
#define PIT_PORT_CMD	0x43

#define PIT_BIN	0x0
#define PIT_BCD	0x1

#define PIT_MODE_INTR_ON_COUNT	0x0
#define PIT_MODE_ONE_SHOT	0x2
#define PIT_MODE_RATE		0x4
#define PIT_MODE_SQUARE_WAVE	0x6
#define PIT_MODE_SOFT_STROBE	0x8
#define PIT_MODE_HARD_STROBE	0xA

#define PIT_RW_INTERN	0x00
#define PIT_RW_LSB	0x10
#define PIT_RW_MSB	0x20
#define PIT_RW_LSB_MSB	0x30

#define PIT_CHANNEL_0	0x00
#define PIT_CHANNEL_1	0x40
#define PIT_CHANNEL_2	0x80
#ifdef PIT_8254
#define PIT_READ_BACK	0xC0
#endif

#define PIT_BASE_FREQ 1193182lu

void pit_init(uint16_t);

#endif
