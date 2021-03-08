# Globals
GIT_ROOT := $(shell git rev-parse --show-toplevel)
OBJDIR := $(GIT_ROOT)/obj
# Module rules will add to this
OBJS :=

# Default target
all: $(OBJDIR)/burritos.iso

# Basic Rules
include $(GIT_ROOT)/Rules.mk

# Module Rules
include $(GIT_ROOT)/kern/module.mk
include $(GIT_ROOT)/libc/module.mk

# Dependency Rules
DEPS := $(addsuffix .d,$(OBJS))
include $(DEPS)

GRUB_MODULES = \
	normal \
	multiboot \
	part_acorn \
	part_amiga \
	part_apple \
	part_bsd \
	part_dfly \
	part_dvh \
	part_gpt \
	part_msdos \
	part_plan \
	part_sun \
	part_sunpc

$(OBJDIR)/burritos.iso: $(OBJDIR)/kern/kernel grub.cfg
	mkdir -p $(OBJDIR)/iso/boot/grub
	cp $(OBJDIR)/kern/kernel $(OBJDIR)/iso/boot/kernel
	cp grub.cfg $(OBJDIR)/iso/boot/grub/grub.cfg
	grub-mkrescue \
		--fonts="" \
		--install-modules="$(GRUB_MODULES)" \
		--locales="" \
		--modules="" \
		--themes="" \
		-d /usr/lib/grub/i386-pc/ \
		-o $@ \
		$(OBJDIR)/iso/

run: $(OBJDIR)/burritos.iso
	qemu-system-i386 \
		-m 32 \
		-no-reboot \
		-drive format=raw,media=cdrom,file=$< \
		-boot d \
		-nographic \
		-monitor telnet:127.0.0.1:55555,server,nowait

.PHONY: clean
clean:
	rm -rf $(OBJDIR)
