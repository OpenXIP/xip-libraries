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

#include "SoXipMouseToggle.h"
#include <Inventor/actions/SoActions.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/sensors/SoFieldSensor.h>


SO_NODE_SOURCE(SoXipMouseToggle);


void SoXipMouseToggle::initClass()
{
	SO_NODE_INIT_CLASS(SoXipMouseToggle, SoNode, "Node");
}


SoXipMouseToggle::SoXipMouseToggle()
{
	SO_NODE_CONSTRUCTOR(SoXipMouseToggle);

	mMouseDownPos = SbVec2f(0, 0);
	mViewportRegion = SbViewportRegion(1, 1);
	mIndex = -1;

    SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON1);
    SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON2);
    SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON3);
    SO_NODE_SET_SF_ENUM_TYPE(mouse, mouseButtonType);
	SO_NODE_ADD_FIELD(mouse, (BUTTON3));

	SO_NODE_ADD_FIELD(sequence, (0));

    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_0);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_1);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_2);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_3);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_4);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_5);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_6);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_7);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_8);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_9);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_10);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_11);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_12);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_13);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_14);
    SO_NODE_DEFINE_ENUM_VALUE(valueType, VALUE_15);
    SO_NODE_SET_SF_ENUM_TYPE(value, valueType);
	SO_NODE_ADD_FIELD(value, (0));

	mSequenceSensor = new SoFieldSensor(sequenceSensorCBFunc, this);
	mSequenceSensor->attach(&sequence);
}


SoXipMouseToggle::~SoXipMouseToggle()
{
	if (mSequenceSensor)
		delete mSequenceSensor;
}


void SoXipMouseToggle::sequenceSensorCBFunc(void *usr, SoSensor *sensor)
{
	SoXipMouseToggle *thisPtr = (SoXipMouseToggle *) usr;

	// sequence has changed, move to first occurence of current selection or firts item
	for (int i = 0; i < thisPtr->sequence.getNum(); i++)
	{
		if (thisPtr->sequence[i] == thisPtr->value.getValue())
		{
			thisPtr->mIndex = i;
			return;
		}
	}

	if (thisPtr->sequence.getNum() > 0)
	{
		thisPtr->mIndex = 0;
		thisPtr->value.setValue(thisPtr->sequence[thisPtr->mIndex]);
	}
	else
	{
		thisPtr->mIndex = -1;
		thisPtr->value.setValue(0);
	}
}


void SoXipMouseToggle::handleEvent(SoHandleEventAction *action)
{
	int i;
	if (!action) return;
	const SoEvent *e = action->getEvent();

	if (SoMouseButtonEvent::isButtonReleaseEvent(e, (SoMouseButtonEvent::Button) mouse.getValue()))
	{
		action->setHandled();
	}
	else if (SoMouseButtonEvent::isButtonPressEvent(e, (SoMouseButtonEvent::Button) mouse.getValue()))
	{
		action->setHandled();

		if (mIndex < 0)
		{
			// first time, move index to what is set in the output
			for (i = 0; i < sequence.getNum(); i++)
			{
				if (*sequence.getValues(i) == value.getValue())
				{
					mIndex = i;

					int v = *sequence.getValues(mIndex);
					if (v < 16)
					{
						value.setValue(v);
					}

					break;
				}
			}
		}
		else if (sequence.getNum() > 0)
		{
			// avoid duplicate entries in sequence, (such as [ 1, 1, 2 ])
			int baseIndex = mIndex;
			for (i = 1; i < sequence.getNum(); i++)
			{
				mIndex = (baseIndex + i) % sequence.getNum();
				if (sequence[mIndex] != sequence[baseIndex]) break;
			}
		
			int v = *sequence.getValues(mIndex);
			if (v < 16)
			{
				value.setValue(v);
			}
		}

		if (action->getWhatAppliedTo() == SoAction::NODE)
		{
			// send a location event after updating the mode
			// so the mouse cursor is updated by manipulators / examiner
			SoHandleEventAction ha(action->getViewportRegion());
			SoLocation2Event ev;
			ev.setPosition(e->getPosition());
			ev.setTime(e->getTime());
			ev.setShiftDown(e->wasShiftDown());
			ev.setCtrlDown(e->wasCtrlDown());
			ev.setAltDown(e->wasAltDown());
			ha.setEvent(&ev);

			ha.apply(action->getNodeAppliedTo());
		}
	}
}

