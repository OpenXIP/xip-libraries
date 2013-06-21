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
#ifndef SOXIPMOUSETOGGLE_H
#define SOXIPMOUSETOGGLE_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFShort.h>
#include <Inventor/events/SoMouseButtonEvent.h>

class SoFieldSensor;


class SoXipMouseToggle : public SoNode
{
	SO_NODE_HEADER(SoXipMouseToggle);

public:
	SoXipMouseToggle();
	static void initClass();

	enum mouseButtonType 
	{
		BUTTON1 = SoMouseButtonEvent::BUTTON1,
		BUTTON2 = SoMouseButtonEvent::BUTTON2,
		BUTTON3 = SoMouseButtonEvent::BUTTON3
	};

	enum valueType 
	{
		VALUE_0,
		VALUE_1,
		VALUE_2,
		VALUE_3,
		VALUE_4,
		VALUE_5,
		VALUE_6,
		VALUE_7,
		VALUE_8,
		VALUE_9,
		VALUE_10,
		VALUE_11,
		VALUE_12,
		VALUE_13,
		VALUE_14,
		VALUE_15,
	};

	SoSFEnum mouse;
	SoMFShort sequence;

	SoSFEnum value;

	virtual void handleEvent(SoHandleEventAction *action);

protected:
	virtual ~SoXipMouseToggle();

	SbViewportRegion mViewportRegion;
	SbVec2f mMouseDownPos;

	int mIndex;
	SoFieldSensor *mSequenceSensor;

	static void sequenceSensorCBFunc(void *usr, SoSensor *sensor);
};


#endif // SOXIPMOUSETOGGLE_H
