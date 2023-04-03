#define CHAR wchar_t
#define L(str) L##str
#define SSCANF swscanf
#define PRINTF wprintf
#define SFMT "%ls"
#include <wchar.h>
#include "tst-sscanf.c"
