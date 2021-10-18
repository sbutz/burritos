ENTRY(_start)

SECTIONS
{
	/*
	 * . is the current Position in this file.
	 *
	 * This is the Address the kernel will be loaded.
	 * At least 1MB (0x100000) must remain free.
	 */
	. = 0x100000;

	/*
	 * Symbol to find the begin of the kernel memory.
	 */
	kernel_start = .;

	/*
	 * Multiboot-Header has to be in the first 8kB.
	 */
	.text : {
		*(multiboot)
		*(.text)
	}
	.data ALIGN(4096) : {
		*(.data)
	}
	.rodata ALIGN(4096) : {
		*(.rodata)
	}
	.bss ALIGN(4096) : {
		*(.bss)
	}

	/*
	 * Symbol to find the end of the kernel memory (rounded to 4K).
	 */
	. = ALIGN(4096);
	kernel_end = .;
}
