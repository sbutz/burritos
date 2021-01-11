#include <syscall.h>

#include "console.h"
#include "gdt.h"
#include "schedule.h"

#define STACK_SIZE 4096
#define MAX_TASKS 2

static struct cpu_state *task_init(void *, uint8_t *, uint8_t *);
static void task_a();
static void task_b();
static void malicous_task_disable_inter();
static void malicous_task_write();

static struct cpu_state *task[MAX_TASKS];
static int num_tasks;
static int current_task;

static uint8_t stack_a[STACK_SIZE];
static uint8_t user_stack_a[STACK_SIZE];
static uint8_t stack_b[STACK_SIZE];
static uint8_t user_stack_b[STACK_SIZE];

void
schedule_init()
{
	task[0] = task_init(task_a, stack_a, user_stack_a);
	task[1] = task_init(task_b, stack_b, user_stack_b);
	num_tasks = 2;
	current_task = -1;
}

static struct cpu_state
*task_init(void *fn, uint8_t *stack, uint8_t *user_stack)
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
		.cs = 0x18 | 0x03, /* Ring 3 */

		.eflags =  0x202, /* Interrupts enabled: IF = 1 */
		/* IF = 1 => 0x200, Reserved bit 0x002 is always 1 */

		.esp = (uint32_t) user_stack + STACK_SIZE,
		.ss = 0x20 | 0x03, /* Ring 3 */
	};


	/* Push Cpu state on Stack. IRET will restore the pushed state. */
	struct cpu_state *task = (void *) (stack + STACK_SIZE - sizeof(state));
	*task = state;

	return task;
}

struct cpu_state *
schedule(struct cpu_state *cpu)
{
	/* Save old cpu state */
	if (current_task >= 0)
		task[current_task] = cpu;

	/* Select next task */
	current_task = (current_task + 1) % num_tasks;
	return task[current_task];
}

static void
task_a()
{
	int i;

	while (1)
	{
		i++;
		if (i == 0x0fffffff)
		{
			syscall(0x1);
			i = 0;
		}
	}
}

static void
task_b()
{
	int i;

	while (1)
	{
		i++;
		if (i == 0x0fffffff)
		{
			syscall(0x2);
			i = 0;
		}
	}
}

static void
malicous_task_disable_inter()
{
	int i;

	asm("cli");

	while (1)
	{
		i++;
		if (i == 0x0fffffff)
		{
			syscall(0x0);
			i = 0;
		}
	}
}

/*
 * Overwrite foreign cpu_state block.
 * TODO: Manipulate program counter.
 * Should not work after implementing memory virtualisation.
 */
static void
malicous_task_write()
{
	uint8_t s;
	uint8_t *p;
	int i;

	for (i = 0; i < 2 * 4096; i++)
	{
		p = (void *) (&s - 2 * 4096 - i);
		*p = 0x0;
	}

	while (1)
	{
		i++;
		if (i == 0x0fffffff)
		{
			syscall(0x0);
			i = 0;
		}
	}
}
