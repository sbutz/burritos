LIBC_SRCS := \
	stdlib.c \
	string.c \
	syscall.c

OBJS += $(call add-objects,$(LIBC_SRCS),libc)

$(OBJDIR)/libc/libc.a: $(call get-objects,libc)
	$(AR) rcs $@ $^
