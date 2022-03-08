#include <stdio.h>
#include <stdarg.h>

void
error(int status, int errnum, const char *message, ...)
{
	va_list ap;
	va_start(ap, message);
	fprintf(stderr, "status %d errnum %d ", status, errnum);
	vfprintf(stderr, message, ap);
	va_end(ap);
}
