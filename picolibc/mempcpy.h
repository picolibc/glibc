#ifndef MEMPCPY_H
#define MEMPCPY_H
#include <string.h>
#include <stddef.h>

#if 0
static inline void *mempcpy(void *restrict dest, const void *restrict src, size_t n) {
	memcpy(dest, src, n);
	return ((char *) dest) + n;
}
#endif

#endif
