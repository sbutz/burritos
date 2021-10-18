#ifndef _MUTLIBOOT_H
#define _MUTLIBOOT_H

#include <stdint.h>

/*
 * For a more detailed explanation of the multiboot structure please refer to
 * from https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
 */


/*
 * Multiboot structure flags.
 * If present the corresponding struct member is set.
 */
#define MULTIBOOT_INFO_MEM_LOWER	0x001
#define MULTIBOOT_INFO_MEM_UPPER	0x001
#define MULTIBOOT_INFO_BOOTDEVICE	0x002
#define MULTIBOOT_INFO_CMDLINE		0x004
#define MULTIBOOT_INFO_MODULE		0x008
#define MULTIBOOT_INFO_SYMS_BIN		0x010
#define MULTIBOOT_INFO_SYMS_ELF		0x020
#define MULTIBOOT_INFO_MMAP		0x040
#define MULTIBOOT_INFO_DRIVES		0x080
#define MULTIBOOT_INFO_CONFIG_TABLE	0x100
#define MULTIBOOT_INFO_BOOT_LOADER_NAME	0x200
#define MULTIBOOT_INFO_APM_TABLE	0x400
#define MULTIBOOT_INFO_VBE		0x800
#define MULTIBOOT_INFO_FRAMEBUFFER	0x1000

/*
 * Indicates no parition at this level.
 */
#define MULTIBOOT_BOOT_DEV_NO_PARITION 0xFF

/*
 * mmap types.
 * All other values indicate a reserved area.
 */
#define MULTIBOOT_MMAP_TYPE_AVAILABLE	0x1
#define MULTIBOOT_MMAP_TYPE_ACPI	0x3
#define MULTIBOOT_MMAP_TYPE_HIBERNATION	0x4
#define MULTIBOOT_MMAP_TYPE_DEFECTIVE	0x5

/*
 * BIOS drive modes.
 *
 * CHS: traditional cylinder/head/sector addressing mode
 * LBA: logical block aressing mode
 */
#define MULTIBOOT_DRIVE_MODE_CHS	0x0
#define MULTIBOOT_DRIVE_MODE_LBA	0x1


/*
 * The boot device.
 */
struct multiboot_boot_dev {
	/*
	 * BIOS disk number.
	 */
	uint8_t bios_disk_nr;

	/*
	 * Parition and subparition information.
	 * If a value is OxFF no paritioning is used on this level.
	 */
	uint8_t bios_part_nr[3];
} __attribute__((packed));

/*
 * A multiboot module.
 */
struct multiboot_module{
	/*
	 * Start address of the module.
	 */
	uint32_t start;

	/*
	 * End address of the module.
	 */
	uint32_t end;

	/*
	 * The module's name.
	 * Pointer to a zero-terminated ASCII-String.
	 */
	char *name;

	/*
	 * Reserved.
	 */
	uint32_t reserved;
} __attribute__((packed));

/*
 * Infomtion on the symbol table of a a.out kernel image.
 */
struct multiboot_syms_bin {
	/*
	 * Size of the table.
	 *
	 * Equal to the size parameter pointed to by `addr`.
	 * May be zero, indicating no symbols.
	 */
	uint32_t tabsize;

	/*
	 * Size of the string table.
	 *
	 * Equal to the size parameter found at the beginning of the string
	 * table.
	 */
	uint32_t strsize;

	/*
	 * Address of the symbol table.
	 *
	 * It points to the size of table (4-byte unsigned long),
	 * followed by an array of a.out format nlist structures,
	 * followed immediately by the array itself.
	 * Then the size (4-byte unsigned long) of a set zero terminated ASCII
	 * strings, and finally the set of string itself.
	 */
	uint32_t addr;

	/*
	 * Reserved.
	 */
	uint32_t reserved;
} __attribute__((packed));

/*
 * Infomtion on the section header table of an elf kernel.
 */
struct multiboot_syms_elf {
	/*
	 * Number of entries.
	 */
	uint32_t num;

	/*
	 * Size of one entry.
	 */
	uint32_t size;

	/*
	 * Address of the first entry.
	 */
	uint32_t addr;

	/*
	 * String table used as the index of names.
	 */
	uint32_t shndx;
} __attribute__((packed));

/*
 * Memory map entry.
 */
struct multiboot_mmap {
	/*
	 * The entry's size.
	 * The total size is `sizeof(size) + size`.
	 */
	uint32_t size;

	/*
	 * Base address of the buffer.
	 */
	uint64_t base_addr;

	/*
	 * Total size of the buffer.
	 */
	uint64_t length;

	/*
	 * Type of the buffer.
	 *
	 * Have a look at MULTIBOOT_MMAP_TYPE_* macros.
	 */
	uint32_t type;
} __attribute__((packed));

/*
 * BIOS drive structure.
 */
struct drive {
	/*
	 * The struct's size.
	 * 10 + 2 * number of ports
	 */
	uint32_t size;

	/*
	 * BIOS drive number.
	 */
	uint8_t drive_num;

	/*
	 * Access mode.
	 * See MULTIBOOT_DRIVE_MODE_*.
	 */
	uint8_t drive_mode;

	/*
	 * Number of drive cylinders.
	 */
	uint16_t drive_cylinders;

	/*
	 * Number of drive heads.
	 */
	uint8_t drive_heads;

	/*
	 * Number of sectors per track.
	 */
	uint8_t drive_sectors;

	/*
	 * Array of I/O ports used by the BIOS to access the drive.
	 */
	uint16_t *ports;
} __attribute__((packed));

/*
 * APM (Advanced Power Management) Table structure.
 */
struct apm_table {
	/*
	 * Version Number.
	 */
	uint16_t version;

	/*
	 * Protected 32-bit code segment.
	 */
	uint16_t csseg;

	/*
	 * Offset of the entry point.
	 */
	uint32_t offset;

	/*
	 * Protected 16-bit code segment.
	 */
	uint16_t cseg_16;

	/*
	 * Protected 16-bit data segment.
	 */
	uint16_t dseg;

	/*
	 * Flags.
	 */
	uint16_t flags;

	/*
	 * Length of the protected 32-bit code segment.
	 */
	uint16_t cseg_len;

	/*
	 * Length of the protected 16-bit code segment.
	 */
	uint16_t cseg_16_len;

	/*
	 * Length of the protected 16-bit data segment.
	 */
	uint16_t dseg_len;
} __attribute__((packed));

/*
 * Framebuffer color (indexed mode).
 */
struct framebuffer_color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} __attribute__((packed));


/*
 * Used to pass information from the bootloader to a multiboot
 * compliant kernel.
 *
 * On start EBX contains a pointer to this struct.
 */
struct multiboot_info {
	/*
	 * Indicates which fields are set.
	 * Use MULTIBOOT_INFO_* to check.
	 */
	uint32_t flags;

	/*
	 * Lower memory in kB.
	 * Lower memory starts at address 0.
	 * Maximum value is 640KB.
	 */
	uint32_t mem_lower;

	/*
	 * Upper memory in kB.
	 * Upper memory starts at address 1MB.
	 */
	uint32_t mem_upper;

	/*
	 * Contains information about the boot device.
	 */
	struct multiboot_boot_dev boot_dev;

	/*
	 * Kernel parameters.
	 * Pointer to zero terminated ASCII-String.
	 */
	char *cmdline;

	/*
	 * Number of multiboot modules loaded by the bootloader.
	 */
	uint32_t module_count;

	/*
	 * Address of the first multiboot module structure.
	 */
	struct multiboot_module *modules;

	/*
	 * Infomtion on the kernel image symbols.
	 *
	 * Consult the `flags` field of multiboot_info to determine the type of
	 * the kernel image.
	 */
	union {
		struct multiboot_syms_bin bin_info;
		struct multiboot_syms_elf elf_info;
	} __attribute__((packed));

	/*
	 * Length of the memory map in bytes.
	 * This is not the number of multiboot_mmap entries.
	 */
	uint32_t mmap_len;

	/*
	 * Address of the memory map.
	 * It points to the first mmap entry.
	 */
	struct multiboot_mmap *mmap;

	/*
	 * Number of drive structures.
	 */
	uint32_t drives_len;

	/*
	 * Address of the first drive struct.
	 */
	struct drive *drives;

	/*
	 * Address of the ROM configuration table returned by the
	 * GET CONFIGURATION BIOS call.
	 */
	uint32_t config_table;

	/*
	 * The Bootloader's name.
	 * Address pointing to a zero-terminated string.
	 */
	char *boot_loader_name;

	/*
	 * Address of the apm table.
	 */
	struct apm_table apm_table;

	/*
	 * Address of the VBE control information returned by the VBE function
	 * 00h.
	 */
	uint32_t vbe_control_info;

	/*
	 * Address of the VBE mode information returned by the VBE function
	 * 01h.
	 */
	uint32_t vbe_mode_info;

	/*
	 * Indicated the current video mode in the format specified by VBE 3.0.
	 */
	uint32_t vbe_mode;

	/*
	 * Table of a protected mdoe interface defined in VBE 2.0+.
	 * This interface is incompatible with the new protocol definied in
	 * VBE 3.0.
	 */
	uint16_t vbe_interface_seg;
	uint16_t vbe_interface_off;
	uint16_t vbe_interface_len;

	/*
	 * Framebuffer address.
	 */
	uint64_t framebuffer_addr;

	/*
	 * Framebuffer pitch in bytes.
	 */
	uint32_t framebuffer_pitch;

	/*
	 * Framebuffer width in pixels.
	 */
	uint32_t framebuffer_width;

	/*
	 * Framebuffer height in pixels.
	 */
	uint32_t framebuffer_height;

	/*
	 * Number of bits per pixel.
	 * If framebuffer_type is 2 it is the bits per characteres (usually 16).
	 */
	uint8_t framebuffer_bpp;

	/*
	 * Framebuffer type.
	 * If set to 0 indexed colors will be used.
	 * If set to 1 direct RGB colors will be used.
	 * If set to 2 EGA standard text mode will be used. In this case
	 * the framebuffer's width and height are expressed in characters.
	 */
	uint8_t framebuffer_type;
	union {
		/* Indexed colors */
		struct {
			/*
			 * Address pointing to an array of colors.
			 */
			struct framebuffer_color *framebuffer_palette_addr;

			/*
			 * Number of colors in the palette.
			 */
			uint32_t framebuffer_palette_len;
		};
		/* RGB colors */
		struct {
			uint8_t framebuffer_red_field_position;
			uint8_t framebuffer_red_mask_size;
			uint8_t framebuffer_green_field_position;
			uint8_t framebuffer_green_mask_size;
			uint8_t framebuffer_blue_field_position;
			uint8_t framebuffer_blue_mask_size;
		};
	};
} __attribute__((packed));

#endif
