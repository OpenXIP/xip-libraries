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