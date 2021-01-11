#include "io.h"
#include "pit_825x.h"

void
pit_init(uint16_t freq)
{
	uint16_t counter = PIT_BASE_FREQ / freq;
	outb(PIT_PORT_CMD, PIT_BIN | PIT_MODE_RATE | PIT_RW_LSB_MSB |
		PIT_CHANNEL_0);
	outb(PIT_PORT_0, counter & 0xff);
	outb(PIT_PORT_0, counter >> 8);
}
