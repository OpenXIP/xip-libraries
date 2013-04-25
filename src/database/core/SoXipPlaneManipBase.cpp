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


/*
 * Copyright (c) 1991-95 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that the name of Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Silicon Graphics.
 *
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT SHALL SILICON GRAPHICS BE LIABLE FOR ANY SPECIAL, INCIDENTAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER OR NOT ADVISED OF THE
 * POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF LIABILITY, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * Copyright (C) 1994, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
 * the contents of this file may not be disclosed to third parties, copied or
 * duplicated in any form, in whole or in part, without the prior written
 * permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
 * and Computer Software clause at DFARS 252.227-7013, and/or in similar or
 * successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
 * rights reserved under the Copyright Laws of the United States.
 */
