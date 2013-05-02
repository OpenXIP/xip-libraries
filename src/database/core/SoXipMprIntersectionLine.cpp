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

#include "SoXipMprIntersectionLine.h"
#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/nodes/SoMatrixTransform.h>
#include <Inventor/nodes/SoBaseColor.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoLineWidthElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/SbBox.h>
#include <Inventor/errors/SoDebugError.h>
#include <xip/inventor/core/XipGeomUtils.h> // XipInventorUtils


const static float CENTER_GAP_SIZE = 0.04f, CENTER_MARKER_SIZE = 0.06f, NORMAL_INDICATOR_SIZE = 0.07f;


SO_KIT_SOURCE(SoXipMprIntersectionLineKit);
SO_KIT_SOURCE(SoXipMprIntersectionLine);


SoXipMprIntersectionLine::SoXipMprIntersectionLine()
{
	SO_KIT_CONSTRUCTOR(SoXipMprIntersectionLine);
	SO_KIT_INIT_INSTANCE();

	// Initialize fields
	SO_NODE_ADD_FIELD(planeMatrix, (SbMatrix::identity()));
	SO_NODE_ADD_FIELD(intersectMatrix, (SbMatrix::identity()));
	SO_NODE_ADD_FIELD(centerPosition, (SbVec3f(0, 0, 0)));
	SO_NODE_ADD_FIELD(centerGap, (FALSE));
	SO_NODE_ADD_FIELD(centerCross, (FALSE));
	SO_NODE_ADD_FIELD(normalIndicators, (TRUE));
	SO_NODE_ADD_FIELD(stubs, (FALSE));
	SO_NODE_ADD_FIELD(stubScale, (10.0f));

	mViewportAspectRatio = 1.f;
	mNeedsUpdate = FALSE;

	SoField *fields[] = { &planeMatrix, &intersectMatrix, &centerPosition, &centerGap, &centerCross, &normalIndicators };
	for (int i = 0; i < 6; i++)
	{
		mFieldSensors[i] = new SoFieldSensor(&fieldSensorCBFunc, this);
		mFieldSensors[i]->attach(fields[i]);
		mFieldSensors[i]->setPriority(0);
	}

	// by default the intersection gap is invisible
	set("gapDrawStyle { style INVISIBLE }");
}


SoXipMprIntersectionLine::~SoXipMprIntersectionLine()
{
	for (int i = 0; i < 6; i++)
	{
		delete mFieldSensors[i];
	}
}


void SoXipMprIntersectionLine::initClass()
{
	// make sure utility node kit class is initialized also
	SoXipMprIntersectionLineKit::initClass();

	SO_KIT_INIT_CLASS(SoXipMprIntersectionLine, SoXipMprIntersectionLineKit, "SoXipMprIntersectionLineKit");
}


void SoXipMprIntersectionLine::update()
{
	SbVec3f points[2], obj[4], objCenter;
	SbVec3f arrowPos[2];
	int i, numArrows = 0;

	// clear all current geometry
	clear();

	// update plane transformation
	SoMatrixTransform *trans = (SoMatrixTransform*) getPart("transform", TRUE);
	trans->matrix.setValue(planeMatrix.getValue());

	if (XipGeomUtils::mprIntersect(planeMatrix.getValue(), intersectMatrix.getValue(), points, mViewportAspectRatio))
	{
		// update pattern
		SbVec3f n1, n2;
		n1 = SbVec3f(planeMatrix.getValue()[2][0], planeMatrix.getValue()[2][1], planeMatrix.getValue()[2][2]);
		n2 = SbVec3f(intersectMatrix.getValue()[2][0], intersectMatrix.getValue()[2][1], intersectMatrix.getValue()[2][2]);
		n1.normalize();
		n2.normalize();

		if (fabs(acos(n1.dot(n2)) - (M_PI / 2)) > 0.01)
		{
			SoDrawStyle *style = (SoDrawStyle*) getPart("drawStyle", TRUE);
			style->linePattern.setValue(0x0f0f);
		}

		// All points are converted to 2D object space for easier
		// handling. The object-to-world conversion is done for the entire
		// geometry with the SoMatrixTransform object.
		SbMatrix m = planeMatrix.getValue().inverse();

		m.multVecMatrix(points[0], obj[0]);
		m.multVecMatrix(points[1], obj[1]);
		m.multVecMatrix(centerPosition.getValue(), objCenter);

		obj[0][2] = 0;
		obj[1][2] = 0;
		objCenter[2] = 0;

		SbLine objLine(obj[0], obj[1]);
		SbVec3f dirArrow, dir = objLine.getDirection();

		m.setRotate(SbRotation(SbVec3f(0.0f, 0.0f, 1.0f), static_cast<float>(M_PI) / 2.0f));
		m.multVecMatrix(dir, dirArrow);

		// make sure we draw to the end of the viewport
		float width = (mViewportAspectRatio < 1.f ? 1.f : mViewportAspectRatio) / 2.f;
		float height = (mViewportAspectRatio > 1.f ? 1.f : 1.f / mViewportAspectRatio) / 2.f;

		// intersection point between frame and line (note that COIN does not support this function):
		//SbBox3f frame(-width, -height, -1.f, width, height, 1.f);
		//objLine.intersect(frame, obj[0], obj[1]);

		SbVec3f ptOnThis, ptOnLine2;
		int objCount = 0;
		if (objLine.getClosestPoints(SbLine(SbVec3f(-width, -height, 0), SbVec3f(-width, height, 0)), ptOnThis, ptOnLine2))
			if ((ptOnThis == ptOnThis) && (ptOnThis.length() <= SbVec2f(width, height).length()))
				obj[objCount++] = ptOnThis;
		if (objLine.getClosestPoints(SbLine(SbVec3f(width, height, 0), SbVec3f(width, -height, 0)), ptOnThis, ptOnLine2))
			if ((ptOnThis == ptOnThis) && (ptOnThis.length() <= SbVec2f(width, height).length()))
				obj[objCount++] = ptOnThis;
		if (objLine.getClosestPoints(SbLine(SbVec3f(width, -height, 0), SbVec3f(-width, -height, 0)), ptOnThis, ptOnLine2))
			if ((ptOnThis == ptOnThis) && (ptOnThis.length() <= SbVec2f(width, height).length()))
				obj[objCount++] = ptOnThis;
		if (objLine.getClosestPoints(SbLine(SbVec3f(-width, height, 0), SbVec3f(width, height, 0)), ptOnThis, ptOnLine2))
			if ((ptOnThis == ptOnThis) && (ptOnThis.length() <= SbVec2f(width, height).length()))
				obj[objCount++] = ptOnThis;

		if (objCount != 2)
		{
			// no intersection
			return;
		}

		// update direction to reflect correct starting point
		dir = obj[1] - obj[0];
		dir.normalize();

		// check if center is on line and therfore valid
		SbLine line(obj[0], obj[1]);
		SbVec3f p = line.getClosestPoint(objCenter);
		SbBool isValidCenter = p.equals(objCenter, XIP_FLT_EPSILON);

		if (!stubs.getValue() && (centerGap.getValue() || centerCross.getValue()) && isValidCenter)
		{
			if (XipGeomUtils::isVecInObjectSpace(objCenter))
			{
				const float d = 2.0;

				// center located within plane, two arrows
				if ((obj[0] - objCenter).length() > (2 * CENTER_GAP_SIZE))
					arrowPos[numArrows++] = objCenter + (-dir * (obj[0] - objCenter).length()) / d;
				if ((obj[1] - objCenter).length() > (2 * CENTER_GAP_SIZE))
					arrowPos[numArrows++] = objCenter + (dir * (obj[1] - objCenter).length()) / d;
			}
			else
			{
				// center outside plane, one arrow only, located at center of line
				float len = (obj[1] - obj[0]).length();
				arrowPos[numArrows++] = obj[0] + (dir * (len / 2));
			}
		}
		else if (stubs.getValue())
		{
			// set up arrows for stubs
			arrowPos[numArrows++] = obj[0] + dir/(stubScale.getValue()*2);
			arrowPos[numArrows++] = obj[1] - dir/(stubScale.getValue()*2);
		}
		else
		{
			// no center given, two arrows at 1/4 and 3/4 of line
			float len = (obj[1] - obj[0]).length();
			arrowPos[numArrows++] = obj[0] + (dir * (len / 4));
			arrowPos[numArrows++] = obj[0] + (dir * (len / 4) * 3);
		}

		// update intersection line
		SoCoordinate3 *coord = (SoCoordinate3*) getPart("lineCoord", TRUE);
		SoLineSet *lineSet = (SoLineSet*) getPart("lineSet", TRUE);
		lineSet->numVertices.setNum(0);

		if (!stubs.getValue() && centerGap.getValue() && isValidCenter && XipGeomUtils::isVecInObjectSpace(objCenter))
		{
			// solid line segments
			p = objCenter - (CENTER_GAP_SIZE * dir);
			coord->point.set1Value(0, XipGeomUtils::isVecInObjectSpace(p) ? p : obj[0]);
			coord->point.set1Value(1, obj[0]);
			lineSet->numVertices.set1Value(0, 2);

			p = objCenter + (CENTER_GAP_SIZE * dir);
			coord->point.set1Value(2, XipGeomUtils::isVecInObjectSpace(p) ? p : obj[1]);
			coord->point.set1Value(3, obj[1]);
			lineSet->numVertices.set1Value(1, 2);

			// "gap" (invisible but important for picking the center)
			coord = (SoCoordinate3*) getPart("gapCoord", TRUE);
			lineSet = (SoLineSet*) getPart("gapLineSet", TRUE);

			coord->point.set1Value(0, objCenter - (CENTER_GAP_SIZE * dir));
			coord->point.set1Value(1, objCenter + (CENTER_GAP_SIZE * dir));
			lineSet->numVertices.set1Value(0, 2);
		}
		else if (stubs.getValue())
		{
			// set up stubs only
			coord->point.set1Value(0, obj[0]);
			coord->point.set1Value(1, obj[0] + dir/stubScale.getValue());
			lineSet->numVertices.set1Value(0, 2);

			coord->point.set1Value(2, obj[1]);
			coord->point.set1Value(3, obj[1] - dir/stubScale.getValue());
			lineSet->numVertices.set1Value(1, 2);

			// "gap" (invisible but important for picking the center)
			coord = (SoCoordinate3*) getPart("gapCoord", TRUE);
			lineSet = (SoLineSet*) getPart("gapLineSet", TRUE);

			coord->point.set1Value(0, obj[0]);
			coord->point.set1Value(1, obj[1]);
			lineSet->numVertices.set1Value(0, 2);
		}
		else
		{
			// set up whole line
			coord->point.set1Value(0, obj[0]);
			coord->point.set1Value(1, obj[1]);
			lineSet->numVertices.set1Value(0, 2);
		}

		// update center cross
		if (centerCross.getValue()  && isValidCenter && XipGeomUtils::isVecInObjectSpace(objCenter))
		{
			int vertices = 0, points = 0;
			coord = (SoCoordinate3*) getPart("crossCoord", TRUE);
			lineSet = (SoLineSet*) getPart("crossLineSet", TRUE);

			if (centerGap.getValue())
			{
				if (XipGeomUtils::isVecInObjectSpace(objCenter + (CENTER_GAP_SIZE * dirArrow)))
				{
					coord->point.set1Value(points++, objCenter + (CENTER_GAP_SIZE * dirArrow));
					coord->point.set1Value(points++, objCenter + (CENTER_MARKER_SIZE * dirArrow));
					lineSet->numVertices.set1Value(vertices++, 2);
				}
				if (XipGeomUtils::isVecInObjectSpace(objCenter - (CENTER_GAP_SIZE * dirArrow)))
				{
					coord->point.set1Value(points++, objCenter - (CENTER_GAP_SIZE * dirArrow));
					coord->point.set1Value(points++, objCenter - (CENTER_MARKER_SIZE * dirArrow));
					lineSet->numVertices.set1Value(vertices++, 2);
				}
			}
			else
			{
				coord->point.set1Value(points++, objCenter - (CENTER_MARKER_SIZE * dirArrow));
				coord->point.set1Value(points++, objCenter + (CENTER_MARKER_SIZE * dirArrow));
				lineSet->numVertices.set1Value(vertices++, 2);
			}
		}

		// update arrows
		if (normalIndicators.getValue())
		{
			SbVec3f halfSpacePosition;

			const float d = 10.0;
			planeMatrix.getValue().multVecMatrix(obj[0] + (d * dirArrow), halfSpacePosition);
			if (!XipGeomUtils::planeFromMatrix(intersectMatrix.getValue()).isInHalfSpace(halfSpacePosition))
			{
				dirArrow *= -1;
			}

			coord = (SoCoordinate3*) getPart("arrowCoord", TRUE);
			lineSet = (SoLineSet*) getPart("arrowLineSet", TRUE);

			const float c1 = 0.3f;
			const float c2 = 0.1f;

			for (i = 0; i < numArrows; i++)
			{
				coord->point.set1Value((i * 6) + 0, arrowPos[i]);
				coord->point.set1Value((i * 6) + 1, arrowPos[i] + (dirArrow * NORMAL_INDICATOR_SIZE));
				lineSet->numVertices.set1Value((i * 3) + 0, 2);

				coord->point.set1Value((i * 6) + 2, arrowPos[i]);
				coord->point.set1Value((i * 6) + 3, arrowPos[i] + (dirArrow * NORMAL_INDICATOR_SIZE * c1) + (dir * NORMAL_INDICATOR_SIZE * c2));
				lineSet->numVertices.set1Value((i * 3) + 1, 2);

				coord->point.set1Value((i * 6) + 4, arrowPos[i]);
				coord->point.set1Value((i * 6) + 5, arrowPos[i] + (dirArrow * NORMAL_INDICATOR_SIZE * c1) - (dir * NORMAL_INDICATOR_SIZE * c2));
				lineSet->numVertices.set1Value((i * 3) + 2, 2);
			}
		}
	}
}


void SoXipMprIntersectionLine::clear()
{
	const SbName lines[] = { "lineSet", "arrowLineSet", "gapLineSet", "crossLineSet" };
	const SbName coords[] = { "lineCoord", "arrowCoord", "gapCoord", "crossCoord" };

	for (int i = 0; i < 4; i++)
	{
		SoLineSet *lineSet = (SoLineSet*) getPart(lines[i], FALSE);
		if (lineSet) lineSet->numVertices.deleteValues(0);

		SoCoordinate3 *coord = (SoCoordinate3*) getPart(coords[i], FALSE);;
		if (coord) coord->point.deleteValues(0);
	}
}


void SoXipMprIntersectionLine::fieldSensorCBFunc(void *user, SoSensor *sensor)
{
	if (user)
	{
		((SoXipMprIntersectionLine*) user)->fieldSensorCB(sensor);
	}
}


void SoXipMprIntersectionLine::fieldSensorCB(SoSensor *sensor)
{
	mNeedsUpdate = TRUE;
}

void SoXipMprIntersectionLine::GLRender(SoGLRenderAction * action)
{
	SbViewportRegion vpRegion = SoViewportRegionElement::get(action->getState());
	float diff = mViewportAspectRatio - vpRegion.getViewportAspectRatio();

	if (mNeedsUpdate || (fabs(diff) > 0.001))
	{
		mViewportAspectRatio = vpRegion.getViewportAspectRatio();
		mNeedsUpdate = FALSE;
		update();
	}

	// let's keep current lineWidth setting
	float lineWidth = SoLineWidthElement::get(action->getState());
	SoDrawStyle *style = (SoDrawStyle*) getPart("drawStyle", TRUE);
	if (style->lineWidth.getValue() != lineWidth)
		style->lineWidth.setValue(lineWidth);

	// draw nodekit
	SoXipMprIntersectionLineKit::GLRender(action);
}


