#include "syscall.h"


void syscall(int num)
{
	asm volatile (
		"mov %0, %%eax;" \
		"int $0x30;"
	: :"r"(num));
}
