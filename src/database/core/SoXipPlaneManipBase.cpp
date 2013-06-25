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

//
// This implementation is based on an SGI example code (LineManip.cpp), which was
// found in the internet. See end of file for copyright notice.
//
#include "SoXipPlaneManipBase.h"
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>


SO_NODE_SOURCE(SoXipPlaneManipBase);


//
// Constructor; sets up scene graph
//
SoXipPlaneManipBase::SoXipPlaneManipBase()
{
	SO_NODE_CONSTRUCTOR(SoXipPlaneManipBase);

	mDragMouseButton = SoMouseButtonEvent::BUTTON1;
	mHandleEventAction = NULL;
	mPlaneProj = new SbPlaneProjector(FALSE);
	mPlaneProj->setPlane(SbPlane(SbVec3f(0, 0, 1), 0));

	SO_NODE_ADD_FIELD(isManipulating, (FALSE));
}


//
// Destructor.  This will be called when this is unref'ed.
//
SoXipPlaneManipBase::~SoXipPlaneManipBase()
{
	delete mPlaneProj;
}


//
// Magic stuff to register this node with the database
//
void SoXipPlaneManipBase::initClass()
{
	// do not tell SoType that we derive from SoGroup since we manage
	// the children on our own and do not want anybody to add theirs in
	// a visual programming environment
	SO_NODE_INIT_CLASS(SoXipPlaneManipBase, SoGroup, "Node");
}


//
// For setting the plane that the manip works in. You pass it a normal.
//
void SoXipPlaneManipBase::setPlane(const SbPlane &plane)
{
	mPlaneProj->setPlane(plane);
}


//
// Updates projectors to the given point (plane remains the same).
//
void SoXipPlaneManipBase::updateProjectors(const SbVec3f &curPt)
{
	SbVec3f dir = mPlaneProj->getPlane().getNormal();
	mPlaneProj->setPlane(SbPlane(dir, curPt));
}


//
// Does the grunt work of projecting the mouse onto the plane
//
SbVec3f SoXipPlaneManipBase::getMouseProjection()
{
	const SoEvent *e = mHandleEventAction->getEvent();

	// If we're grabbing, we've already got our view parameters.
	// If not, then we'd better get them now.
	// NOTE: If you're grabbing and you try to get view parameters, you'll
	//       get a bad answer. Grabbing causes you to skip over camera
	//       nodes directly to this one. So the state has no valid view info.
	if (mHandleEventAction->getGrabber() != this)
	{
		extractViewingParams(mHandleEventAction);
	}

	mPlaneProj->setViewVolume(mViewVolume);
	return mPlaneProj->project(e->getNormalizedPosition(mVpRegion));
}


void SoXipPlaneManipBase::handleEvent(SoHandleEventAction *action)
{
	SbBool handled = FALSE;
	const SoEvent *e = action->getEvent();

	mHandleEventAction = action;

	if (SoMouseButtonEvent::isButtonPressEvent(e, mDragMouseButton) && !e->wasShiftDown() && !e->wasCtrlDown())
	{
		handled = dragBegin();
	}
	else if (e->isOfType(SoLocation2Event::getClassTypeId()) && (action->getGrabber() == this)) 
	{
		handled = dragMove();
	}
	else if (SoMouseButtonEvent::isButtonReleaseEvent(e, mDragMouseButton) && (action->getGrabber() == this)) 
	{
		handled = dragEnd();
	}

	if (handled)
	{
		action->setHandled();
	}
}

SbBool SoXipPlaneManipBase::dragBegin()
{
//	mHandleEventAction->setGrabber(this);
//	isManipulating.setValue(TRUE);

	return FALSE;
}


SbBool SoXipPlaneManipBase::dragMove()
{
	if (!isManipulating.getValue())
	{
		isManipulating.setValue(TRUE);
	}

	return TRUE;
}


SbBool SoXipPlaneManipBase::dragEnd()
{
	mHandleEventAction->releaseGrabber();
	isManipulating.setValue(FALSE);

	return TRUE;
}


void SoXipPlaneManipBase::extractViewingParams(SoHandleEventAction *ha)
{
	if (!ha) 
	{
		// If the action is NULL, use default values for view info.
		mViewVolume.ortho(-1, 1, -1, 1, 1, 10);
		mVpRegion = SbViewportRegion(1, 1);
	}
	else 
	{
		// Get the view info from the action.
		SoState *state = ha->getState();
		mViewVolume = SoViewVolumeElement::get(state);
		mVpRegion = SoViewportRegionElement::get(state);
	}
}


SbVec2f SoXipPlaneManipBase::getMousePosNormalized()
{
	const SoEvent *e = mHandleEventAction->getEvent();

	if (mHandleEventAction->getGrabber() != this)
	{
		extractViewingParams(mHandleEventAction);
	}

	return e->getNormalizedPosition(mVpRegion);
}


