// Copyright Siemens Corporate Research Inc. 2007
// Author Sylvain Jaume <sylvain.jaume@siemens.com>

#ifndef _XIP_SYSTEM_XIPGLWINDOW_H_
#define _XIP_SYSTEM_XIPGLWINDOW_H_

#ifdef WIN32
//#include <GL/wgl.h>
#endif /* WIN32 */

#ifdef LINUX
# include <GL/glx.h>
#endif /* LINUX */

#ifdef DARWIN
# include <AGL/agl.h>
#endif /* DARWIN */

#endif // _XIP_SYSTEM_XIPGLWINDOW_H_

