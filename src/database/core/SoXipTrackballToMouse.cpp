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

#include "SoXipTrackballToMouse.h"
#include <Inventor/actions/SoActions.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include "SoXipMprIntersectionManip.h"
#include <xip/inventor/core/SoXipCursor.h>
#include <xip/inventor/core/SoXipPickRadiusElement.h>

SO_NODE_SOURCE(SoXipTrackballToMouse);


void SoXipTrackballToMouse::initClass()
{
	SO_NODE_INIT_CLASS(SoXipTrackballToMouse, SoGroup, "Group");

	SO_ENABLE(SoHandleEventAction, SoXipPickRadiusElement);
}


SoXipTrackballToMouse::SoXipTrackballToMouse()
{
	SO_NODE_CONSTRUCTOR(SoXipTrackballToMouse);
	SO_NODE_ADD_FIELD(on, (FALSE));

    SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, ANY);
    SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON1);
    SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON2);
    SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON3);
    SO_NODE_SET_SF_ENUM_TYPE(buttonMask, mouseButtonType);
	SO_NODE_ADD_FIELD(buttonMask, (ANY));

	mGrabber = 0;
	
	#ifdef WIN32
	mCaptureWnd = 0;
	#endif
	mTimerSensor = new SoTimerSensor(timerSensorCBFunc, this);
	mTimerSensor->setInterval(0.5);
	mShowCursor = 10;
	mMouseButtonDown = -1;
	mHandleEventAction = new SoHandleEventAction(SbViewportRegion());
	mPickRoot = 0;
	mReleaseOnMousePressed = TRUE;
	mPickRadius = 3.0f;
	
}


SoXipTrackballToMouse::~SoXipTrackballToMouse()
{
	if (mHandleEventAction)
	{
		delete mHandleEventAction;
	}
	delete mTimerSensor;
}


void SoXipTrackballToMouse::handleEvent(SoHandleEventAction *action)
{
	if (!action || !mHandleEventAction) return;

	if (action == mHandleEventAction)
	{
		// set pick radius
		SoXipPickRadiusElement::set(action->getState(), mPickRadius);

		// set view volume and pick root from "parent" action and invoke children
		SoViewVolumeElement::set(action->getState(), this, mViewVolume);
		if (mPickRoot)
			mHandleEventAction->setPickRoot(mPickRoot);

		SoGroup::handleEvent(action);
		return;
	}

	if (!on.getValue())
	{
		// use element to set pick radius
		mPickRadius = 3.0f;
		SoXipPickRadiusElement::set(action->getState(), mPickRadius);

		SoXipMprIntersectionManip::setPickRadius(3);
		SoGroup::handleEvent(action);
	}
	else
	{
		// trackball conversion is on
		// use element to set pick radius
		mPickRadius = 8.0f;
		SoXipPickRadiusElement::set(action->getState(), mPickRadius);

		SoXipMprIntersectionManip::setPickRadius(8);
		const SoEvent *event = action->getEvent();

		mHandleEventAction->setViewportRegion(action->getViewportRegion());
		mHandleEventAction->setEvent(event);
		mPickRoot = action->getPickRoot();

		if (action->getGrabber() == this)
		{
			action->setHandled();

			// during interaction
			if (SO_MOUSE_RELEASE_EVENT(event, ANY))
			{
				if (mReleaseOnMousePressed)
				{
					// handle second mouse release
					((SoMouseButtonEvent*) event)->setButton((SoMouseButtonEvent::Button) mMouseButtonDown);
					mHandleEventAction->setEvent(event);
					mMouseButtonDown = -1;
					SoXipCursor::setClass(0);

					mHandleEventAction->apply(this);
					if (mHandleEventAction->isHandled())
						action->setHandled();
					action->releaseGrabber();
					release();
				}
				else
				{
					// grap capture after first mouse release but do not pass on to children
					grab();
				}
			}
			else if (SO_MOUSE_PRESS_EVENT(event, ANY))
			{
				mReleaseOnMousePressed = TRUE;
			}
			else
			{
				// process all other events
				mHandleEventAction->apply(this);
				if (mHandleEventAction->isHandled())
					action->setHandled();
			}
		}
		else
		{
			// no interaction yet
			mViewVolume = SoViewVolumeElement::get(action->getState());
			mHandleEventAction->apply(this);
			if (mHandleEventAction->isHandled())
				action->setHandled();
			else
				SoXipCursor::setCursor();

			if (SO_MOUSE_PRESS_EVENT(event, ANY))
			{
				if (mHandleEventAction->getGrabber() != 0)
				{
					// start new interaction
					// make sure the mouse release event has the same button as mouse press
					mMouseButtonDown = ((SoMouseButtonEvent*) event)->getButton();

					switch (mMouseButtonDown)
					{
					case SoMouseButtonEvent::BUTTON1: if (!(buttonMask.getValue() & BUTTON1)) mMouseButtonDown = -1; break;
					case SoMouseButtonEvent::BUTTON2: if (!(buttonMask.getValue() & BUTTON2)) mMouseButtonDown = -1; break;
					case SoMouseButtonEvent::BUTTON3: if (!(buttonMask.getValue() & BUTTON3)) mMouseButtonDown = -1; break;
					}

					// only start interaction if button is enabled in the mask
					if (mMouseButtonDown >= 0)
					{
						action->setGrabber(this);
						#ifdef WIN32
						mCaptureWnd = ::GetCapture();
						#endif
						mReleaseOnMousePressed = FALSE;
						SoXipCursor::setClass("ACTIVE");
					}
				}
			}
		}
	}
}


void SoXipTrackballToMouse::grab()
{
	#ifdef WIN32
	if (mCaptureWnd)
	{
		::SetCapture(mCaptureWnd);
		
		mShowCursor = 1;
		//mTimerSensor->schedule();
		mCaptureWnd = 0;
	}
	#endif
}


void SoXipTrackballToMouse::release()
{
	#ifdef WIN32
	mTimerSensor->unschedule();
	if (mShowCursor == 0)
		::ShowCursor(TRUE);
	#endif
}


// timer is used to flash the cursor while interacting
void SoXipTrackballToMouse::timerSensorCBFunc(void *usr, SoSensor *sensor)
{
	SoXipTrackballToMouse *obj = (SoXipTrackballToMouse*) usr;

	if (obj)
	{
		obj->mShowCursor--;

		if (obj->mShowCursor == 0)
		{
			#ifdef WIN32
			::ShowCursor(FALSE);
			#endif
		}

		if (obj->mShowCursor < 0)
		{
			obj->mShowCursor = 1;
			#ifdef WIN32
			::ShowCursor(TRUE);
			#endif
		}
	}
}
