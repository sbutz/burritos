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

int kprintf(const char *str) {
	int i;

	// bis Nullterminator erreicht ist
	//TODO: Pruefung, dass nicht ausserhalb des Videospeichers geschrieben wird
	for (i = 0; str[i] != '\0'; i++) {
		switch(str[i]) {
			case '\n':
				if ((cursor + i * 2)  % 160)
					cursor += 160 - ((cursor + i * 2) % 160) - 2;
				break;
			default:
				video[cursor + i * 2] = str[i];
				video[cursor + i * 2 + 1] = LIGHT_GRAY;
		}
	}
	cursor += i * 2;

	return  i;
}
