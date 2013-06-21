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
