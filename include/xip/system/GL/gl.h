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
    xip/system/GL/gl.h

    This header is intended to provide a platform independent inclusion
    of GL/gl.h header file and should be used by all source files in XIP.
    Do not setup an include path pointing to xip/system/, this file
    must be included with xip/system/GL/gl.h

    Copyright (C) 2008, Siemens Corporate Research

    Authors:
      Sylvain Jaume, sylvain.jaume@siemens.com
      Patric Ljung, patric.ljung@siemens.com

    This file is part of XIP, sponsored by NSF, and provided under the
    caBIG(tm) license.  See end of file for full license.
*/

/*
    Notes

    Header files providing platform independence are located in
    xip/system/GL and the real standard files are placed in the
    subdirectory standard.

    Header files that are platform specific, e.g. wglext.h and
    glxext.h, are located within this directory or in the platform's
    native location (i.e. for Apple OS X and Linux).

    Current list of header files provided for OpenGL in XIP.

    Headers providing platform independence:

      xip/system/GL/gl.h
      xip/system/GL/glu.h
      xip/system/GL/glext.h

    Standard header files from OpenGL.org

      xip/system/GL/standard/gl.h
      xip/system/GL/standard/glext.h
      xip/system/GL/wglext.h
      xip/system/GL/glxext.h
			
  ------------------------------------------------------------------------	
*/

#ifndef _XIP_SYSTEM_GL_H_
#define _XIP_SYSTEM_GL_H_

#if defined(WIN32)

#include <windows.h>
//#include <xip/system/GL/standard/gl.h>
#include <GL/glew.h>

#elif defined(linux)

//#include <xip/system/GL/standard/gl.h>
//#include <GL/gl.h>
#include <GL/glew.h>

#elif defined(DARWIN)

//#include <OpenGL/gl.h>
#include <GL/glew.h>

#endif // Platform selection

#endif // _XIP_SYSTEM_GL_H_

