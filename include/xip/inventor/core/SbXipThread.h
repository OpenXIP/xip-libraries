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
#ifndef SBXIPTHREAD_H
#define SBXIPTHREAD_H

#include <xip/inventor/core/xipivcore.h>
#include <Inventor/sensors/SoSensor.h>

// simple thread
class XIPIVCORE_API SbXipThread
{
public:
	SbXipThread();
	virtual ~SbXipThread();

	virtual void create();
	virtual void destroy();
	virtual void join();

	virtual void evaluate() = 0;

protected:
#ifdef _WINDOWS
	HANDLE mThreadHandle;
#else
	pthread_t mThreadHandle;
#endif
};


// thread with notification sensor
class SbXipThreadNotify : public SbXipThread
{
public:
	SbXipThreadNotify();
	SbXipThreadNotify(SoSensorCB *func, void *data);
	virtual ~SbXipThreadNotify();

	virtual void startNotify();

	virtual void setFunction(SoSensorCB *func);
	virtual void setData(void *data);
	virtual SoSensorCB * getFunction() const;
	virtual void * getData() const;

protected:
	SoSensor *mNotifySensor;
};

#endif // SBXIPTHREAD_H


