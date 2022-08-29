#include <stdint.h>
#include <string.h>

#include "console.h"
#include "pmm.h"
#include "vmm.h"


static void vmm_map_page(struct vmm_context *, uintptr_t, uintptr_t);
static void enable_paging();

/*
 * Temporary context used until scheduling starts and a tasks ctx is active.
 */
static struct vmm_context *boot_ctx;

void vmm_init()
{
	int i;

	/*
	 * Map first for 4MB for use in the setup process.
	 */
	boot_ctx = vmm_context_create();
	for (i = 0; i < 4096 * 1024; i += 4096)
		vmm_map_page(boot_ctx, i, i);
	vmm_context_activate(boot_ctx);

	enable_paging();
}

struct vmm_context *
vmm_context_create()
{
	struct vmm_context *ctx = pmm_alloc();

	ctx->pagedir = pmm_alloc();
	memset(ctx->pagedir, 0, 1024);

	return ctx;
}

void
vmm_context_activate(struct vmm_context *ctx)
{
	asm volatile ("mov %0, %%cr3": : "r"(ctx->pagedir));
}

void *
vmm_alloc(struct vmm_context *ctx)
{
	int pd_idx, pt_idx;
	uintptr_t virt;
	uint32_t *pagetab;

	/* Find unused virtual page. */
	for (pd_idx = 0; pd_idx < 1024; pd_idx++)
	{
		if (ctx->pagedir[pd_idx] == 0) {
			virt = pd_idx << 22;
			vmm_map_page(ctx, virt, (uintptr_t) pmm_alloc());
			return (void *) virt;
		} else {
			pagetab = (uint32_t *) (ctx->pagedir[pd_idx] & PAGE_MASK);
			for (pt_idx = 0; pt_idx < 1024; pt_idx++)
			{
				if (pagetab[pt_idx] == 0) {
					virt = (pd_idx << 22) | (pt_idx << 12);
					vmm_map_page(ctx, virt, (uintptr_t) pmm_alloc());
					return (void *) virt;
				}
			}
		}
	}

	return NULL;
}

void
vmm_free(struct vmm_context *ctx, void *addr)
{
	//TODO: assert(addr % PAGE_SIZE == 0);
}

static void
vmm_map_page(struct vmm_context *ctx, uintptr_t virt, uintptr_t phys)
{
	unsigned int pd_idx, pt_idx;

	pd_idx = virt >> 22;
	pt_idx = (virt >> 12) % 1024;

	if (ctx->pagedir[pd_idx] == 0) {
		ctx->pagedir[pd_idx] = (uint32_t) pmm_alloc()
			| PAGE_VALID | PAGE_WRITE | PAGE_USER;
		memset((uint32_t *) ctx->pagedir[pd_idx], 0, 1024);
	}

	uint32_t *pagetab = (uint32_t *) (ctx->pagedir[pd_idx] & PAGE_MASK);
	//TODO: assert(phys % PAGE_SIZE == 0);
	pagetab[pt_idx] = phys | PAGE_VALID | PAGE_WRITE | PAGE_USER;

	/*
	 * Invalidate the TLB cache.
	 * TODO: explain why
	 */
	asm volatile ("invlpg %0" : : "m"(virt) : "memory");
}

static void
enable_paging()
{
	uint32_t cr0;
	asm volatile ("mov %%cr0, %0": "=r"(cr0));
	cr0 |= (1 << 31);
	asm volatile ("mov %0, %%cr0": : "r"(cr0));
}
