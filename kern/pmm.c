#include <stddef.h>

#include "console.h"
#include "pmm.h"
#include "system.h"

extern const void kernel_start;
extern const void kernel_end;


#define MAX_MEM		4294967296
#define BITMAP_SIZE	MAX_MEM / PAGE_SIZE / sizeof(uint32_t)
#define BIT_SIZE(x)	(sizeof(x) * 8)
static uint32_t bitmap[BITMAP_SIZE];

static void pmm_mark_page_used(uintptr_t);

void
pmm_init(struct multiboot_info *mbs)
{
	struct multiboot_mmap *mmap, *mmap_end;
	uintptr_t addr;
	int i;

	if (mbs != NULL || !(mbs->flags & MULTIBOOT_INFO_MMAP))
	{
		/*
		 * Mark all memory used.
		 */
		for (i = 0; i < BITMAP_SIZE; i++)
			bitmap[i] = 0xffffffff;
		
		/*
		 * Free memory specified by the multiboot memory map.
		 */
		mmap = mbs->mmap;
		mmap_end = (struct multiboot_mmap *)
			((uintptr_t) mbs->mmap + mbs->mmap_len);
		while (mmap <= mmap_end) {
			if (mmap->type == MULTIBOOT_MMAP_TYPE_AVAILABLE)
			{
				//kprintf("%s: Free Mem: Start %x Len %x\n",
				//    __func__,
				//    (uint32_t) mmap->base_addr,
				//    (uint32_t) mmap->length);

				for (addr = mmap->base_addr;
				     addr < mmap->base_addr + mmap->length;
				     addr += PAGE_SIZE)
					pmm_free((void *) addr);
			}
			mmap = (struct multiboot_mmap *)
				((uintptr_t) mmap + mmap->size + sizeof(mmap->size));
		}

		/*
		 * Mark memory used by the multiboot struct and all memory pointed to.
		 * TODO: select needed parts of the multiboot struct
		 */
	}
	else
	{
		kprintf("No memory map provided\n");

		/*
		 * Mark all memory as unused.
		 */
		for (i = 0; i < BITMAP_SIZE; i++)
			bitmap[i] = 0x0;
		
	}

	/*
	 * Mark the kernels memory used.
	 */
	for (addr = (uintptr_t) &kernel_start;
	     addr < (uintptr_t) &kernel_end;
	     addr += PAGE_SIZE)
		pmm_mark_page_used(addr);
}

static void
pmm_mark_page_used(uintptr_t addr)
{
	int page, idx, shift;

	//TODO: assert(addr % PAGE_SIZE == 0);

	page = addr / PAGE_SIZE;
	idx = page / BIT_SIZE(bitmap[0]);
	shift = page % BIT_SIZE(bitmap[0]);

	bitmap[idx] |= (1 << shift);
}

void *
pmm_alloc()
{
	int i, j;
	uintptr_t addr;

	for (i = 0; i < BITMAP_SIZE; i++)
	{
		if (bitmap[i] != 0xffffffff)
		{
			addr = i * BIT_SIZE(bitmap[0]) * PAGE_SIZE;
			for (j = 0; j < sizeof(bitmap[0]); j++)
			{
				if (! (bitmap[i] & (1 << j)))
				{
					addr += j * PAGE_SIZE;
					bitmap[i] |= 1 << j;
					return (void *) addr;
				}
			}
		}
	}

	panic("Out of memory");
	return NULL;
}

void
pmm_free(void *ptr)
{
	int page, idx, shift;

	page = ((uintptr_t) ptr) / PAGE_SIZE;
	idx = page / BIT_SIZE(bitmap[0]);
	shift = page % BIT_SIZE(bitmap[0]);

	bitmap[idx] &= ~(1 << shift);
}
