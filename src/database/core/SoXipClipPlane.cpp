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

#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <xip/inventor/core/SoXipClipPlaneElement.h>
#include "SoXipClipPlane.h"

SO_NODE_SOURCE(SoXipClipPlane);

void SoXipClipPlane::initClass()
{
	SO_NODE_INIT_CLASS(SoXipClipPlane, SoNode, "SoNode");
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Constructor
//
// Use: public

SoXipClipPlane::SoXipClipPlane()
//
////////////////////////////////////////////////////////////////////////
{
    SO_NODE_CONSTRUCTOR(SoXipClipPlane);

    // Default clipping plane defines the half-space with non-negative x
    SO_NODE_ADD_FIELD(plane, (SbPlane(SbVec3f(1.0, 0.0, 0.0), 0.0)));
    SO_NODE_ADD_FIELD(on,    (TRUE));
	SO_NODE_ADD_FIELD(flip,	(FALSE));

    isBuiltIn = TRUE;
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Destructor
//
// Use: private

SoXipClipPlane::~SoXipClipPlane()
//
////////////////////////////////////////////////////////////////////////
{
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Typical action method.
//
// Use: extender

void
SoXipClipPlane::doAction(SoAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    // Add clip plane only if it is active
    if (!on.isIgnored() && !on.getValue())
		return;

    if (!plane.isIgnored())
	{
		SbPlane p = plane.getValue();
		if (flip.getValue())
			p = SbPlane(-p.getNormal(), -p.getDistanceFromOrigin());
		SoXipClipPlaneElement::add(action->getState(), this, p);
    }
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Performs callback action
//
// Use: extender

void
SoXipClipPlane::callback(SoCallbackAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    SoXipClipPlane::doAction(action);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Performs GL rendering on a clipPlane node.
//
// Use: extender

void
SoXipClipPlane::GLRender(SoGLRenderAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    SoXipClipPlane::doAction(action);
}

////////////////////////////////////////////////////////////////////////
//
// Description:
//    Performs picking on a clipPlane node.
//
// Use: extender

void
SoXipClipPlane::pick(SoPickAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    SoXipClipPlane::doAction(action);
}
