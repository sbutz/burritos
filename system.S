.section .text

.globl cpu_relax
cpu_relax:
	hlt
	ret

.globl disable_irqs
disable_irqs:
	cli
	ret
