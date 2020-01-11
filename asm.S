.section .text

.globl out_b
out_b:
	mov %dx, -3(%ebp);
	mov %al, -1(%ebp);
	outb %al, %dx
	ret

.globl halt
halt:
	cli
	hlt
