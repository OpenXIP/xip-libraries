#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <X11/Xmd.h> // to define 'typedef CARD8 BOOL'

# ifdef __cplusplus
#  include <string>
#  include <algorithm>
# endif // __cplusplus

typedef unsigned int     uint32_t;
typedef unsigned short   uint16_t;
typedef int64_t 	 __int64;

#ifdef _NATIVE_WCHAR_T_DEFINED
typedef wchar_t WCHAR;
#else // _NATIVE_WCHAR_T_DEFINED
typedef unsigned short WCHAR;
#endif // _NATIVE_WCHAR_T_DEFINED

#define MAX_PATH PATH_MAX
