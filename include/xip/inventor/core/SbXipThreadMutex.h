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
#ifndef SBXIPTHREADMUTEX_H
#define SBXIPTHREADMUTEX_H

#include <xip/system/standard.h>
#include <xip/inventor/core/xipivcore.h>
//#include <Inventor/SoDB.h>	// for windows.h

// wrapper for pthread_mutex_t / CriticalSection
class XIPIVCORE_API SbXipThreadMutex
{
public:
	SbXipThreadMutex();
	virtual ~SbXipThreadMutex();

	void lock();
	void unlock();

protected:
#ifdef _WINDOWS
	CRITICAL_SECTION mMutex;
#else
	pthread_mutex_t mMutex;
#endif
};

#endif // SBXIPTHREADMUTEX_H


