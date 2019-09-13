#include "console.h"

void init()
{
	int i;

	kclear();

	for (i = 0; i < 50; i++) {
		kprintf("i = %x, &i = %p\n", i, &i);
	}
}
