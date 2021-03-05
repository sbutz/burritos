LIBC_SRCS := \
	string.c \
	syscall.S

LIBC_OBJS := $(call objects,$(LIBC_SRCS),libc)

$(OBJDIR)/libc/libc.a: $(LIBC_OBJS)
	$(AR) rcs $@ $^
