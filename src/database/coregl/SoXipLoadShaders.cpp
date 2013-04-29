/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
 */

/**
 *	Node class for shader programs
 */
#include <xip/system/standard.h>
#include <xip/system/GL/gl.h>
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

	// Open the shader file
	in.open(filename);
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


