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


#include "SoXipBoundingBox.h"
#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <xip/system/GL/gl.h>
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