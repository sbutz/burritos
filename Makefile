SUBDIRS += libc
SUBDIRS += kern

all: $(SUBDIRS) iso run

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

iso: $(SUBDIRS)
	cp kern/kernel iso/boot/kernel
	genisoimage \
		-R \
		-b boot/grub/stage2_eltorito \
		-no-emul-boot \
		-boot-load-size 4 \
		-A os \
		-input-charset utf8 \
		-quiet \
		-boot-info-table \
		-o os.iso \
		iso/

run: iso
	qemu-system-i386 \
		-m 32 \
		-no-reboot \
		-drive format=raw,media=cdrom,file=os.iso \
		-nographic \
		-monitor telnet:127.0.0.1:55555,server,nowait

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -f os.iso
