KERN_SRCS := \
	console.c \
	fb.c \
	gdt.S \
	gdt.c \
	idt.S \
	idt.c \
	io.c \
	main.c \
	pic_8259.c \
	pit_825x.c \
	schedule.c \
	start.S \
	system.S
	uart_8250.c \

OBJS += $(call add-objects,$(KERN_SRCS),kern)

LD_ADD := -T$(GIT_ROOT)/kern/kernel.ld

#TODO: move tasks outside kern to remove cross dependency
$(OBJDIR)/kern/kernel: \
		$(call get-objects,kern) \
		$(GIT_ROOT)/kern/kernel.ld \
		$(OBJDIR)/libc/libc.a
	$(LD) $(LDFLAGS) $(LD_ADD) -o $@ $(call get-objects,kern) -lc
