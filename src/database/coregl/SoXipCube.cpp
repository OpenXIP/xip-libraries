#include <xip/system/standard.h>
#include "SoXipCube.h"

#ifdef NEW_SHAPE_IMPLEMENTATION

#include <Inventor/SbBox.h>
#include <Inventor/SoPrimitiveVertex.h>

SO_NODE_SOURCE(SoXipCube);

SoXipCube::SoXipCube() {
	SO_NODE_CONSTRUCTOR(SoXipCube);

	SO_NODE_ADD_FIELD(scale, (SbVec3f(1, 1, 1)));
	SO_NODE_ADD_FIELD(offset, (SbVec3f(-0.5, -0.5, -0.5)));
	SO_NODE_ADD_FIELD(culling, (NONE));

	SO_NODE_DEFINE_ENUM_VALUE(Culling, NONE);
	SO_NODE_DEFINE_ENUM_VALUE(Culling, FRONT);
	SO_NODE_DEFINE_ENUM_VALUE(Culling, BACK);
	SO_NODE_SET_SF_ENUM_TYPE(culling, Culling);
}

void SoXipCube::initClass() {
	SO_NODE_INIT_CLASS(SoXipCube, SoNode, "SoNode");
}

void SoXipCube::generatePrimitives(SoAction* action)
{
	SbVec3f vertices[8] = {
		SbVec3f(0.0, 0.0, 0.0),
		SbVec3f(1.0, 0.0, 0.0),
		SbVec3f(0.0, 1.0, 0.0),
		SbVec3f(1.0, 1.0, 0.0),
		SbVec3f(0.0, 0.0, 1.0),
		SbVec3f(1.0, 0.0, 1.0),
		SbVec3f(0.0, 1.0, 1.0),
		SbVec3f(1.0, 1.0, 1.0),
	};
    
	int indices[24] = {0, 2, 3, 1, 4, 5, 7, 6, 0, 1, 5, 4, 2, 6, 7, 3, 0, 4, 6, 2, 1, 3, 7, 5};
	const SbVec3f vScale = scale.getValue();
	const SbVec3f vOffset = offset.getValue();

	SbVec4f tVertices[8];
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 3; j++)
            tVertices[i][j] = (vertices[i][j] + vOffset[j]) * vScale[j];
    for (int i = 0; i < 8; i++)
        tVertices[i][3] = 1.0;

    SoPrimitiveVertex pv;

	for (int i = 0; i < 6; i++)
    {
        beginShape(action, TRIANGLE_FAN);
        for (int j = 0; j < 4; j++)
        {
            int ind = i * 4 + j;
            pv.setPoint(vertices[indices[ind]]);
            pv.setTextureCoords(tVertices[indices[ind]]);
            shapeVertex(&pv);
        }
        endShape();
	}

}

void SoXipCube::computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center)
{
    box.makeEmpty();

	SbVec3f vertices[8] = {
		SbVec3f(0.0, 0.0, 0.0),
		SbVec3f(1.0, 0.0, 0.0),
		SbVec3f(0.0, 1.0, 0.0),
		SbVec3f(1.0, 1.0, 0.0),
		SbVec3f(0.0, 0.0, 1.0),
		SbVec3f(1.0, 0.0, 1.0),
		SbVec3f(0.0, 1.0, 1.0),
		SbVec3f(1.0, 1.0, 1.0),
	};

	SbVec3f tVertices[8];

	int indices[24] = {0, 2, 3, 1, 4, 5, 7, 6, 0, 1, 5, 4, 2, 6, 7, 3, 0, 4, 6, 2, 1, 3, 7, 5};
	const SbVec3f vScale = scale.getValue();
	const SbVec3f vOffset = offset.getValue();

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 3; j++)
            tVertices[i][j] = (vertices[i][j] + vOffset[j]) * vScale[j];

	for (int i = 0; i < 8; i++)
        box.extendBy(tVertices[i]);
}

void SoXipCube::GLRender(SoGLRenderAction* action)
{
	//doAction(action);
    doAction();
}

void SoXipCube::doAction()
{
	SbVec3f vertices[8] = {
		SbVec3f(0.0, 0.0, 0.0),
		SbVec3f(1.0, 0.0, 0.0),
		SbVec3f(0.0, 1.0, 0.0),
		SbVec3f(1.0, 1.0, 0.0),
		SbVec3f(0.0, 0.0, 1.0),
		SbVec3f(1.0, 0.0, 1.0),
		SbVec3f(0.0, 1.0, 1.0),
		SbVec3f(1.0, 1.0, 1.0),
	};

	SbVec3f tVertices[8];

	int indices[24] = {0, 2, 3, 1,
                       4, 5, 7, 6,
                       0, 1, 5, 4,
                       2, 6, 7, 3,
                       0, 4, 6, 2,
                       1, 3, 7, 5};

	GLenum cullFace = culling.getValue();

	if (cullFace) {
		glPushAttrib(GL_ENABLE_BIT);
		glEnable(GL_CULL_FACE);
		glCullFace(cullFace);
	}

	const SbVec3f vScale = scale.getValue();
	const SbVec3f vOffset = offset.getValue();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			tVertices[i][j] = (vertices[i][j] + vOffset[j]) * vScale[j];
		}
	}

	glBegin(GL_QUADS);
	for (int i = 0; i < 24; i++)
    {
		glTexCoord3fv(&vertices[indices[i]][0]);
		glVertex3fv(&tVertices[indices[i]][0]);
	}
	glEnd();

	if (cullFace) {
		glPopAttrib();
	}
}






#else

SO_NODE_SOURCE(SoXipCube);

SoXipCube::SoXipCube() {
	SO_NODE_CONSTRUCTOR(SoXipCube);

	SO_NODE_ADD_FIELD(scale, (SbVec3f(1, 1, 1)));
	SO_NODE_ADD_FIELD(offset, (SbVec3f(-0.5, -0.5, -0.5)));
	SO_NODE_ADD_FIELD(culling, (NONE));

	SO_NODE_DEFINE_ENUM_VALUE(Culling, NONE);
	SO_NODE_DEFINE_ENUM_VALUE(Culling, FRONT);
	SO_NODE_DEFINE_ENUM_VALUE(Culling, BACK);
	SO_NODE_SET_SF_ENUM_TYPE(culling, Culling);
}

void SoXipCube::initClass() {
	SO_NODE_INIT_CLASS(SoXipCube, SoNode, "SoNode");
}

void SoXipCube::GLRender(SoGLRenderAction* action) {
	SbVec3f vertices[8] = {
		SbVec3f(0, 0, 0),
		SbVec3f(1, 0, 0),
		SbVec3f(0, 1, 0),
		SbVec3f(1, 1, 0),
		SbVec3f(0, 0, 1),
		SbVec3f(1, 0, 1),
		SbVec3f(0, 1, 1),
		SbVec3f(1, 1, 1),
	};

	SbVec3f tVertices[8];

	int indices[24] = {0, 2, 3, 1, 4, 5, 7, 6, 0, 1, 5, 4, 2, 6, 7, 3, 0, 4, 6, 2, 1, 3, 7, 5};

	GLenum cullFace = culling.getValue();

	if (cullFace) {
		glPushAttrib(GL_ENABLE_BIT);
		glEnable(GL_CULL_FACE);
		glCullFace(cullFace);
	}

	const SbVec3f &vScale = scale.getValue();
	const SbVec3f &vOffset = offset.getValue();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 3; j++) {
			tVertices[i][j] = (vertices[i][j] + vOffset[j]) * vScale[j];
		}
	}

	glBegin(GL_QUADS);
	for (int i = 0; i < 24; i++) {
		glTexCoord3fv(&vertices[indices[i]][0]);
		glVertex3fv(&tVertices[indices[i]][0]);
	}
	glEnd();

	if (cullFace) {
		glPopAttrib();
	}
}

#endif


