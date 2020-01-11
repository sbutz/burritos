.section .text

.globl halt
halt:
	cli
	hlt

.globl inb
inb:
	mov %dx, -2(%ebp)
	inb %dx, %al
	ret

.globl outb
outb:
	mov %dx, -3(%ebp)
	mov %al, -1(%ebp)
	outb %al, %dx
	ret
