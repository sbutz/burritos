include ../Makefile.inc

OBJS = $(patsubst %.c, %.o, $(wildcard *.c))

all: libc.a

libc.a: $(OBJS)
	$(AR) rcs libc.a $(OBJS)

.PHONY: clean
clean:
	rm -f $(OBJS) libc.a
