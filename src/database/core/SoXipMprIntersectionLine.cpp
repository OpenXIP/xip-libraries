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

#include <xip/common/XipDebug.h>

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
		SbBox3f frame(-width, -height, -1.f, width, height, 1.f);
		bool intersected = objLine.intersect(frame, obj[0], obj[1]) == TRUE;

		//SbVec3f ptOnThis, ptOnLine2;
		//int objCount = 0;
		//if (objLine.getClosestPoints(SbLine(SbVec3f(-width, -height, 0), SbVec3f(-width, height, 0)), ptOnThis, ptOnLine2))
		//	if ((ptOnThis == ptOnThis) && (ptOnThis.length() <= SbVec2f(width, height).length()))
		//		obj[objCount++] = ptOnThis;
		//if (objLine.getClosestPoints(SbLine(SbVec3f(width, height, 0), SbVec3f(width, -height, 0)), ptOnThis, ptOnLine2))
		//	if ((ptOnThis == ptOnThis) && (ptOnThis.length() <= SbVec2f(width, height).length()))
		//		obj[objCount++] = ptOnThis;
		//if (objLine.getClosestPoints(SbLine(SbVec3f(width, -height, 0), SbVec3f(-width, -height, 0)), ptOnThis, ptOnLine2))
		//	if ((ptOnThis == ptOnThis) && (ptOnThis.length() <= SbVec2f(width, height).length()))
		//		obj[objCount++] = ptOnThis;
		//if (objLine.getClosestPoints(SbLine(SbVec3f(-width, height, 0), SbVec3f(width, height, 0)), ptOnThis, ptOnLine2))
		//	if ((ptOnThis == ptOnThis) && (ptOnThis.length() <= SbVec2f(width, height).length()))
		//		obj[objCount++] = ptOnThis;


		//if (objCount != 2)
		if ( !intersected )
		{
			// no intersection
			//XipDebug::output("no intersection line box intersection\n");
			return;
		}

		// update direction to reflect correct starting point
		dir = obj[1] - obj[0];
		dir.normalize();

		// check if center is on line and therefore valid
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
	//else
	//{
	//	//XipDebug::output("no intersection");
	//}
}


void SoXipMprIntersectionLine::clear()
{
	//XipDebug::output("%d: clear() is called\n", uniqueId);
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
	//XipDebug::output("SoXipMprIntersectionLine::GLRender");
	SbViewportRegion vpRegion = SoViewportRegionElement::get(action->getState());
	float diff = mViewportAspectRatio - vpRegion.getViewportAspectRatio();

	//if (mNeedsUpdate || (fabs(diff) > 0.001))
	{
		mViewportAspectRatio = vpRegion.getViewportAspectRatio();
		mNeedsUpdate = FALSE;
		update();
	}
	//else
	//{
	//	XipDebug::output("%d: No need to update %d %f\n", uniqueId, (int)mNeedsUpdate, fabs(diff));
	//}

	// let's keep current lineWidth setting
	float lineWidth = SoLineWidthElement::get(action->getState());
	SoDrawStyle *style = (SoDrawStyle*) getPart("drawStyle", TRUE);
	if (style->lineWidth.getValue() != lineWidth)
		style->lineWidth.setValue(lineWidth);

	// draw nodekit
	if (glIsEnabled(GL_LINE_SMOOTH) && !glIsEnabled(GL_BLEND))
	{
		// blending must be enabled in order for line smoothing to work
		glEnable(GL_BLEND);
		SoXipMprIntersectionLineKit::GLRender(action);
		glDisable(GL_BLEND);
	}
	else
	{
		SoXipMprIntersectionLineKit::GLRender(action);
	}
}


