.section .text

.globl inb
inb:
	# Port
	mov 4(%esp), %dx
	inb %dx, %al
	ret

.globl outb
outb:
	# Port
	mov 4(%esp), %dx
	# Data
	mov 8(%esp), %ax
	outb %al, %dx
	ret
