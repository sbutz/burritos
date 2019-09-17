#ifndef GDT_H
#define GDT_H

#include <stdint.h>

#define GDT_ENTRIES 3

#define GDT_ACCESS_PRESENT 0x80
#define GDT_ACCESS_RING0 0x00
#define GDT_ACCESS_RING3 0x60
#define GDT_ACCESS_SEGMENT 0x10

#define GDT_ACCESS_DATASEG 0x02
#define GDT_ACCESS_CODESEG 0x0a
#define GDT_ACCESS_TTSSEG 0x09

#define GDT_FLAG_4K_GRAN 0x08
#define GDT_FLAG_32_BIT 0x04

struct gdt_entry {
	uint16_t limit_lower;
	uint16_t base_lower;
	uint8_t base_middle;
	uint8_t access;
	uint8_t flags_limit_higher;
	uint8_t base_higher;
} __attribute__((packed));

struct gdt_description {
	uint16_t limit;
	void *pointer;
} __attribute__((packed));

void gdt_init();

struct gdt_entry gdt[GDT_ENTRIES];
struct gdt_description gdtp;

#endif
