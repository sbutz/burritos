#ifndef _GDT_H
#define _GDT_H

#include <stdint.h>

#define GDT_ACCESS_PRESENT 0x80
#define GDT_ACCESS_RING0 0x00
#define GDT_ACCESS_RING3 0x60
#define GDT_ACCESS_SEGMENT 0x10

#define GDT_ACCESS_DATASEG 0x02
#define GDT_ACCESS_CODESEG 0x0a
#define GDT_ACCESS_TTSSEG 0x09

#define GDT_FLAG_4K_GRAN 0x08
#define GDT_FLAG_32_BIT 0x04

struct gdt_entry
{
	uint16_t limit_lower;
	uint16_t base_lower;
	uint8_t base_middle;
	uint8_t access;
	uint8_t flags_limit_higher;
	uint8_t base_higher;
} __attribute__((packed));

struct gdt_description
{
	uint16_t limit;
	void *pointer;
} __attribute__((packed));

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
} __attribute__((packed));

void gdt_init();
void tss_set_kernel_stack(uint32_t);

#endif
