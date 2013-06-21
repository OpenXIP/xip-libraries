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

#include "SoXipMprLock.h"
#include <Inventor/actions/SoActions.h>
#include <xip/inventor/core/SoXipMprLockElement.h>


SO_NODE_SOURCE(SoXipMprLock);


void SoXipMprLock::initClass()
{
	SO_NODE_INIT_CLASS(SoXipMprLock, SoNode, "Node");

	// enable elements goes here
	SO_ENABLE(SoHandleEventAction, SoXipMprLockElement);
}


SoXipMprLock::SoXipMprLock()
{
	SO_NODE_CONSTRUCTOR(SoXipMprLock);

	SO_NODE_ADD_FIELD(orientation, (FALSE));
	SO_NODE_ADD_FIELD(position, (FALSE));
	SO_NODE_ADD_FIELD(scale, (FALSE));
	SO_NODE_ADD_FIELD(lineOrientation, (FALSE));
	SO_NODE_ADD_FIELD(linePosition, (FALSE));
}


void SoXipMprLock::handleEvent(SoHandleEventAction *action)
{
	int32_t lock = 0;

	if (orientation.getValue()) lock |= SoXipMprLockElement::ORIENTATION;
	if (position.getValue()) lock |= SoXipMprLockElement::POSITION;
	if (scale.getValue()) lock |= SoXipMprLockElement::SCALE;
	if (lineOrientation.getValue()) lock |= SoXipMprLockElement::LINE_ORIENTATION;
	if (linePosition.getValue()) lock |= SoXipMprLockElement::LINE_POSITION;

	SoXipMprLockElement::set(action->getState(), this, lock);
}

