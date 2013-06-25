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

#include <xip/inventor/core/SoXipMprActiveElement.h>
#include "SoXipMprActive.h"
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoHandleEventAction.h>


SO_NODE_SOURCE(SoXipMprActive);


SoXipMprActive::
SoXipMprActive(void)
{
	SO_NODE_CONSTRUCTOR(SoXipMprActive);

	SO_NODE_ADD_FIELD(on, (TRUE));
	SO_NODE_ADD_FIELD(id, (-1));
}


SoXipMprActive::~SoXipMprActive()
{
}


void 
SoXipMprActive::initClass(void)
{
	SO_NODE_INIT_CLASS(SoXipMprActive, SoNode, "Node");

	SO_ENABLE(SoGLRenderAction, SoXipMprActiveElement);
	SO_ENABLE(SoPickAction,     SoXipMprActiveElement);
	SO_ENABLE(SoCallbackAction, SoXipMprActiveElement);
	SO_ENABLE(SoHandleEventAction, SoXipMprActiveElement);
	SO_ENABLE(SoGetBoundingBoxAction, SoXipMprActiveElement);


}


void SoXipMprActive::doAction(SoAction * action)
{
	if (!on.isIgnored() && !on.getValue()) return;

	SoXipMprActiveElement::set(action->getState(), this, id.getValue(), &id);
}


void SoXipMprActive::GLRender(SoGLRenderAction * action)
{
	doAction(action);
}


void SoXipMprActive::callback(SoCallbackAction * action)
{
	doAction(action);
}


void SoXipMprActive::pick(SoPickAction * action)
{
	doAction(action);
}


void SoXipMprActive::getBoundingBox(SoGetBoundingBoxAction *action)
{
	doAction(action);
}

void SoXipMprActive::handleEvent(SoHandleEventAction *action)
{
	doAction(action);
}


