.section multiboot

#define MB_MAGIC 0x1badb002
#define MB_FLAGS 0x0
#define MB_CHECKSUM -(MB_MAGIC + MB_FLAGS)

// Multiboot Header, muss in den ersten 8192 Bytes des Image sein
.align 4
.int	MB_MAGIC
.int	MB_FLAGS
.int	MB_CHECKSUM


.section .text

.extern init

.global _start
_start:
	// Stack initialisieren
	mov $kernel_stack, %esp

	// C Main Methode
	call init

	// Nichts mehr zu tun, also Interrupts unterbinden und CPU anhalten
_stop:
	cli
	hlt
	jmp _stop


.section .bss
.space 8192
kernel_stack:
