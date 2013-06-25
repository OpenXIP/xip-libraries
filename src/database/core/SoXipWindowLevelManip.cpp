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


#include "SoXipWindowLevelManip.h"
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoComplexityElement.h>
#include <xip/inventor/core/SoXipWindowLevelElement.h>

#include <algorithm>



const unsigned int MAX_SCREENRESOLUTION = 1024;
const unsigned int STEP = 5;
const float DBCLICK_TIME = .3f;

SO_NODE_SOURCE(SoXipWindowLevelManip);


SoXipWindowLevelManip::SoXipWindowLevelManip()
{
	mComplexity = SoComplexityElement::getDefault();

	mLastEventTime = SbTime::zero();

	SO_NODE_CONSTRUCTOR(SoXipWindowLevelManip);

	SO_NODE_ADD_FIELD(window, (1.f));
	SO_NODE_ADD_FIELD(level, (0.5f));

	SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON1);
	SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON2);
	SO_NODE_DEFINE_ENUM_VALUE(mouseButtonType, BUTTON3);
	SO_NODE_SET_SF_ENUM_TYPE(mouse, mouseButtonType);
	SO_NODE_ADD_FIELD(mouse, (BUTTON2));

	SO_NODE_ADD_FIELD(handleComplexity, (FALSE));

	mDefaultWindow = window.getValue();
	mDefaultLevel = level.getValue();
}


void SoXipWindowLevelManip::initClass()
{
	SO_NODE_INIT_CLASS(SoXipWindowLevelManip, SoNode, "Node");

	SO_ENABLE(SoGLRenderAction, SoComplexityElement);

	SO_ENABLE( SoGLRenderAction,	SoXipWindowLevelElement );
	SO_ENABLE(SoPickAction,     SoXipWindowLevelElement);
	SO_ENABLE(SoCallbackAction, SoXipWindowLevelElement);
}


SoXipWindowLevelManip::~SoXipWindowLevelManip()
{
}


void SoXipWindowLevelManip::handleEvent(SoHandleEventAction *action)
{
	const SoEvent *e = action->getEvent();
	SbBool handled = FALSE;

	if (SO_KEY_PRESS_EVENT(e, PAD_MULTIPLY))
	{
		float w = - (float)STEP / MAX_SCREENRESOLUTION;
		w += window.getValue();
		if (w < 0.f) w = 0.f;
		if (window.getValue() != w)
			window.setValue(w);

		handled = TRUE;
	}
	else if (SO_KEY_PRESS_EVENT(e, PAD_SUBTRACT))
	{
		float w = (float)STEP / MAX_SCREENRESOLUTION;
		w += window.getValue();
		if (w > 1.f) w = 1.f;
		if (window.getValue() != w)
			window.setValue(w);

		handled = TRUE;
	}
	else if (SO_KEY_PRESS_EVENT(e, NUM_LOCK))
	{
		float l = - (float)STEP / MAX_SCREENRESOLUTION;
		l += level.getValue();
		if (l < 0.f) l = 0.f;
		if (level.getValue() != l)
			level.setValue(l);

		handled = TRUE;
	}
	else if (SO_KEY_PRESS_EVENT(e, PAD_DIVIDE))
	{
		float l = (float)STEP / MAX_SCREENRESOLUTION;
		l += level.getValue();
		if (l > 1.f) l = 1.f;
		if (level.getValue() != l)
			level.setValue(l);

		handled = TRUE;
	}
	else if ( SoMouseButtonEvent::isButtonPressEvent( e, (SoMouseButtonEvent::Button)mouse.getValue() ) )
	{
		if ( !action->getGrabber() && !e->wasShiftDown() && !e->wasCtrlDown() && !e->wasAltDown() )
		{
			action->setGrabber(this);
			handled = TRUE;

			mLastMousePosition = e->getPosition();

			mComplexity = (SoComplexityElement::getDefault() - 0.01f) / 2.f;

			if ( (e->getTime() - mLastEventTime).getValue() < DBCLICK_TIME )
				autoWindowing.touch();

			mLastEventTime = e->getTime();
		}
	}
	else if (e->isOfType(SoLocation2Event::getClassTypeId()))
	{
		if (action->getGrabber() == this)
		{
			handled = TRUE;

			SbVec2s diff = e->getPosition() - mLastMousePosition;
			mLastMousePosition = e->getPosition();

			float w = (float)diff[0] / ( 2 * MAX_SCREENRESOLUTION );
			float l = (float)diff[1] / ( 2 * MAX_SCREENRESOLUTION );

			l += level.getValue();
			w += window.getValue();

			if (l > 1.f) l = 1.f;
			if (l < 0.f) l = 0.f;
			if (w > 1.f) w = 1.f;
			if (w < 0.f) w = 0.f;

			if (level.getValue() != l)
				level.setValue(l);
			if (window.getValue() != w)
				window.setValue(w);
		}
	}
	else if (SoMouseButtonEvent::isButtonReleaseEvent(e, (SoMouseButtonEvent::Button) mouse.getValue()) && (action->getGrabber() == this)) 
	{
		action->releaseGrabber();
		handled = TRUE;

		// trigger last update with full complexity
		if (handleComplexity.getValue()) level.touch();

		mComplexity = SoComplexityElement::getDefault();
	}

	if (handled)
	{
		action->setHandled();
	}
}


void SoXipWindowLevelManip::GLRender(SoGLRenderAction *action)
{
	if (handleComplexity.getValue() && (mComplexity < SoComplexityElement::getDefault()))
	{
		float complexity = SoComplexityElement::get(action->getState());
		SoComplexityElement::set(action->getState(), std::min(mComplexity, complexity));
	}

	if (window.getValue() != mDefaultWindow)
	{
		SoXipWindowLevelElement::setWindow( action->getState(), this,window.getValue() );
	}

	if (level.getValue() != mDefaultLevel)
	{
		SoXipWindowLevelElement::setLevel( action->getState(), this,level.getValue() );
	}

	SoNode::GLRender(action);
}


