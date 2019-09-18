.section .text
.extern idtp
.globl idt_load
idt_load:
	lidt idtp
	ret
