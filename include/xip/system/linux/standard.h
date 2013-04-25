#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

# ifdef __cplusplus
#  include <string>
#  include <algorithm>
# endif /* __cplusplus */

typedef unsigned int     uint32_t;
typedef unsigned short   uint16_t;
typedef bool             BOOL;
typedef int64_t 	 __int64;

#if !defined(_NATIVE_WCHAR_T_DEFINED)
typedef unsigned short WCHAR;
#else
typedef wchar_t WCHAR;
#endif

#define MAX_PATH PATH_MAX
