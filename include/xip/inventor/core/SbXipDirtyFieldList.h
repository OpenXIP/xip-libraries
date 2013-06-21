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
#ifndef SBXIPDIRTYFIELDLIST_H
#define SBXIPDIRTYFIELDLIST_H

#include <Inventor/SoLists.h>
#include <Inventor/sensors/SoDelayQueueSensor.h>
#include <xip/inventor/core/xipivcore.h>

// this util is exported for use in other libraries but should not be made public yet
// until we have confirmed there are no side effects
class XIPIVCORE_API SbXipDirtyFieldList
{
public:
	static void initClass();
	static void append(SoField *field);
	static void remove(SoField *field);

private:
	static void dirtySensorCB(void * data, SoSensor * sensor);

	static SbPList mDirty;
	static SoDelayQueueSensor mDirtySensor;
};

#endif // SBXIPDIRTYFIELDLIST_H


