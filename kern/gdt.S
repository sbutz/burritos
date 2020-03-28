.section .text

.extern gdtp
.globl gdt_load
gdt_load:
	lgdt gdtp
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	ret
