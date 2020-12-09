#include "schedule.h"
#include "console.h"

#define STACK_SIZE 4096
#define MAX_TASKS 2

static struct cpu_state *task_init(void *fn, uint8_t *stack);
static void task_a();
static void task_b();
static void malicous_task_disable_inter();
static void malicous_task_write();

static struct cpu_state *task[MAX_TASKS];
static int num_tasks;
static int current_task;

static uint8_t stack_a[STACK_SIZE];
static uint8_t stack_b[STACK_SIZE];

void schedule_init()
{
	task[0] = task_init(task_a, stack_a);
	task[1] = task_init(malicous_task_write, stack_b);
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

// Disable interrrupts to prevent task switch
static void malicous_task_disable_inter()
{
	asm("cli");
	while (1)
		kprintf("It's just Rick and Morty\n");
}

// Overwrite foreign cpu_state block
// TODO: just overwrite forgein saved programm counter
static void malicous_task_write()
{
	uint8_t s;
	uint8_t *p;
	int i;

	for (i = 0; i < sizeof(struct cpu_state); i++)
	{
		p = (void *) (&s - 4096 - i);
		*p = 0x0;
	}

	while (1)
		kprintf("A hundred years Rick and Morty\n");
}
