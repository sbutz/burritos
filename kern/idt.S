.section .text

.extern idtp
.globl idt_load
idt_load:
	lidt idtp
	ret

.macro intr_stub num
	.globl intr_stub_\num
	intr_stub_\num:
		# Error Code
		push $0x0
		# Interrupt Nummer
		push $\num
		jmp common_intr_handler
.endm

.macro intr_stub_error_code num
	.globl intr_stub_\num
	intr_stub_\num:
		# Interrupt Nummer
		push $0x\num
		jmp common_intr_handler
.endm

.extern handle_intr
common_intr_handler:
	push %ebp
	push %edi
	push %esi
	push %edx
	push %ecx
	push %ebx
	push %eax

	# Passing pointer to cpu state to interrupt handler
	push %esp
	call handle_intr
	# Pop pointer
	add $4, %esp

	# Restore registers
	pop %eax
	pop %ebx
	pop %ecx
	pop %edx
	pop %esi
	pop %edi
	pop %ebp

	# Interrupt Nummer und Error Code loeschen
	add $8, %esp

	iret

# Exceptions
intr_stub 0
intr_stub 1
intr_stub 2
intr_stub 3
intr_stub 4
intr_stub 5
intr_stub 6
intr_stub 7
intr_stub_error_code 8
intr_stub 9
intr_stub_error_code 10
intr_stub_error_code 11
intr_stub_error_code 12
intr_stub_error_code 13
intr_stub_error_code 14
intr_stub 15
intr_stub 16
intr_stub_error_code 17
intr_stub 18

# Hardware-Interrupts (IRQs)
intr_stub 32
intr_stub 33
intr_stub 34
intr_stub 35
intr_stub 36
intr_stub 37
intr_stub 38
intr_stub 39
intr_stub 40
intr_stub 41
intr_stub 42
intr_stub 43
intr_stub 44
intr_stub 45
intr_stub 46
intr_stub 47

# Syscalls
intr_stub 48
