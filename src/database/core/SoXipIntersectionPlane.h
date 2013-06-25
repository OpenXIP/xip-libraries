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
// \file    SoXipIntersectionPlane.h
// \author  Vivien Delage
// \date    2005-03-29
//
// Used to draw a intersection between a plane and a box in the scene
*/
//----------------------------------------------------------------------------------

#ifndef SOXIPINTERSECTIONPLANE_H
#define SOXIPINTERSECTIONPLANE_H


//inventor includes
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFPlane.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <vector>


#define IBOX_NUM_POINTS		20
#define IBOX_NUM_INDEXES	30



//! Intersection plane rendering node
class SoXipIntersectionPlane : public SoShape
{
	//! Implements the runtime type system interface of this new node.
	SO_NODE_HEADER(SoXipIntersectionPlane);


public:
	//! Constructor
	SoXipIntersectionPlane();

	//! Initializes this class (called on dll initialization).
	static void  initClass();

	// This implements the GL rendering action.
	virtual void  GLRender(SoGLRenderAction *action);

	// Generates triangles representing a pyramid.
	virtual void generatePrimitives(SoAction *action){}

	// This computes the bounding box
	virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);


	//! possible rendering parts of the box
	enum renderingParts {
		ALL    = 0x01,
		FRONT   = 0x02,
		BACK = 0x03
	};

	//@{! Fields

	//! input field which should contain the box to calculate intersection with 
	SoSFMatrix boundingBox;

	//! input field which should contain the plane to render
	SoSFPlane plane;

	//! rendering parts of the plane
	SoSFEnum parts;

	//! to activate or no the rendering 
	SoSFBool on;
	//@}


protected:
	//! Protected destructor
	virtual ~SoXipIntersectionPlane();

	//! calculate the plane intersection points with the input cube
	void calculateCubeIntersection(bool boxChanged);

	//! called to calculated visible part of the intersection plane
	//! and add the correct index to the corsseponding IndexedLineSet
	void calculateVisibleParts(SoState *state);

private:
	//! list used to store the calculated intersection points before rendering
	std::vector<SbVec3f> mFaceNormals;

	//! table used to store the intersection points
	SbVec3f mTabVec[IBOX_NUM_POINTS];

	//! table used to store the lines indexes
	int mTabIndex[IBOX_NUM_INDEXES];

	//! original bousing box without matrix transformation
	SbVec3f mBoundingBox[8];

	//! bousing box after matrix transformation
	SbVec3f mTransBoundingBox[8];

	// pointer on the coordinate node used to draw the lines
	SoCoordinate3 *pCoordinates;

	// pointer on the lineSet node used to draw the lines
	SoIndexedLineSet *pLines;

	// minimum coordinate of the box 
	SbVec3f mMinBox;

	// maximum coordinate of the box
	SbVec3f mMaxBox;

	// cached plane
	SbPlane mCachedPlane;

	// cached bounding box
	SbMatrix mCachedBBox;

	//! calculate the  intersection point between a plane and a line
	bool calculateLineIntersection(const SbPlane & plane, const SbVec3f &pA, const SbVec3f &pB, SbVec3f &res);

	//! get the normal of a face giving 3 points of it
	SbVec3f getNormal(const SbVec3f &p1, const SbVec3f &p2, const SbVec3f &p3);

	//!call to update the bounding box with the new transformation matrix
	bool updateBoundingBox();
};

#endif // SOXIPINTERSECTIONPLANE_H

