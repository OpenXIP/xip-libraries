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

#include <xip/system/standard.h>
#include "SoXipDogEar.h"
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <xip/inventor/core/SoXipCursor.h>
#include <Inventor/SbLinear.h>
#include <xip/system/GL/gl.h>
#include <algorithm>


SO_NODE_SOURCE(SoXipDogEar);

void SoXipDogEar::initClass()
{
	SO_NODE_INIT_CLASS(SoXipDogEar, SoNode, "Node");
}

SoXipDogEar::SoXipDogEar()
{
	SO_NODE_CONSTRUCTOR(SoXipDogEar);

	SO_NODE_ADD_FIELD(next, ());
	SO_NODE_ADD_FIELD(previous, ());

	mForwardDirection = TRUE;
	mTimerSensor = new SoTimerSensor(timerSensorCBFunc, this);
}

SoXipDogEar::~SoXipDogEar()
{
	if (mTimerSensor)
	{
		delete mTimerSensor;
	}
}

void SoXipDogEar::GLRender(SoGLRenderAction * action)
{
	SbViewportRegion viewportRegion = SoViewportRegionElement::get( action->getState() );
	SbVec2s s = viewportRegion.getViewportSizePixels();

	int dogEarSize = getDogEarSize(viewportRegion);
	if (dogEarSize <= 0) return;

	glPushAttrib(GL_TRANSFORM_BIT | GL_ENABLE_BIT | GL_LINE_BIT | GL_CURRENT_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, s[0], 0, s[1], -1, 1);

	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_TRIANGLES);
		glVertex2i(s[0] - dogEarSize, s[1] - dogEarSize);
		glVertex2i(s[0] - dogEarSize, s[1]);
		glVertex2i(s[0], s[1] - dogEarSize);
	glEnd();

	glColor3f(0.f, 0.f, 0.f);
	glBegin(GL_TRIANGLES);
		glVertex2i(s[0], s[1]);
		glVertex2i(s[0], s[1] - dogEarSize);
		glVertex2i(s[0] - dogEarSize, s[1]);
	glEnd();

	glBegin(GL_LINES);
		glVertex2i(s[0] - dogEarSize, s[1] - dogEarSize);
		glVertex2i(s[0] - dogEarSize, s[1]);
	glEnd();

	glColor3f(0.4f, 0.4f, 0.4f);
	glBegin(GL_LINES);
		glVertex2i(s[0] - dogEarSize, s[1] - dogEarSize);
		glVertex2i(s[0], s[1] - dogEarSize);

		glVertex2i(s[0] - dogEarSize, s[1]);
		glVertex2i(s[0], s[1]);

		glVertex2i(s[0], s[1]);
		glVertex2i(s[0], s[1] - dogEarSize);
	glEnd();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	glPopAttrib();
}

void SoXipDogEar::handleEvent(SoHandleEventAction *action)
{
	const SoEvent *e = action->getEvent();
	SbBool handled = FALSE;
	
	if (SO_KEY_PRESS_EVENT(e, PAD_1))
	{
		next.touch();
		handled = TRUE;
	}
	else if (SO_KEY_PRESS_EVENT(e, PAD_2))
	{
		previous.touch();
		handled = TRUE;
	}
	else if (SoMouseButtonEvent::isButtonPressEvent(e, SoMouseButtonEvent::BUTTON1))
	{
		mMouseDownPosition = e->getPosition();

		if ((action->getGrabber() == 0))// && !e->wasShiftDown() && !e->wasCtrlDown())
		{
			SbViewportRegion viewportRegion = SoViewportRegionElement::get( action->getState() );
			SbVec2s o = viewportRegion.getViewportOriginPixels();
			SbVec2s s = viewportRegion.getViewportSizePixels();

			int dogEarSize = getDogEarSize(viewportRegion);
			if (dogEarSize <= 0) return;

			SbVec2s p = e->getPosition() - o - s + SbVec2s(dogEarSize, dogEarSize);

			if ((p[0] >= 0) && (p[0] < dogEarSize) && (p[1] >= 0) && (p[1] < dogEarSize))
			{
				// click on dog ear
				float side = (float) (-p[0] + dogEarSize) / (float) p[1];

				if (side <= 1.f)
				{
					mForwardDirection = TRUE;
					next.touch();
				}
				else
				{
					mForwardDirection = FALSE;
					previous.touch();
				}

				mTimerSensor->setInterval(0.5f);
				mTimerSensor->schedule();
				action->setGrabber(this);

				SoXipCursor::setCursor();
				handled = TRUE;
			}
		}
	}
	else if (SoMouseButtonEvent::isButtonReleaseEvent(e, SoMouseButtonEvent::BUTTON1))
	{
		mTimerSensor->unschedule();
		if (action->getGrabber() == this)
		{
			action->releaseGrabber();
			SoXipCursor::setCursor();
			handled = TRUE;
		}
		else
		{
			// set event to handled if the click was on the dog ear so SoXipPickAction stays inactive
			SbViewportRegion viewportRegion = SoViewportRegionElement::get( action->getState() );
			SbVec2s o = viewportRegion.getViewportOriginPixels();
			SbVec2s s = viewportRegion.getViewportSizePixels();

			int dogEarSize = getDogEarSize(viewportRegion);
			if (dogEarSize <= 0) return;

			SbVec2s p = mMouseDownPosition - o - s + SbVec2s(dogEarSize, dogEarSize);

			if ((p[0] >= 0) && (p[0] < dogEarSize) && (p[1] >= 0) && (p[1] < dogEarSize))
			{
				handled = TRUE;
			}
		}
	}
	else if (e->isOfType(SoLocation2Event::getClassTypeId()))
	{
		if (mTimerSensor->isScheduled() || (action->getGrabber() == this))
		{
			SoXipCursor::setCursor();

			handled = TRUE;
		}
		else //if (!e->wasShiftDown() && !e->wasCtrlDown())
		{
			SbViewportRegion viewportRegion = SoViewportRegionElement::get( action->getState() );
			SbVec2s o = viewportRegion.getViewportOriginPixels();
			SbVec2s s = viewportRegion.getViewportSizePixels();

			int dogEarSize = getDogEarSize(viewportRegion);
			if (dogEarSize <= 0) return;

			SbVec2s p = e->getPosition() - o - s + SbVec2s(dogEarSize, dogEarSize);

			if ((p[0] >= 0) && (p[0] < dogEarSize) && (p[1] >= 0) && (p[1] < dogEarSize))
			{
				// click on dog ear
				handled = TRUE;

				SoXipCursor::setCursor();
			}
		}
	}

	if (handled)
	{
		action->setHandled();
	}
}

void SoXipDogEar::timer(SoSensor *sensor)
{
	if (mTimerSensor->getInterval() > 0.05f)
	{
		// first timeout, switch to auto repeat
		mTimerSensor->setInterval(0.05f);
	}
	else
	{
		// in auto repeat mode
		if (mForwardDirection)
		{
			next.touch();
		}
		else
		{
			previous.touch();
		}
	}
}

void SoXipDogEar::timerSensorCBFunc(void *usr, SoSensor *sensor)
{
	((SoXipDogEar*)usr)->timer(sensor);
}

int SoXipDogEar::getDogEarSize(const SbViewportRegion &viewportRegion)
{
	SbVec2s s = viewportRegion.getViewportSizePixels();

	int minSize = std::min(s[0], s[1]);
	int dogEarSize = minSize / 8;
	if (dogEarSize < 10) return 0;
	dogEarSize = std::min(dogEarSize, 50);

	return dogEarSize;
}


void SoXipDogEar::rayPick(SoRayPickAction *action)
{
	action->setObjectSpace(SbMatrix::identity());

	SbViewVolume vv = SoViewVolumeElement::get(action->getState()); //action->getViewVolume();
	SbViewportRegion viewportRegion = SoViewportRegionElement::get( action->getState() );

	int dogEarSize = getDogEarSize(viewportRegion);
	if (dogEarSize <= 0) return;

	float d = vv.getNearDist() + vv.getDepth() * 0.01;
	float sw = ((float) dogEarSize / (float) viewportRegion.getViewportSizePixels()[0]);
	float sh = ((float) dogEarSize / (float) viewportRegion.getViewportSizePixels()[1]);

	SbVec3f topRight    = vv.getPlanePoint(d, SbVec2f(1, 1));
	SbVec3f topLeft     = vv.getPlanePoint(d, SbVec2f(1 - sw, 1));
	SbVec3f bottomLeft  = vv.getPlanePoint(d, SbVec2f(1 - sw, 1 - sh));
	SbVec3f bottomRight = vv.getPlanePoint(d, SbVec2f(1, 1 - sh));

	// if dogear is picked, pickAll is always FALSE: only dogear is returned
	SbVec3f barycentric, intersection;
	SbBool front;
	if (action->intersect(topLeft, topRight, bottomRight, intersection, barycentric, front))
	{
		action->setPickAll(FALSE);
		action->addIntersection(intersection);
	}
	else if (action->intersect(topLeft, bottomRight, bottomLeft, intersection, barycentric, front))
	{
		action->setPickAll(FALSE);
		action->addIntersection(intersection);
	}
}
