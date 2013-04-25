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
#include <xip/system/standard.h>
#include <xip/system/GL/gl.h>
#include <algorithm>

#include "SoXipOrientationCube.h"

#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/SbLinear.h>

///////////////////////////////////////////////////////////////////////

#define IS_FACE(v, x, y, z)	((v[0] * x + v[1] * y + v[2] * z) > -0.00001)


static void drawGLLetter(char letter)
{
	const double myScale = 0.5;

	glPushMatrix();

	switch(letter)
	{
	case 'F':
		glScaled(0.6, 1.0, 1.0);
		glBegin(GL_LINES);
			glVertex3d( -0.7 * myScale, -0.7 * myScale, -1.0 * myScale);
			glVertex3d(  0.7 * myScale, -0.7 * myScale, -1.0 * myScale);
			glVertex3d( -0.7 * myScale, -0.7 * myScale, -1.0 * myScale);
			glVertex3d( -0.7 * myScale,  0.7 * myScale, -1.0 * myScale);
			glVertex3d( -0.7 * myScale,  0.0 * myScale, -1.0 * myScale);
			glVertex3d(  0.2 * myScale,  0.0 * myScale, -1.0 * myScale);
		glEnd();
	break;

	case 'H':
		glScaled(0.6, 1.0, 1.0);
		glBegin(GL_LINES);
 		    glVertex3d( 0.7 * myScale, 0.7 * myScale,  1.0 * myScale);
		    glVertex3d( 0.7 * myScale, -0.7 * myScale, 1.0 * myScale);
		    glVertex3d(-0.7 * myScale, 0.7 * myScale,   1.0 * myScale );
		    glVertex3d(-0.7 * myScale, -0.7 * myScale, 1.0 * myScale );
		    glVertex3d(-0.7 * myScale, 0.0, 1.0 * myScale);
		    glVertex3d( 0.7 * myScale ,  0.0, 1.0 * myScale);
 		    glVertex3d( -0.7 * myScale, 0.7 * myScale,  1.0 * myScale);
		    glVertex3d( -1.1 * myScale, 0.7 * myScale, 1.0 * myScale);
		glEnd();
	break;

	case 'L':
		glScaled(1.0, 0.6, 1.0);
		glRotated(90, 1, 0, 0);
		glBegin(GL_LINES);
 		    glVertex3d( 1.0 * myScale ,  0.7 * myScale , 0.7 * myScale );
		    glVertex3d( 1.0 * myScale , -0.7 * myScale , 0.7 * myScale );		
		    glVertex3d( 1.0 * myScale , -0.7 * myScale , 0.7 * myScale );
		    glVertex3d( 1.0 * myScale , -0.7 * myScale , -0.7 * myScale );		
		glEnd();
	break;

	case 'R':
		glScaled(1.0, 0.6, 1.0);
		glRotated(90, 1, 0, 0);
		glBegin(GL_LINES);
			glVertex3d( -1.0 * myScale , 0.7 * myScale ,  -0.7 * myScale );
			glVertex3d( -1.0 * myScale , 0.7 * myScale , 0.0);
			glVertex3d( -1.0 * myScale , 0.0,  -0.7 * myScale );
			glVertex3d( -1.0 * myScale , 0.0, 0.0);
			glVertex3d( -1.0 * myScale , 0.7 * myScale , -0.7 * myScale );
			glVertex3d( -1.0 * myScale , -0.7 * myScale , -0.7 * myScale );
			glVertex3d( -1.0 * myScale , 0.0, -0.7 * myScale );
			glVertex3d( -1.0 * myScale , -0.7 * myScale , 0.7 * myScale );
		glEnd();

		//Semi circle for completion //
		// Needs improvement
		glBegin(GL_LINE_STRIP);
			glNormal3d( -myScale,  0.0,  0.0);
			glVertex3d( -1.0 * myScale , 0.7 * myScale , 0.0);
			glVertex3d( -1.0 * myScale , 0.6 * myScale , 0.35 * myScale );
			glVertex3d( -1.0 * myScale , 0.45 * myScale , 0.6 * myScale );
			glVertex3d( -1.0 * myScale , 0.35 * myScale , 0.7 * myScale );
			glVertex3d( -1.0 * myScale , 0.25 * myScale , 0.6 * myScale );
			glVertex3d( -1.0 * myScale , 0.10 * myScale , 0.35 * myScale );
			glVertex3d( -1.0 * myScale , 0.0, 0.0);		
		glEnd();
	break;

	case 'A':
		glScaled(0.6, 1.0, 1.0);
		glRotated(180, 0, 1, 0);
		glBegin(GL_LINES);
			glVertex3d( 0.0 , -1.0 * myScale ,  -0.7 * myScale );
			glVertex3d( -0.7 * myScale , -1.0 * myScale , 0.7 * myScale );		
			glVertex3d( 0.0, -1.0 * myScale ,  -0.7 * myScale );
			glVertex3d( 0.7 * myScale , -1.0 * myScale , 0.7 * myScale );		
			glVertex3d(  -.35 * myScale , -1.0 * myScale , -0.0 * myScale );
			glVertex3d(  0.35 * myScale ,  -1.0 * myScale , -0.0);		
		glEnd();
	break;

	case 'P':
		glScaled(0.6, 1.0, 1.0);
		glRotated(-90, 0, 1, 0);
		glBegin(GL_LINE_STRIP);
			glVertex3d(  0.7 * myScale , 1.0 * myScale , 0.0);
			glVertex3d(  0.6 * myScale , 1.0 * myScale , 0.35 * myScale );
			glVertex3d(  0.45 * myScale , 1.0 * myScale , 0.6 * myScale );
			glVertex3d(  0.35 * myScale , 1.0 * myScale , 0.7 * myScale );
			glVertex3d(  0.25 * myScale , 1.0 * myScale , 0.6 * myScale );
			glVertex3d(  0.10 * myScale , 1.0 * myScale , 0.35 * myScale );
			glVertex3d(  0.0, 1.0 * myScale , 0.0);		
		glEnd();

		glBegin(GL_LINES);
			glVertex3d( -0.7 * myScale , 1.0 * myScale ,  -0.7 * myScale );
			glVertex3d(  0.7 * myScale , 1.0 * myScale ,  -0.7 * myScale );		
			glVertex3d(  0.7 * myScale , 1.0 * myScale , 0.0 * myScale );
			glVertex3d(  0.7 * myScale , 1.0 * myScale ,  -0.7 * myScale );		
			glVertex3d(  0.0 * myScale , 1.0 * myScale , 0.0 * myScale );
			glVertex3d(  0.0 * myScale , 1.0 * myScale ,  -0.7 * myScale );		
		glEnd();
	break;
	}

	glPopMatrix();
}


static void drawLetterBoundingBox(const SbRotation &rot, const SbVec3f &cameraOrientation, bool front, int primitive, int side, int letters)
{
	double tmp;
	double norm[3];

	// half lengths are used here
	double width = .5;
	double height = .5;
	double depth = .5;

	// read rotation
	norm[0] = -cameraOrientation[0];
	norm[1] = -cameraOrientation[1];
	norm[2] = -cameraOrientation[2];

	SbVec3f axis;
	float radians;
	rot.getValue(axis, radians);
	glRotatef(radians / static_cast<float>(M_PI) * 180.f, axis[0], axis[1], axis[2]);

	if (side & 1)
	{
		// top / bottom
		tmp = IS_FACE(norm, 0, 1, 0) == front ? height : -height;
		glBegin(primitive);
		glVertex3d(-width, tmp, -depth);
		glVertex3d(+width, tmp, -depth);
		glVertex3d(+width, tmp, +depth);
		glVertex3d(-width, tmp, +depth);
		glEnd();

		if (front && letters)
		{
			if (tmp == height)
			{
				drawGLLetter('P');
			}
			else
			{
				drawGLLetter('A');
			}
		}
	}

	if (side & 2)
	{
		// left / right
		tmp = IS_FACE(norm, 1, 0, 0) == front ? width : -width;
		glBegin(primitive);
		glVertex3d(tmp, -height, -depth);
		glVertex3d(tmp, +height, -depth);
		glVertex3d(tmp, +height, +depth);
		glVertex3d(tmp, -height, +depth);
		glEnd();

		if (front && letters)
		{
			if (tmp == width)
			{
				drawGLLetter('L');
			}
			else
			{
				drawGLLetter('R');
			}
		}
	}

	if (side & 4)
	{
		// rear / front
		tmp = IS_FACE(norm, 0, 0, 1) == front ? depth : -depth;
		glBegin(primitive);
		glVertex3d(-width, -height, tmp);
		glVertex3d(-width, +height, tmp);
		glVertex3d(+width, +height, tmp);
		glVertex3d(+width, -height, tmp);
		glEnd();

		if (front && letters)
		{
			if (tmp == depth)
			{
				drawGLLetter('H');
			}
			else
			{
				drawGLLetter('F');
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////





SO_NODE_SOURCE(SoXipOrientationCube);

void SoXipOrientationCube::initClass()
{
	SO_NODE_INIT_CLASS(SoXipOrientationCube, SoNode, "Node");
}

SoXipOrientationCube::SoXipOrientationCube()
{
	SO_NODE_CONSTRUCTOR(SoXipOrientationCube);
}

SoXipOrientationCube::~SoXipOrientationCube()
{
}

void SoXipOrientationCube::GLRender(SoGLRenderAction * action)
{
	int i;

	SbViewportRegion viewportRegion = SoViewportRegionElement::get(action->getState());
	SbVec2s s = viewportRegion.getViewportSizePixels();

	// get the camera orientation
	SbViewVolume vVol = SoViewVolumeElement::get(action->getState());

	SbMatrix affine, proj;
	SbVec3f trans, scale;
	SbRotation rot, so;

	vVol.getMatrices(affine, proj);
	affine.getTransform(trans, rot, scale, so);

	glPushAttrib(GL_TRANSFORM_BIT | GL_ENABLE_BIT | GL_LINE_BIT | GL_CURRENT_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);

	// disable clip planes
	int maxClipPlanes;
	glGetIntegerv(GL_MAX_CLIP_PLANES, &maxClipPlanes);
	maxClipPlanes = std::min(maxClipPlanes, 16);
	for (i = 0; i < maxClipPlanes; i++)
	{
		glDisable(GL_CLIP_PLANE0 + i);
	}

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glLineWidth(1);
	glDisable(GL_LINE_STIPPLE);
	glColor3f(0.75f, 0.75f, 0.2f);
	glTranslatef(0.7f, -0.7f, 0.0f);
	float aspectRatio = viewportRegion.getViewportAspectRatio();
	float cubeSize = 0.15f;
	if (aspectRatio < 1.0)
		cubeSize *= aspectRatio;

	glScalef(cubeSize / aspectRatio, cubeSize, cubeSize);
	drawLetterBoundingBox(rot, vVol.getProjectionDirection(), true, GL_LINE_LOOP, 7, true);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	glPopAttrib();
}



