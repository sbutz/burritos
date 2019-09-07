#include "console.h"

void init()
{
	const char *hello = "Hello World\n";

	kclear();

	kprintf(hello);
	kprintf(hello);
	kprintf(hello);
}
