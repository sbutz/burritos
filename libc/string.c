#include "string.h"

int strncmp(const char *str1, const char *str2, size_t size )
{
	int i;

	for (i = 0; i < size; i++)
	{
		if (str1[i] == str2[i])
		{
			if (str1[i] == '\0')
				return 0;
		}
		else
		{
			if (str1[i] > str2[i])
				return 1;
			else
				return -1;
		}
	}

	return 0;
}
