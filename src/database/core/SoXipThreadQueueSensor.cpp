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

#include <xip/inventor/core/SoXipThreadQueueSensor.h>
#include <xip/inventor/core/SoXipThreadManager.h>


SoXipThreadQueueSensor::SoXipThreadQueueSensor() : SoSensor()
{
	// just to make sure the queue is initialized
	SoXipThreadManager::initClass();
}


SoXipThreadQueueSensor::SoXipThreadQueueSensor(SoSensorCB *func, void *data) : SoSensor(func, data)
{
	// just to make sure the queue is initialized
	SoXipThreadManager::initClass();
}


SoXipThreadQueueSensor::~SoXipThreadQueueSensor()
{
	unschedule();
}


void SoXipThreadQueueSensor::schedule()
{
	SoXipThreadManager::getInstance()->insert(this);
}


void SoXipThreadQueueSensor::unschedule()
{
	SoXipThreadManager::getInstance()->remove(this);
}


SbBool SoXipThreadQueueSensor::isScheduled() const
{
	// call thread manager instead of keeping a member variable
	// to avoid threading issues (thread manager uses mutex)
	return SoXipThreadManager::getInstance()->find(this);
}


SbBool SoXipThreadQueueSensor::isBefore(const SoSensor *s) const
{
	return TRUE;
}

