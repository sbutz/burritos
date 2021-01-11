#ifndef _SERIAL_H
#define _SERIAL_H

#define IER 1
#define IIR 2
#define LCR 3
#define MCR 4
#define LSR 5
#define MSR 6
#define SCR 7

#define BAUD 9600

void serial_init();
void serial_putc(char);
void serial_puts(char *);
char serial_getc();

#endif
