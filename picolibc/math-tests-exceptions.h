#include <math.h>

#if defined(_SUPPORTS_ERREXCEPT) || !defined(PICOLIBC_LONG_DOUBLE_NOEXCEPT)
#define EXCEPTION_TESTS_long_double	0
#else
#define EXCEPTION_TESTS_long_double	1
#endif
#if defined(_SUPPORTS_ERREXCEPT) || !defined(PICOLIBC_DOUBLE_NOEXCEPT)
#define EXCEPTION_TESTS_double	0
#else
#define EXCEPTION_TESTS_double	1
#endif
#if defined(_SUPPORTS_ERREXCEPT) || !defined(PICOLIBC_FLOAT_NOEXCEPT)
#define EXCEPTION_TESTS_float		0
#else
#define EXCEPTION_TESTS_float	1
#endif
