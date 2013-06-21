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
#include "SoXipPickAction.h"
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/SoPickedPoint.h>

SO_NODE_SOURCE(SoXipPickAction);



/** \fn SoXipPickAction::SoXipPickAction()
* All input and output fields are added and initialized here. 
* \return none
*/
SoXipPickAction::SoXipPickAction()
{
	SO_NODE_CONSTRUCTOR(SoXipPickAction);

	SO_NODE_DEFINE_ENUM_VALUE(keyButtonType, SHIFT);
	SO_NODE_DEFINE_ENUM_VALUE(keyButtonType, CONTROL);
	SO_NODE_SET_SF_ENUM_TYPE(key, keyButtonType);

	SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON1);
	SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON2);
	SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON3);
	SO_NODE_SET_SF_ENUM_TYPE(mouse, mouseButtonType);

	SO_NODE_ADD_FIELD(key, (0));
	SO_NODE_ADD_FIELD(mouse, (BUTTON1));
	SO_NODE_ADD_FIELD(multiplePoints, (FALSE));
	SO_NODE_ADD_FIELD(point, (SbVec3f(0, 0, 0)));

	point.setNum(0);
}


/*! \fn SoXipPickAction::~SoXipPickAction()
* \brief Destructor, cleans up internal data
* \return None
*/
SoXipPickAction::~SoXipPickAction()
{
}


/*! \fn SoXipPickAction::initClass()
* Initializes this class. Called on dll initialization.
* \return void
*/
void SoXipPickAction::initClass()
{
    SO_NODE_INIT_CLASS(SoXipPickAction, SoNode, "Node");
}


/*! \fn SoXipPickAction::handleEvent(SoHandleEventAction *action)
*  Overrides handleEvent to compute and set mouse point(s) to the points field
*
*  \param action - the current state action, no action taken if input action is NULL
*  \return void
*/
void SoXipPickAction::handleEvent(SoHandleEventAction *action)
{
    if (!action)
        return;

	const SoEvent *e = action->getEvent();
    if (!e)
        return;

	SbBool keyOk = TRUE;
	if (key.getValue() & SHIFT) keyOk &= e->wasShiftDown();
	if (key.getValue() & CONTROL) keyOk &= e->wasCtrlDown();
	if (!(key.getValue() & SHIFT)) keyOk &= !e->wasShiftDown();
	if (!(key.getValue() & CONTROL)) keyOk &= !e->wasCtrlDown();

	if (keyOk)
	{
		if (SoMouseButtonEvent::isButtonReleaseEvent(e, (SoMouseButtonEvent::Button) mouse.getValue()))
		{
			SoRayPickAction pa(action->getViewportRegion());
			SbVec2s pixel = action->getEvent()->getPosition(); 
			pa.setPoint(pixel);
			pa.setRadius(3);
			pa.enableCulling(TRUE);
			//pa.setPickAll(true);
			pa.apply(action->getNodeAppliedTo());

			const SoPickedPoint *picked_point = pa.getPickedPoint();
			if (picked_point)
			{
				SbVec3f pt = picked_point->getPoint();
				
				if (multiplePoints.getValue())
				{
					point.set1Value(point.getNum(), pt);
				}
				else
				{
					point.setValue(pt);
				}

				action->setHandled();
			}
		}
	}

	SoNode::handleEvent(action);	
}


