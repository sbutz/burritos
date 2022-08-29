#ifndef _VMM_H
#define _VMM_H

/*
 * TODO: whats is the virtual memory manager (vmm)?
 * pdir exists per virtual address space -> per task
 * cr3 points to page directory
 * page directory has 1024 entries each 4 byte
 * each page directory entry points to a page table
 * page table consists of 1024 entries each 4 byte
 * each entry points to physical address
 *
 * address translation:
 */

struct vmm_context
{
	uint32_t *pagedir; /* Page directory */
};

/*
 * Page directory entry constants.
 * TODO: document bit fields
 */
#define PAGE_VALID	0x1
#define PAGE_WRITE	0x2
#define PAGE_USER	0x4
#define PAGE_MASK	0xfffff000


void vmm_init();
struct vmm_context *vmm_context_create();
void vmm_context_activate(struct vmm_context *);
void *vmm_alloc(struct vmm_context *);
void vmm_free(struct vmm_context *, void *);

#endif
