
#include <xip/system/GL/gl.h>

#include "SoXipBackground.h"
#include <Inventor/actions/SoActions.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>



SO_NODE_SOURCE(SoXipBackground);


void SoXipBackground::initClass()
{
	SO_NODE_INIT_CLASS(SoXipBackground, SoNode, "Node");
}


SoXipBackground::SoXipBackground()
{
	SO_NODE_CONSTRUCTOR(SoXipBackground);

	SO_NODE_ADD_FIELD(color, (SbColor(0, 0, 0)));
	color.set("[ 0 0 0, 0 0 0, 0.5 0.5 0.5, 0.5 0.5 0.5 ]");

	SO_NODE_ADD_FIELD(alpha, (1));
	alpha.set("[ 1 , 1 , 1, 1 ]");
}


SoXipBackground::~SoXipBackground()
{
}


void SoXipBackground::GLRender(SoGLRenderAction *action)
{
	if (color.getNum() <= 0) return;
	if (!action) return;

	// do nothing if in delayed path
	if (action->isRenderingDelayedPaths()) return;

	glPushAttrib(GL_ENABLE_BIT);

	// do not write depth buffer values, do not use shading, do not perform depth test or blending
	GLboolean depthMask;
	glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMask);
	glDepthMask(FALSE);

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	// make sure we always have 4 colors in the list
	const SbColor *colors = color.getValues(0);
	SbColor tmpColors[4];
	float tmpAlphas[4];
	for (int i = 0; i < 4; i++){
		tmpColors[i] = (i < color.getNum()) ? colors[i] : colors[color.getNum() - 1];
		tmpAlphas[i] = (i < alpha.getNum()) ? alpha[i] : alpha[alpha.getNum() - 1];

	}

	glBegin(GL_QUADS);
	glColor4f(tmpColors[0][0], tmpColors[0][1], tmpColors[0][2], alpha[0]);
	glVertex2i(-1, -1);

	glColor4f(tmpColors[1][0], tmpColors[1][1], tmpColors[1][2], alpha[1]);
	glVertex2i(1, -1);

	glColor4f(tmpColors[2][0], tmpColors[2][1], tmpColors[2][2], alpha[2]);
	glVertex2i(1, 1);

	glColor4f(tmpColors[3][0], tmpColors[3][1], tmpColors[3][2], alpha[3]);
	glVertex2i(-1, 1);
	glEnd();

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDepthMask(depthMask);

	glPopAttrib();
}


