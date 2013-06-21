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
#include "SoXipOpenGLError.h"
#include <Inventor/errors/SoError.h>
#include <Inventor/errors/SoDebugError.h>
#include <string>
#include <xip/system/GL/glu.h>

SO_NODE_SOURCE(SoXipOpenGLError);

SoXipOpenGLError::SoXipOpenGLError() {
	SO_NODE_CONSTRUCTOR(SoXipOpenGLError);
	SO_NODE_ADD_FIELD(raiseError, (true));
	
}

SoXipOpenGLError::~SoXipOpenGLError() {
}

void SoXipOpenGLError::initClass() {
	SO_NODE_INIT_CLASS(SoXipOpenGLError, SoNode, "Node");
	
}

void SoXipOpenGLError::GLRender(SoGLRenderAction *action) {
	GLenum glError;
	
	
	glError=glGetError();
	if(glError!=GL_NO_ERROR)
	{
       const char *errstr = reinterpret_cast<const char *>(gluErrorString(glError));
	   if(raiseError.getValue()==TRUE)SoError::post("OpenGL Error: %s\n",errstr);
	   else SoDebugError::postWarning("OpenGL Error: %s\n",errstr);

		
	}
}






