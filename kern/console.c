#include <stdarg.h>

#include "console.h"
#include "fb.h"

static char HEX[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a',
	'b', 'c', 'd', 'e', 'f' };

static void _printc(char c);
static int _printp(void *ptr);
static int _printh(unsigned int num);

void console_init()
{
	fb_init();
}

int kprintf(const char *fmt, ...)
{
	int i, total;
	va_list args;

	va_start(args, fmt);
	for (i = 0, total = 0; fmt[i] != '\0'; i++) {
		if (i > 0 && fmt[i - 1] == '%') {
			switch(fmt[i]) {
				case 'p':
					total += _printp(va_arg(args, void *));
					break;
				case 'x':
					total += _printh(va_arg(args, unsigned int));
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

static void _printc(char c)
{
	fb_putc(c);
}

static int _printp(void *ptr)
{
	return _printh((unsigned int) ptr);
}

static int _printh(unsigned int num)
{
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
