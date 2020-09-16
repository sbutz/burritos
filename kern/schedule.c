#include "schedule.h"
#include "console.h"

#define STACK_SIZE 4096
#define MAX_TASKS 2

static struct cpu_state *task_init(void *fn, uint8_t *stack);
static void task_a();
static void task_b();

static struct cpu_state *task[MAX_TASKS];
static int num_tasks;
static int current_task;

static uint8_t stack_a[STACK_SIZE];
static uint8_t stack_b[STACK_SIZE];

void schedule_init()
{
	task[0] = task_init(task_a, stack_a);
	task[1] = task_init(task_b, stack_b);
	num_tasks = 2;
	current_task = -1;
}

static struct cpu_state *task_init(void *fn, uint8_t *stack)
{
	struct cpu_state state = {
		.eax = 0,
		.ebx = 0,
		.ecx = 0,
		.edx = 0,
		.esi = 0,
		.edi = 0,
		.ebp = 0,

		//.intr = 0,
		//.error_code = 0,

		.eip = (uint32_t) fn,
		.cs = 0x08, /* Ring 0 */

		.eflags =  0x202, /* Interrupts eingeschaltet: IF = 1 */
		// IF = 1 => 0x200, Reserved bit 0x002 is always 1

		//.ss = ungenutzt
		//.esp = ungenutzt
	};


	// CPU Zustand auf Stack ablegen damit er durch interrupt handler
	// wiederhergestellt (= gestartet) werden kann
	struct cpu_state *task = (void *) (stack + STACK_SIZE - sizeof(state));
	*task = state;

	return task;
}

struct cpu_state *schedule(struct cpu_state *cpu)
{
	// Alten Cpu Stand sichern
	if (current_task >= 0)
		task[current_task] = cpu;

	// Naechsten Task auswaehlen und zurueckgeben
	current_task = (current_task + 1) % num_tasks;
	return task[current_task];
}

static void task_a()
{
	while (1)
		kprintf("A\n");
}

static void task_b()
{
	while (1)
		kprintf("B\n");
}
