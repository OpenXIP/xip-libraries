// Copyright Siemens Corporate Research Inc. 2007
// Author Sylvain Jaume <sylvain.jaume@siemens.com>

#ifndef _XIP_SYSTEM_STANDARD_H_
#define _XIP_SYSTEM_STANDARD_H_

#ifdef WIN32
#include <xip/system/windows/standard.h>
#endif // WIN32

#ifdef linux 
#include <xip/system/linux/standard.h>
#endif // linux

#ifdef DARWIN
#include <xip/system/osx/standard.h>
#endif // DARWIN

#endif // _XIP_SYSTEM_STANDARD_H_
