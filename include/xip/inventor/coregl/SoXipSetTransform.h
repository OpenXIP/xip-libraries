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

/**
 *	Node class for texture handling
 */

#ifndef SO_XIP_SET_TRANSFORM_H
#define SO_XIP_SET_TRANSFORM_H

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/inventor/coregl/xipivcoregl.h>

class XIPIVCOREGL_API SoXipSetTransform : public SoNode {
	SO_NODE_HEADER(SoXipSetTransform);

public:
	enum MatrixType {
		PROJECTION,
		MODEL,
		VIEW,
		TEXTURE
	};

	SoXipSetTransform();

	void GLRender(SoGLRenderAction* action);
	
	static void initClass();

	SoSFEnum matrixType;
	SoSFMatrix matrix;
	SoSFBool multiply;
};


#endif 
