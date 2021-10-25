#include "stdlib.h"
#include "syscall.h"

void exit()
{
	syscall(0x10);
}
