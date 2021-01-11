#include <stdint.h>

#include "gdt.h"

struct tss_entry
{
   uint32_t prev_tss; /* Linked list entry if using hardware task switching. */
   uint32_t esp0;     /* Stack pointer to load when changing to kernel mode. */
   uint32_t ss0;      /* Stack segment to load when changing to kernel mode. */
   uint32_t esp1;     /* The remaining fields are unused. */
   uint32_t ss1;
   uint32_t esp2;
   uint32_t ss2;
   uint32_t cr3;
   uint32_t eip;
   uint32_t eflags;
   uint32_t eax;
   uint32_t ecx;
   uint32_t edx;
   uint32_t ebx;
   uint32_t esp;
   uint32_t ebp;
   uint32_t esi;
   uint32_t edi;
   uint32_t es;
   uint32_t cs;
   uint32_t ss;
   uint32_t ds;
   uint32_t fs;
   uint32_t gs;
   uint32_t ldt;
   uint16_t trap;
   uint16_t iomap_base;
} __packed;
typedef struct tss_entry tss_entry_t;

extern void gdt_load();
extern void tss_load();

static void gdt_set_entry(unsigned int, uint32_t, uint32_t, uint8_t, uint8_t);

static tss_entry_t tss;


void
gdt_init()
{
	gdtp.limit = GDT_ENTRIES * sizeof(struct gdt_entry) - 1;
	gdtp.pointer = gdt;

	/* Nulldeskriptor */
	gdt_set_entry(0, 0, 0, 0, 0);

	/* Codesegment Kernel */
	gdt_set_entry(1, 0, 0xfffff, GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 |
		GDT_ACCESS_SEGMENT | GDT_ACCESS_CODESEG, GDT_FLAG_32_BIT |
		GDT_FLAG_4K_GRAN);

	/* Datasegment Kernel */
	gdt_set_entry(2, 0, 0xfffff, GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 |
		GDT_ACCESS_SEGMENT | GDT_ACCESS_DATASEG, GDT_FLAG_32_BIT |
		GDT_FLAG_4K_GRAN);

	/* Codesegment Userspace */
	gdt_set_entry(3, 0, 0xfffff, GDT_ACCESS_PRESENT | GDT_ACCESS_RING3 |
		GDT_ACCESS_SEGMENT | GDT_ACCESS_CODESEG, GDT_FLAG_32_BIT |
		GDT_FLAG_4K_GRAN);

	/* Datasegment Userspace  */
	gdt_set_entry(4, 0, 0xfffff, GDT_ACCESS_PRESENT | GDT_ACCESS_RING3 |
		GDT_ACCESS_SEGMENT | GDT_ACCESS_DATASEG, GDT_FLAG_32_BIT |
		GDT_FLAG_4K_GRAN);

	/* Task State Segment Multitasking */
	gdt_set_entry(5, (uint32_t) &tss, sizeof(tss), GDT_ACCESS_TTSSEG |
		GDT_ACCESS_PRESENT | GDT_ACCESS_RING3, 0);

	/* Task State Segment Double Fault */
	/*TODO: implement */
	
	gdt_load();

	tss.ss0 = 0x10; /* Kernel Data Segment */
	tss_load();
}

void
tss_set_kernel_stack(uint32_t ptr)
{
	tss.esp0 = ptr;
}


static void
gdt_set_entry(unsigned int n, uint32_t base, uint32_t limit, uint8_t access,
	uint8_t flags)
{

	gdt[n].limit_lower = limit & 0xffff;
	gdt[n].base_lower = base & 0xffff;
	gdt[n].base_middle = (base >> 16) & 0xff;
	gdt[n].access = access;
	gdt[n].flags_limit_higher = (flags << 4) | ((limit >> 16) & 0xf);
	gdt[n].base_higher = base >> 24;
}
