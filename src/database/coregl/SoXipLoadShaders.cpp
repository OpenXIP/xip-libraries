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
#include <xip/system/standard.h>
#include <xip/system/GL/gl.h>
#include <xip/inventor/core/XipStringUtils.h>

#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <xip/inventor/coregl/SoXipShaderProgramElement.h>
#include <xip/inventor/coregl/SoXipGLSLShaderProgramElement.h>
#include "SoXipLoadShaders.h"
#include <string>
#include <vector>
#include <fstream>

#undef DEBUG

#ifdef DEBUG
#define FUNCID(...) SoDebugError::postInfo(__FUNCTION__, __VA_ARGS__);
#else
#define FUNCID(...)
#endif

SO_NODE_SOURCE(SoXipLoadShaders);

/**
 *	Constructor
 */
SoXipLoadShaders::SoXipLoadShaders()
{
	SO_NODE_CONSTRUCTOR(SoXipLoadShaders);
	SO_NODE_ADD_FIELD(fpFilename, (""));
	SO_NODE_ADD_FIELD(vpFilename, (""));
	SO_NODE_ADD_FIELD(fpDefines, (""));
	SO_NODE_ADD_FIELD(vpDefines, (""));
    SO_NODE_ADD_FIELD(reload, ());

	mVpSensor = new SoFieldSensor(hasChangedCB, this);
	mVpSensor->attach(&this->vpFilename);
	mFpSensor = new SoFieldSensor(hasChangedCB, this);
	mFpSensor->attach(&this->fpFilename);
	mVpDefinesSensor = new SoFieldSensor(hasChangedCB, this);
	mVpDefinesSensor->attach(&this->vpDefines);
	mFpDefinesSensor = new SoFieldSensor(hasChangedCB, this);
	mFpDefinesSensor->attach(&this->fpDefines);
    mTriggerSensor = new SoFieldSensor(hasChangedCB, this);
    mTriggerSensor->attach(&reload);

	mVpHandle = 0;
	mFpHandle = 0;
	mProgramHandle = 0;
	mHasChanged = true;
}

/**
 *	Destructor
 */	
SoXipLoadShaders::~SoXipLoadShaders()
{
	delete mVpSensor;
	delete mFpSensor;
	delete mVpDefinesSensor;
	delete mFpDefinesSensor;

	deleteShaders();
}

/**
 *	delete and reset the shader programs 
 */	
void SoXipLoadShaders::deleteShaders()
{
	// If program handle is valid, delete it
	if (mProgramHandle != 0)
	{
		// DeleteProgram detaches shaders and deletes program
		glDeleteProgram(mProgramHandle);
		mProgramHandle = 0;
	}
	// If vertex handle is valid
	if (mVpHandle != 0)
	{
		// Delete vertex shader
		// NOTE - NVIDIA drivers from August 2006 complain that the handle passed is invalid,
		// even though glIsShader(handle) returns true. Assume this is a driver bug.
		// It actually does free the handle when called. If not called, it doesn't free it.
		glDeleteShader(mVpHandle);
		mVpHandle = 0;
	}
	// If fragment handle is valid
	if (mFpHandle != 0)
	{
		// Delete fragment shader
		glDeleteShader(mFpHandle);
		mFpHandle = 0;
	}
}

/**	
 *	Initializes the class
 */
void SoXipLoadShaders::initClass()
{
	SO_NODE_INIT_CLASS(SoXipLoadShaders, SoNode, "SoNode");
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
	SO_ENABLE(SoGLRenderAction, SoXipShaderProgramElement);
	SO_ENABLE(SoGLRenderAction, SoXipGLSLShaderProgramElement);
}

/**	
 *	Local procedure that takes an input string and an input delimiters string
 *	as inputs and fills up a std::vector with the appropriate tokens from
 *	the input string.
 *	Used to create the preprocessor definitions that are to be added ad the
 *	beginning of the shader programs.
 */
void tokenize(const std::string& str,
			  std::vector<std::string>& tokens,
			  const std::string& delimiters = " ")
{
	// Skip delimiters at the beginning
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first non-delimiter character
	std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		// Add a token to the vector of tokens
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next non-delimiter character
		pos = str.find_first_of(delimiters, lastPos);
	}
}

/**
 *	Read a shader file. Add the preprocessor definitions at
 *	the beginning of the file before the compilation.
 */	
bool SoXipLoadShaders::readShadersFile(const char *filename, const char *defines, GLuint handle)
{
	std::ifstream				in;
	std::string					s, line;
	GLchar						*programString;
	std::vector<std::string>	vDefines;
	
#ifdef WIN32
    //assuming everything is done using the bad backslashes... so we convert all forward slashes to those
    const char * fileLocal = XipReplaceChar(filename, '/', '\\').getString();
#else //UNIX
    //assuming the other way around since we need forward slashes now...
    const char * fileLocal = XipReplaceChar(filename, '\\', '/').getString();
#endif //WIN32

	// Open the shader file
	in.open(fileLocal);
	if (in.fail())
		return false;

	// Create a vector of preprocessor definitions
	tokenize(defines, vDefines);
	std::vector<std::string>::iterator it = vDefines.begin();
	
	// Add the #defines to the source file
	while (it != vDefines.end())
		s += "#define " + *it++ + "\n";
	
	// Append the source code
	while (std::getline(in, line))
		s += line + "\n";
	
	programString = (GLchar *)s.c_str();

	// Set the source code of the shader
	glShaderSource(handle, 1, (const GLchar**) &programString, NULL);
	return true;
}

/**
 *	Compile a GLSL shader program
 */	
GLuint SoXipLoadShaders::compileShader(const char	*filename, 
									   const char	*defines,
									   GLenum		type)
{
	GLint status = 0;

	// Create the handle for the shader
	GLuint handle = glCreateShader(type);

	// Read and compile the shader program
	if (readShadersFile(filename, defines, handle))
	{
		glCompileShader(handle);
		glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
	}
	else
	{
		SoError::post("Shader file \"%s\" could not be opened\n", filename);
		glDeleteShader(handle);
		return 0;
	}

	// Check the compilation status
	if (!status)
	{
		SoError::post("Shader file \"%s\" could not be compiled\n", filename);
		printShaderLog(handle);
		glDeleteShader(handle);
		return 0;
	}
	return handle;
}

/**
 *	Links GLSL shader programs
 */	
GLuint SoXipLoadShaders::linkShaders()
{
	GLint isLinked;

	// Create a GLSL program
	GLuint handle = glCreateProgram();

	// Attach the vertex and fragment shaders to the GLSL program
	if (mVpHandle != 0)
		glAttachShader(handle, mVpHandle);
	if (mFpHandle != 0)
		glAttachShader(handle, mFpHandle);

	// Link the shaders
	glLinkProgram(handle);

	// Check the link status
	glGetProgramiv(handle, GL_LINK_STATUS, &isLinked);
	if (!isLinked)
	{
		SoError::post("Program could not be linked\n");
		printProgramLog(handle);
		glDeleteProgram(handle);
		return 0;
	}
	return handle;
}

/**
 *	Print a log when compiling a shader fails 
 */	
void SoXipLoadShaders::printShaderLog(GLuint shader)
{
	GLint length = 0;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
	if (length > 0)
	{
		GLchar *info = new GLchar[length + 1];
		glGetShaderInfoLog(shader, length, NULL, info);
		info[length] = 0;
		SoError::post(info);
		delete[] info;
	}
}

/**
 *	Print a log when linking shaders fails 
 */	
void SoXipLoadShaders::printProgramLog(GLuint program)
{
	GLint length = 0;

	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
	if (length > 0)
	{
		GLchar *info = new GLchar[length + 1];
		glGetProgramInfoLog(program, length, NULL, info);
		info[length] = 0;
		SoError::post(info);
		delete[] info;
	}
}

/**
 *	GLRender. Set the Element to the Program Id
 */
void SoXipLoadShaders::GLRender(SoGLRenderAction *action)
{
	if (!GLOW_ARB_shading_language_100)
		return;

	if (mHasChanged)
	{
		FUNCID("Recompiling shaders");

		// Delete existing shaders
		deleteShaders();
		// Compile non-empty shaders
		if (vpFilename.getValue() != "")
			mVpHandle = compileShader(vpFilename.getValue().getString(),
						   vpDefines.getValue().getString(),
						   GL_VERTEX_SHADER);
		if (fpFilename.getValue() != "")
			mFpHandle = compileShader(fpFilename.getValue().getString(),
						   fpDefines.getValue().getString(),
						   GL_FRAGMENT_SHADER);

		// If any compilation succeeded, link shaders
		if (mVpHandle != 0 || mFpHandle != 0)
		{
			mProgramHandle = linkShaders();

			// If linking failed, free shaders
			if (mProgramHandle == 0)
				deleteShaders();
		}

		mHasChanged = false;
	}
    
	SoXipGLSLShaderProgramElement::set(action->getState(), mProgramHandle);
}


