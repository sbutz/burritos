.section multiboot

#define MB_MAGIC 0x1badb002
#define MB_FLAGS 0x2
#define MB_CHECKSUM - (MB_MAGIC + MB_FLAGS)

/*
 * This is the Multiboot Header.
 * It must be placed in the first 8kB of the Image.
 */
.align 4
.int	MB_MAGIC
.int	MB_FLAGS
.int	MB_CHECKSUM


.section .text

.extern main

.global _start
_start:
	/* Init Kernel Stack */
	mov $kernel_stack, %esp

	/* Save Pointer to Mutliboot struct */
	push %ebx

	/* Main Entry Point */
	call main

	/* Disabled Interrupts and halt. */
	cli
_stop:
	hlt
	jmp _stop


.section .bss
.space 8192
kernel_stack:
