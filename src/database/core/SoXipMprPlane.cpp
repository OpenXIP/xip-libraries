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

#include "SoXipMprPlane.h"
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/elements/SoClipPlaneElement.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <xip/inventor/core/SoXipMprPlaneElement.h>


SO_NODE_SOURCE(SoXipMprPlane);


SoXipMprPlane::SoXipMprPlane(void)
{
	SO_NODE_CONSTRUCTOR(SoXipMprPlane);

	SO_NODE_ADD_FIELD(on, (TRUE));
	SO_NODE_ADD_FIELD(plane, (SbMatrix::identity()));
	SO_NODE_ADD_FIELD(center, (SbVec3f(0, 0, 0)));
	SO_NODE_ADD_FIELD(color, (SbColor(1, 1, 1)));
	SO_NODE_ADD_FIELD(id, (0));
	SO_NODE_ADD_FIELD(stepSize, (0));
	SO_NODE_ADD_FIELD(thickness, (1));
}


SoXipMprPlane::~SoXipMprPlane()
{
}


void SoXipMprPlane::initClass(void)
{
	SO_NODE_INIT_CLASS(SoXipMprPlane, SoNode, "Node");

	SO_ENABLE(SoGLRenderAction, SoXipMprPlaneElement);
	SO_ENABLE(SoPickAction,     SoXipMprPlaneElement);
	SO_ENABLE(SoCallbackAction, SoXipMprPlaneElement);
	SO_ENABLE(SoHandleEventAction, SoXipMprPlaneElement);

	SO_ENABLE(SoGLRenderAction, SoClipPlaneElement);
	SO_ENABLE(SoPickAction,     SoClipPlaneElement);
	SO_ENABLE(SoCallbackAction, SoClipPlaneElement);
	SO_ENABLE(SoHandleEventAction, SoClipPlaneElement);
}


void SoXipMprPlane::doAction(SoAction * action)
{
	// don't do anything if turned off
	if (!on.isIgnored() && !on.getValue()) return;

	// add MPR plane element
	SoXipMprPlaneElement::add(
		action->getState(),
		this,
		plane.getValue(),
		center.getValue(),
		color.getValue(),
		id.getValue(),
		stepSize.getValue(),
		thickness.getValue(),
		&plane,
		&center);

}


void SoXipMprPlane::GLRender(SoGLRenderAction * action)
{
	doAction(action);
}


void SoXipMprPlane::callback(SoCallbackAction * action)
{
	doAction(action);
}


void SoXipMprPlane::pick(SoPickAction * action)
{
	doAction(action);
}


void SoXipMprPlane::handleEvent(SoHandleEventAction *action)
{
	doAction(action);
}


