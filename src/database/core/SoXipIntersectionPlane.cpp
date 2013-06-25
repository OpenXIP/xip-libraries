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
//! The Inventor module class SoXipIntersectionPlane derived from SoNode
/*!
// \file    SoXipIntersectionPlane.cpp
// \author  Vivien Delage
// \date    2005-03-29
//
// Used to draw the intersection beetween a plane and a box in the scene
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

// Local includes
#include "SoXipIntersectionPlane.h"
//#include <Inventor/fields/SoMFLong.h>

#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/SbBox.h>
#include <Inventor/SbLinear.h>

#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>


SO_NODE_SOURCE(SoXipIntersectionPlane);


// --------------------------------------------------------------------------
//! Initializes this class. Called on dll initialization.
// --------------------------------------------------------------------------
void SoXipIntersectionPlane::initClass()
{
	SO_NODE_INIT_CLASS(SoXipIntersectionPlane, SoNode, "Node");

	SO_ENABLE(SoGLRenderAction, SoViewVolumeElement);
	SO_ENABLE(SoGLRenderAction, SoModelMatrixElement);
}


// --------------------------------------------------------------------------
//! Constructor, creates fields
// --------------------------------------------------------------------------
SoXipIntersectionPlane::SoXipIntersectionPlane()
{
	// Execute inventor internal stuff for node construction.
	SO_NODE_CONSTRUCTOR(SoXipIntersectionPlane);

	// possible rendering parts of the box  
	SO_NODE_DEFINE_ENUM_VALUE(renderingParts, ALL);
	SO_NODE_DEFINE_ENUM_VALUE(renderingParts, FRONT);
	SO_NODE_DEFINE_ENUM_VALUE(renderingParts, BACK);

	// Copy static information for "renderingParts" enumerated type field
	// into this instance. 
	SO_NODE_SET_SF_ENUM_TYPE(parts, renderingParts);

	// add the fields
	SO_NODE_ADD_FIELD(on, (true));
	SO_NODE_ADD_FIELD(boundingBox,(SbMatrix::identity()));
	SO_NODE_ADD_FIELD(plane,(SbPlane(SbVec3f(1, 0, 0), 0)));
	SO_NODE_ADD_FIELD(parts, (ALL));  

	pCoordinates = new SoCoordinate3();
	pCoordinates->ref();
	pLines = new SoIndexedLineSet();
	pLines->ref();

	mBoundingBox[0] = SbVec3f(0, 1, 1);
	mBoundingBox[1] = SbVec3f(0, 0, 1);
	mBoundingBox[2] = SbVec3f(1, 0, 1);
	mBoundingBox[3] = SbVec3f(1, 1, 1);
	mBoundingBox[4] = SbVec3f(0, 1, 0);
	mBoundingBox[5] = SbVec3f(0, 0, 0);
	mBoundingBox[6] = SbVec3f(1, 0, 0);
	mBoundingBox[7] = SbVec3f(1, 1, 0);

	updateBoundingBox();
	calculateCubeIntersection(true);
}


// --------------------------------------------------------------------------
//! Protected destructor to cleans up internally created nodes and node sensor.
// --------------------------------------------------------------------------
SoXipIntersectionPlane::~SoXipIntersectionPlane()
{
	if(pCoordinates){pCoordinates->unref();}
	if(pLines){pLines->unref();}
}

// --------------------------------------------------------------------------
//! called to calculated visible part of the intersection plane
//! and add the correct index to the corresponding IndexedLineSet
// --------------------------------------------------------------------------
void SoXipIntersectionPlane::calculateVisibleParts(SoState *state)
{
	float angle;
	int i;
	std::vector<int> idxList;
	int n = pCoordinates->point.getNum();

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

	int part = parts.getValue();
	for (i = 0; i < n; i += 2)
	{
		SbVec3f lineNormal = mFaceNormals[i / 2];
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
			idxList.push_back(-1);
		}
	}

	int listSize = static_cast<int>(idxList.size());
	SbBool changed = FALSE;
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
//! calculate the intersection points with the input cube
// --------------------------------------------------------------------------
void SoXipIntersectionPlane::calculateCubeIntersection(bool boxChanged)
{
	if(!pCoordinates)
		return;

	// get the input plane
	SbPlane planeInter(plane.getValue());

	// see if computation is necessary
	if (!(planeInter != mCachedPlane || boxChanged))
	{
		return;
	}
	mCachedPlane = planeInter;


	// variable used to calculate each intersection points with the box
	bool b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12;
	SbVec3f p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12;


	// clear the lists containing the normals before updating a new one
	mFaceNormals.clear();


	// used to know the current index of the coordinate table
	int numPoint=0;

	// temporary pointer on the intersection points table
	SbVec3f * ptTabVec = mTabVec;


	// calculate the possible intersection points with each line of the box
	b1 =  calculateLineIntersection(planeInter, mTransBoundingBox[0], mTransBoundingBox[1], p1);
	b2 =  calculateLineIntersection(planeInter, mTransBoundingBox[1], mTransBoundingBox[2], p2);
	b3 =  calculateLineIntersection(planeInter, mTransBoundingBox[2], mTransBoundingBox[3], p3);
	b4 =  calculateLineIntersection(planeInter, mTransBoundingBox[3], mTransBoundingBox[0], p4);

	b5 =  calculateLineIntersection(planeInter, mTransBoundingBox[7], mTransBoundingBox[6], p5);
	b6 =  calculateLineIntersection(planeInter, mTransBoundingBox[6], mTransBoundingBox[5], p6);
	b7 =  calculateLineIntersection(planeInter, mTransBoundingBox[5], mTransBoundingBox[4], p7);
	b8 =  calculateLineIntersection(planeInter, mTransBoundingBox[4], mTransBoundingBox[7], p8);

	b9 =  calculateLineIntersection(planeInter, mTransBoundingBox[4], mTransBoundingBox[0], p9);
	b10 = calculateLineIntersection(planeInter, mTransBoundingBox[3], mTransBoundingBox[7], p10);
	b11 = calculateLineIntersection(planeInter, mTransBoundingBox[1], mTransBoundingBox[5], p11);
	b12 = calculateLineIntersection(planeInter, mTransBoundingBox[6], mTransBoundingBox[2], p12);



	// add the interesection points to the list, face after face of the cube
	// the intersection will be draw line by line
	// add the normal of the face at the end of each face

	//face 1
	if(b1)  {*ptTabVec++ = p1; numPoint++;}
	if(b2)  {*ptTabVec++ = p2; numPoint++;}
	if(b3)  {*ptTabVec++ = p3; numPoint++;}
	if(b4)  {*ptTabVec++ = p4; numPoint++;}

	if(b1 || b2 || b3 || b4)
		mFaceNormals.push_back(getNormal(mTransBoundingBox[0], mTransBoundingBox[1], mTransBoundingBox[2]));

	//face 2
	if(b3)  {*ptTabVec++ = p3; numPoint++;}
	if(b12) {*ptTabVec++ = p12; numPoint++;}
	if(b5)  {*ptTabVec++ = p5; numPoint++;}
	if(b10) {*ptTabVec++ = p10; numPoint++;}

	if(b3 || b12 || b5 || b10)
		mFaceNormals.push_back(getNormal(mTransBoundingBox[3], mTransBoundingBox[2], mTransBoundingBox[6]));

	//face 3
	if(b5)  {*ptTabVec++ = p5; numPoint++;}
	if(b6)  {*ptTabVec++ = p6; numPoint++;}
	if(b7)  {*ptTabVec++ = p7; numPoint++;}
	if(b8)  {*ptTabVec++ = p8; numPoint++;}

	if(b5 || b6 || b7 || b8)
		mFaceNormals.push_back(getNormal(mTransBoundingBox[7], mTransBoundingBox[6], mTransBoundingBox[5]));

	//face 4
	if(b7)  {*ptTabVec++ = p7; numPoint++;}
	if(b11) {*ptTabVec++ = p11; numPoint++;}
	if(b1)  {*ptTabVec++ = p1; numPoint++;}
	if(b9)  {*ptTabVec++ = p9; numPoint++;}

	if(b7 || b11 || b1 || b9)
		mFaceNormals.push_back(getNormal(mTransBoundingBox[4], mTransBoundingBox[5], mTransBoundingBox[1]));
	
	//face 5
	if(b9)  {*ptTabVec++ = p9; numPoint++;}
	if(b4)  {*ptTabVec++ = p4; numPoint++;}
	if(b10) {*ptTabVec++ = p10; numPoint++;}
	if(b8)  {*ptTabVec++ = p8; numPoint++;}

	if(b9 || b4 || b10 || b8)
		mFaceNormals.push_back(getNormal(mTransBoundingBox[4], mTransBoundingBox[0], mTransBoundingBox[3]));
	
	//face 6
	if(b11) {*ptTabVec++ = p11; numPoint++;}
	if(b6)  {*ptTabVec++ = p6; numPoint++;}
	if(b12) {*ptTabVec++ = p12; numPoint++;}
	if(b2)  {*ptTabVec++ = p2; numPoint++;}

	if(b11 || b6 || b12 || b2)
		mFaceNormals.push_back(getNormal(mTransBoundingBox[1], mTransBoundingBox[5], mTransBoundingBox[6]));

	
	// give the points to the SoCoordinate node

	pCoordinates->point.setNum(numPoint);
	pCoordinates->point.setValues(0, numPoint, mTabVec);
}

// --------------------------------------------------------------------------
//! calculate the  intersection point between a plane and a line
//! return true if an intersection exist, false else
// --------------------------------------------------------------------------
bool SoXipIntersectionPlane::calculateLineIntersection(const SbPlane & plane, 
													   const SbVec3f &pA, 
													   const SbVec3f &pB, SbVec3f &res)
{
	SbVec3f tmpIntersectionPoint;
	SbLine tmpLine(pA, pB);
	float xA, xB, xP, yA, yB, yP, zA, zB, zP;

	// check if plane and line are parallel and return false if this is the case.
	// (TGS's SbPlane::intersect returns true if the line lies in the plane, but we don't want this)
	SbVec3f normal = plane.getNormal();
	if (abs(tmpLine.getDirection().dot(normal)) < 0.0001f)
		return false;

	// calculate the intersection point if exist
	if(plane.intersect(tmpLine,tmpIntersectionPoint))
	{
		pA.getValue(xA, yA, zA);
		pB.getValue(xB, yB, zB);
		tmpIntersectionPoint.getValue(xP, yP, zP);

		// look if the interesection point is beetween pA and pB
		// if it is the case, return the intersection point
		if(((xP <= xA)  && (xP >= xB)) || ((xP <= xB) && (xP >= xA)))
			if(((yP <= yA)  && (yP >= yB)) || ((yP <= yB) && (yP >= yA)))
				if(((zP <= zA)  && (zP >= zB)) || ((zP <= zB) && (zP >= zA)))
				{
					res = tmpIntersectionPoint;
					return true;
				}
	}

	return false;
}


//-----------------------------------------------------------------------------
//! get the normal of a face giving 3 points of it
//-----------------------------------------------------------------------------
SbVec3f SoXipIntersectionPlane::getNormal(const SbVec3f &p1, const SbVec3f &p2, const SbVec3f &p3)
{
	SbVec3f tmpVec1, tmpVec2, tmpVecRes;

	tmpVec1 = p1 - p2;
	tmpVec2 = p3 - p2;

	tmpVecRes = tmpVec1.cross(tmpVec2);
	tmpVecRes.normalize();

	return tmpVecRes;
}


//--------------------------------------------------------------------------
//! called whenever the scene is rendered
//--------------------------------------------------------------------------
void SoXipIntersectionPlane::GLRender(SoGLRenderAction *action)
{
	// draw only if the checkbox is on
	if(on.getValue())
	{
		bool boxChanged = updateBoundingBox();
		calculateCubeIntersection(boxChanged);
		calculateVisibleParts(action->getState());

		if (pCoordinates->point.getNum() > 0)
		{
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
		}
	}

	SoShape::GLRender(action);
}

//-----------------------------------------------------------------------------
//! This computes the bounding box
//-----------------------------------------------------------------------------
void SoXipIntersectionPlane::computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center)
{
//	box = SbBox3f(mMinBox, mMaxBox);
//	center = box.getCenter();
}

//-----------------------------------------------------------------------------
//call to update the bounding box with the new transformation matrix
//-----------------------------------------------------------------------------
bool SoXipIntersectionPlane::updateBoundingBox()
{
	if (boundingBox.getValue() == mCachedBBox)
	{
		return false;
	}
	mCachedBBox = boundingBox.getValue();

	boundingBox.getValue().multVecMatrix(mBoundingBox[0], mTransBoundingBox[0]);
	boundingBox.getValue().multVecMatrix(mBoundingBox[1], mTransBoundingBox[1]);
	boundingBox.getValue().multVecMatrix(mBoundingBox[2], mTransBoundingBox[2]);
	boundingBox.getValue().multVecMatrix(mBoundingBox[3], mTransBoundingBox[3]);
	boundingBox.getValue().multVecMatrix(mBoundingBox[4], mTransBoundingBox[4]);
	boundingBox.getValue().multVecMatrix(mBoundingBox[5], mTransBoundingBox[5]);
	boundingBox.getValue().multVecMatrix(mBoundingBox[6], mTransBoundingBox[6]);
	boundingBox.getValue().multVecMatrix(mBoundingBox[7], mTransBoundingBox[7]);


	// calculate min and max to compute the bounding box
	float minX, minY, minZ, maxX, maxY, maxZ, curX, curY, curZ;
	mTransBoundingBox[0].getValue(minX, minY, minZ);
	mTransBoundingBox[0].getValue(maxX, maxY, maxZ);

	for(int i=1; i< 8; i++)
	{
		mTransBoundingBox[i].getValue(curX, curY, curZ);

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

	mMinBox.setValue(minX, minY, minZ);
	mMaxBox.setValue(maxX, maxY, maxZ);
	return true;
}
