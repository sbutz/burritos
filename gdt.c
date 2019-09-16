#include "console.h"

#define GDT_ENTRIES 3

#define GDT_FLAG_PRESENT 0x80
#define GDT_FLAG_RING0 0x00
#define GDT_FLAG_RING3 0x60
#define GDT_FLAG_SEGMENT 0x10

#define GDT_FLAG_DATASEG 0x02
#define GDT_FLAG_CODESEG 0x0a
//#define GDT_FLAG_TTSSEG 0x09

#define GDT_FLAG_4K_GRAN 0x800
#define GDT_FLAG_32_BIT 0x400

static void gdt_set_entry(int n, unsigned int base, unsigned int limit,
	int flags);
static void gdt_load();

static unsigned long long gdt[GDT_ENTRIES];

// Global Descriptor Table Pointer
// GDT Register ist 6-Byte breit. Durch 'packed' struct padding verhindern.
struct gdtp {
	short limit;
	void *pointer;
} __attribute__((packed));

void gdt_init() {
	// Nulldeskriptor
	gdt_set_entry(0, 0, 0, 0);
	// Codesegment Kernel
	gdt_set_entry(1, 0, 0xfffff, GDT_FLAG_PRESENT | GDT_FLAG_RING0 |
		GDT_FLAG_SEGMENT | GDT_FLAG_CODESEG | GDT_FLAG_32_BIT |
		GDT_FLAG_4K_GRAN);
	// Datasegment Kernel
	gdt_set_entry(2, 0, 0xfffff, GDT_FLAG_PRESENT | GDT_FLAG_RING0 |
		GDT_FLAG_SEGMENT | GDT_FLAG_DATASEG | GDT_FLAG_32_BIT |
		GDT_FLAG_4K_GRAN);
	// Codesegment Userland
	//gdt_set_entry(3, 0, 0xfffff, GDT_FLAG_PRESENT | GDT_FLAG_RING3 |
	//	GDT_FLAG_SEGMENT | GDT_FLAG_CODESEG | GDT_FLAG_32_BIT |
	//	GDT_FLAG_4K_GRAN);
	// Datasegment Kernelland
	//gdt_set_entry(4, 0, 0xfffff, GDT_FLAG_PRESENT | GDT_FLAG_RING3 |
	//	GDT_FLAG_SEGMENT | GDT_FLAG_DATASEG | GDT_FLAG_32_BIT |
	//	GDT_FLAG_4K_GRAN);
	// Task State Segment Multitasking
	// Task State Segment Fehlerbehandlung bei Double Faults
	
	gdt_load();
}

static void gdt_set_entry(int n, unsigned int base, unsigned int limit, int flags) {
	gdt[n] = 0LL;
	gdt[n] |= limit & 0xffffLL;
	gdt[n] |= (base & 0xffffffLL) << 16;
	gdt[n] |= (flags & 0xffLL) << 40;
	gdt[n] |= ((limit >> 16) & 0xfLL ) << 48;
	gdt[n] |= ((flags >> 8) & 0xffLL) << 52;
	gdt[n] |= ((base >> 16) & 0xffLL) << 56;
}

static void gdt_load() {
	struct gdtp ptr = {
		.limit = GDT_ENTRIES * 8 - 1,
		.pointer = gdt,
	};

	asm volatile("lgdt %0" : : "m" (ptr));
	asm volatile("mov $0x10, %ax\n"
		"mov %ax, %ds\n"
		"mov %ax, %es\n"
		"mov %ax, %fs\n"
		"mov %ax, %gs\n"
		"mov %ax, %ss"
	);
}
