#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "idt.h"

void schedule_init();
struct cpu_state *schedule(struct cpu_state *cpu);

#endif
