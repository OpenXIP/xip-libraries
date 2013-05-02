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

#include "SoXipViewportGroup.h"
#include <xip/inventor/core/SoXipCursor.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/misc/SoChildList.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <xip/inventor/core/SoXipActiveViewportElement.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoRayPickAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/actions/SoLineHighlightRenderAction.h>
#include <Inventor/actions/SoGetMatrixAction.h>
#include <Inventor/actions/SoBoxHighlightRenderAction.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>

#include <Inventor/elements/SoCoordinateElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoProjectionMatrixElement.h>
#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/elements/SoLinePatternElement.h>


#ifndef MIN
# define MIN(a,b) ( a < b ? a : b )
#endif

SO_NODE_SOURCE(SoXipViewportGroup);


SoXipViewportGroup::SoXipViewportGroup(void) : SoGroup()
{
	mWindowWidth = 0;
	mWindowHeight = 0;
	mActiveViewport = -1;
	mPickViewport = 0;
	mLastButtonDownTime = SbTime::getTimeOfDay();
	mResizeMode = RESIZE_NONE;
	mResizeValid = FALSE;

	SO_NODE_CONSTRUCTOR(SoXipViewportGroup);

	SO_NODE_ADD_FIELD(on, (TRUE));
	SO_NODE_ADD_FIELD(activateOnClick, (TRUE));
	SO_NODE_ADD_FIELD(maximizeOnDoubleClick, (FALSE));
	SO_NODE_ADD_FIELD(resizable, (FALSE));
	SO_NODE_ADD_FIELD(relative, (TRUE));
	SO_NODE_ADD_FIELD(viewports, (SbVec4f( 0, 0, 1, 1)));
	SO_NODE_ADD_FIELD(current, (0));
	SO_NODE_ADD_FIELD(maximized, (FALSE));

	mRelativeFieldSensors = new SoFieldSensor( &fieldSensorCBFunc, this );
	mRelativeFieldSensors->attach(&relative);
	mRelativeFieldSensors->setPriority(0);

	mLineSet = new SoIndexedLineSet();
	mLineSet->ref();
}

SoXipViewportGroup::SoXipViewportGroup( int numChildren ) : SoGroup( numChildren )
{
	mWindowWidth = 0;
	mWindowHeight = 0;
	mActiveViewport = -1;
	mPickViewport = 0;
	mLastButtonDownTime = SbTime::getTimeOfDay();
	mResizeMode = RESIZE_NONE;
	mResizeValid = FALSE;
	
	SO_NODE_CONSTRUCTOR(SoXipViewportGroup);

	SO_NODE_ADD_FIELD(on, (TRUE));
	SO_NODE_ADD_FIELD(relative, (TRUE));
	SO_NODE_ADD_FIELD(viewports, (SbVec4f( 0, 0, 1, 1)));
	SO_NODE_ADD_FIELD(current, (-1));

	mRelativeFieldSensors = new SoFieldSensor( &fieldSensorCBFunc, this );
	mRelativeFieldSensors->attach(&relative);
	mRelativeFieldSensors->setPriority(0);

	mLineSet = new SoIndexedLineSet();
	mLineSet->ref();
}


SoXipViewportGroup::~SoXipViewportGroup()
{
	if (mRelativeFieldSensors)
	{
		delete mRelativeFieldSensors;
	}

	if (mLineSet)
	{
		mLineSet->unref();
	}
}


void SoXipViewportGroup::initClass(void)
{
	SO_NODE_INIT_CLASS(SoXipViewportGroup, SoGroup, "Group");

	SO_ENABLE(SoGLRenderAction, SoXipActiveViewportElement);
	SO_ENABLE(SoHandleEventAction, SoXipActiveViewportElement);
}


int SoXipViewportGroup::pickViewportGroup(SoAction *action, SbVec2s point) const
{
	int numIndices;
	const int* indices;
	int lastChildIndex;

	if (maximized.getValue())
		return current.getValue();

	if( action->getPathCode( numIndices, indices ) == SoAction::IN_PATH )
		lastChildIndex = indices[ numIndices - 1 ];
	else
		lastChildIndex = getNumChildren() - 1;

	SbViewportRegion viewportRegion = SoViewportRegionElement::get( action->getState() );

	int maxIndex = MIN( viewports.getNum() - 1, lastChildIndex );
	for( int i = 0; i <= maxIndex; ++ i )
	{
		SbVec4f values = viewports[ i ].getValue();
		if (values[2] == 0 || values[3] == 0)
			continue;

		if( relative.getValue() )
		{
			SbVec2f origin( values[0] , values[1] ), size( values[2], values[3] );
			viewportRegion.setViewport( origin, size );
		}
		else
		{
			SbVec2s origin( static_cast<short>(values[0]) , static_cast<short>(values[1]) ), 
							size( static_cast<short>(values[2]), static_cast<short>(values[3]) );
		}

		SbVec2s origin, size;
		origin = viewportRegion.getViewportOriginPixels();
		size = viewportRegion.getViewportSizePixels();

		if ((origin[0] <= point[0]) && ((origin[0] + size[0]) >= point[0])
			&& (origin[1] <= point[1]) && ((origin[1] + size[1]) >= point[1]))
		{
			return i;
		}
	}

	return -1;
}


void SoXipViewportGroup::doAction(SoAction * action)
{
	// don't do anything if turned off
	if (!on.isIgnored() && !on.getValue()) return;

	action->getState()->push();

	int numIndices;
	const int* indices;
	int lastChildIndex;

	if( action->getPathCode( numIndices, indices ) == SoAction::IN_PATH )
		lastChildIndex = indices[ numIndices - 1 ];
	else
		lastChildIndex = getNumChildren() - 1;

	// record window size for conversion absolut -> relative and back
	SbViewportRegion viewportRegion = SoViewportRegionElement::get( action->getState() );
	SbViewportRegion originalViewportRegion = viewportRegion;
	mWindowWidth  = viewportRegion.getWindowSize()[ 0 ];
	mWindowHeight = viewportRegion.getWindowSize()[ 1 ];

	int maxIndex = MIN( viewports.getNum() - 1, lastChildIndex );
	for( int i = 0; i <= maxIndex; ++ i )
	{
		SbVec4f values = viewports[ i ].getValue();
		if (values[2] <= 0 || values[3] <= 0)
			continue;

		if( relative.getValue() )
		{
			SbVec2f origin( values[0] , values[1] ), size( values[2], values[3] );
			viewportRegion.setViewport( origin, size );
		}
		else
		{
			SbVec2s origin( static_cast<short>(values[0]) , static_cast<short>(values[1]) ), 
							size( static_cast<short>(values[2]), static_cast<short>(values[3]) );
			viewportRegion.setViewportPixels( origin, size );
		}

		if (maximized.getValue())
		{
			if (i != current.getValue())
			{
				continue;
			}
			else
			{
				viewportRegion.setViewportPixels(0, 0, mWindowWidth, mWindowHeight);
			}
		}

		// reduce viewport size by 1 pixel to avoid overlaps
		SbVec2s origin = viewportRegion.getViewportOriginPixels();
		SbVec2s size = viewportRegion.getViewportSizePixels() - SbVec2s(1, 1);
		viewportRegion.setViewportPixels(origin, size);

		if ((size[0] <= 0) || (size[1] <= 0))
			continue;

		if (action->isOfType(SoHandleEventAction::getClassTypeId()))
		{
			if ((current.getValue() >= 0) && (i != current.getValue()))
			{
				// button/click events are only send to the active viewport
				if (((SoHandleEventAction*) action)->getEvent()->isOfType(SoButtonEvent::getClassTypeId())) continue;

				// if activateOnClick is set all events are send only to the active viewport
				if (activateOnClick.getValue()) continue;
			}
			((SoHandleEventAction*)action)->setViewportRegion(viewportRegion);

			SoXipActiveViewportElement::set(action->getState(), this, i == current.getValue());
		}
		else if (action->isOfType(SoPickAction::getClassTypeId()))
		{
			// SoPickAction can only be processed one child.
			if (i == mPickViewport)
			{
				((SoPickAction*)action)->setViewportRegion(viewportRegion);
				SoViewportRegionElement::set( action->getState(),  viewportRegion );
				
				getChildren()->traverse( action, i );
			}

			// do not proceed to traversal code below
			continue;		
		}
		else if (action->isOfType(SoGLRenderAction::getClassTypeId()))
		{
			((SoGLRenderAction*)action)->setViewportRegion(viewportRegion);
			mActiveViewport = i;

			SoXipActiveViewportElement::set(action->getState(), this, i == current.getValue());
		}
		else if (action->isOfType(SoGetBoundingBoxAction::getClassTypeId()))
		{
			// SoGetBoundingBoxAction can only be processed by the active child.
			// For all other children create and apply a new action.
			if (i == mActiveViewport)
			{
				((SoGetBoundingBoxAction*)action)->setViewportRegion(viewportRegion);
				SoViewportRegionElement::set( action->getState(),  viewportRegion );
				
				getChildren()->traverse( action, i );
			}
			else
			{
				SoGetBoundingBoxAction bba(viewportRegion);
				bba.apply((SoNode*) getChildren()->get(i));
			}

			// do not proceed to traversal code below
			continue;
		}
		else if (action->isOfType(SoGetMatrixAction::getClassTypeId()))
		{
			((SoGetMatrixAction*)action)->setViewportRegion(viewportRegion);
		}
		else if (action->isOfType(SoLineHighlightRenderAction::getClassTypeId()))
		{
			((SoLineHighlightRenderAction*)action)->setViewportRegion(viewportRegion);
		}
		else if (action->isOfType(SoBoxHighlightRenderAction::getClassTypeId()))
		{
			((SoBoxHighlightRenderAction*)action)->setViewportRegion(viewportRegion);
		}

		SoViewportRegionElement::set( action->getState(),  viewportRegion );
		
		getChildren()->traverse( action, i );
	}


	// restore original viewport for all actions and state
	viewportRegion = originalViewportRegion;

	if (action->isOfType(SoGetBoundingBoxAction::getClassTypeId()))
	{
		((SoGetBoundingBoxAction*)action)->setViewportRegion(viewportRegion);
	}
	else if (action->isOfType(SoHandleEventAction::getClassTypeId()))
	{
		((SoHandleEventAction*)action)->setViewportRegion(viewportRegion);
	}
	else if (action->isOfType(SoGLRenderAction::getClassTypeId()))
	{
		((SoGLRenderAction*)action)->setViewportRegion(viewportRegion);
	}
	else if (action->isOfType(SoGetBoundingBoxAction::getClassTypeId()))
	{
		((SoGetBoundingBoxAction*)action)->setViewportRegion(viewportRegion);
	}
	else if (action->isOfType(SoGetMatrixAction::getClassTypeId()))
	{
		((SoGetMatrixAction*)action)->setViewportRegion(viewportRegion);
	}
	else if (action->isOfType(SoLineHighlightRenderAction::getClassTypeId()))
	{
		((SoLineHighlightRenderAction*)action)->setViewportRegion(viewportRegion);
	}
	else if (action->isOfType(SoBoxHighlightRenderAction::getClassTypeId()))
	{
		((SoBoxHighlightRenderAction*)action)->setViewportRegion(viewportRegion);
	}

	action->getState()->pop();

	mActiveViewport = -1;
}


void SoXipViewportGroup::getBoundingBox(SoGetBoundingBoxAction * action)
{
	// Compute bounding box is sometimes called while rendering. In this case
	// let the bounding box action traverse the currently rendered path
	// (mActiveViewport is set within doAction() for each child when applying
	// GLRenderAction).
	if (mActiveViewport < 0)
		mActiveViewport = current.getValue();

	action->getState()->push();
	doAction(action);
	action->getState()->pop();
}


void SoXipViewportGroup::GLRender(SoGLRenderAction * action)
{
	mActiveViewport = current.getValue();
	doAction(action);

	if (mResizeMode)
	{
		action->getState()->push();

		GLboolean isDepthTestEnabled = ::glIsEnabled(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);

		SbVec3f coordinates[4];
		int numCoordinates = 0;

		if (mResizeMode & RESIZE_HORIZONTAL)
		{
			coordinates[numCoordinates++] = SbVec3f(0.f, (float) mResizePos[1], 0.f);
			coordinates[numCoordinates++] = SbVec3f((float) mWindowWidth, (float) mResizePos[1], 0.f);
		}

		if (mResizeMode & RESIZE_VERTICAL)
		{
			coordinates[numCoordinates++] = SbVec3f((float) mResizePos[0], 0.f, 0.f);
			coordinates[numCoordinates++] = SbVec3f((float) mResizePos[0], (float) mWindowHeight, 0.f);
		}


		SbViewVolume viewVol;
		SbMatrix affine, proj;
		viewVol.ortho(0, (float) mWindowWidth, 0, (float) mWindowHeight, -1, 1);
		viewVol.getMatrices(affine, proj);

		SoViewVolumeElement::set(action->getState(), this, viewVol);
		SoViewingMatrixElement::set(action->getState(), this, affine);
		SoProjectionMatrixElement::set(action->getState(), this, proj);

		SoColorPacker cPacker;
		SbColor col = mResizeValid ? SbColor(0.8f, 0.8f, 0.8f) : SbColor(0.5f, 0.5f, 0.5f);
		SoLazyElement::setDiffuse(action->getState(), this, 1, &col, &cPacker);
		SoLinePatternElement::set(action->getState(), mResizeValid ? 0xffff : 0xf0f0);

		SoCoordinateElement::set3(action->getState(), this, numCoordinates, coordinates);
		mLineSet->coordIndex.set(numCoordinates == 4 ? "[ 0 , 1 , -1 , 2 , 3 ]" : "[ 0 , 1 ]");
 
		action->traverse(mLineSet);

		if (isDepthTestEnabled)
			glEnable(GL_DEPTH_TEST);

		action->getState()->pop();
	}
}


void SoXipViewportGroup::callback(SoCallbackAction * action)
{
	mActiveViewport = current.getValue();
	doAction(action);
}


void SoXipViewportGroup::pick(SoPickAction * action)
{
	mActiveViewport = current.getValue();
	doAction(action);
}


void SoXipViewportGroup::rayPick (SoRayPickAction *action)
{
	mActiveViewport = current.getValue();
	doAction(action);
}


void SoXipViewportGroup::updateCursor()
{
	switch (mResizeMode)
	{
	case RESIZE_HORIZONTAL:	SoXipCursor::setCursor("SPLIT_H"); break;
	case RESIZE_VERTICAL:	SoXipCursor::setCursor("SPLIT_V"); break;
	case RESIZE_ALL:		SoXipCursor::setCursor("SPLIT_HV"); break;
	}
}


void SoXipViewportGroup::handleEvent (SoHandleEventAction *action)
{
	// in order to not confuse manipulators, events from a SoHandleEventAction
	// are only forwarded to currently active viewport group
	const SoEvent *e = action->getEvent();

	if (!action->getGrabber())
	{
		mPickViewport = this->pickViewportGroup(action, e->getPosition());
	}

	if (!action->getGrabber())
	{
		if (resizable.getValue())
		{
			mResizeMode = resize(e->getPosition(), e->getPosition(), FALSE);
			if (mResizeMode)
			{
				if (SO_MOUSE_PRESS_EVENT(e, BUTTON1))
				{
					action->setHandled();
					action->setGrabber(this);
					mResizeStart = e->getPosition();
					mResizePos = e->getPosition();
					updateCursor();
				}
				else if (e->isOfType(SoLocation2Event::getClassTypeId()))
				{
					action->setHandled();
					updateCursor();
				}
			}
		}
	}
	else if ((action->getGrabber() == this) && SO_MOUSE_RELEASE_EVENT(e, BUTTON1))
	{
		action->setHandled();
		action->releaseGrabber();
		mResizeMode = RESIZE_NONE;

		resize(mResizeStart, e->getPosition());
		startNotify();
	}
	else if ((action->getGrabber() == this) && e->isOfType(SoLocation2Event::getClassTypeId()))
	{
		action->setHandled();
		mResizePos = e->getPosition();
		mResizeValid = resize(mResizeStart, mResizePos, FALSE) ? TRUE : FALSE;
		startNotify();
		updateCursor();
	}

	
	if (!action->isHandled() && SO_MOUSE_PRESS_EVENT(e, ANY)) 
	{
		// capture
		int pick = this->pickViewportGroup(action, e->getPosition());
		if (pick >= 0)
		{
			if (current.getValue() != pick)
			{
				current.setValue(pick);
				if (activateOnClick.getValue())
					action->setHandled();
			}

			if (maximizeOnDoubleClick.getValue())
			{
				if (SO_MOUSE_PRESS_EVENT(e, BUTTON1))
				{
					SbTime t = e->getTime() - mLastButtonDownTime;

					if (t.getMsecValue() < 250)
					{
						maximized.setValue(!maximized.getValue());
						action->setHandled();
					}
					else mLastButtonDownTime = e->getTime();
				}
			}
		}
	}

	if (!action->isHandled())
	{
		mActiveViewport = current.getValue();
		doAction(action);
	}
}


void SoXipViewportGroup::fieldSensorCBFunc(void *user, SoSensor *sensor)
{
	SoXipViewportGroup *obj = (SoXipViewportGroup *) user;

	if( obj )
		obj->fieldSensorCB( sensor );
}


void SoXipViewportGroup::fieldSensorCB(SoSensor *sensor)
{
	if( relative.getValue() )
	{
		for( int i = 0; i < viewports.getNum();	++ i )
		{
			SbVec4f values = viewports[i].getValue();
			values[0] /= mWindowWidth;
			values[1] /= mWindowHeight;
			values[2] /= mWindowWidth;
			values[3] /= mWindowHeight;
			viewports.set1Value(i, SbVec4f(values[ 0 ], values[ 1 ], values[ 2 ], values[ 3 ] ));
		}
	}
	else
	{
		for( int i = 0; i < viewports.getNum();	++ i )
		{
			SbVec4f values = viewports[i].getValue();
			values[0] *= mWindowWidth;
			values[1] *= mWindowHeight;
			values[2] *= mWindowWidth;
			values[3] *= mWindowHeight;
			viewports.set1Value(i, values[ 0 ], values[ 1 ], values[ 2 ], values[ 3 ] );
		}
	}
}


SbBool SoXipViewportGroup::isOnBorder(SbVec2s origin, SbVec2s size, viewportBorder_t which, SbVec2s pos, int epsilon) const
{
	// do not allow picking of lines on the window border
	if ((pos[0] < 10) || (pos[1] < 10) || (pos[0] > (mWindowWidth - 10)) || (pos[1] > (mWindowHeight - 10)))
		return FALSE;

	switch (which)
	{
	case VIEWPORT_RIGHT:
		{
			int pickLine = origin[0] + size[0];
			if (abs(pickLine - pos[0]) < epsilon)
			{
				return TRUE;
			}
		} break;
	case VIEWPORT_LEFT:
		{
			int pickLine = origin[0];
			if (abs(pickLine - pos[0]) < epsilon)
			{
				return TRUE;
			}
		} break;
	case VIEWPORT_TOP:
		{
			int pickLine = origin[1] + size[1];
			if (abs(pickLine - pos[1]) < epsilon)
			{
				return TRUE;
			}
		} break;
	case VIEWPORT_BOTTOM:
		{
			int pickLine = origin[1];
			if (abs(pickLine - pos[1]) < epsilon)
			{
				return TRUE;
			}
		} break;
	}

	return FALSE;
}


SoXipViewportGroup::resizeMode_t SoXipViewportGroup::resize(SbVec2s from, SbVec2s to, SbBool applyChange)
{
	SbViewportRegion viewportRegion(mWindowWidth, mWindowHeight);
	SoMFVec4f viewportsResized;
	int resizeMode = RESIZE_NONE;

	int maxIndex = viewports.getNum() - 1;
	for( int i = 0; i <= maxIndex; ++ i )
	{
		SbVec4f values = viewports[ i ].getValue();
		if (values[2] <= 0 || values[3] <= 0)
			continue;

		if( relative.getValue() )
		{
			SbVec2f origin( values[0] , values[1] ), size( values[2], values[3] );
			viewportRegion.setViewport( origin, size );
		}
		else
		{
			SbVec2s origin( static_cast<short>(values[0]) , static_cast<short>(values[1]) ), 
							size( static_cast<short>(values[2]), static_cast<short>(values[3]) );
			viewportRegion.setViewportPixels( origin, size );
		}

		SbVec2s origin = viewportRegion.getViewportOriginPixels();
		SbVec2s size   = viewportRegion.getViewportSizePixels();

		SbVec2s originResized = origin;
		SbVec2s sizeResized   = size;

		const int pickRadius = 4;

		// vertical
		if ((origin[0] < to[0]) && ((origin[0] + size[0]) > to[0]))
		{
			// cut
			if (isOnBorder(origin, size, VIEWPORT_LEFT, from, pickRadius))
			{
				resizeMode |= RESIZE_VERTICAL;
				int diff = to[0] - origin[0];
				if (diff > 0)
				{
					originResized[0] += diff;
					sizeResized[0] -= diff;
				}
			}
			else if (isOnBorder(origin, size, VIEWPORT_RIGHT, from, pickRadius))
			{
				resizeMode |= RESIZE_VERTICAL;
				int diff = (origin[0] + size[0]) - to[0];
				if (diff > 0)
				{
					sizeResized[0] -= diff;
				}
			}
		}
		else
		{
			// enlarge
			if (isOnBorder(origin, size, VIEWPORT_RIGHT, from, pickRadius))
			{
				resizeMode |= RESIZE_VERTICAL;
				int diff = to[0] - (origin[0] + size[0]);
				if (diff > 0)
				{
					sizeResized[0] += diff;
				}
			}
			else if (isOnBorder(origin, size, VIEWPORT_LEFT, from, pickRadius))
			{
				resizeMode |= RESIZE_VERTICAL;
				int diff = origin[0] - to[0];
				if (diff > 0)
				{
					originResized[0] -= diff;
					sizeResized[0] += diff;
				}
			}
		}

		// horizontal
		if ((origin[1] < to[1]) && ((origin[1] + size[1]) > to[1]))
		{
			// cut
			if (isOnBorder(origin, size, VIEWPORT_BOTTOM, from, pickRadius))
			{
				resizeMode |= RESIZE_HORIZONTAL;
				int diff = to[1] - origin[1];
				if (diff > 0)
				{
					originResized[1] += diff;
					sizeResized[1] -= diff;
				}
			}
			else if (isOnBorder(origin, size, VIEWPORT_TOP, from, pickRadius))
			{
				resizeMode |= RESIZE_HORIZONTAL;
				int diff = (origin[1] + size[1]) - to[1];
				if (diff > 0)
				{
					sizeResized[1] -= diff;
				}
			}
		}
		else
		{
			// enlarge
			if (isOnBorder(origin, size, VIEWPORT_TOP, from, pickRadius))
			{
				resizeMode |= RESIZE_HORIZONTAL;
				int diff = to[1] - (origin[1] + size[1]);
				if (diff > 0)
				{
					sizeResized[1] += diff;
				}
			}
			else if (isOnBorder(origin, size, VIEWPORT_BOTTOM, from, pickRadius))
			{
				resizeMode |= RESIZE_HORIZONTAL;
				int diff = origin[1] - to[1];
				if (diff > 0)
				{
					originResized[1] -= diff;
					sizeResized[1] += diff;
				}
			}
		}


		viewportRegion.setViewportPixels(originResized, sizeResized);

		if ((originResized[0] < 0) || (originResized[1] < 0) ||
			(sizeResized[0] < 10) || (sizeResized[1] < 10) ||
			((originResized[0] + 10) > mWindowWidth) || 
			((originResized[1] + 10) > mWindowHeight) ||
			((originResized[0] + sizeResized[0] - 1) > mWindowWidth) || 
			((originResized[1] + sizeResized[1] - 1) > mWindowHeight) )
		{
			//SoDebugError::postWarning("viewport", "out of range: %d %d > %d %d", originResized[0] + sizeResized[0], originResized[1] + sizeResized[1], mWindowWidth, mWindowHeight);
			return RESIZE_NONE;
		}

		if( relative.getValue() )
		{
			SbVec4f v(
				viewportRegion.getViewportOriginPixels()[0], viewportRegion.getViewportOriginPixels()[1],
				viewportRegion.getViewportSizePixels()[0], viewportRegion.getViewportSizePixels()[1]);
			v[0] /= mWindowWidth - 0.5f;
			v[1] /= mWindowHeight - 0.5f;
			v[2] /= mWindowWidth - 0.5f;
			v[3] /= mWindowHeight - 0.5f;
			viewportsResized.set1Value(i, v);
		}
		else
		{
			SbVec4f v(
				viewportRegion.getViewportOriginPixels()[0], viewportRegion.getViewportOriginPixels()[1],
				viewportRegion.getViewportSizePixels()[0], viewportRegion.getViewportSizePixels()[1]);

			viewportsResized.set1Value(i, v);
		}
	}

	if (!isOverlapping(viewportsResized.getNum(), viewportsResized.getValues(0)))
	{
		if (applyChange && resizeMode)
			viewports = viewportsResized;

		return ((resizeMode_t) resizeMode);
	}

	return RESIZE_NONE;
}


SbBool SoXipViewportGroup::isOverlapping(int num, const SbVec4f *v) const
{
	for (int i = 0; i < num; i++)
	{
		SbBox2f a(v[i][0], v[i][1], v[i][0] + v[i][2] * 0.99f, v[i][1] + v[i][3] * 0.99f); 
		
		for (int j = 0; (j < num) && (j != i); j++)
		{
			SbBox2f b(v[j][0], v[j][1], v[j][0] + v[j][2] * 0.99f, v[j][1] + v[j][3] * 0.99f); 

			if (a.intersect(b))
				return TRUE;
		}
	}

	return FALSE;
}
