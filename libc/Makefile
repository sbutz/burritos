include ../Makefile.inc

C_SRCS = $(shell find -name '*.[c]')
OBJS = $(addsuffix .o,$(basename $(C_SRCS)))

all: libc.a

libc.a: $(OBJS)
	$(AR) rcs libc.a $(OBJS)

.PHONY: clean
clean:
	rm -f $(OBJS) libc.a
