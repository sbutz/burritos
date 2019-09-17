CC = cc
LD = ld

ASFLAGS = -m32
CFLAGS = -m32 -Wall -g -fno-stack-protector -nostdinc
LDFLAGS = -n -melf_i386 -Tkernel.ld


LIBS = -I $(CURDIR)/libc
C_SRCS = $(shell find -name '*.[c]')
OBJS = $(addsuffix .o,$(basename $(C_SRCS)))
AS_SRCS = $(shell find -name '*.[S]')
OBJS += $(addsuffix .s,$(basename $(AS_SRCS)))

run: iso
	qemu-system-i386 -cdrom os.iso

iso: kernel
	cp kernel iso/boot/kernel
	genisoimage \
		-R \
		-b boot/grub/stage2_eltorito \
		-no-emul-boot \
		-boot-load-size 4 \
		-A os \
		-input-charset utf8 \
		-quiet \
		-boot-info-table \
		-o os.iso iso/

kernel: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $^

%.s: %.S
	$(CC) $(ASFLAGS) -c -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJS) kernel os.iso
