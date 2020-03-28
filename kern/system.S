.section .text

.globl cpu_relax
cpu_relax:
	hlt
	ret

.globl enable_irqs
enable_irqs:
	sti
	ret

.globl disable_irqs
disable_irqs:
	cli
	ret
