#include <stdint.h>

#include "gdt.h"

extern void gdt_load();

static void gdt_set_entry(unsigned int n, uint32_t base, uint32_t limit,
	uint8_t access, uint8_t flags) {

	gdt[n].limit_lower = limit & 0xffff;
	gdt[n].base_lower = base & 0xffff;
	gdt[n].base_middle = (base >> 16) & 0xff;
	gdt[n].access = access;
	gdt[n].flags_limit_higher = (flags << 4) | ((limit >> 16) & 0xf);
	gdt[n].base_higher = base >> 24;
}

void gdt_init() {
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
	
	gdt_load();
}
