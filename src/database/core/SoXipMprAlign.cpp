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
