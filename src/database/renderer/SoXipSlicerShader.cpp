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


#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <xip/inventor/coregl/SoXipShaderProgramElement.h>
#include <xip/inventor/coregl/SoXipGLSLShaderProgramElement.h>
#include "SoXipSlicerShader.h"
#include <string>
#include <vector>
#include <fstream>

#undef DEBUG

#ifdef DEBUG
#define FUNCID(...) SoDebugError::postInfo(__FUNCTION__, __VA_ARGS__);
#else
#define FUNCID(...)
#endif

SO_NODE_SOURCE(SoXipSlicerShader);

/**
 *	Constructor
 */
SoXipSlicerShader::SoXipSlicerShader()
{
	SO_NODE_CONSTRUCTOR(SoXipSlicerShader);
    SO_NODE_ADD_FIELD(volumeUnit, (0));
    SO_NODE_ADD_FIELD(lutUnit,    (0));
    SO_NODE_ADD_FIELD(shading,  (TRUE));
    SO_NODE_ADD_FIELD(lighting, (TRUE));
    SO_NODE_ADD_FIELD(volsize,   (SbVec3f(0.0,0.0,0.0)));

    mVpHandle = 0;
	mFpHandle = 0;
	mProgramHandle = 0;
	mHasChanged = true;
    mNodeId = 0;
}

/**
 *	Destructor
 */	
SoXipSlicerShader::~SoXipSlicerShader()
{
	deleteShaders();
}

/**
 *	delete and reset the shader programs 
 */	
void SoXipSlicerShader::deleteShaders()
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
void SoXipSlicerShader::initClass()
{
	SO_NODE_INIT_CLASS(SoXipSlicerShader, SoNode, "SoNode");
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
	SO_ENABLE(SoGLRenderAction, SoXipShaderProgramElement);
	SO_ENABLE(SoGLRenderAction, SoXipGLSLShaderProgramElement);
}





/**
 *	Read a shader file. Add the preprocessor definitions at
 *	the beginning of the file before the compilation.
 */	
bool SoXipSlicerShader::readShaderFiles()
{
    GLchar * vPrgStr =
        "void main()"
        "{"
            "gl_TexCoord[0] = gl_TextureMatrix[0] *  gl_MultiTexCoord0;"
            "gl_ClipVertex = gl_ModelViewMatrix * gl_Vertex;"
            "gl_Position = ftransform();"
        "}"
        "";

#if 0

    GLchar * fPrgStr =
            "uniform sampler3D volume;"
            "uniform sampler2D lut;"
            ""
            "void main()"
            "{"
            "   float d = texture3D(volume, gl_TexCoord[0].xyz).r;"
            "   vec4  c = texture2D(lut, vec2(d, 0.1));"
            "   c.rgb *= c.a;"
            "   gl_FragColor = c;"
            "}"
            "";

#else

    GLchar * fPrgStr =
        "uniform sampler3D volume;"
        "uniform sampler2D lut;"
        "uniform vec3 vSize;"
        "uniform float selfShading;"
        "uniform float gradLighting;"
        ""
        "vec4 sampleTF(const in float dens)"
        "{"
        "   return texture2D(lut, vec2(dens, 0.1));"
        "}"
        ""
        "vec3 computegradient()"
        "{"
        "   vec3 sample1;"
        "   vec3 sample2;"
        "   vec3 offset = vec3(1.0/vSize.x, 1.0/vSize.y, 1.0/vSize.z);"
        "   sample1.x = texture3D(volume, gl_TexCoord[0].xyz-vec3(offset.x,0.0,0.0)).x;"
        "   sample2.x = texture3D(volume, gl_TexCoord[0].xyz+vec3(offset.x,0.0,0.0)).x;"
        "   sample1.y = texture3D(volume, gl_TexCoord[0].xyz-vec3(0.0,offset.y,0.0)).y;"
        "   sample2.y = texture3D(volume, gl_TexCoord[0].xyz+vec3(0.0,offset.y,0.0)).y;"
        "   sample1.z = texture3D(volume, gl_TexCoord[0].xyz-vec3(0.0,0.0,offset.z)).z;"
        "   sample2.z = texture3D(volume, gl_TexCoord[0].xyz+vec3(0.0,0.0,offset.z)).z;"
        "   return sample2 - sample1;"
        "}"
        ""
        "vec4 shade(const in float dens, const in vec4 shadingParam)"
        "{"
        "   vec3 lightdir = vec3(-gl_NormalMatrix[0][2],-gl_NormalMatrix[1][2],-gl_NormalMatrix[2][2]);"
        "   vec3 halfway = lightdir;"
        "   lightdir = normalize(lightdir);"
        "   halfway = normalize(halfway);"
        "   vec4 color = sampleTF(dens);"
        "   vec4 gradient;"
        "   gradient.xyz = computegradient();"
        "   gradient.w = length(gradient.xyz);"
        "   gradient.xyz = normalize(gradient.xyz);"
        "   if (gradient.w > 0.003)"
        "   {"
        "       float diffuse =  max(dot(gradient.xyz, lightdir), 0.0);"
        "       float specular = pow(max(dot(halfway, gradient.xyz), 0.0), shadingParam.w);"
        "       color.rgb = (shadingParam.x + shadingParam.y * diffuse) * color.rgb + shadingParam.z * specular * color.a;"
        "   }"
        ""
        "   return color;"
        "}"
        ""
        "void main()"
        "{"
        "   float d = texture3D(volume, gl_TexCoord[0].xyz).r;"
        "   vec4 p = vec4(0.3, 0.6, 0.7, 64.0);"
        ""
        "   vec4 c = mix(sampleTF(d), shade(d, p), gradLighting);"
        "   c.rgb *= mix(1.0, smoothstep(0.0,0.4,c.a), selfShading);"
        ""
        "   gl_FragColor = c;"
        "}"
        "";
#endif
    
    if (!vPrgStr || !fPrgStr)
        return false;

	// Set the source code of the shader
	glShaderSource(mVpHandle, 1, (const GLchar**) &vPrgStr, NULL);
	glShaderSource(mFpHandle, 1, (const GLchar**) &fPrgStr, NULL);
	return true;
}

/**
 *	Compile a GLSL shader program
 */	
GLuint SoXipSlicerShader::compileShaders()
{
	GLint vpStatus = 0;
	GLint fpStatus = 0;

	// Create the handle for the shader
	mVpHandle = glCreateShader(GL_VERTEX_SHADER);
	mFpHandle = glCreateShader(GL_FRAGMENT_SHADER);

    readShaderFiles();

    glCompileShader(mVpHandle);
    glGetShaderiv(mVpHandle, GL_COMPILE_STATUS, &vpStatus);
	if (!vpStatus)
	{
		SoDebugError::postWarning(__FUNCTION__, "Vertex shader file could not be compiled\n");
		printShaderLog(mVpHandle);
		glDeleteShader(mVpHandle);
		return 0;
	}

    glCompileShader(mFpHandle);
    glGetShaderiv(mFpHandle, GL_COMPILE_STATUS, &fpStatus);
	if (!fpStatus)
	{
		SoDebugError::postWarning(__FUNCTION__, "Fragment shader file could not be compiled\n");
		printShaderLog(mFpHandle);
		glDeleteShader(mFpHandle);
		return 0;
	}

	return 1;
}

/**
 *	Links GLSL shader programs
 */	
GLuint SoXipSlicerShader::linkShaders()
{
	GLint isLinked = 0;

	// Create a GLSL program
	mProgramHandle = glCreateProgram();

	// Attach the vertex and fragment shaders to the GLSL program
	if (mVpHandle != 0)
		glAttachShader(mProgramHandle, mVpHandle);
	if (mFpHandle != 0)
		glAttachShader(mProgramHandle, mFpHandle);

	// Link the shaders
	glLinkProgram(mProgramHandle);

	// Check the link status
	glGetProgramiv(mProgramHandle, GL_LINK_STATUS, &isLinked);
	if (!isLinked)
	{
		SoDebugError::postWarning(__FUNCTION__, "Program could not be linked\n");
		printProgramLog(mProgramHandle);
		glDeleteProgram(mProgramHandle);
		return 0;
	}

	return mProgramHandle;
}

/**
 *	Print a log when compiling a shader fails 
 */	
void SoXipSlicerShader::printShaderLog(GLuint shader)
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
void SoXipSlicerShader::printProgramLog(GLuint program)
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
void SoXipSlicerShader::GLRender(SoGLRenderAction *action)
{
    if (!GLOW_ARB_shading_language_100)
		return;

    if (mNodeId != getNodeId())
    {
        mNodeId = getNodeId();
        mHasChanged = true;
    }

	if (mHasChanged)
	{
		FUNCID("Recompiling shaders");

		// Delete existing shaders
		deleteShaders();
		// Compile non-empty shaders
        compileShaders();

		// If any compilation succeeded, link shaders
		if (mVpHandle != 0 || mFpHandle != 0)
		{
			linkShaders();

			// If linking failed, free shaders
			if (mProgramHandle == 0)
				deleteShaders();
		}

        SoDebugError::postInfo(__FUNCTION__, "Compiled Shader (%d)", mProgramHandle);

		mHasChanged = false;
	}
    
	SoXipGLSLShaderProgramElement::set(action->getState(), mProgramHandle);

    int v = volumeUnit.getValue();
    int a = lutUnit.getValue();
	GLint vloc = glGetUniformLocation(mProgramHandle, "volume");
	GLint aloc = glGetUniformLocation(mProgramHandle, "lut");
    if (vloc > -1)
	    glUniform1iv(vloc, 1, &v);
    if (aloc > -1)
        glUniform1iv(aloc, 1, &a);

    float ss = (shading.getValue()) ? 1.0 : 0.0;
    float gl = (lighting.getValue()) ? 1.0 : 0.0;
    GLint ssloc = glGetUniformLocation(mProgramHandle, "selfShading");
    GLint glloc = glGetUniformLocation(mProgramHandle, "gradLighting");
    if (ssloc > -1)
        glUniform1f(ssloc, ss);
    if (glloc > -1)
        glUniform1f(glloc, gl);

    GLint sloc = glGetUniformLocation(mProgramHandle, "vSize");
    SbVec3f s = volsize.getValue();
    if (sloc > -1)
        glUniform3f(sloc, s[0],s[1],s[2]);
}
