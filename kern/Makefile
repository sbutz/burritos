include ../Makefile.inc

LDFLAGS += -Tkernel.ld

C_SRCS = $(shell find -name '*.c')
OBJS = $(addsuffix .o,$(basename $(C_SRCS)))
AS_SRCS = $(shell find -name '*.[S]')
OBJS += $(addsuffix .s,$(basename $(AS_SRCS)))

all: kernel

kernel: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^ -lc

.PHONY: clean
clean:
	rm -f $(OBJS) kernel
