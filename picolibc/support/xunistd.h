#include <unistd.h>
#define xmunmap(base, size) munmap(base, size)
#define xmmap(base, size, prot, parm, a) check_malloc(size)
