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

#ifndef SOXIPPLANEMANIPBASE_H
#define SOXIPPLANEMANIPBASE_H

#include <Inventor/SbLinear.h>
#include <Inventor/events/SoEvents.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/SbViewportRegion.h>

class SbPlaneProjector;


// Base class for manipulators operating on a plane (typically for 2D geometry).
class SoXipPlaneManipBase : public SoGroup
{
	SO_NODE_HEADER(SoXipPlaneManipBase);

public:
	SoXipPlaneManipBase();
	static void initClass();

	SoSFBool isManipulating;

protected:
	virtual ~SoXipPlaneManipBase();

	virtual SbBool dragBegin();
	virtual SbBool dragMove();
	virtual SbBool dragEnd();
	virtual void handleEvent(SoHandleEventAction *action);
	virtual void extractViewingParams(SoHandleEventAction *action);
	virtual SbVec2f getMousePosNormalized();

	virtual void setPlane(const SbPlane &plane);
	virtual void updateProjectors(const SbVec3f &curPt);
	virtual SbVec3f getMouseProjection();

	SoHandleEventAction	*mHandleEventAction;
	SoMouseButtonEvent::Button mDragMouseButton;
	SbViewVolume		mViewVolume;
	SbViewportRegion	mVpRegion;
	SbPlaneProjector	*mPlaneProj;
};

#endif // SOXIPPLANEMANIPBASE_H
