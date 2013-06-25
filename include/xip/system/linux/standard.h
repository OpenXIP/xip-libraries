/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
// Author Sylvain Jaume <sylvain.jaume@siemens.com>

#ifndef _XIP_LINUX_STANDARD_H_
#define _XIP_LINUX_STANDARD_H_

#include <linux/limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <X11/Xmd.h> // to define 'typedef CARD8 BOOL'


//redefine windows specific functions, types etc.
#ifndef _strtoi64
//used in SoInt64 / SoMFInt64 ...
#define _strtoi64 strtoll
#endif //_strtoi64

//#ifdef __cplusplus
//#include <string>
//#include <algorithm>
//#endif // __cplusplus

//typedef unsigned short   uint16_t;
//typedef unsigned int     uint32_t;
//typedef int64_t 	 __int64;
//typedef u_int64_t        uint64_t;


//TODO properly...
//#ifndef _i64toa(val, buf, base)
//used in SoInt64 / SoMFInt64 ...
#define _i64toa(val, buf, base) sprintf(buf, "%ll", val)
//#endif //_i64toa(val, buf, base)

#ifndef _vsnwprintf
//used in XipException && XipLog
//looks like we need to fall back to a less secure version?
//#define _vsnwprintf vsnwprintf
#define _vsnwprintf vswprintf
#endif //_vsnwprintf

#ifndef MAX_PATH
//used in XipLog // REALLY this should NOT be used, since it may not be consistent
#define MAX_PATH PATH_MAX
#endif //MAX_PATH

//#ifndef wcsnlen(wchar, maxlength)
//used in XipLog
//unfortunately wcsnlen is only a GNU extension for linux & doesn't exist on the mac 
#define wcsnlen(wchar, maxlength) wcslen(wchar)
//#endif //wcsnlen(wchar, maxlength)

//TYPES
//#ifndef __int64
//#define __int64 int64_t
//#endif //__int64
typedef int64_t __int64;

//#ifndef __uint64
//#define __uint64 uint64_t
//#endif //__uint64
typedef uint64_t __uint64;


#ifdef _NATIVE_WCHAR_T_DEFINED
typedef wchar_t WCHAR;
#else // _NATIVE_WCHAR_T_DEFINED
typedef unsigned short WCHAR;
#endif // _NATIVE_WCHAR_T_DEFINED

#define MAX_PATH PATH_MAX

#endif // _XIP_LINUX_STANDARD_H_
