#ifndef _HACKS_H
#define _HACKS_H

#ifndef NO_GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#define __STDC_WANT_IEC_60559_BFP_EXT__

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
#define getrlimit(a,b)	((void) (a), (void) (b), 0)
#define sigsetjmp(a,b)	setjmp(a)
#define siglongjmp(a,b) longjmp(a,b)
#define sigjmp_buf jmp_buf

extern void *check_malloc(unsigned long size);

#define mmap(base, size, prot, parm, a, b) check_malloc(size)
#define MAP_FAILED NULL
#define MAP_SHARED 0
#define MAP_PRIVATE 0
#define MAP_FIXED 0
#define MAP_FILE 0
#define MAP_ANONYMOUS 0
#define PROT_READ 1
#define PROT_WRITE 2

#define mprotect(base, size, prot) ((void) (base), (void) (size), 0)
#define posix_fallocate(a, b, c) 0
#define munmap(base, size) (free(base), (void) (size), 0)
#define __BIG_ENDIAN BIG_ENDIAN
#define __LITTLE_ENDIAN LITTLE_ENDIAN
#define __BYTE_ORDER BYTE_ORDER
#define MERGE(w0, sh_1, w1, sh_2) (((w0) >> (sh_1)) | ((w1) << (sh_2)))

#define TEMP_FAILURE_RETRY(x) (x)

#define RLIMIT_STACK	0

#define IS_IN(x)	0

static inline int chdir(const char *a) { return 0; }

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
#define fgetc_unlocked fgetc
#define fgets_unlocked fgets
#define fopen64 fopen

#define FILENAME_MAX	512
#define P_tmpdir "/tmp"

#define mtrace()
#define remove(x) unlink(x)

#define GL_UNUSED

static inline long sysconf(int x) { switch (x) { case 8: return 0x1000; default: return -1; } }

#define xsysconf sysconf
#define xmalloc malloc
#define xcalloc calloc
#define xsetlocale setlocale
#define _setjmp setjmp
#define copysignf32x copysignf
#define strfromf32x strfromf

#define powerof2(x)	(((x) & ((x)-1)) == 0)

#define loff_t off_t

#define __USE_ISOC11

#ifdef __riscv
#if __riscv_flen < 64
#define DBL_NO_EXCEPT	1
#endif
#if __riscv_flen < 128
#define LDBL_NO_EXCEPT	1
#endif
#endif

#ifdef __arm__
#if defined(__SOFTFP__) || (__ARM_FP & 0x8) == 0
#define DBL_NO_EXCEPT	1
#define LDBL_NO_EXCEPT	1
#endif

#if defined(__SOFTFP__) || (__ARM_FP & 0x4) == 0
#define FLT_NO_EXCEPT	1
#define DBL_NO_EXCEPT	1
#define LDBL_NO_EXCEPT	1
#endif
#endif

#ifndef FLT_NO_EXCEPT
#define FLT_NO_EXCEPT 0
#endif

#ifndef DBL_NO_EXCEPT
#define DBL_NO_EXCEPT 0
#endif

#ifndef LDBL_NO_EXCEPT
#define LDBL_NO_EXCEPT 0
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
#include <fcntl.h>
#include <stdio.h>

#define stat64 stat
#define fstat64 fstat
#endif
