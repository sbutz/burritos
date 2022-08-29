KERN_SRCS := \
	console.c \
	fb.c \
	gdt.c \
	idt.c \
	io.c \
	main.c \
	pic_8259.c \
	pit_825x.c \
	pmm.c \
	queue.c \
	schedule.c \
	system.c \
	uart_8250.c \
	vmm.c \
	gdt.S \
	idt.S \
	start.S

OBJS += $(call add-objects,$(KERN_SRCS),kern)

LD_ADD := -T$(GIT_ROOT)/kern/kernel.ld

#TODO: move tasks outside kern to remove cross dependency
$(OBJDIR)/kern/kernel: \
		$(call get-objects,kern) \
		$(GIT_ROOT)/kern/kernel.ld \
		$(OBJDIR)/libc/libc.a
	$(LD) $(LDFLAGS) $(LD_ADD) -o $@ $(call get-objects,kern) -lc
