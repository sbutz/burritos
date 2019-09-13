#include <stdarg.h>

#include "console.h"

// Speicher ist 4kB gross.
// 80x25 Zeichen.
static char *video = (char*) 0xb8000;
static int cursor = 0;
static char HEX[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a',
	'b', 'c', 'd', 'e', 'f' };

static void _printc(char c);
static int _printp(void *ptr);
static int _printh(unsigned long num);

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

int kprintf(const char *fmt, ...) {
	int i, total;
	va_list args;

	va_start(args, fmt);
	for (i = 0, total = 0; fmt[i] != '\0'; i++) {
		if (i > 0 && fmt[i - 1] == '%') {
			cursor -= 2;
			switch(fmt[i]) {
				case 'p':
					total += _printp(va_arg(args, void *));
					break;
				case 'x':
					total += _printh(va_arg(args, unsigned long));
					break;
			}
		} else {
			_printc(fmt[i]);
			total++;
		}
	}
	va_end(args);

	return total;
}

static void _printc(char c) {
	if (cursor >= BUFFER_SIZE)
		kscroll();

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

static int _printp(void *ptr) {
	return _printh((unsigned long) ptr);
}

static int _printh(unsigned long num) {
	int i, total, digit;

	_printc('0');
	_printc('x');
	total = 2;

	for (i = 0; i < 32; i += 4) {
		digit = (num << i) >> 28;
		_printc(HEX[digit]);
		total++;
	}

	return total;
}
