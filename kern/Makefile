include ../Makefile.inc

LDFLAGS += -Tkernel.ld

OBJS = $(patsubst %.c, %.o, $(wildcard *.c))
OBJS += $(patsubst %.S, %.s, $(wildcard *.S))

all: kernel

kernel: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^ -lc

.PHONY: clean
clean:
	rm -f $(OBJS) kernel
