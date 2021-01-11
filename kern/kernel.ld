ENTRY(_start)

SECTIONS
{
	/*
	 * . is the current Position in this file.
	 * . ist die aktuelle Position in der Datei.
	 *
	 * This is the Address the kernel will be loaded.
	 * At least 1MB (0x100000) must remain free.
	 */
	. = 0x100000;

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
}
