LIBC_SRCS := \
	string.c \
	syscall.S

OBJS += $(call add-objects,$(LIBC_SRCS),libc)

$(OBJDIR)/libc/libc.a: $(call get-objects,libc)
	$(AR) rcs $@ $^
