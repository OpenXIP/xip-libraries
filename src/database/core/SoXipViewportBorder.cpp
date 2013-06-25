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

#include "SoXipViewportBorder.h"
#include <Inventor/elements/SoViewportRegionElement.h>
#include <xip/inventor/core/SoXipActiveViewportElement.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/sensors/SoTimerSensor.h>
#include <xip/inventor/core/SoXipCursor.h>
#include <xip/system/GL/gl.h>
#include <algorithm>

SO_NODE_SOURCE(SoXipViewportBorder);


void SoXipViewportBorder::initClass()
{
	SO_NODE_INIT_CLASS(SoXipViewportBorder, SoNode, "Node");

	SO_ENABLE(SoGLRenderAction, SoXipActiveViewportElement);
}

SoXipViewportBorder::SoXipViewportBorder()
{
	SO_NODE_CONSTRUCTOR(SoXipViewportBorder);

	SO_NODE_ADD_FIELD(activeColor, (SbColor(0.6f, 0.6f, 0.6f)));
	SO_NODE_ADD_FIELD(activeLineWidth, (3.f));
	SO_NODE_ADD_FIELD(activeLinePattern, (0xffff));

	SO_NODE_ADD_FIELD(inactiveColor, (SbColor(0.4f, 0.4f, 0.4f)));
	SO_NODE_ADD_FIELD(inactiveLineWidth, (1.f));
	SO_NODE_ADD_FIELD(inactiveLinePattern, (0xffff));
}

SoXipViewportBorder::~SoXipViewportBorder()
{
}

void SoXipViewportBorder::GLRender(SoGLRenderAction * action)
{
	SbViewportRegion viewportRegion = SoViewportRegionElement::get( action->getState() );
	SbVec2s s = viewportRegion.getViewportSizePixels();

	double oldLineWidth = 1.0;
	glGetDoublev(GL_LINE_WIDTH, &oldLineWidth);

	glPushAttrib(GL_TRANSFORM_BIT | GL_ENABLE_BIT | GL_LINE_BIT | GL_CURRENT_BIT);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);
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
	unsigned short pattern;
	float lineWidth;
	SbColor color;

	if (SoXipActiveViewportElement::get(action->getState()))
	{
		pattern = activeLinePattern.getValue();
		lineWidth = activeLineWidth.getValue();
		color = activeColor.getValue();
	}
	else
	{
		pattern = inactiveLinePattern.getValue();
		lineWidth = inactiveLineWidth.getValue();
		color = inactiveColor.getValue();
	}

	if (lineWidth <= 0) return;

	glColor3f(color[0], color[1], color[2]);
	glLineStipple(1, pattern);
	glEnable(GL_LINE_STIPPLE);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, s[0], 0, s[1], -1, 1);

	// cast to int to avoid compiler warnings	
	int iLineWidth = static_cast<int>(lineWidth);
	int iLineWidth05 = static_cast<int>(lineWidth+0.5f);

	if (pattern == 0xffff)
	{
		// draw solid blocks
		// Note that on some graphics card GL_LINE_LOOP does not look good for thicker lines
		// (first/last corner not filled). This is why we use GL_QUADS instead.
		glBegin(GL_QUADS);

		glVertex2i(0, 0);
		glVertex2i(iLineWidth, 0);
		glVertex2i(iLineWidth, s[1]);
		glVertex2i(0, s[1]);

		glVertex2i(0, 0);
		glVertex2i(s[0], 0);
		glVertex2i(s[0], iLineWidth);
		glVertex2i(0, iLineWidth);

		glVertex2i(s[0] - iLineWidth, 0);
		glVertex2i(s[0], 0);
		glVertex2i(s[0], s[1]);
		glVertex2i(s[0] - iLineWidth, s[1]);

		glVertex2i(0, s[1] - iLineWidth);
		glVertex2i(s[0], s[1] - iLineWidth);
		glVertex2i(s[0], s[1]);
		glVertex2i(0, s[1]);

		glEnd();
	}
	else
	{
		// draw stippled line
		glLineWidth(lineWidth);
		lineWidth /= 2.f;
		
		glBegin(GL_LINES);

		glVertex2i(iLineWidth, 0 + iLineWidth);
		glVertex2i(s[0] - iLineWidth + 1, 0 + iLineWidth);

		glVertex2i(iLineWidth, s[1] - iLineWidth);
		glVertex2i(s[0] - iLineWidth + 1, s[1] - iLineWidth);

		glVertex2i(s[0] - iLineWidth05, s[1] - iLineWidth);
		glVertex2i(s[0] - iLineWidth05, iLineWidth);

		glVertex2i(iLineWidth05, s[1] - iLineWidth);
		glVertex2i(iLineWidth05, iLineWidth);

		glEnd();
	}


	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	glLineWidth(oldLineWidth);

	glPopAttrib();
}



