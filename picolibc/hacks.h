#ifndef _HACKS_H
#define _HACKS_H

#define _GNU_SOURCE 1

#if defined __GNUC__ && defined __GNUC_MINOR__
# define __GNUC_PREREQ(maj, min) \
	((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
# define __GNUC_PREREQ(maj, min) 0
#endif

#if defined __clang_major__ && defined __clang_minor__
# define __glibc_clang_prereq(maj, min) \
  ((__clang_major__ << 16) + __clang_minor__ >= ((maj) << 16) + (min))
#else
# define __glibc_clang_prereq(maj, min) 0
#endif

/* Whether to use feature set F.  */
#define __GLIBC_USE(F)	__GLIBC_USE_ ## F

#define clock_gettime(a,b)
#define nanosleep(a,b)
#define setrlimit(a,b)

static inline int chdir(const char *a) { return 0; }

#define stat64 stat
#define fstat64 fstat

#define M_PERTURB -6

struct rlimit { int rlim_cur, rlim_max; };

typedef long long off64_t;

#define TIMEOUTFACTOR 1

#define __FE_UNDEFINED	0

typedef void (*sighandler_t)(int);

#define __vsnprintf_internal(s,n,fmt,ap,x) vsnprintf(s,n,fmt,ap)

#define program_invocation_short_name "hello"
#define HAVE_DECL_PROGRAM_INVOCATION_NAME 1
extern char *program_invocation_name;

#define fwrite_unlocked fwrite
#define putc_unlocked putc
#define fputs_unlocked fputs
#define sleep(x)

#define GL_UNUSED

static inline long sysconf(int x) { switch (x) { case 8: return 0x1000; default: return -1; } }

#define xsysconf sysconf
#define xmalloc malloc

#define powerof2(x)	(((x) & ((x)-1)) == 0)

#define loff_t off_t

#define __USE_ISOC11

#ifdef __riscv
#if __riscv_flen < 64
#define DBL_NO_EXCEPT	1
#endif
#endif

#ifdef __arm__
#if defined(__SOFTFP__) || (__ARM_FP & 0x8) == 0
#define DBL_NO_EXCEPT	1
#endif

#if defined(__SOFTFP__) || (__ARM_FP & 0x4) == 0
#define FLT_NO_EXCEPT	1
#endif
#endif

#ifndef FLT_NO_EXCEPT
#define FLT_NO_EXCEPT 0
#endif

#ifndef DBL_NO_EXCEPT
#define DBL_NO_EXCEPT 0
#endif

/* XXX arch-specific */
#if defined(__riscv)
#define TININESS_AFTER_ROUNDING 1
#else
#define TININESS_AFTER_ROUNDING 0
#endif

# define CMPLX(x, y) __builtin_complex ((double) (x), (double) (y))
# define CMPLXF(x, y) __builtin_complex ((float) (x), (float) (y))
# define CMPLXL(x, y) __builtin_complex ((long double) (x), (long double) (y))

#define __atomic_store_n(loc, val, sem) (*(loc) = (val))
#define __atomic_add_fetch(loc, val, sem) (*(loc) += (val))

#include "../misc/sys/cdefs.h"
#include <math.h>
#endif
