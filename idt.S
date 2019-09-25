.section .text

.extern idtp
.globl idt_load
idt_load:
	lidt idtp
	ret

.macro new_intr_handler num
	.globl intr_handler_\num
	intr_handler_\num:
		# Error Code
		push $0x0
		# Interrupt Nummer
		push $0x\num
		jmp common_intr_handler
.endm

.extern intr_handler
common_intr_handler:
	push %eax
	push %ebx
	push %ecx
	push %edx
	push %esi
	push %edi
	push %ebp
	# ESP wird bereits von der Instruktion INT gesichert

	call intr_handler

	pop %ebp
	pop %edi
	pop %esi
	pop %edx
	pop %ecx
	pop %ebx
	pop %eax

	# Interrupt Nummer und Error Code loeschen
	add $8, %esp

	iret

new_intr_handler 1
new_intr_handler 2
