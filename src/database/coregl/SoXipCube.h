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

#ifndef SO_XIP_CUBE_H
#define SO_XIP_CUBE_H

#define NEW_SHAPE_IMPLEMENTATION

/**
 *  Component       : XIP
 *  Name            : SoXipCube
 *  Author          : Lindholm S, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 2-Oct-2007
 *  Description     :   Extension from the regular Inventor cube
 *                      with 3D texture coordinates and culling
 *                      options for use in a raycast scheme.
 *                      Previously named SoXipRaycastCube.
 *
 *  Copyright � Siemens AG 2006-2007. All Rights Reserved.
 */

#ifdef NEW_SHAPE_IMPLEMENTATION


#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/actions/SoGetBoundingBoxAction.h>
#include <xip/system/GL/gl.h>


class SoXipCube : public SoShape
{
	SO_NODE_HEADER(SoXipCube);

public:
	enum Culling {
		NONE = 0,
		FRONT = GL_FRONT,
		BACK = GL_BACK,
	};

	SoXipCube();

	virtual void GLRender(SoGLRenderAction* action);
	//virtual void getBoundingBox(SoGetBoundingBoxAction* action);
    virtual void computeBBox(SoAction* action, SbBox3f &box, SbVec3f &center);
    virtual void generatePrimitives(SoAction* action);
	void doAction();
	
	static void initClass();

	SoSFVec3f scale;
	SoSFVec3f offset;
	SoSFEnum culling;
};

#else

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/system/GL/gl.h>


class SoXipCube : public SoNode {
	SO_NODE_HEADER(SoXipCube);

public:
	enum Culling {
		NONE = 0,
		FRONT = GL_FRONT,
		BACK = GL_BACK,
	};

	SoXipCube();

	void GLRender(SoGLRenderAction* action);
	
	static void initClass();

	SoSFVec3f scale;
	SoSFVec3f offset;
	SoSFEnum culling;
};

#endif //NEW_SHAPE_IMPLEMENTATION

#endif // SO_XIP_CUBE_H
