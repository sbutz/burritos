#ifndef _SYSTEM_H
#define _SYSTEM_H

void halt();
void enable_irqs();
void disable_irqs();
void panic(char *);

#endif
