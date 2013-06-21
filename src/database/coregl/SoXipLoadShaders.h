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

#ifndef SO_XIP_LOAD_SHADERS
#define SO_XIP_LOAD_SHADERS

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/sensors/SoFieldSensor.h>


class SoGLRenderAction;

/**
 *	SoXipLoadShaders. An Open Inventor node to load
 *	GLSL shader programs.
 */
class SoXipLoadShaders : public SoNode
{
	SO_NODE_HEADER(SoXipLoadShaders);

public:
	/**
	 *	Constructor
	 */
	SoXipLoadShaders();

	/**	
	 *	Initializes the class
	 */
	static void initClass();
	
	/**	
	 *	Field for the path to the vertex program
	 */
	SoSFString	vpFilename;
	/**	
	 *	Field for the path to the fragment program
	 */
	SoSFString	fpFilename;
	/**	
	 *	Field to add preprocessor definitions to the
	 *	vertex program (separated by ' ')
	 */
	SoSFString	vpDefines;
	/**	
	 *	Field to add preprocessor definitions to the
	 *	fragment program (separated by ' ')
	 */
	SoSFString	fpDefines;

    SoSFTrigger reload;

protected:
	/**
	 *	Destructor
	 */	
	~SoXipLoadShaders();

	/**
	 *	GLRender
	 */
	virtual void GLRender(SoGLRenderAction *action);

	/**
	 *	Callback for the sensor attached to the fields
	 */
	inline void setHasChanged()
	{
		this->mHasChanged = true;
	}

private:

	/**
	 *	Read a shader file
	 */	
	bool readShadersFile(const char *filename, const char *defines, GLuint handle);
	
	/**
	 *	Compile a GLSL shader program
	 */	
	GLuint compileShader(	const char	*filename, 
							const char	*defines,
							GLenum		type);
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
	SoFieldSensor				*mVpSensor;
	SoFieldSensor				*mFpSensor;
	SoFieldSensor				*mVpDefinesSensor;
	SoFieldSensor				*mFpDefinesSensor;
    SoFieldSensor               *mTriggerSensor;

	/**
	 *	GLSL Program Handle (Id) ie. when shaders are linked
	 */	
	GLuint						mProgramHandle;
	/**
	 *	GLSL Vertex Program Handle (Id)
	 */	
	GLuint						mVpHandle;
	/**
	 *	GLSL Fragment Program Handle (Id)
	 */	
	GLuint						mFpHandle;

	/**
	 *	Has any field been modified ?
	 */	
	bool						mHasChanged;

	/**
	 *	Callback for the sensor attached to the fields
	 *	(call to an inline callback)
	 */
	static void	hasChangedCB(void * data,SoSensor*) { ((SoXipLoadShaders *)data)->setHasChanged(); };
};

#endif // SO_XIP_LOAD_SHADERS
