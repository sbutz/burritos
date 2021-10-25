#ifndef _PMM_H
#define _PMM_H

#include "multiboot.h"

/*
 * The physical memory manager (pmm) saves which physical memory is allocated.
 */

#define PAGE_SIZE	4096

void pmm_init(struct multiboot_info *);
void *pmm_alloc();
void pmm_free(void *);

#endif
