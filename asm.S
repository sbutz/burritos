.section .text

.globl relax
relax:
	hlt
	ret

.globl disable_irqs
disable_irqs:
	cli
	ret

.globl inb
inb:
	mov 4(%esp), %dx
	inb %dx, %al
	ret

.globl outb
outb:
	mov 4(%esp), %dx
	mov 8(%esp), %ax
	outb %al, %dx
	ret
