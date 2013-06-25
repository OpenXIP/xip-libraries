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

#include <xip/system/GL/gl.h>

#include "SoXipQuad.h"
#include <xip/system/standard.h>

#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/actions/SoActions.h>

#include <Inventor/elements/SoTextureCoordinateElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>


SO_NODE_SOURCE(SoXipQuad);

SoXipQuad::SoXipQuad()
{
    SO_NODE_CONSTRUCTOR(SoXipQuad);

    SO_NODE_ADD_FIELD(offset, (SbVec3f(0.0, 0.0, 0.0)));
}

void SoXipQuad::initClass()
{
    if (SoShape::getClassTypeId() == SoType::badType())
    {
        SoShape::initClass();
    }

    SO_NODE_INIT_CLASS(SoXipQuad, SoShape, "Shape");

    SO_ENABLE(SoGLRenderAction,       SoTextureCoordinateElement);
    SO_ENABLE(SoPickAction,           SoTextureCoordinateElement);
    SO_ENABLE(SoCallbackAction,       SoTextureCoordinateElement);
    SO_ENABLE(SoGetBoundingBoxAction, SoTextureCoordinateElement);
    SO_ENABLE(SoGLRenderAction,       SoGLTextureEnabledElement);
}

void SoXipQuad::GLRender(SoGLRenderAction* action)
{
    if (!shouldGLRender(action))
        return;

    SoState * state = action->getState();

    state->push();

    SoShape::GLRender(action);

    state->pop();
}

void SoXipQuad::generatePrimitives(SoAction *action)
{
    SoPrimitiveVertex pv;
    SoState *state = action->getState();
    SbBool useTexFunc =
        (SoTextureCoordinateElement::getType(state) ==
         SoTextureCoordinateElement::FUNCTION);

    const SoTextureCoordinateElement *tce = 0;
    SbVec4f texCoord;

    if (useTexFunc) {
        tce = SoTextureCoordinateElement::getInstance(state);
    }
    else {
        texCoord[2] = 0.0;
        texCoord[3] = 1.0;
    }

    SbVec3f point;
    SbVec3f off = offset.getValue();
    SbVec3f normal;
    normal.setValue(0.0, 0.0, 1.0);

#define GEN_VERTEX(pv, x, y, z, s, t, normal)   \
    point.setValue(x, y, z);                    \
    if (useTexFunc && tce)                      \
        texCoord = tce->get(point, normal);     \
    else {                                      \
        texCoord[0] = s; texCoord[1] = t;       \
    }                                           \
    pv.setPoint(point);                         \
    pv.setNormal(normal);                       \
    pv.setTextureCoords(texCoord);              \
    shapeVertex(&pv);

    // generate quad
    beginShape(action, TRIANGLE_FAN);
    GEN_VERTEX(pv,  0.0 + off[0],  0.0 + off[1], 0.0 + off[2],  0.0, 0.0, normal);
    GEN_VERTEX(pv,  1.0 + off[0],  0.0 + off[1], 0.0 + off[2],  1.0, 0.0, normal);
    GEN_VERTEX(pv,  1.0 + off[0],  1.0 + off[1], 0.0 + off[2],  1.0, 1.0, normal);
    GEN_VERTEX(pv,  0.0 + off[0],  1.0 + off[1], 0.0 + off[2],  0.0, 1.0, normal);
    endShape();
}

void SoXipQuad::computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center)
{
    SbVec3f off = offset.getValue();
    SbVec3f bmin = SbVec3f(0.0 + off[0], 0.0 + off[1], 0.0 + off[2]);
    SbVec3f bmax = SbVec3f(1.0 + off[0], 1.0 + off[1], 1.0 + off[2]);

    box.setBounds(bmin, bmax);
    center = SbVec3f(0.5 + off[0], 0.5 + off[1], 0.0 + off[2]);
}
