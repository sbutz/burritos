AR = ar
CC = cc
LD = ld

CLIBS := -I $(GIT_ROOT)/libc
CFLAGS := -m32 -Wall -Werror -g -fno-stack-protector -ffreestanding
LDFLAGS := -n -melf_i386 -L $(OBJDIR)/libc

# C files
$(OBJDIR)/%.o: $(GIT_ROOT)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $< $(CLIBS)

# Assembly files
$(OBJDIR)/%.s: $(GIT_ROOT)/%.S
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Dependeny files
$(OBJDIR)/%.o.d: $(GIT_ROOT)/%.c
	@mkdir -p $(dir $@)
	$(CC) -MM -MG -MT $(basename $@) $^ | \
		sed -e 's@^\(.*\)\.o:@\1.o.d \1.o:@' > $@

#TODO: get rid of c and assembly source files sharing the same basename
$(OBJDIR)/%.s.d: $(GIT_ROOT)/%.S
	@mkdir -p $(dir $@)
	$(CC) -MM -MG -MT $(basename $@) $^ | \
		sed -e 's@^\(.*\)\.o:@\1.s.d \1.o:@' > $@

# Convenience macro used to define object files
# $1: Source files
# $2: Subdirectory in $(OBJDIR)
define add-objects
	$(patsubst %.c, $(OBJDIR)/$(2)/%.o, $(filter %.c,$(1))) \
	$(patsubst %.S, $(OBJDIR)/$(2)/%.s, $(filter %.S,$(1)))
endef

# Convenience macro used to get object files
# $1: Subdirectory in $(OBJDIR)
define get-objects
	$(filter $(OBJDIR)/$(1)/%,$(OBJS))
endef
