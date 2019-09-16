#ifndef STDINT_H
#define STDINT_H

/* Exakte Typen */
typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long long int int64_t;
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

/* Kleine Typen */
typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;
typedef long long int int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long long int uint_least64_t;

/* Schnelle Typen */
typedef unsigned  char int_fast8_t;
typedef int int_fast16_t;
typedef int int_fast32_t;
typedef long long int int_fast64_t;
typedef char uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long long int uint_fast64_t;

/* Void Pointer */
typedef int intptr_t;
typedef unsigned int uintptr_t;

/* Groesste Typen */
typedef long long int intmax_t;
typedef unsigned long long int uintmax_t;

/* Minima und Maxima der Typen */
#define INT8_MIN -127-1
#define INT16_MIN -32767-1
#define INT32_MIN -2147483647-1
#define INT64_MIN -9223372036854775807LL-1

#define INT8_MAX 127
#define INT16_MAX 32767
#define INT32_MAX 2147483647
#define INT64_MAX 9223372036854775807LL

#define UINT8_MAX 255
#define UINT16_MAX 65536
#define UINT32_MAX 4294967295U
#define UINT64_MAX 18446744073709551615LLU

#define INT_LEAST8_MIN -127-1
#define INT_LEAST16_MIN -32767-1
#define INT_LEAST32_MIN -2147483647-1
#define INT_LEAST64_MIN -9223372036854775807LL-1

#define INT_LEAST8_MAX 127
#define INT_LEAST16_MAX 32767
#define INT_LEAST32_MAX 2147483647
#define INT_LEAST64_MAX 9223372036854775807LL

#define UINT_LEAST8_MAX 255
#define UINT_LEAST16_MAX 65535
#define UINT_LEAST32_MAX 4294967295U
#define UINT_LEAST64_MAX 18446744073709551615LLU

#define INT_FAST8_MIN -127-1
#define INT_FAST16_MIN -2147483647-1
#define INT_FAST32_MIN -2147483647-1
#define INT_FAST64_MIN -9223372036854775807LL-1

#define INT_FAST8_MAX 127
#define INT_FAST16_MAX 2147483647
#define INT_FAST32_MAX 2147483647
#define INT_FAST64_MAX 9223372036854775807LL

#define UINT_FAST8_MAX 255
#define UINT_FAST16_MAX 4294967295U
#define UINT_FAST32_MAX 4294967295U
#define UINT_FAST64_MAX 18446744073709551615LLU

#define INTPTR_MIN -2147483647-1
#define INTPTR_MAX 2147483647
#define UINTPTR_MAX 4294967295U

#define INTMAX_MIN -9223372036854775807LL-1
#define INTMAX_MAX 9223372036854775807LL

#define UINTMAX_MAX 18446744073709551615LLU

#define PTRDIFF_MIN -2147483647-1
#define PTRDIFF_MAX 2147483647

#define SIG_ATOMIC_MIN -2147483647-1
#define SIG_ATOMIC_MAX 2147483647

#define SIZE_MAX 4294967295U

#define WCHAR_MIN -2147483647-1
#define WCHAR_MAX 2147483647

# define WINT_MIN 0u
# define WINT_MAX 4294967295u

/* Konvertierungsmakros */
/* Duerfen laut ISO Standard C99 nicht ohne explizite Anweisung in C++
   implementiert sein. */
#if !defined __cplusplus || defined __STDC_CONSTANT_MACROS

#define INT8_C(c) c
#define INT16_C(c)c
#define INT32_C(c) c
#define INT64_C(c) c ## LL

#define UINT8_C(c) c
#define UINT16_C(c) c
#define UINT64_C(c) c ## ULL

#define INTMAX_C(c) c ## LL
#define UINTMAX_C(c) c ## ULL

#endif

#endif
