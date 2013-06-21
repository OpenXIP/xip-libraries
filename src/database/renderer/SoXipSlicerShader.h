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
 *	Node class for shader programs
 */

#ifndef SO_XIP_SLICER_SHADER
#define SO_XIP_SLICER_SHADER

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/sensors/SoFieldSensor.h>


class SoGLRenderAction;

/**
 *	SoXipSlicerShader. An Open Inventor node to load
 *	GLSL shader programs.
 */
class SoXipSlicerShader : public SoNode
{
	SO_NODE_HEADER(SoXipSlicerShader);

public:
	/**
	 *	Constructor
	 */
	SoXipSlicerShader();

	/**	
	 *	Initializes the class
	 */
	static void initClass();

    SoSFInt32   volumeUnit;
    SoSFInt32   lutUnit;
    SoSFBool    shading;
    SoSFBool    lighting;
    SoSFVec3f   volsize;

protected:
	/**
	 *	Destructor
	 */	
	~SoXipSlicerShader();

	/**
	 *	GLRender
	 */
	virtual void GLRender(SoGLRenderAction *action);

private:

	/**
	 *	Read a shader file
	 */	
	bool readShaderFiles();
	/**
	 *	Compile a GLSL shader program
	 */	
	GLuint compileShaders();
	/**
	 *	Links GLSL shader programs
	 */	
	GLuint linkShaders();

	/**
	 *	Delete and reset the shader programs 
	 */	
	void deleteShaders();

	/**
	 *	Print a log when compiling a shader fails 
	 */	
	void printShaderLog(GLuint shader);

	/**
	 *	Print a log when linking shaders fails 
	 */	
	void printProgramLog(GLuint program);

	/**
	 *	Field sensors
	 */	
    SoFieldSensor               *mTriggerSensor;

	GLuint						mProgramHandle;
	GLuint						mVpHandle;
	GLuint						mFpHandle;

	/**
	 *	Has any field been modified ?
	 */	
	bool						mHasChanged;
    int                         mNodeId;
};

#endif // SO_XIP_SLICER_SHADER
