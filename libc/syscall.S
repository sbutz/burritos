.section .text

.globl syscall
syscall:
	mov 4(%esp), %eax
	int $0x30
	ret
