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
#include <xip/inventor/coregl/SoXipGlowElement.h>
#include "SoXipUniformVariable.h"
#include <xip/inventor/coregl/SoXipGLSLShaderProgramElement.h>

SO_NODE_SOURCE(SoXipUniformVariable);

/**
 *	 Implementation of base class SoXipUniformVariable
 */
void SoXipUniformVariable::initClass()
{
	SO_NODE_INIT_CLASS( SoXipUniformVariable,SoNode,"Node");
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement );
	SO_ENABLE( SoGLRenderAction, SoXipGLSLShaderProgramElement );
}

void SoXipUniformVariable::GLRender(SoGLRenderAction* action)
{
	if (mName != name.getValue())
	{
		mDisplayError = TRUE;
		mName = name.getValue();
	}
	doAction(action);
}

/**
 *	Constructor
 */
SoXipUniformVariable::SoXipUniformVariable()
{
	SO_NODE_CONSTRUCTOR(SoXipUniformVariable);
	SO_NODE_ADD_FIELD(name,(""));
	programHandle = 0;
	mDisplayError = TRUE;
	mName = SbString("");
}

SoXipUniformVariable::~SoXipUniformVariable()
{

}

/**
 *	getLocation : return the location of a uniform variable
 *	in a shader program so that its value can be modified
 */
GLint SoXipUniformVariable::getLocation()
{
	GLhandleARB	programObject = glGetHandleARB(GL_PROGRAM_OBJECT_ARB);
#ifdef DARWIN
	GLint		loc	= glGetUniformLocationARB(programObject,  name.getValue().getString());
#else
	GLint		loc	= glGetUniformLocation(programObject,  name.getValue().getString());
#endif /* DARWIN */
	
	if (loc == -1 && mDisplayError)
	{
		SoDebugError::postInfo("SoXipUniformVariable::getLocation", "Unknown uniform variable: %s", name.getValue().getString());
		mDisplayError = FALSE;
	}
	return loc;
}

void SoXipUniformVariable::doAction(SoAction *action)
{

}

/**
 *	 Implementation of derived class SoXipUniformFloat
 */
SO_NODE_SOURCE(SoXipUniformFloat);

void SoXipUniformFloat::initClass()
{
	SO_NODE_INIT_CLASS( SoXipUniformFloat,SoXipUniformVariable,"SoXipUniformVariable");
}

/**
 *	Constructor
 */
SoXipUniformFloat::SoXipUniformFloat()
{
	SO_NODE_CONSTRUCTOR(SoXipUniformFloat);
	SO_NODE_ADD_FIELD(value,(0.0));
}

void SoXipUniformFloat::doAction(SoAction *action)
{
//	programHandle = SoXipGLSLShaderProgramElement::get(action->getState());
	glUniform1fv(getLocation(), value.getNum(), value.getValues(0));
}

/**
 *	 Implementation of derived class SoXipUniformVec2f
 */
SO_NODE_SOURCE(SoXipUniformVec2f);

void SoXipUniformVec2f::initClass()
{
	SO_NODE_INIT_CLASS( SoXipUniformVec2f,SoXipUniformVariable,"SoXipUniformVariable");
}

/**
 *	Constructor
 */
SoXipUniformVec2f::SoXipUniformVec2f()
{
	SO_NODE_CONSTRUCTOR(SoXipUniformVec2f);
	SO_NODE_ADD_FIELD(value,(0.0,0.0));
}

void SoXipUniformVec2f::doAction(SoAction *action)
{
	float x,y;
	value.getValue().getValue(x,y);
	glUniform2f(getLocation(), x,y);
}

/**
 *	 Implementation of derived class SoXipUniformVec3f
 */
SO_NODE_SOURCE(SoXipUniformVec3f);

void SoXipUniformVec3f::initClass()
{
	SO_NODE_INIT_CLASS( SoXipUniformVec3f,SoXipUniformVariable,"SoXipUniformVariable");
}

/**
 *	Constructor
 */
SoXipUniformVec3f::SoXipUniformVec3f()
{
	SO_NODE_CONSTRUCTOR(SoXipUniformVec3f);
	SO_NODE_ADD_FIELD(value,(0.0,0.0,0.0));
}

void SoXipUniformVec3f::doAction(SoAction *action)
{
	float x,y,z;
	value.getValue().getValue(x,y,z);
	glUniform3f(getLocation(), x,y,z);
}

/**
 *	 Implementation of derived class SoXipUniformVec4f
 */
SO_NODE_SOURCE(SoXipUniformVec4f);

void SoXipUniformVec4f::initClass()
{
	SO_NODE_INIT_CLASS( SoXipUniformVec4f,SoXipUniformVariable,"SoXipUniformVariable");
}

/**
 *	Constructor
 */
SoXipUniformVec4f::SoXipUniformVec4f()
{
	SO_NODE_CONSTRUCTOR(SoXipUniformVec4f);
	SO_NODE_ADD_FIELD(value,(0.0,0.0,0.0,0.0));
}

void SoXipUniformVec4f::doAction(SoAction *action)
{
	float x,y,z,w;
	value.getValue().getValue(x,y,z,w);
	glUniform4f(getLocation(), x,y,z,w);
}

/**
 *	 Implementation of derived class SoXipUniformInt
 */
SO_NODE_SOURCE(SoXipUniformInt);

void SoXipUniformInt::initClass()
{
	SO_NODE_INIT_CLASS( SoXipUniformInt,SoXipUniformVariable,"SoXipUniformVariable");
}

/**
 *	Constructor
 */
SoXipUniformInt::SoXipUniformInt()
{
	SO_NODE_CONSTRUCTOR(SoXipUniformInt);
	SO_NODE_ADD_FIELD(value,(0));
}

void SoXipUniformInt::doAction(SoAction *action)
{
	glUniform1iv(getLocation(), value.getNum(), value.getValues(0));
}

/**
 *	 Implementation of derived class SoXipUniformMatrix4
 */
SO_NODE_SOURCE(SoXipUniformMatrix4);

void SoXipUniformMatrix4::initClass()
{
	SO_NODE_INIT_CLASS( SoXipUniformMatrix4,SoXipUniformVariable,"SoXipUniformVariable");
}

/**
 *	Constructor
 */
SoXipUniformMatrix4::SoXipUniformMatrix4()
{
	SO_NODE_CONSTRUCTOR(SoXipUniformMatrix4);
	SO_NODE_ADD_FIELD(value,(SbMatrix::identity()));
}

void SoXipUniformMatrix4::doAction(SoAction *action)
{
	SbMatrix m = value.getValue();
    glUniformMatrix4fv(getLocation(),1, false, (float*)m);
}

/**
 *	 Implementation of derived class SoXipUniformMatrix3
 */
SO_NODE_SOURCE(SoXipUniformMatrix3);

void SoXipUniformMatrix3::initClass()
{
	SO_NODE_INIT_CLASS(SoXipUniformMatrix3, SoXipUniformVariable, "SoXipUniformVariable");
}

/**
 *	Constructor
 */
SoXipUniformMatrix3::SoXipUniformMatrix3()
{
	SO_NODE_CONSTRUCTOR(SoXipUniformMatrix3);
	SO_NODE_ADD_FIELD(value, (0));
}

void SoXipUniformMatrix3::doAction(SoAction *action)
{
	int num = value.getNum();
	if (num == 9) {
		glUniformMatrix3fv(getLocation(), 1 ,false, value.getValues(0));
	}
	else {
		SoDebugError::postInfo(__FUNCTION__, "Requires 9 floats");
	}
}


