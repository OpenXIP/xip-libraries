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
#include <xip/inventor/coregl/SoXipGlowElement.h>

#include "SoXipMprRender.h"
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbBox.h>
#include <assert.h>


SO_NODE_SOURCE(SoXipMprRender);


//////////////////////////////////////////////////////////////////////////////////////////
///
void SoXipMprRender::initClass()
{
	SO_NODE_INIT_CLASS(SoXipMprRender, SoShape, "Shape");
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
	SO_ENABLE(SoGLRenderAction, SoViewVolumeElement);
	SO_ENABLE(SoGLRenderAction, SoModelMatrixElement);
}

//////////////////////////////////////////////////////////////////////////////////////////
///
SoXipMprRender::SoXipMprRender()
{
	SO_NODE_CONSTRUCTOR(SoXipMprRender);

}


//////////////////////////////////////////////////////////////////////////////////////////
///
void SoXipMprRender::GLRender(SoGLRenderAction * action)
{
	SoState *state = action->getState();

	// Get corners
	SbVec3f	corners[4];
	SbViewVolume viewVolume = SoViewVolumeElement::get(state);
	float dist = viewVolume.getNearDist() + viewVolume.getDepth() * 0.5f;
	corners[0] = viewVolume.getPlanePoint(dist, SbVec2f(0, 0));
	corners[1] = viewVolume.getPlanePoint(dist, SbVec2f(1, 0));
	corners[2] = viewVolume.getPlanePoint(dist, SbVec2f(1, 1));
	corners[3] = viewVolume.getPlanePoint(dist, SbVec2f(0, 1));
	
	// Get bounding box span and start from model matrix
	SbMatrix modelMat = SoModelMatrixElement::get(state);
	SbVec3f wSpan, wStart;
	SbRotation dummy;
	modelMat.getTransform(wStart, dummy, wSpan, dummy);

	// Convert the corner points from worldspace to model space
	for (int i = 0; i < 4; ++i)
	{
		corners[i] -= wStart;
		corners[i][0] = (corners[i][0] / wSpan[0]);
		corners[i][1] = (corners[i][1] / wSpan[1]);
		corners[i][2] = (corners[i][2] / wSpan[2]);
	}
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();


	// Render mpr
	glBegin(GL_QUADS);
	glTexCoord3fv(corners[0].getValue());
	glVertex2f(-1, -1);
	glTexCoord3fv(corners[1].getValue());
    glVertex2f(1, -1);
	glTexCoord3fv(corners[2].getValue());
	glVertex2f(1, 1);
	glTexCoord3fv(corners[3].getValue());
	glVertex2f(-1, 1);
    glEnd();

	glPopMatrix();
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

//////////////////////////////////////////////////////////////////////////////////////////
void SoXipMprRender::computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center)
{
    center.setValue(0.5, 0.5, 0.5);
    box.setBounds(0, 0, 0, 1, 1, 1);
}

