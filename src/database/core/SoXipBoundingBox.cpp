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

//----------------------------------------------------------------------------------
//! The Inventor module class SoXipBoundingBox derived from SoNode
/*!
// \file    SoXipBoundingBox.cpp
// \author  Vivien Delage
// \date    2005-03-29
//
// Used to draw a bounding box englobing objects
*/
//----------------------------------------------------------------------------------



/****************************************
       The cube box geometry

					f3
			   4---------7
			  /|        /|
		 f4	 / |  f5   / |
			/  |      /  |
			0---------3  |
			|  |      |  |
			|  5------|--6
			|  /      |  /
			| /   f6  | / f2
			|/        |/
			1---------2
				f1

face1 ->   0, 1, 2, 3
face2 ->   3, 2, 6, 7
face3 ->   7, 6, 5, 4
face4 ->   4, 5, 1, 0
face5 ->   4, 0, 3, 7
face6 ->   1, 5, 6, 2

****************************************/

#include <xip/system/GL/gl.h>
#include "SoXipBoundingBox.h"
#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <math.h>
#include <vector>


SO_NODE_SOURCE(SoXipBoundingBox)


// --------------------------------------------------------------------------
//! Initializes this class. Called on dll initialization.
// --------------------------------------------------------------------------
void SoXipBoundingBox::initClass()
{
	SO_NODE_INIT_CLASS(SoXipBoundingBox, SoNode, "Node");

	SO_ENABLE(SoGLRenderAction, SoViewVolumeElement);
	SO_ENABLE(SoGLRenderAction, SoModelMatrixElement);
}


// --------------------------------------------------------------------------
//! Constructor, creates fields
// --------------------------------------------------------------------------
SoXipBoundingBox::SoXipBoundingBox()
{
	// Execute inventor internal stuff for node construction.
	SO_NODE_CONSTRUCTOR(SoXipBoundingBox);


	//possible rendering parts of the box  
	SO_NODE_DEFINE_ENUM_VALUE(renderingParts, ALL);
	SO_NODE_DEFINE_ENUM_VALUE(renderingParts, FRONT);
	SO_NODE_DEFINE_ENUM_VALUE(renderingParts, BACK);


	// Copy static information for "renderingParts" enumerated type field
	// into this instance. 
	SO_NODE_SET_SF_ENUM_TYPE(parts, renderingParts);
	
	// add the fields
    SO_NODE_ADD_FIELD(on, (TRUE));
	SO_NODE_ADD_FIELD(boundingBox,(SbMatrix::identity()));
	SO_NODE_ADD_FIELD(parts, (ALL));


	mBoundingBox[0] = SbVec3f(0, 1, 1);
	mBoundingBox[1] = SbVec3f(0, 0, 1);
	mBoundingBox[2] = SbVec3f(1, 0, 1);
	mBoundingBox[3] = SbVec3f(1, 1, 1);
	mBoundingBox[4] = SbVec3f(0, 1, 0);
	mBoundingBox[5] = SbVec3f(0, 0, 0);
	mBoundingBox[6] = SbVec3f(1, 0, 0);
	mBoundingBox[7] = SbVec3f(1, 1, 0);


	pCoordinates = new SoCoordinate3();
	pCoordinates->ref();
	pLines = new SoIndexedLineSet();
	pLines->ref();

	// Create a sensor calling for bounding box field changes. Use a priority 0
	// sensor to be sure that changes are not delayed or collected.
	mBoundingBoxSensor = new SoFieldSensor(&fieldSensorCBFunc, this);
	mBoundingBoxSensor->setPriority(0);
	mBoundingBoxSensor->attach(&boundingBox);

	setCubeGeometry();
}


// --------------------------------------------------------------------------
//! Protected destructor to cleans up internally created nodes and node sensor.
// --------------------------------------------------------------------------
SoXipBoundingBox::~SoXipBoundingBox()
{
	// Remove the node sensor.
	if (mBoundingBoxSensor)
	{
		delete mBoundingBoxSensor;
		mBoundingBoxSensor = 0;
	}
	
	if (pCoordinates)
	{
		pCoordinates->unref();
		pCoordinates = 0;
	}
	if (pLines)
	{
		pLines->unref();
		pLines = 0;
	}
}


// --------------------------------------------------------------------------
//! set the cube geometry into the coordinate node using the boundingbox input
// --------------------------------------------------------------------------
void SoXipBoundingBox::setCubeGeometry()
{
	if(!pCoordinates)
		return;

	// temporary pointer on the box points table
	SbVec3f *ptTabVec = mTabVec;

	
	// add the box points to the list, face after face of the cube
	// add the normal of the face at the end of each face

	//face 1
	boundingBox.getValue().multVecMatrix(mBoundingBox[0], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[1], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[2], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[3], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[0], *ptTabVec++);

	mCubeNormals[0] = getNormal(mTabVec[0], mTabVec[1], mTabVec[2]);
	mCubeFirstPoint[0] = mBoundingBox[0];

	//face 2
	boundingBox.getValue().multVecMatrix(mBoundingBox[3], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[2], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[6], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[7], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[3], *ptTabVec++);

	mCubeNormals[1] = getNormal(mTabVec[5], mTabVec[6], mTabVec[7]);
	mCubeFirstPoint[1] = mBoundingBox[3];

	//face 3
	boundingBox.getValue().multVecMatrix(mBoundingBox[7], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[6], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[5], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[4], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[7], *ptTabVec++);

	mCubeNormals[2] = getNormal(mTabVec[10], mTabVec[11], mTabVec[12]);
	mCubeFirstPoint[2] = mBoundingBox[7];

	//face 4
	boundingBox.getValue().multVecMatrix(mBoundingBox[4], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[5], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[1], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[0], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[4], *ptTabVec++);

	mCubeNormals[3] = getNormal(mTabVec[15], mTabVec[16], mTabVec[17]);
	mCubeFirstPoint[3] = mBoundingBox[5];

	//face 5
	boundingBox.getValue().multVecMatrix(mBoundingBox[4], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[0], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[3], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[7], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[4], *ptTabVec++);

	mCubeNormals[4] = getNormal(mTabVec[20], mTabVec[21], mTabVec[22]);
	mCubeFirstPoint[4] = mBoundingBox[4];

	//face 6
	boundingBox.getValue().multVecMatrix(mBoundingBox[1], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[5], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[6], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[2], *ptTabVec++);
	boundingBox.getValue().multVecMatrix(mBoundingBox[1], *ptTabVec++);

	mCubeNormals[5] = getNormal(mTabVec[25], mTabVec[26], mTabVec[27]);
	mCubeFirstPoint[5] = mBoundingBox[1];

	// give the points to the SoCoordinate node
	pCoordinates->point.setValues(0, BBOX_NUM_POINTS, mTabVec);


	// calculate min and max to compute the bounding box
	float minX, minY, minZ, maxX, maxY, maxZ, curX, curY, curZ;
	mTabVec[0].getValue(minX, minY, minZ);
	mTabVec[0].getValue(maxX, maxY, maxZ);

	for(int i=1; i< BBOX_NUM_POINTS; i++)
	{
		mTabVec[i].getValue(curX, curY, curZ);

		if(minX > curX)
			minX = curX;
		
		if(minY > curY)
			minY = curY;
		
		if(minZ > curZ)
			minZ = curZ;

		if(maxX < curX)
			maxX = curX;
		
		if(maxY < curY)
			maxY = curY;
		
		if(maxZ < curZ)
			maxZ = curZ;
	}

	minBox.setValue(minX, minY, minZ);
	maxBox.setValue(maxX, maxY, maxZ);
}


// --------------------------------------------------------------------------
//! called to calculated visible part of the bounding box
//! and add the correct index to the corresponding IndexedLineSet
// --------------------------------------------------------------------------
void SoXipBoundingBox::calculateVisibleParts(SoState *state)
{
	std::vector<int> idxList;
	int i, n = pCoordinates->point.getNum();

	// get the camera orientation
	SbViewVolume vVol = SoViewVolumeElement::get(state);
	SbVec3f zCamVector = vVol.getProjectionDirection();

	// get the projection of the camera position in the volume space 
	SbMatrix vModelMatrix = SoModelMatrixElement::get(state);
	SbVec3f camPoint = vVol.getProjectionPoint();
	SbVec3f camProjPoint;
	SbVec3f camProjVector;
	const SbMatrix modelInverse(vModelMatrix.inverse());
	modelInverse.multVecMatrix(camPoint, camProjPoint);
	modelInverse.multDirMatrix(zCamVector, camProjVector);

	// angle between normal and camera orientation
	float angle;

	int part = parts.getValue();
	for (i = 0; i < n; i += 5)
	{
		SbVec3f lineNormal = mCubeNormals[i / 5];
		SbVec3f pointLine = mTabVec[i];
		SbVec3f dirCamFace = pointLine - camProjPoint;

		// compute the angle depending of the camera projection type
		if(vVol.getProjectionType() == SbViewVolume::PERSPECTIVE)
			angle = lineNormal.dot(dirCamFace);
		else
			angle = lineNormal.dot(camProjVector);

		if ((part == ALL) || ((part == FRONT) & (angle >= 0)) || ((part == BACK) & (angle < 0)))
		{
			idxList.push_back(i);
			idxList.push_back(i + 1);
			idxList.push_back(i + 2);
			idxList.push_back(i + 3);
			idxList.push_back(i + 4);
			idxList.push_back(-1);
		}
	}

	SbBool changed = FALSE;
	int listSize = static_cast<int>(idxList.size());
	if (pLines->coordIndex.getNum() != listSize)
	{
		pLines->coordIndex.setNum(listSize);
	}

	const int *val = pLines->coordIndex.getValues(0);
	for (i = 0; i < listSize; i++)
	{
		if (val[i] != idxList[i]) break;
	}

	if (i != listSize)
	{
		pLines->coordIndex.setValues(0, listSize, &idxList[0]);
	}
}


// --------------------------------------------------------------------------
//! called whenever the scene is rendered
// --------------------------------------------------------------------------
void SoXipBoundingBox::GLRender(SoGLRenderAction *action)
{
    if (on.getValue())
    {
	    calculateVisibleParts(action->getState());	

	    glPushAttrib(GL_ENABLE_BIT);
	    
		if (glIsEnabled(GL_LINE_SMOOTH) && !glIsEnabled(GL_BLEND))
		{
			// blending must be enabled in order for line smoothing to work
			glEnable(GL_BLEND);
		}

	    int maxClipPlanes;
	    glGetIntegerv(GL_MAX_CLIP_PLANES, &maxClipPlanes);
	    for (int i = 0; i < maxClipPlanes; i++)
	    {
		    glDisable(GL_CLIP_PLANE0 + i);
	    }
	    pCoordinates->GLRender(action);
	    pLines->GLRender(action);
	    glPopAttrib();

	    SoShape::GLRender(action);
    }
}


//-----------------------------------------------------------------------------
//! This computes the bounding box
//-----------------------------------------------------------------------------
void SoXipBoundingBox::computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center)
{
	box = SbBox3f(minBox, maxBox);
	center = box.getCenter();
}


//-----------------------------------------------------------------------------
//! get the normal of a face giving 3 points of it
//-----------------------------------------------------------------------------
SbVec3f SoXipBoundingBox::getNormal(const SbVec3f &p1, const SbVec3f &p2, const SbVec3f &p3)
{
	SbVec3f tmpVec1, tmpVec2, tmpVecRes;

	tmpVec1 = p1 - p2;
	tmpVec2 = p3 - p2;

	tmpVecRes = tmpVec1.cross(tmpVec2);
	tmpVecRes.normalize();

	return tmpVecRes;
}


void SoXipBoundingBox::fieldSensorCBFunc(void *user, SoSensor *sensor)
{
	SoXipBoundingBox* thisPtr = (SoXipBoundingBox*) user;

	if (sensor == thisPtr->mBoundingBoxSensor)
	{
		thisPtr->setCubeGeometry();
	}

	thisPtr->touch();
}
