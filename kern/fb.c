#include "fb.h"

static char *video = (char*) 0xb8000; /* VGA Video Memory */
static int cursor = 0;

static void fb_scroll();

void
fb_init()
{
	int i;

	for (i = 0; i < BUFFER_SIZE; i++)
		video[i] = 0x0;
	cursor = 0;
}

void
fb_putc(char c)
{
	if (cursor >= BUFFER_SIZE)
		fb_scroll();

	switch(c) {
		case '\n':
			cursor += 160 - (cursor % 160) - 2;
			break;
		default:
			video[cursor] = c;
			video[cursor + 1] = LIGHT_GRAY;
	}

	cursor += 2;
}


void
fb_scroll()
{
	int i;

	for (i = 0; i < BUFFER_SIZE - LINE_SIZE; i++) {
		video[i] = video[i + LINE_SIZE];
	}
	for (; i < BUFFER_SIZE; i++) {
		video[i] = 0x0;
	}
	cursor -= LINE_SIZE;
}
