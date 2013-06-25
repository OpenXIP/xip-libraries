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

#ifndef SO_XIP_OPENGL_ERROR_H
#define SO_XIP_OPENGL_ERROR_H


/**
 *  Component       : XIP
 *  Name            : SoXipOpenGLError
 *  Author          : Vetter C, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 7-Feb-2008
 *  Description     : A node that checks for OpenGL Error.
 *                    Allows quick check whether a network/node produces OpenGL errors 
 *
 *  Copyright � Siemens AG 2006-2008. All Rights Reserved.
 */
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/fields/SoSFBool.h>
#include <xip/system/GL/gl.h>
#include <xip/system/GL/glu.h>

class SoXipOpenGLError : public SoNode {
	SO_NODE_HEADER(SoXipOpenGLError);

public:
	

	SoXipOpenGLError();

	void GLRender(SoGLRenderAction* action);
	
	static void initClass();
	/*
	* if RaiseError is checked an error message is used, whenever an OpenGL error is encountered
	* otherwise a warning mesage is used
	*/

    SoSFBool	raiseError;
    ~SoXipOpenGLError() ;
	
};


#endif //SO_XIP_OPENGL_ERROR_H
