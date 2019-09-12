#include "console.h"

// Speicher ist 4kB gross.
// 80x25 Zeichen.
static char *video = (char*) 0xb8000;
static int cursor = 0;

void kclear() {
	int i;

	for (i = 0; i < BUFFER_SIZE; i++)
		video[i] = 0x0;
	cursor = 0;
}

void kscroll() {
	int i;

	for (i = 0; i < BUFFER_SIZE - LINE_SIZE; i++) {
		video[i] = video[i + LINE_SIZE];
	}
	for (i = BUFFER_SIZE - LINE_SIZE; i < BUFFER_SIZE; i++) {
		video[i] = 0x0;
	}

	cursor -= LINE_SIZE;
}

int kprintf(const char *fmt) {
	int i, offset;

	// bis Nullterminator erreicht ist
	for (i = 0; fmt[i] != '\0'; i++) {
		offset = cursor + i * 2;

		if (offset >= BUFFER_SIZE)
			kscroll();

		switch(fmt[i]) {
			case '\n':
				if ((cursor + i * 2)  % 160)
					cursor += 160 - ((cursor + i * 2) % 160) - 2;
				break;
			default:
				video[cursor + i * 2] = fmt[i];
				video[cursor + i * 2 + 1] = LIGHT_GRAY;
		}
	}
	cursor += i * 2;

	return  i;
}
