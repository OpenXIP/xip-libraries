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

/*------------------------------------------------------------------------
    xip/system/GL/glext.h

    This header is intended to provide a platform independent inclusion
    of GL/glext.h header file and should be used by all source files in XIP.
    Do not setup an include path pointing to xip/system/, this file
    must be included with xip/system/GL/glext.h

    Copyright (C) 2008, Siemens Corporate Research

    Authors:
      Sylvain Jaume, sylvain.jaume@siemens.com
      Patric Ljung, patric.ljung@siemens.com

    This file is part of XIP, sponsored by NSF, and provided under the
    caBIG(tm) license.  See end of file for full license.

  ------------------------------------------------------------------------
*/

/*
  ------------------------------------------------------------------------

    Notes

    Header files providing platform independence are located in
    xip/system/GL and the real standard files are placed in the
    subdirectory standard.

    Header files that are platform specific, e.g. wglext.h and
    glxext.h, are located within this directory or in the platform's
    native location (i.e. for OS X and Linux).

  ------------------------------------------------------------------------
*/

#ifndef _XIP_SYSTEM_GLEXT_H_
#define _XIP_SYSTEM_GLEXT_H_

#if defined(WIN32)

  #include <xip/system/GL/standard/glext.h>
  #include <xip/system/GL/wglext.h>
  #define xipGlGetProcAddress(x) wglGetProcAddress(x)

#elif defined(linux)

  #include <X11/Xlib.h>
  #include <X11/Xmd.h>
  #include <xip/system/GL/standard/glext.h>
  #include <xip/system/GL/glxext.h>

  #include <GL/glx.h>
  #define glActiveTextureARB glActiveTextureARBext
  #ifdef GLX_VERSION_1_4
    #define xipGlGetProcAddress(x) glXGetProcAddress((const GLubyte*)x)
  #else
    #define xipGlGetProcAddress(x) glXGetProcAddress((const GLubyte*)x)
  #endif

#elif defined(DARWIN)

  #include <OpenGL/glext.h>
  //#define xipGlGetProcAddress(x) aglGetProcAddress(x)

#endif // Platform selection

#endif // _XIP_SYSTEM_GL_H_

