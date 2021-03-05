# Globals
GIT_ROOT := $(shell git rev-parse --show-toplevel)
OBJDIR := $(GIT_ROOT)/obj

# Default target
all: $(OBJDIR)/burritos.iso

# Basic Rules
include Rules.mk

# Include subdirectories
include $(GIT_ROOT)/kern/module.mk
include $(GIT_ROOT)/libc/module.mk


$(OBJDIR)/burritos.iso: $(OBJDIR)/kern/kernel grub.cfg
	mkdir -p $(OBJDIR)/iso/boot/grub
	cp $(OBJDIR)/kern/kernel $(OBJDIR)/iso/boot/kernel
	cp grub.cfg $(OBJDIR)/iso/boot/grub/grub.cfg
	grub-mkrescue \
		--fonts="" \
		--install-modules="normal multiboot" \
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
		-nographic \
		-monitor telnet:127.0.0.1:55555,server,nowait

.PHONY: clean
clean:
	rm -rf $(OBJDIR)
