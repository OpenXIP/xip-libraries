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

#include <xip/inventor/core/SoXipThreadManager.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/errors/SoMemoryError.h>
#include <Inventor/sensors/SoDelayQueueSensor.h>


SoXipThreadManager* SoXipThreadManager::mInstance = 0;


void SoXipThreadManager::initClass()
{
	if (!mInstance)
		mInstance = new SoXipThreadManager;
}


SoXipThreadManager* SoXipThreadManager::getInstance()
{
	if (!mInstance)
		initClass();

	return mInstance;
}


SoXipThreadManager::SoXipThreadManager()
{
	mHead = 0;
	mDelayQueueSensor = new SoDelayQueueSensor(processThreadQueueCB, this);
	if (mDelayQueueSensor)
	{
		mDelayQueueSensor->setPriority(1);
		mDelayQueueSensor->schedule();
	}
	else
	{
		SoMemoryError::post("SoDelayQueueSensor");
	}
}


SoXipThreadManager::~SoXipThreadManager()
{
	if (mDelayQueueSensor)
		delete mDelayQueueSensor;
}


void SoXipThreadManager::insert(SoSensor *sensor)
{
	mMutex.lock();

	sensor->setNextInQueue(0);

	if (mHead)
	{
		// insert new sensor at end of queue so the sensors
		// are triggered in the order of scheduling
		SoSensor *i = mHead;
		while (i)
		{
			if (i == sensor)
				// already scheduled
				break;

			if (!i->getNextInQueue())
			{
				// last item
				i->setNextInQueue(sensor);
				break;
			}

			i = i->getNextInQueue();
		}
	}
	else
	{
		// nothing in the queue yet, sensor becomes the new head
		mHead = sensor;
	}

	mMutex.unlock();
}


void SoXipThreadManager::remove(SoSensor *sensor)
{
	mMutex.lock();

	if (mHead)
	{
		if (mHead == sensor)
		{
			// just make next node the new head
			mHead = mHead->getNextInQueue();
		}
		else
		{
			// whoever has sensor as the next node
			// needs to be pointed to the one after sensor
			SoSensor *i = mHead;
			do
			{
				if (i->getNextInQueue() == sensor)
				{
					i->setNextInQueue(sensor->getNextInQueue());
					break;
				}

				i = i->getNextInQueue();
			}
			while (i);
		}
	}

	mMutex.unlock();
}


SbBool SoXipThreadManager::find(const SoSensor *sensor)
{
	SbBool found = FALSE;

	mMutex.lock();

	SoSensor *i = mHead;
	while (i)
	{
		if (i == sensor)
		{
			found = TRUE;
			break;
		}
		i = i->getNextInQueue();
	}

	mMutex.unlock();

	return found;
}


void SoXipThreadManager::processQueue()
{
	mMutex.lock();

	// triggers all pending sensors
	// to allow rescheduling of sensors in teh callback,
	// mHead is cleared before the loop and next in queue
	// is queried before triggering
	SoSensor *i = mHead;
	mHead = 0;

	while (i)
	{
		SoSensor *current = i;
		i = i->getNextInQueue();

		try
		{
			current->trigger();
		}
		catch(...)
		{
			SoDebugError::post("SoXipThreadManager::processQueue", "Unhandled exception!");
		}
	}

	mMutex.unlock();
}


void SoXipThreadManager::processThreadQueueCB(void *data, SoSensor *sensor)
{
	((SoXipThreadManager*) data)->processQueue();

	sensor->schedule();
}

