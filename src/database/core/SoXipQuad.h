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

#ifndef SOXIPQUAD_H
#define SOXIPQUAD_H

#include <xip/inventor/coregl/xipivcoregl.h>
//#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/SbBox.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <xip/system/GL/gl.h>

class SoXipQuad : public SoShape
{
    SO_NODE_HEADER(SoXipQuad);

public:

    SoXipQuad();

    virtual void GLRender(SoGLRenderAction* action);
    virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);
    virtual void generatePrimitives(SoAction *action);
	
    static void initClass();

    SoSFVec3f offset;
};


#endif // SOXIPQUAD_H



