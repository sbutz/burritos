#ifndef STDDEF_H
#define STDDEF_H

typedef long unsigned int size_t;

typedef long int ptrdiff_t;

typedef int wchar_t;

#define NULL ((void *) 0)
/* Offset of member MEMBER in a struct of type TYPE. */

#define offsetof(TYPE, MEMBER) __builtin_offsetof (TYPE, MEMBER)

#endif
