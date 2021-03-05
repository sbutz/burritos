KERN_SRCS := \
	console.c \
	fb.c \
	gdt.c \
	idt.c \
	main.c \
	pic_8259.c \
	pit_825x.c \
	schedule.c \
	uart_8250.c \
	gdt.S \
	idt.S \
	io.S \
	start.S \
	system.S

KERN_OBJS := $(call objects,$(KERN_SRCS),kern)

LD_ADD := -T$(GIT_ROOT)/kern/kernel.ld

$(OBJDIR)/kern/kernel: $(KERN_OBJS) $(GIT_ROOT)/kern/kernel.ld $(OBJDIR)/libc/libc.a
	$(LD) $(LDFLAGS) $(LD_ADD) -o $@ $(KERN_OBJS) -lc
