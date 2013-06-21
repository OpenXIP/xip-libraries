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
#include "SoXipDrawQuad.h"

SO_NODE_SOURCE(SoXipDrawQuad);

SoXipDrawQuad::SoXipDrawQuad() {
	SO_NODE_CONSTRUCTOR(SoXipDrawQuad);

	SO_NODE_ADD_FIELD(enableTexture, (true));
	SO_NODE_ADD_FIELD(filter, (SAME));
	SO_NODE_ADD_FIELD(blend, (false));
	SO_NODE_ADD_FIELD(colors, (SbVec3f(1, 1, 1)));

	SO_NODE_DEFINE_ENUM_VALUE(Filter, SAME);
	SO_NODE_DEFINE_ENUM_VALUE(Filter, NEAREST);
	SO_NODE_DEFINE_ENUM_VALUE(Filter, LINEAR);
	SO_NODE_SET_SF_ENUM_TYPE(filter, Filter);
}

void SoXipDrawQuad::initClass() {
	SO_NODE_INIT_CLASS(SoXipDrawQuad, SoNode, "SoNode");
}

void SoXipDrawQuad::GLRender(SoGLRenderAction* action) {
	glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
	glDisable(GL_LIGHTING);

	if (blend.getValue()) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
	}

	if (enableTexture.getValue()) {
		glEnable(GL_TEXTURE_2D);
	}

	GLint minFilter, magFilter;

	GLint texFilter = filter.getValue();

	if (texFilter != SAME) {
		glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, &minFilter);
		glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, &magFilter);

		if (texFilter != minFilter)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texFilter);

		if (texFilter != magFilter)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texFilter);
	}

    SbVec3f cornerColors[4];
	const SbVec3f *pColors = colors.getValues(0);
	if (colors.getNum() >= 4) {
		cornerColors[0] = pColors[0];
		cornerColors[1] = pColors[1];
		cornerColors[2] = pColors[2];
		cornerColors[3] = pColors[3];
	}
	else if (colors.getNum() >= 2) {
		cornerColors[0] = pColors[0];
		cornerColors[1] = pColors[0];
		cornerColors[2] = pColors[1];
		cornerColors[3] = pColors[1];
	}
	else if (colors.getNum() == 1) {
		cornerColors[0] = pColors[0];
		cornerColors[1] = pColors[0];
		cornerColors[2] = pColors[0];
		cornerColors[3] = pColors[0];
	}
    else {
        cornerColors[0] = SbVec3f(0.0, 0.0, 0.0);
		cornerColors[1] = SbVec3f(0.0, 0.0, 0.0);
		cornerColors[2] = SbVec3f(0.0, 0.0, 0.0);
		cornerColors[3] = SbVec3f(0.0, 0.0, 0.0);
    }

	glBegin(GL_TRIANGLE_STRIP);
	glColor3fv(&(cornerColors[0][0]));
	glTexCoord2f(0, 0);
	glVertex3f(-1, -1, 0);
	glColor3fv(&(cornerColors[1][0]));
	glTexCoord2f(1, 0);
	glVertex3f(1, -1, 0);
	glColor3fv(&(cornerColors[2][0]));
	glTexCoord2f(0, 1);
	glVertex3f(-1, 1, 0);
	glColor3fv(&(cornerColors[3][0]));
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, 0);
	glEnd();

	if (texFilter != SAME) {
		if (texFilter != minFilter)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);

		if (texFilter != magFilter)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	}

	glPopAttrib();
}


