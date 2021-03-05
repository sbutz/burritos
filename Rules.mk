AR = ar
CC = cc
LD = ld

CLIBS := -I $(GIT_ROOT)/libc
CFLAGS := -m32 -Wall -g -fno-stack-protector -ffreestanding
LDFLAGS := -n -melf_i386 -L $(OBJDIR)/libc

$(OBJDIR)/%.o: $(GIT_ROOT)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $^ $(CLIBS)

$(OBJDIR)/%.s: $(GIT_ROOT)/%.S
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $^

# Convenience macro used to define object files
# $1: Source files
# $2: Subdirectory in $(OBJDIR)
define objects
	$(patsubst %.c, $(OBJDIR)/$(2)/%.o, $(filter %.c,$(1))) \
	$(patsubst %.S, $(OBJDIR)/$(2)/%.s, $(filter %.S,$(1)))
endef

