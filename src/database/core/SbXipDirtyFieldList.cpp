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

#include <xip/inventor/core/SbXipDirtyFieldList.h>
#include <xip/inventor/core/SoXipSFData.h>
#include <xip/inventor/core/SoXipMFData.h>


SbPList SbXipDirtyFieldList::mDirty;
SoDelayQueueSensor SbXipDirtyFieldList::mDirtySensor;


void SbXipDirtyFieldList::initClass()
{
	mDirtySensor.setFunction(dirtySensorCB);
}


// Because the data pointers are not serialized, the fields must be marked as dirty after deserialization.
// This static method is called by SoXipSFData and SoXipMFData whenever values are read from a stream.
void SbXipDirtyFieldList::append(SoField *field)
{
	int i;

	if (field)
	{
		for (i = mDirty.getLength() - 1; i >= 0; i--)
		{
			if (mDirty.get(i) == field) return;
		}

		mDirty.append(field);

		if (!mDirtySensor.isScheduled())
		{
			mDirtySensor.schedule();
		}
	}
}


// This static method is called by SoXipSFData and SoXipMFData destructors to make sure we do not have invalid
// pointers in the list.
void SbXipDirtyFieldList::remove(SoField *field)
{
	int i;

	if (field)
	{
		for (i = mDirty.getLength() - 1; i >= 0; i--)
		{
			if (mDirty.get(i) == field)
			{
				mDirty.remove(i);
			}
		}
	}
}


// Delay queue callback that will touch all fields in the "dirty" list.
void SbXipDirtyFieldList::dirtySensorCB(void * data, SoSensor * sensor)
{
	int i;
	
	if (mDirtySensor.isScheduled())
	{
		mDirtySensor.unschedule();
	}

	for (i = mDirty.getLength() - 1; i >= 0; i--)
	{
		SoField *field = (SoField *) mDirty.get(i);
		if (field)
		{
			field->touch();
		}
	}

	mDirty.truncate(0);
}
