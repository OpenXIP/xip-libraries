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

#include "SoXipMprAlign.h"
#include <xip/inventor/core/SoXipMprPlaneElement.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <xip/inventor/core/XipGeomUtils.h>

#ifndef __cdecl
#define __cdecl
#endif

SO_NODE_SOURCE(SoXipMprAlign);


void SoXipMprAlign::initClass()
{
	SO_NODE_INIT_CLASS(SoXipMprAlign, SoNode, "Node");

	// enable elements goes here
	// SO_ENABLE(SoGLRenderAction, ...);
}


SoXipMprAlign::SoXipMprAlign()
{
	SO_NODE_CONSTRUCTOR(SoXipMprAlign);

	SO_NODE_ADD_FIELD(position, (SbVec3f(0, 0, 0)));
	SO_NODE_ADD_FIELD(nearestVoxel, ());

	SO_NODE_ADD_FIELD(modelMatrix, (SbMatrix::identity()));
	SO_NODE_ADD_FIELD(width, (0));
	SO_NODE_ADD_FIELD(height, (0));
	SO_NODE_ADD_FIELD(depth, (0));

	mUpdatePosition = FALSE;
	mUpdateNearestVoxel = FALSE;


	mPositionSensor = new SoFieldSensor((SoSensorCB (__cdecl *))&fieldSensorCBFunc, this);
	if (mPositionSensor)
	{
		mPositionSensor->setPriority(0);
		mPositionSensor->attach(&position);
	}

	mNearestVoxelSensor = new SoFieldSensor((SoSensorCB (__cdecl *))&fieldSensorCBFunc, this);
	if (mNearestVoxelSensor)
	{
		mNearestVoxelSensor->setPriority(0);
		mNearestVoxelSensor->attach(&nearestVoxel);
	}
}


SoXipMprAlign::~SoXipMprAlign()
{
	if (mPositionSensor) delete mPositionSensor;
	if (mNearestVoxelSensor) delete mNearestVoxelSensor;
}


void SoXipMprAlign::fieldSensorCBFunc( void* userData, SoSensor* sensor)
{
	SoXipMprAlign *thisPtr = (SoXipMprAlign *) userData;

	if (sensor == thisPtr->mPositionSensor) thisPtr->mUpdatePosition = TRUE;
	if (sensor == thisPtr->mNearestVoxelSensor) thisPtr->mUpdateNearestVoxel = TRUE;
}


void SoXipMprAlign::GLRender(SoGLRenderAction *action)
{
	if (mUpdatePosition)
	{
		mUpdatePosition = FALSE;
		align(action, position.getValue());
	}

	if (mUpdateNearestVoxel)
	{
		mUpdateNearestVoxel = FALSE;

		if ((width.getValue() > 0) && (height.getValue() > 0) && (depth.getValue() > 0))
		{
			SoXipMprPlaneElement *element = SoXipMprPlaneElement::getInstance(action->getState());
			if (element)
			{
				int numPlanes = element->getNum();

				for (int i = 0; i < numPlanes; i++)
				{
					SbMatrix m = element->getMatrix(i);
					SbVec3f translation, scaleFactor, center, object;
					SbRotation rotation, scaleOrientation;
					m.getTransform(translation, rotation, scaleFactor, scaleOrientation);

					modelMatrix.getValue().inverse().multVecMatrix(translation, object);

					object[0] = int(object[0] * width.getValue() + 0.5);
					object[1] = int(object[1] * height.getValue() + 0.5);
					object[2] = int(object[2] * depth.getValue() + 0.5);

					object[0] /= width.getValue();
					object[1] /= height.getValue();
					object[2] /= depth.getValue();

					SbVec3f pt;
					modelMatrix.getValue().multVecMatrix(object, pt);

					align(action, pt, i);
				}
			}
		}
	}
}


void SoXipMprAlign::align(SoAction *action, SbVec3f pt, int which)
{
	SoXipMprPlaneElement *element = SoXipMprPlaneElement::getInstance(action->getState());
	if (!element) return;

	int numPlanes = element->getNum();
	if (numPlanes <= 0) return;

	int iStart = 0;
	int iEnd = numPlanes;

	if (which >= 0)
	{
		iStart = which;
		iEnd = which + 1;
		if (iEnd > numPlanes) iEnd = numPlanes;
	}

	for (int i = iStart; i < iEnd; i++)
	{
		SbMatrix m = element->getMatrix(i);

		SbVec3f t, s;
		SbRotation r, so;
		m.getTransform(t, r, s, so);

		SbPlane plane = XipGeomUtils::planeFromMatrix(m);
		SbLine line(t, t + plane.getNormal());
		m.setTransform(pt, r, s, so);
		plane = XipGeomUtils::planeFromMatrix(m);
		if (plane.intersect(line, t))
		{
			m.setTransform( t, r, s, so );

			SbVec3f ptObjectSpace;
			SbMatrix pInv = m.inverse();
			pInv.multVecMatrix( pt, ptObjectSpace );

            SbVec3f offset( 0, 0, 0 );
			if( ptObjectSpace[0] > 0.5 )
				offset[0] = ptObjectSpace[0] - 0.4;
			else if( ptObjectSpace[0] < -0.5 )
				offset[0] = ptObjectSpace[0] + 0.4;	
			if( ptObjectSpace[1] > 0.5 )
				offset[1] = ptObjectSpace[1] - 0.4;	
			else if( ptObjectSpace[1] < -0.5 )
				offset[1] = ptObjectSpace[1] + 0.4;	

			SbMatrix scaleMatrix;
			scaleMatrix.setTransform( SbVec3f(0, 0, 0), r, s, so );
			scaleMatrix.multVecMatrix( offset, offset );

			m.setTransform( t + offset, r, s, so );
		}

		element->setMatrix(i, m);

        if (element->getCenter(i) != pt)
            element->setCenter(i, pt);

	}
}
