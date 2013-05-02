// Copyright Siemens Corporate Research Inc. 2007
// Author Sylvain Jaume <sylvain.jaume@siemens.com>

#ifndef _XIP_WINDOWS_STANDARD_H_
#define _XIP_WINDOWS_STANDARD_H_

//#define NOMINMAX
#include <windows.h>

#ifdef __cplusplus
#include <algorithm>
#endif // __cplusplus

typedef __int64 int64_t;

#define snprintf _snprintf
//#define glGetProcAddress wglGetProcAddress

#endif // _XIP_WINDOWS_STANDARD_H_

