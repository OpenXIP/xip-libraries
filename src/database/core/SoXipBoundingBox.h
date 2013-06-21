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
// \file    SoXipBoundingBox.h
// \author  Vivien Delage
// \date    2005-03-29
//
// Used to draw a bounding box englobing objects
*/
//----------------------------------------------------------------------------------

#ifndef SOXIPBOUNDINGBOX_H
#define SOXIPBOUNDINGBOX_H


//inventor includes
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoIndexedLineSet.h>


#define BBOX_NUM_FACES		6
#define BBOX_NUM_POINTS		30
#define BBOX_NUM_INDEXES	36



//! bounding box class
class SoXipBoundingBox : public SoShape
{
	//! Implements the runtime type system interface of this new node.
	SO_NODE_HEADER(SoXipBoundingBox);

public:
	//! Constructor
	SoXipBoundingBox();

	//! Initializes this class (called on dll initialization).
	static void  initClass();

   // This implements the GL rendering action.
   virtual void GLRender(SoGLRenderAction *action);

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

    //! on/off switch
    SoSFBool on;

	//! input field which should contain the boundingBox
	SoSFMatrix boundingBox;

	//! rendering parts of the box  
	SoSFEnum parts;

	//@}

protected:
	//! Protected destructor
	virtual ~SoXipBoundingBox();


	//! get the normal of a face giving 3 points of it
	SbVec3f getNormal(const SbVec3f &p1, const SbVec3f &p2, const SbVec3f &p3);

	//! called to calculated visible part of the intersection plane
	//! and add the correct index to the corsseponding IndexedLineSet
	void calculateVisibleParts(SoState *state);

	//! set the cube geometry into the coordinate3 node using the boundingbox input
	void setCubeGeometry();

	SoFieldSensor *mBoundingBoxSensor;


private:

	//! Normals of the cube faces
	SbVec3f mCubeNormals[BBOX_NUM_FACES];

	//! used to store one point of each cube face for computing purpose
	SbVec3f mCubeFirstPoint[BBOX_NUM_FACES];

	//! table table used to store the lines indexes
	int mTabIndex[BBOX_NUM_INDEXES];

	//! table used to store the box points
	SbVec3f mTabVec[BBOX_NUM_POINTS];	

	//! original bousing box without matrix transformation
	SbVec3f mBoundingBox[8];

	// pointer on the coordinate node used to draw the lines
	SoCoordinate3 *pCoordinates;

	// pointer on the lineSet node used to draw the lines
	SoIndexedLineSet *pLines;

	// minimum coordinate of the box 
	SbVec3f minBox;

	// maximum coordinate of the box
	SbVec3f maxBox;

	static void fieldSensorCBFunc(void *, SoSensor *);
};

#endif // SOXIPBOUNDINGBOX_H

