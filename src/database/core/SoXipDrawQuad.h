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
#ifndef SO_XIP_DRAW_QUAD_H
#define SO_XIP_DRAW_QUAD_H

#include <xip/inventor/coregl/xipivcoregl.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/system/GL/gl.h>


class SoXipDrawQuad : public SoNode {
	SO_NODE_HEADER(SoXipDrawQuad);

public:
	enum Filter {
		SAME = 0,
		NEAREST = GL_NEAREST,
		LINEAR = GL_LINEAR,
	};

	SoXipDrawQuad();

	void GLRender(SoGLRenderAction* action);
	
	static void initClass();

	SoSFBool enableTexture;
	SoSFEnum filter;
	SoSFBool blend;
	SoMFVec3f colors;
	SoSFBool orthographic;
};


#endif // SO_DRAW_QUAD_H



