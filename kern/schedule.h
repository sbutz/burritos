#ifndef _SCHEDULE_H
#define _SCHEDULE_H

#include "idt.h"

void schedule_init();
struct cpu_state *schedule(struct cpu_state *);

#endif
