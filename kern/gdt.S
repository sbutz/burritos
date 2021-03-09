.section .text

.globl gdt_load
gdt_load:
	mov %eax, -8(%ebp)
	lgdt (%eax)
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	ret

.globl tss_load
tss_load:
	mov $0x2b, %ax # Segment Selector
	ltr %ax
	ret
