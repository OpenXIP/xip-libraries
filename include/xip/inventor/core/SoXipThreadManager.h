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
#ifndef SOXIPTHREADMANAGER_H
#define SOXIPTHREADMANAGER_H

#include <Inventor/sensors/SoSensor.h>
#include <xip/inventor/core/SbXipThreadMutex.h>

class SoDelayQueueSensor;


// thread-safe sensor queue used by SoDelayQueueSensor
class XIPIVCORE_API SoXipThreadManager
{
public:
	static SoXipThreadManager* getInstance();
	static void initClass();

	SoXipThreadManager();
	virtual ~SoXipThreadManager();

	virtual void insert(SoSensor *sensor);
	virtual void remove(SoSensor *sensor);
	virtual SbBool find(const SoSensor *sensor);
	virtual void processQueue();

protected:
	SoSensor *mHead;
	SoDelayQueueSensor *mDelayQueueSensor;
	SbXipThreadMutex mMutex;
	static SoXipThreadManager* mInstance;

private:
	static void processThreadQueueCB(void *data, SoSensor *sensor);
};


#endif SOXIPTHREADMANAGER_H
