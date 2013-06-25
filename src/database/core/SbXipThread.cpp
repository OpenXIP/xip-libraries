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

#include <Inventor/errors/SoMemoryError.h>
#include <xip/inventor/core/SbXipThread.h>
#include <xip/inventor/core/SoXipThreadQueueSensor.h>

#ifdef _WINDOWS
#include <process.h>
#else
#include <pthread.h>
#endif


SbXipThread::SbXipThread()
{
	mThreadHandle = 0;
}


SbXipThread::~SbXipThread()
{
	destroy();
}


#ifdef _WINDOWS
void SbXipThread_threadFunc(void *thread)
{
	((SbXipThread*) thread)->evaluate();
}
#else
void* SbXipThread_threadFunc(void *thread)
{
	((SbXipThread*) thread)->evaluate();

	return NULL;
}
#endif


void SbXipThread::create()
{
#ifdef _WINDOWS
	mThreadHandle = (HANDLE) ::_beginthread(SbXipThread_threadFunc, 0, (void*) this);
#else
	pthread_create(&mThreadHandle, 0, SbXipThread_threadFunc, (void*) this);
#endif
}


void SbXipThread::destroy()
{
}


void SbXipThread::join()
{
#ifdef _WINDOWS
	WaitForSingleObject(mThreadHandle, INFINITE);
#else
	//int status;
    void ** value_ptr;
	pthread_join(mThreadHandle, value_ptr);
#endif
}




SbXipThreadNotify::SbXipThreadNotify()
{
	mNotifySensor = new SoXipThreadQueueSensor;
	if (!mNotifySensor)
		SoMemoryError::post("SoXipThreadQueueSensor");
}


SbXipThreadNotify::SbXipThreadNotify(SoSensorCB *func, void *data)
{
	mNotifySensor = new SoXipThreadQueueSensor(func, data);
	if (!mNotifySensor)
		SoMemoryError::post("SoXipThreadQueueSensor");
}


SbXipThreadNotify::~SbXipThreadNotify()
{
	if (mNotifySensor)
		delete mNotifySensor;
}


void SbXipThreadNotify::setFunction(SoSensorCB *func)
{
	if (mNotifySensor)
		mNotifySensor->setFunction(func);
}


void SbXipThreadNotify::setData(void *data)
{
	if (mNotifySensor)
		mNotifySensor->setData(data);
}


SoSensorCB * SbXipThreadNotify::getFunction() const
{
	return mNotifySensor ? mNotifySensor->getFunction() : 0;
}


void * SbXipThreadNotify::getData() const
{
	return mNotifySensor ? mNotifySensor->getData() : 0;
}


void SbXipThreadNotify::startNotify()
{
	if (mNotifySensor)
		mNotifySensor->schedule();
}



