/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
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
