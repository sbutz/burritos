#include <stddef.h>
#include <stdlib.h>
#include <syscall.h>

#include "console.h"
#include "gdt.h"
#include "pmm.h"
#include "queue.h"
#include "schedule.h"
#include "system.h"
#include "vmm.h"

struct task {
	struct cpu_state *state;
	uint8_t *stack;
	uint8_t *user_stack;
	struct vmm_context *vmm_ctx;
};

static struct task *task_create(void *);
static void task_delete(struct task *);
static void task_a();
static void task_b();
static void idle();
//static void malicous_task_disable_inter();
//static void malicous_task_write();

static struct queue *tasks;
static struct task *current_task;
static struct task *idle_task;


void
schedule_init()
{
	tasks = queue_init();
	current_task = NULL;
	idle_task = task_create(idle);

	queue_push(tasks, task_create(task_a));
	queue_push(tasks, task_create(task_b));
}

void
exit_current_task()
{
	task_delete(current_task);
	current_task = NULL;
}

struct cpu_state *
schedule(struct cpu_state *cpu)
{
	/* Save old cpu state */
	if (current_task != NULL)
	{
		current_task->state = cpu;
		queue_push(tasks, current_task);
	}

	/* Select next task */
	current_task = queue_pop(tasks);
	if (current_task == NULL)
		current_task = idle_task;

	return current_task->state;
}

static struct task *
task_create(void *fn)
{
	uintptr_t *exit_fn;
	struct cpu_state *state;
	struct task *t;

	//TODO: pmm_alloc durch vmm_alloc ersetzen
	//kernel memory in alle vmm_contexts mappen in vmm_context_create()
	//schedule muss vmm_ctx herstellen
	//vmm_map_page braucht flag fuer USER/KERNEL Memory
	//free methode um allen speicher in page tables (mit USER Flag) freizugeben
	//syscall fuer memory alloc

	t = pmm_alloc();
	t->state = pmm_alloc();
	t->stack = pmm_alloc();
	t->user_stack = pmm_alloc();
	t->vmm_ctx = vmm_context_create();

	t->state->eax = 0;
	t->state->ebx = 0;
	t->state->ecx = 0;
	t->state->edx = 0;
	t->state->esi = 0;
	t->state->edi = 0;
	t->state->ebp = 0;
	//t->state->intr = 0;
	//t->state->error_code = 0;
	t->state->eip = (uint32_t) fn;
	t->state->cs = 0x18 | 0x03; /* Ring 3 */
	t->state->eflags =  0x202; /* Interrupts enabled: IF = 1 */
	/* IF = 1 => 0x200, Reserved bit 0x002 is always 1 */
	t->state->esp = (uint32_t) t->user_stack + PAGE_SIZE;
	t->state->ss = 0x20 | 0x03; /* Ring 3 */

	/* Place exit function on stack */
	/* TODO: Test: what happens if modified by user */
	t->state->esp -= sizeof(uintptr_t);
	exit_fn = (void *) t->state->esp;
	*exit_fn = (uintptr_t) exit;

	/* Push Cpu state on Stack. IRET will restore the pushed state. */
	state = (void *) (t->stack + PAGE_SIZE - sizeof(t->state));
	*state = *(t->state);

	return t;
}

static void
task_delete(struct task *t)
{
	pmm_free(t->stack);
	pmm_free(t->user_stack);
	pmm_free(t);
}

static void
idle()
{
	while(1)
		halt();
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
			break;
		}
	}
	syscall(0x3);
	syscall(0x3);
	return;
}

//static void
//malicous_task_disable_inter()
//{
//	int i;
//
//	asm("cli");
//
//	while (1)
//	{
//		i++;
//		if (i == 0x0fffffff)
//		{
//			syscall(0x0);
//			i = 0;
//		}
//	}
//}

/*
 * Overwrite foreign cpu_state block.
 * TODO: Manipulate program counter.
 * Should not work after implementing memory virtualisation.
 */
//static void
//malicous_task_write()
//{
//	uint8_t s;
//	uint8_t *p;
//	int i;
//
//	for (i = 0; i < 2 * 4096; i++)
//	{
//		p = (void *) (&s - 2 * 4096 - i);
//		*p = 0x0;
//	}
//
//	while (1)
//	{
//		i++;
//		if (i == 0x0fffffff)
//		{
//			syscall(0x0);
//			i = 0;
//		}
//	}
//}
