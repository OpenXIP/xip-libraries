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

#include "SoXipMprIntersectionManip.h"
#include <xip/inventor/core/SoXipMprLockElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoPickAction.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/elements/SoClipPlaneElement.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/SoPickedPoint.h>
#include <Inventor/projectors/SbPlaneProjector.h>
#include <Inventor/errors/SoDebugError.h>
#include <xip/inventor/core/SoXipCursor.h>
#include <xip/inventor/core/SoXipMprPlaneElement.h>
#include <xip/inventor/core/SoXipMprActiveElement.h>
#include <assert.h>
#include <xip/inventor/core/XipGeomUtils.h>
#include "SoXipMprIntersectionLine.h"



SO_NODE_SOURCE(SoXipMprIntersectionManip);

float SoXipMprIntersectionManip::mPickRadius = 3;


SoXipMprIntersectionManip::SoXipMprIntersectionManip()
{
	SO_NODE_CONSTRUCTOR(SoXipMprIntersectionManip);

	mPickedLine = -1;
	mPickedRotate = FALSE;
	mPickedCenter = FALSE;

	SO_NODE_DEFINE_ENUM_VALUE(modeType, INTERSECTION);
	SO_NODE_DEFINE_ENUM_VALUE(modeType, TRANSLATION);
	SO_NODE_DEFINE_ENUM_VALUE(modeType, FREE);
	SO_NODE_SET_SF_ENUM_TYPE(mode, modeType);

	SO_NODE_ADD_FIELD(on, (TRUE));
	SO_NODE_ADD_FIELD(mode, (INTERSECTION));
	SO_NODE_ADD_FIELD(stubs, (FALSE));
	SO_NODE_ADD_FIELD(stubScale, (10.0f));

	mModeFieldSensor = new SoFieldSensor(&fieldSensorCBFunc, this);
	mModeFieldSensor->attach(&mode);

	SoFieldSensor *fieldSensor;
	SoField *fields[] = { &mode, &stubs, &stubScale };
	for (int i = 0; i < (sizeof(fields) / sizeof(SoField*)); i++)
	{
		fieldSensor = new SoFieldSensor(&fieldSensorCBFunc, this);
		fieldSensor->attach(fields[i]);
		if (i <= 1) fieldSensor->setPriority(0);
		mInputSensors.push_back(fieldSensor);
	}

	mMprLock = 0;
}


SoXipMprIntersectionManip::~SoXipMprIntersectionManip()
{
	delete mModeFieldSensor;
}


void SoXipMprIntersectionManip::initClass()
{
	SO_NODE_INIT_CLASS(SoXipMprIntersectionManip, SoXipPlaneManipBase, "SoXipPlaneManipBase");

	SO_ENABLE(SoGLRenderAction, SoXipMprPlaneElement);
	SO_ENABLE(SoPickAction,     SoXipMprPlaneElement);
	SO_ENABLE(SoCallbackAction, SoXipMprPlaneElement);
	SO_ENABLE(SoHandleEventAction, SoXipMprPlaneElement);

	SO_ENABLE(SoGLRenderAction, SoXipMprActiveElement);
	SO_ENABLE(SoPickAction,     SoXipMprActiveElement);
	SO_ENABLE(SoCallbackAction, SoXipMprActiveElement);
	SO_ENABLE(SoHandleEventAction, SoXipMprActiveElement);
}


void SoXipMprIntersectionManip::fieldSensorCBFunc(void *user, SoSensor *sensor)
{
	((SoXipMprIntersectionManip*)user)->inputChanged(((SoFieldSensor*) sensor)->getAttachedField(), sensor);
}

void SoXipMprIntersectionManip::inputChanged(SoField *which, SoSensor *sensor)
{
	if (which == &mode)
	{
		mPickedLine = -1;
		mMprPlaneList.clear();
		removeAllChildren();
	}
	if ( (which == &stubs) || (which == &stubScale) )
	{
		updateGeometry();
	}
}


void SoXipMprIntersectionManip::fieldSensorCB(SoSensor *sensor)
{
	mPickedLine = -1;
	mMprPlaneList.clear();
	removeAllChildren();
}


void SoXipMprIntersectionManip::GLRender(SoGLRenderAction * action)
{
	if (on.getValue())
	{
		updateElement(action);

		GLboolean depthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);
		
		GLboolean blendTestEnabled = glIsEnabled(GL_BLEND);
				
		SoXipPlaneManipBase::GLRender(action);

		if (depthTestEnabled)
			glEnable(GL_DEPTH_TEST);

		if (blendTestEnabled)
			glEnable(GL_BLEND);
	}
}


void SoXipMprIntersectionManip::callback(SoCallbackAction *action)
{
	if (on.getValue())
	{
		updateElement(action);
		SoXipPlaneManipBase::callback(action);
	}
}


void SoXipMprIntersectionManip::pick(SoPickAction *action)
{
	if (on.getValue())
	{
		updateElement(action);
		SoXipPlaneManipBase::pick(action);
	}
}


void SoXipMprIntersectionManip::getBoundingBox(SoGetBoundingBoxAction *action)
{
	if (on.getValue())
	{
		SoXipPlaneManipBase::getBoundingBox(action);
	}
}


void SoXipMprIntersectionManip::updateElement(SoAction * action)
{
	unsigned int i;
	assert(action != 0);

	// check state
	SoState *state = action->getState();
	if (!state) return;

	SoXipMprPlaneElement *element = SoXipMprPlaneElement::getInstance(state);
	if (!element) return;

	// the cast should be fine. I assume that the length of a list is greater-equal 0
	unsigned int numPlanes = static_cast<unsigned int>(element->getNum());
	int basePlane = numPlanes - 1;

	/* not sure what this block was for but it causes a crash with the IFE network image
	// let's just comment it out for now and simply return while dragging (found in revision 916)
  
	// while dragging, only update MPR elements
	if (mPickedLine >= 0) 
	{
		SbVec3f movement = getMouseProjection() - mPickPosition;

		// translate all MPR planes to new mouse position
		for (i = 0; i < mMprPlaneList.size(); i++)
		{
			SbMatrix m = XipGeomUtils::translatePlaneNormal(mMprPlaneList[i].matrix, movement);
			element->setMatrix(i, m);
		}

		return;
	}	*/

	// do not update while dragging
	if (mPickedLine >= 0) return;


	// first, check if anything has changed
	if (numPlanes == mMprPlaneList.size())
	{
		for (i = 0; i < numPlanes; i++)
		{
			if (!mMprPlaneList[i].matrix.equals(element->getMatrix(i), XIP_FLT_EPSILON) ||
				!mMprPlaneList[i].center.equals(element->getCenter(i), XIP_FLT_EPSILON) ||
				(mMprPlaneList[i].id != element->getId(i)) ||
				(mMprPlaneList[i].color != element->getColor(i))) break;
		}

		// no change in any of the matrices
		if (i == mMprPlaneList.size()) return;
	}

	// copy updated elements into member variable
	mMprPlaneList.resize(numPlanes);
	for (i = 0; i < numPlanes; i++)
	{
		mMprPlaneList[i].node = 0;
		mMprPlaneList[i].matrix = element->getMatrix(i);
		mMprPlaneList[i].center = element->getCenter(i);
		mMprPlaneList[i].color = element->getColor(i);
		mMprPlaneList[i].matrixField = element->getMatrixField(i);
		mMprPlaneList[i].centerField = element->getCenterField(i);
		mMprPlaneList[i].id = element->getId(i);
	}

	// update projection plane
	if (basePlane >= 0)
		setPlane(XipGeomUtils::planeFromMatrix(mMprPlaneList[basePlane].matrix));

	// update current geometry
	updateGeometry();
}


void SoXipMprIntersectionManip::updateGeometry()
{
	unsigned int i;
	SbMatrix planeMatrix;
	SbBool hasIntersectionPoint = FALSE;

	// the cast should be fine. I assume that the length of a list is greater-equal 0
	unsigned int numPlanes = static_cast<unsigned int>(mMprPlaneList.size());

	// return if no planes are found
	if (numPlanes < 2)
		return;

	unsigned int basePlane = numPlanes - 1;

	// can't compute intersection lines with less than 2 planes
	// or invalid base plane
	//if ((numPlanes < 2) || (basePlane < 0) /*|| (basePlane >= numPlanes) -> this can never be true, see definition of baseplane*/) return;

	// clear current geometry first
	removeAllChildren();

	planeMatrix = mMprPlaneList[basePlane].matrix;


	// compute intersection point of 3 planes
	if (((mode.getValue() == TRANSLATION) || (mode.getValue() == INTERSECTION)) && (numPlanes > 2))
	{
		hasIntersectionPoint = XipGeomUtils::planeIntersect(
			XipGeomUtils::planeFromMatrix(mMprPlaneList[0].matrix),
			XipGeomUtils::planeFromMatrix(mMprPlaneList[1].matrix),
			XipGeomUtils::planeFromMatrix(mMprPlaneList[2].matrix),
			mIntersectionPosition);

		if (hasIntersectionPoint)
		{
			// update center on all planes
			for (i = 0; i < numPlanes; i++)
			{
				if (mMprPlaneList[i].centerField && !mMprPlaneList[i].center.equals(mIntersectionPosition, XIP_FLT_EPSILON))
				{
					mMprPlaneList[i].centerField->setValue(mIntersectionPosition);
				}
			}
		}
	}

	// create new geometry
	for (i = 0; i < numPlanes; i++)
	{
		if (i != basePlane)
		{
			// will be referenced by addChild() and unreferenced/deleted by removeAllChildren()
			mMprPlaneList[i].node = new SoXipMprIntersectionLine();
			mMprPlaneList[i].node->stubs = stubs;
			mMprPlaneList[i].node->stubScale = stubScale;

			SoBaseColor *col = SO_GET_PART(mMprPlaneList[i].node, "color", SoBaseColor);
			col->rgb.setValue(mMprPlaneList[i].color);

			if (hasIntersectionPoint)
			{
				mMprPlaneList[i].node->centerPosition.setValue(mIntersectionPosition);
				mMprPlaneList[i].node->centerGap.setValue(TRUE);
			}
			else
			{
				// project center point on intersection line (closest point)
				SbVec3f point = projectCenterOnPlane(mMprPlaneList[i].matrix, mMprPlaneList[i].center);
				mMprPlaneList[i].node->centerPosition.setValue(point);

				mMprPlaneList[i].node->centerGap.setValue(TRUE);
				mMprPlaneList[i].node->centerCross.setValue(TRUE);
			}

			mMprPlaneList[i].node->planeMatrix.setValue(planeMatrix);
			mMprPlaneList[i].node->intersectMatrix.setValue(mMprPlaneList[i].matrix);

			addChild(mMprPlaneList[i].node);
		}
	}
}


SbBool SoXipMprIntersectionManip::dragBegin()
{
	if (mPickedLine >= 0) return TRUE;

	updateElement(mHandleEventAction);

	size_t numPlanes = mMprPlaneList.size();
	// if there are no planes there is nothing to do
	if (numPlanes <= 0) 
		return FALSE;

	// last plane is baseplane
	size_t basePlane = numPlanes - 1;

	mPickedCenter = FALSE;
	mPickedRotate = FALSE;
	mPickedLine = getPickedLine();

	if (mPickedLine >= 0)
	{
		mPickPosition = getMouseProjection();
		updateProjectors(mPickPosition);

		mHandleEventAction->setGrabber(this);

		if (mPickedLine >= static_cast<int>(numPlanes))
		{
			SoDebugError::post(__FILE__, "Picked line greater array size!\n");
			mPickedLine = FALSE;
			return FALSE;
		}

		if (SoXipMprActiveElement::getMprIndex(mHandleEventAction->getState()) != mMprPlaneList[mPickedLine].id)
		{
			// need to update active MPR element
			SoSFInt32 *field = SoXipMprActiveElement::getMprFieldIndex(mHandleEventAction->getState());
			if (field)
			{
				field->setValue(mMprPlaneList[mPickedLine].id);
			}

			SoXipMprActiveElement::set(mHandleEventAction->getState(), this, mMprPlaneList[mPickedLine].id, field);
		}

		// if in INTERSECTION mode, check if center point was picked
		if (((mode.getValue() == TRANSLATION) || (mode.getValue() == INTERSECTION)) && (numPlanes > 2))
		{
			SbVec3f obj[2];
			//int basePlane = mMprPlaneList.size() - 1;
			SbMatrix worldToObj = mMprPlaneList[basePlane].matrix.inverse();
			worldToObj.multVecMatrix(mPickPosition, obj[0]);
			worldToObj.multVecMatrix(mIntersectionPosition, obj[1]);

			if (XipGeomUtils::isVecInObjectSpace(obj[0] - obj[1], 0.06f))
			{
				SoXipCursor::setCursor("MOVE");

				mPickedCenter = TRUE;
			}
			else if ((mode.getValue() == INTERSECTION) && !XipGeomUtils::isVecInObjectSpace(obj[0] - obj[1], 0.25))
			{
				SoXipCursor::setCursor("ROTATE_LINE");

				mPickedRotate = TRUE;
				mRotatePosition = projectCenterOnPlane(mMprPlaneList[mPickedLine].matrix, mMprPlaneList[mPickedLine].center);
				mMprPlaneList[mPickedLine].center = mRotatePosition;
			}
			else
			{
				SoXipCursor::setCursor(XipGeomUtils::isVecInObjectSpace(obj[0] - obj[1], 0.06f) ? "MOVE ": "MOVE_LINE");
			}
		}
		else
		{
			// free mode, check if center or off-center (rotate)
			mRotatePosition = projectCenterOnPlane(mMprPlaneList[mPickedLine].matrix, mMprPlaneList[mPickedLine].center);
			mMprPlaneList[mPickedLine].center = mRotatePosition;

			// save the position at which the translation has started to add delta mouse movement to it
			for (size_t i = 0; i < basePlane; i++)
			{
				mMprPlaneList[i].translateOrigin = projectCenterOnPlane(mMprPlaneList[i].matrix, mMprPlaneList[i].center);
			}

			SbVec3f obj[2];
			//int basePlane = mMprPlaneList.size() - 1;
			SbMatrix worldToObj = mMprPlaneList[basePlane].matrix.inverse();

			worldToObj.multVecMatrix(mPickPosition, obj[0]);
			worldToObj.multVecMatrix(mRotatePosition, obj[1]);

			if (XipGeomUtils::isVecInObjectSpace(obj[0] - obj[1], 0.25))
			{
				SoXipCursor::setCursor("MOVE_LINE");
				mPickedCenter = TRUE;
			}
			else
			{
				SoXipCursor::setCursor("ROTATE_LINE");
			}
		}

		return TRUE;
	}
	else
	{
		// picked base plane
		//int basePlane = mMprPlaneList.size() - 1;

		if (SoXipMprActiveElement::getMprIndex(mHandleEventAction->getState()) != mMprPlaneList[basePlane].id)
		{
			// need to update active MPR element
			SoSFInt32 *field = SoXipMprActiveElement::getMprFieldIndex(mHandleEventAction->getState());
			if (field)
			{
				field->setValue(mMprPlaneList[basePlane].id);
			}

			SoXipMprActiveElement::set(mHandleEventAction->getState(), this, mMprPlaneList[basePlane].id, field);
		}
	}

	return FALSE;
}


SbBool SoXipMprIntersectionManip::dragMove()
{
	if (mPickedLine >= 0)
	{
		switch (mode.getValue())
		{
		case FREE:
			dragMoveFree();			
			break;

		case TRANSLATION:
		case INTERSECTION:
			if (!mPickedRotate && (mMprPlaneList.size() > 2))
			{
				dragMoveIntersection();
			}
			else
			{
				dragMoveFree();
			}
			break;
		}
	}

	return SoXipPlaneManipBase::dragMove();
}


void SoXipMprIntersectionManip::dragMoveFree()
{
	size_t numPlanes = mMprPlaneList.size();
	if ( numPlanes <= 0) 
		return;

	// last plane is baseplane
	size_t basePlane = numPlanes - 1;

	if (mPickedCenter)
	{
		// translate
		SoXipCursor::setCursor("MOVE_LINE");

		SbVec3f movement = getMouseProjection() - mPickPosition;
		SbMatrix t;
		t.setTranslate(movement);

		for (size_t i = 0; i < basePlane; i++)
		{
			if (!(mMprLock & SoXipMprLockElement::LINE_POSITION))
				if (static_cast<int>(i) != mPickedLine) continue;

			SbMatrix m = mMprPlaneList[i].matrix * t;

			mMprPlaneList[i].node->intersectMatrix.setValue(m);

			SbVec3f point = projectCenterOnPlane(m, mMprPlaneList[i].translateOrigin + movement);
			mMprPlaneList[i].node->centerPosition.setValue(point);
			mMprPlaneList[i].center = point;

			// update fields
			if (mMprPlaneList[i].matrixField)
			{
				if (!mMprPlaneList[i].matrixField->getValue().equals(m, XIP_FLT_EPSILON))
				{
					mMprPlaneList[i].matrixField->setValue(m);
				}
			}

			mMprPlaneList[i].center = mMprPlaneList[i].node->centerPosition.getValue();
			if (mMprPlaneList[i].centerField)
			{
				if (!mMprPlaneList[i].centerField->getValue().equals(mMprPlaneList[i].center, XIP_FLT_EPSILON))
				{
					mMprPlaneList[i].centerField->setValue(mMprPlaneList[i].center);
				}
			}
		}
	}
	else
	{
		// rotate
		SoXipCursor::setCursor("ROTATE_LINE");

		SbVec3f mousePos = getMouseProjection();
		//int basePlane = mMprPlaneList.size() - 1;
		SbVec3f center = mRotatePosition;
		SbLine line;

		if (XipGeomUtils::planeIntersect(XipGeomUtils::planeFromMatrix(mMprPlaneList[basePlane].matrix), XipGeomUtils::planeFromMatrix(mMprPlaneList[mPickedLine].matrix), line))
		{
			float rad;
			SbVec3f axis;
			SbRotation fromToRot;

			SbVec3f n1 = line.getDirection(), n2 = mousePos - center;
			n2.normalize();
			fromToRot.setValue(n1, n2);
			fromToRot.getValue(axis, rad);

			if (rad > (M_PI / 2))
			{
				// adjust rotation around current axis to avoid flip in direction
				fromToRot.setValue(axis, rad - static_cast<float>(M_PI));
			}

			SbMatrix m = mMprPlaneList[mPickedLine].matrix;
			SbMatrix rot, trans;
			rot.setRotate(fromToRot);
			trans.setTranslate(-center);

			for (size_t i = 0; i < basePlane; i++)
			{
				if (!(mMprLock & SoXipMprLockElement::LINE_ORIENTATION))
					if (static_cast<int>(i) != mPickedLine) continue;

				SbMatrix m = mMprPlaneList[i].matrix;

				m *= trans;
				m *= rot;
				m *= trans.inverse();

				mMprPlaneList[i].node->intersectMatrix.setValue(m);
				mMprPlaneList[i].matrix = m;

				if (mMprPlaneList[i].matrixField)
				{
					if (!mMprPlaneList[i].matrixField->getValue().equals(m, XIP_FLT_EPSILON))
					{
						mMprPlaneList[i].matrixField->setValue(m);
					}
				}

				SbVec3f point = projectCenterOnPlane(mMprPlaneList[i].matrix, mMprPlaneList[i].center);
				mMprPlaneList[i].node->centerPosition.setValue(point);
				mMprPlaneList[i].node->intersectMatrix.setValue(m);
			}
		}
	}
}


void SoXipMprIntersectionManip::dragMoveIntersection()
{
	size_t numPlanes = mMprPlaneList.size();
	// if no planes are defined return
	if (numPlanes == 0)
		return;

	size_t basePlane = numPlanes - 1;

	size_t i = 0;
	SbVec3f movement = getMouseProjection() - mPickPosition;

	SoXipCursor::setCursor(mPickedCenter ? "MOVE" : "MOVE_LINE");

	if (!mPickedCenter)
	{
		// translate only the picked line
		SbMatrix m = XipGeomUtils::translatePlaneNormal(mMprPlaneList[mPickedLine].matrix, movement);
		mMprPlaneList[mPickedLine].node->intersectMatrix.setValue(m);

		if (mMprPlaneList[mPickedLine].matrixField)
		{
			if (!mMprPlaneList[mPickedLine].matrixField->getValue().equals(m, XIP_FLT_EPSILON))
			{
				mMprPlaneList[mPickedLine].matrixField->setValue(m);
			}
		}

		// compute new intersection point
		SbVec3f intersectionPoint;
		if (XipGeomUtils::planeIntersect(
				XipGeomUtils::planeFromMatrix(m),
				XipGeomUtils::planeFromMatrix(mMprPlaneList[(mPickedLine + 1) % 3].matrix),
				XipGeomUtils::planeFromMatrix(mMprPlaneList[(mPickedLine + 2) % 3].matrix),
				intersectionPoint))
		{
			for (i = 0; i < basePlane; i++)
			{
				if (mMprPlaneList[i].node)
				{
					mMprPlaneList[i].node->centerPosition.setValue(intersectionPoint);
				}
			}
		}
	}
	else
	{
		// translate all MPR planes to new mouse position (except current one)
		for (i = 0; i < basePlane; i++)
		{
			SbMatrix m = XipGeomUtils::translatePlaneNormal(mMprPlaneList[i].matrix, movement);

			if (mMprPlaneList[i].node)
			{
				mMprPlaneList[i].node->centerPosition.setValue(mIntersectionPosition + movement);
				mMprPlaneList[i].node->intersectMatrix.setValue(m);

				mMprPlaneList[i].center = mIntersectionPosition + movement;
			}

			if (mMprPlaneList[i].matrixField)
			{
				if (!mMprPlaneList[i].matrixField->getValue().equals(m, XIP_FLT_EPSILON))
				{
					mMprPlaneList[i].matrixField->setValue(m);
				}
			}
		}
	}
}


SbBool SoXipMprIntersectionManip::dragEnd()
{
	mPickedLine = -1;
	mPickedCenter = FALSE;

	// set last active cursor
	SoXipCursor::update();

	size_t numPlanes = mMprPlaneList.size();
	// if no planes are defined return
	if (numPlanes == 0)
		return SoXipPlaneManipBase::dragEnd();

	size_t basePlane = numPlanes - 1;

	// update center position in MPR plane element
	// (while manipulating only the centerPosition field of the intersection line is updated)
	for (size_t i = 0; i < basePlane; i++)
	{
		mMprPlaneList[i].center = mMprPlaneList[i].node->centerPosition.getValue();
		if (mMprPlaneList[i].centerField)
		{
			if (!mMprPlaneList[i].centerField->getValue().equals(mMprPlaneList[i].center, XIP_FLT_EPSILON))
			{
				mMprPlaneList[i].centerField->setValue(mMprPlaneList[i].center);
			}
		}
	}

	return SoXipPlaneManipBase::dragEnd();
}


int SoXipMprIntersectionManip::getPickedLine()
{
	// Can't pick if we don't have an action, now can we?
	if (!mHandleEventAction) 
		return -1;

	size_t numPlanes = mMprPlaneList.size();
	if (numPlanes == 0) 
		return -1;

	size_t basePlane = numPlanes - 1;

	SoRayPickAction pa(mHandleEventAction->getViewportRegion());
	pa.setPoint(mHandleEventAction->getEvent()->getPosition());
	pa.setRadius(mPickRadius);
	pa.setPickAll(TRUE);
	pa.enableCulling(FALSE);
	pa.apply(mHandleEventAction->getNodeAppliedTo());

	SoPickedPointList pointList = pa.getPickedPointList();
	int picked = -1;

	for (int j = 0; j < pointList.getLength(); j++)
	{
		const SoPickedPoint *picked_point = pointList[j];
		if (!picked_point) 
			continue;

		// check for dog ear or other geometry on top of reference lines,
		// which is very close to the near plane (distance ~ 1)
		
		//int basePlane = mMprPlaneList.size() - 1;
		SbPlane nearPlane = XipGeomUtils::planeFromMatrix(mMprPlaneList[basePlane].matrix);
		SbPlane pickPlane(nearPlane.getNormal(), picked_point->getPoint());
		float dist = fabs(nearPlane.getDistanceFromOrigin() - pickPlane.getDistanceFromOrigin());
		if ((dist > 0.95) && (dist < 1.05))
		{
			picked = -1;
			break;
		}

		const SoPath *dpath = picked_point->getPath();
		if (!dpath) return -1;

		for (size_t i = 0; i < numPlanes; i++)
		{
			if (mMprPlaneList[i].node)
			{
				SoNode *node = mMprPlaneList[i].node->getPart("lineSet", FALSE);
				if (node)
				{
					if (dpath->containsNode(node))
					{
						picked = static_cast<int>(i);
					}
				}

				node = mMprPlaneList[i].node->getPart("gapLineSet", FALSE);
				if (node)
				{
					if (dpath->containsNode(node))
					{
						picked = static_cast<int>(i);
					}
				}
			}
		}
	}

	return picked;
}


SbVec3f SoXipMprIntersectionManip::projectCenterOnPlane(const SbMatrix &intersectMatrix, const SbVec3f &center)
{
	// project center point on intersection line (closest point)
	SbPlane plane = XipGeomUtils::planeFromMatrix(mMprPlaneList[mMprPlaneList.size() - 1].matrix);
	SbPlane intersectPlane = XipGeomUtils::planeFromMatrix(intersectMatrix);
	SbLine line;

	if (XipGeomUtils::planeIntersect(plane, intersectPlane, line))
	{
		return line.getClosestPoint(center);
	}

	return center;
}


void SoXipMprIntersectionManip::handleEvent(SoHandleEventAction *action)
{
	if (!action || !on.getValue()) return;
	if (mMprPlaneList.size() <= 0) return;

	SoXipPlaneManipBase::handleEvent(action);

	if (action->getGrabber() == 0)
	{
		mMprLock = SoXipMprLockElement::get(action->getState());
	}

	if (action->getEvent()->isOfType(SoLocation2Event::getClassTypeId()))
	{
		if (!action->getGrabber() &&
			!action->isHandled() &&
			!action->getEvent()->wasShiftDown() &&
			!action->getEvent()->wasCtrlDown())
		{
			int picked = getPickedLine();
			if (picked >= 0)
			{
				// free mode, check if center or off-center (rotate)
				mRotatePosition = projectCenterOnPlane(mMprPlaneList[picked].matrix, mMprPlaneList[picked].center);
				mPickPosition = getMouseProjection();

				SbVec3f obj[2];
				size_t basePlane = mMprPlaneList.size() - 1;
				SbMatrix worldToObj = mMprPlaneList[basePlane].matrix.inverse();

				worldToObj.multVecMatrix(mPickPosition, obj[0]);
				worldToObj.multVecMatrix(mRotatePosition, obj[1]);

				if ((mode.getValue() != TRANSLATION) && !XipGeomUtils::isVecInObjectSpace(obj[0] - obj[1], 0.25))
				{
					SoXipCursor::setCursor("ROTATE_LINE");
				}
				else
				{
					SoXipCursor::setCursor((mode.getValue() != FREE) && XipGeomUtils::isVecInObjectSpace(obj[0] - obj[1], 0.06f) ? "MOVE" : "MOVE_LINE");
				}

				action->setHandled();
			}
		}
	}
}


void SoXipMprIntersectionManip::setPickRadius(float radius)
{
	mPickRadius = radius;
}
