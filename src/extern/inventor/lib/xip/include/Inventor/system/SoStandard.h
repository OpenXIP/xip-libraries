// Copyright Siemens Corporate Research Inc. 2007
// Author Sylvain Jaume <sylvain.jaume@siemens.com>

#ifndef _INVENTOR_SYSTEM_STANDARD_H_
#define _INVENTOR_SYSTEM_STANDARD_H_

#ifdef WIN32
#include <Inventor/system/windows/standard.h>
#endif // WIN32

#ifdef linux 
#include <Inventor/system/linux/standard.h>
#endif // linux

#ifdef __APPLE__
#include <Inventor/system/osx/standard.h>
#endif // __APPLE__

#endif // _XIP_SYSTEM_STANDARD_H_
