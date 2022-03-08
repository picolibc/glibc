#define __MY_CONCAT(a,b) a ## b
#define __MY_CONCATX(a,b) __MY_CONCAT(a,b)
#define TEST_EXCEPTIONS	!__MY_CONCATX(PREFIX, _NO_EXCEPT)
