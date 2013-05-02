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


#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/inventor/coregl/SoXipGLOWElement.h>
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
