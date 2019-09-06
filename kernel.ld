ENTRY(_start)

SECTIONS
{
	/*
	 * . ist die aktuelle Position in der Datei
	 */
	. = 0x100000;

	/*
	 * Multiboot-Header muss in den ersten 8kB sein.
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
