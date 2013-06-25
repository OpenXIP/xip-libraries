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

#include <xip/inventor/core/SbXipThreadMutex.h>


SbXipThreadMutex::SbXipThreadMutex()
{
#ifdef _WINDOWS
	InitializeCriticalSection(&mMutex);
#else
//	Should be remplaced by boost implementation
//	pthread_mutex_init(&mMutex, NULL);
#endif
}


SbXipThreadMutex::~SbXipThreadMutex()
{
#ifdef _WINDOWS
	DeleteCriticalSection(&mMutex);
#else
	//	Should be remplaced by boost implementation
//	pthread_mutex_destroy(&mMutex);
#endif
}


void SbXipThreadMutex::lock()
{
#ifdef _WINDOWS
	EnterCriticalSection(&mMutex);
#else
//	Should be remplaced by boost implementation
	//	pthread_mutex_lock(&mMutex);
#endif
}


void SbXipThreadMutex::unlock()
{
#ifdef _WINDOWS
	LeaveCriticalSection(&mMutex);
#else
	//	Should be remplaced by boost implementation
//	pthread_mutex_unlock(&mMutex);
#endif
}

