GIT_ROOT = $(shell git rev-parse --show-toplevel)

AR = ar
CC = cc
LD = ld

CLIBS += -I $(GIT_ROOT)/libc
CFLAGS = -m32 -Wall -g -fno-stack-protector -ffreestanding
ASFLAGS = -m32
LDFLAGS = -n -melf_i386 -L $(GIT_ROOT)/libc
LD_LIBRARY_PATH = $(GIT_ROOT)/libc

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(CLIBS)

%.s: %.S
	$(CC) $(ASFLAGS) -c -o $@ $^
