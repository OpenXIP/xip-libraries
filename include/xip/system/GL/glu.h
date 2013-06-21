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

/*
  ------------------------------------------------------------------------

    xip/system/GL/glu.h

    This header is intended to provide a platform independent inclusion
    of GL/glu.h header file and should be used by all source files in XIP.
    Do not setup an include path pointing to xip/system/, this file
    must be included with xip/system/GL/glu.h

    Copyright (C) 2008, Siemens Corporate Research

    Authors:
      Sylvain Jaume, sylvain.jaume@siemens.com
      Patric Ljung, patric.ljung@siemens.com

    This file is part of XIP, sponsored by NSF, and provided under the
    caBIG(tm) license.  See end of file for full license.

  ------------------------------------------------------------------------
*/

#ifndef _XIP_SYSTEM_GLU_H_
#define _XIP_SYSTEM_GLU_H_

#if defined(WIN32)

#include <GL/glu.h>

#elif defined(linux)

#include <GL/glu.h>

#elif defined(DARWIN)

#include <OpenGL/glu.h>
//#include <GL/glu.h>

#endif // Platform selection

#endif // _XIP_SYSTEM_GLU_H_

