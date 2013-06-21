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
#include <xip/system/standard.h>
#include <xip/system/GL/gl.h>
#include <algorithm>

#include "SoXipOrientationCube.h"

#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/SbLinear.h>
#include <xip/system/GL/gl.h>


///////////////////////////////////////////////////////////////////////

#define IS_FACE(v, x, y, z)	((v[0] * x + v[1] * y + v[2] * z) > -0.00001)


static void drawGLLetter(char letter)
{
    const double myScale = 0.5;

    glPushMatrix();

    switch(letter)
    {
    case 'F':
        glScaled(myScale * 0.6, myScale, myScale);
        glBegin(GL_LINES);
        glVertex3d( -0.7, -0.7, -1.0);
        glVertex3d(  0.7, -0.7, -1.0);
        glVertex3d( -0.7, -0.7, -1.0);
        glVertex3d( -0.7,  0.7, -1.0);
        glVertex3d( -0.7,  0.0, -1.0);
        glVertex3d(  0.2,  0.0, -1.0);
        glEnd();
        break;

    case 'H':
        glScaled(myScale * 0.6, myScale, myScale);
        glBegin(GL_LINES);
        glVertex3d( 0.7, 0.7,  1.0);
        glVertex3d( 0.7, -0.7, 1.0);
        glVertex3d(-0.7, 0.7,   1.0 );
        glVertex3d(-0.7, -0.7, 1.0 );
        glVertex3d(-0.7, 0.0, 1.0);
        glVertex3d( 0.7 ,  0.0, 1.0);
        glVertex3d( -0.7, 0.7,  1.0);
        glVertex3d( -1.1, 0.7, 1.0);
        glEnd();
        break;

    case 'L':
        glScaled(myScale, myScale * 0.6, myScale);
        glRotated(90, 1, 0, 0);
        glBegin(GL_LINES);
        glVertex3d( 1.0 ,  0.7 , 0.7 );
        glVertex3d( 1.0 , -0.7 , 0.7 );		
        glVertex3d( 1.0 , -0.7 , 0.7 );
        glVertex3d( 1.0 , -0.7 , -0.7 );		
        glEnd();
        break;

    case 'R':
        glScaled(myScale, myScale * 0.6, myScale);
        glRotated(90, 1, 0, 0);
        glBegin(GL_LINES);
        glVertex3d( -1.0 , 0.7 ,  -0.7 );
        glVertex3d( -1.0 , 0.7 , 0.0);
        glVertex3d( -1.0 , 0.0,  -0.7 );
        glVertex3d( -1.0 , 0.0, 0.0);
        glVertex3d( -1.0 , 0.7 , -0.7 );
        glVertex3d( -1.0 , -0.7 , -0.7 );
        glVertex3d( -1.0 , 0.0, -0.7 );
        glVertex3d( -1.0 , -0.7 , 0.7 );
        glEnd();

        //Semi circle for completion //
        // Needs improvement
        glBegin(GL_LINE_STRIP);
        glNormal3d( -1.0,  0.0,  0.0);
        glVertex3d( -1.0 , 0.7 , 0.0);
        glVertex3d( -1.0 , 0.6 , 0.35 );
        glVertex3d( -1.0 , 0.45 , 0.6 );
        glVertex3d( -1.0 , 0.35 , 0.7 );
        glVertex3d( -1.0 , 0.25 , 0.6 );
        glVertex3d( -1.0 , 0.10 , 0.35 );
        glVertex3d( -1.0 , 0.0, 0.0);		
        glEnd();
        break;

    case 'A':
        glScaled(0.6 * myScale, myScale, myScale);
        glRotated(180, 0, 1, 0);
        glBegin(GL_LINES);
        glVertex3d( 0.0 , -1.0 ,  -0.7 );
        glVertex3d( -0.7 , -1.0 , 0.7 );		
        glVertex3d( 0.0, -1.0 ,  -0.7 );
        glVertex3d( 0.7 , -1.0 , 0.7 );		
        glVertex3d(  -.35 , -1.0 , -0.0 );
        glVertex3d(  0.35 ,  -1.0 , -0.0);		
        glEnd();
        break;

    case 'P':
        glScaled(myScale * 0.6, myScale, myScale);
        glRotated(-90, 0, 1, 0);
        glBegin(GL_LINE_STRIP);
        glVertex3d(  0.7 , 1.0 , 0.0);
        glVertex3d(  0.6 , 1.0 , 0.35 );
        glVertex3d(  0.45 , 1.0 , 0.6 );
        glVertex3d(  0.35 , 1.0 , 0.7 );
        glVertex3d(  0.25 , 1.0 , 0.6 );
        glVertex3d(  0.10 , 1.0 , 0.35 );
        glVertex3d(  0.0, 1.0 , 0.0);		
        glEnd();

        glBegin(GL_LINES);
        glVertex3d( -0.7 , 1.0 ,  -0.7 );
        glVertex3d(  0.7 , 1.0 ,  -0.7 );		
        glVertex3d(  0.7 , 1.0 , 0.0 );
        glVertex3d(  0.7 , 1.0 ,  -0.7 );		
        glVertex3d(  0.0 , 1.0 , 0.0 );
        glVertex3d(  0.0 , 1.0 ,  -0.7 );		
        glEnd();
        break;
    }

    glPopMatrix();
}


static void drawLetterBoundingBox(const SbRotation &rot, bool front, int primitive, int side, int letters)
{
    double tmp;
    double norm[3];

    // half lengths are used here
    double width = .5;
    double height = .5;
    double depth = .5;

    // read rotation
    SbMatrix rotMat;
    rotMat.setRotate(rot.inverse());

    norm[0] = rotMat[2][0];
    norm[1] = rotMat[2][1];
    norm[2] = rotMat[2][2];

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

	SO_NODE_DEFINE_ENUM_VALUE(orientationType, FEET);
	SO_NODE_DEFINE_ENUM_VALUE(orientationType, HEAD);
	SO_NODE_DEFINE_ENUM_VALUE(orientationType, LEFT);
	SO_NODE_DEFINE_ENUM_VALUE(orientationType, RIGHT);
	SO_NODE_DEFINE_ENUM_VALUE(orientationType, ANTERIOR);
	SO_NODE_DEFINE_ENUM_VALUE(orientationType, POSTERIOR);

	SO_NODE_ADD_FIELD(size, (0.15f));
	SO_NODE_ADD_FIELD(position, (SbVec2f(0.7f, -0.7f)));

	SO_NODE_SET_SF_ENUM_TYPE(orientation, orientationType);
	SO_NODE_ADD_FIELD(orientation, (FEET));
}


SoXipOrientationCube::~SoXipOrientationCube()
{
}


void SoXipOrientationCube::GLRender(SoGLRenderAction * action)
{
    SbViewportRegion viewportRegion = SoViewportRegionElement::get(action->getState());
    SbVec2s s = viewportRegion.getViewportSizePixels();

    glPushAttrib(GL_TRANSFORM_BIT | GL_ENABLE_BIT | GL_LINE_BIT | GL_CURRENT_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_ALPHA_TEST);

    if (glIsEnabled(GL_LINE_SMOOTH) && !glIsEnabled(GL_BLEND))
    {
        // blending must be enabled in order for line smoothing to work
        glEnable(GL_BLEND);
    }

#if 0
    // disable clip planes
    int maxClipPlanes;
    glGetIntegerv(GL_MAX_CLIP_PLANES, &maxClipPlanes);
	maxClipPlanes = std::min(maxClipPlanes, 16);
    for (int i = 0; i < maxClipPlanes; i++)
    {
        glDisable(GL_CLIP_PLANE0 + i);
    }
#endif

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glLineWidth(1);
    glDisable(GL_LINE_STIPPLE);
    glColor3f(0.75f, 0.75f, 0.2f);

    float aspectRatio = viewportRegion.getViewportAspectRatio();
    SbVec2f trans = getTranslation(aspectRatio);
    glTranslatef(trans[0], trans[1], 0.f);

    SbVec3f scale = getScale(aspectRatio);
    glScalef(scale[0], scale[1], scale[2]);

    drawLetterBoundingBox(getRotation(action), true, GL_LINE_LOOP, 7, true);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);

    glPopAttrib();
}




void SoXipOrientationCube::handleEvent(SoHandleEventAction *action)
{
	if (SO_MOUSE_RELEASE_EVENT(action->getEvent(), BUTTON1))
	{
		orientationType picked = getPickedSide(action);

		if (picked != -1)
		{
			orientation.setValue(picked);
		}
	}
}


SoXipOrientationCube::orientationType SoXipOrientationCube::getPickedSide(SoHandleEventAction *action)
{
	orientationType sides[] = { RIGHT, ANTERIOR , FEET, LEFT, POSTERIOR , HEAD };

	SbViewportRegion viewportRegion = SoViewportRegionElement::get(action->getState());
	float aspectRatio = viewportRegion.getViewportAspectRatio();

	// screen to ogl
	SbVec2f pos = action->getEvent()->getNormalizedPosition(viewportRegion);
	pos -= SbVec2f(0.5f, 0.5f);
	pos *= 2.f;

	// placement of cube
	pos -= getTranslation(aspectRatio);

	// adjust for viewport aspect ratio
	if (aspectRatio > 1.0)
		pos[0] *= aspectRatio;
	else
		pos[1] /= aspectRatio;


	// transform ray points into object space
	SbMatrix m;
	m.setRotate(getRotation(action).inverse());
	SbVec3f projDir = m[2];

	SbVec3f p1(pos[0], pos[1], -2), p1t;
	SbVec3f p2(pos[0], pos[1], 2), p2t;

	m.multVecMatrix(p1, p1t);
	m.multVecMatrix(p2, p2t);

	SbLine ray(p1t, p2t);
	float length = 0.5f * size.getValue();

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			SbVec3f norm(0, 0, 0);
			norm[i] = j ? 1.f : -1.f;

			SbPlane plane(norm, length);
			SbVec3f pt;

			if (IS_FACE(projDir, norm[0], norm[1], norm[2]) && plane.intersect(ray, pt))
			{
				int ca = (i + 1) % 3, cb = (i + 2) % 3;

				if ((pt[ca] >= -length) && (pt[ca] <= length) && (pt[cb] >= -length) && (pt[cb] <= length))
				{
					return sides[(j * 3) + i];
				}
			}
		}
	}

	return (orientationType) -1;
}


SbVec2f SoXipOrientationCube::getTranslation(float aspectRatio) const
{
	float x = position.getValue()[0], y = position.getValue()[1];

	if (aspectRatio >= 1.f)
	{
		if (x > 0.5f)  // dock right
			x = 1.f - ((1.f - x) / aspectRatio);
		else if (x < -0.5f)	 // dock left
			x = -1.f + ((1.f + x) / aspectRatio);
	}
	else
	{
		if (y > 0.5f)  // dock top
			y = 1.f - ((1.f - y) * aspectRatio);
		else if (y < -0.5f)  // dock bottom
			y = -1.f + ((1.f + y) * aspectRatio);
	}

	return SbVec2f(x, y);
}


SbVec3f SoXipOrientationCube::getScale(float aspectRatio) const
{
	float s = size.getValue();
	
	if (aspectRatio < 1.0)
		s *= aspectRatio;

	return SbVec3f(s / aspectRatio, s, s);
}


SbRotation SoXipOrientationCube::getRotation(SoAction *action) const
{
	SbViewVolume vVol = SoViewVolumeElement::get(action->getState());
	SbMatrix affine, proj;
	vVol.getMatrices(affine, proj);

	SbVec3f trans, scale;
	SbRotation rot, so;
	affine.getTransform(trans, rot, scale, so);

	return rot;
}
