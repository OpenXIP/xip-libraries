/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2005 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). eXtensible Imaging Platform (XIP)
 *  was created with NCI funding and is part of the caBIG(tm) 
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

#include <xip/system/standard.h>
#include <xip/system/GL/gl.h>
#include <xip/inventor/core/XipStringUtils.h>

#include <xip/inventor/coregl/ShaderEngine.h>
#include <fstream>
// Used for timestamp lookup on shader source
#include <sys/stat.h>
#include <time.h>

#define TCALLOC(num, Type) reinterpret_cast<Type *>(calloc(num, sizeof(Type)))


/**
 *	Delete a specific shader program and its attachments.
 * @param programHandle Shader program to delete
 */	
void ShaderEngine::deleteShader(GLuint& shaderHandle)
{
    if (glIsShader(shaderHandle))
        glDeleteShader(shaderHandle);
    shaderHandle = 0;
}

/**
 *	Delete a specific shader program and its attachments.
 * @param programHandle Shader program to delete
 */	
void ShaderEngine::deleteProgram(GLuint& programHandle)
{
	// If program handle is valid, delete it
	if (glIsProgram(programHandle))
	{
        // Get attached shaders
        int numShaders;
        glGetProgramiv(programHandle, GL_ATTACHED_SHADERS, &numShaders);
        GLuint * shaders = TCALLOC(numShaders, GLuint);
        glGetAttachedShaders(programHandle, NULL, &numShaders, shaders);

	    // Delete program and shaders
	    glDeleteProgram(programHandle);
        for(int i=0; i<numShaders; i++)
            ShaderEngine::deleteShader(shaders[i]);
        free(shaders);
        programHandle = 0;
	}
}

/**
 *	Read a shader file. Add the preprocessor definitions at
 *	the beginning of the file before the compilation.
 */	
std::string ShaderEngine::readShaderSourceFile(const char *filename)
{
    std::string dummy;
    return readShaderSourceFile(filename, dummy);
}

/**
 *	Read a shader file. Add the preprocessor definitions at
 *	the beginning of the file before the compilation.
 */	
std::string ShaderEngine::readShaderSourceFile(const char *filename, std::string& errorMsg)
{
    std::ifstream				in;
	std::string					s, line;

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
    {
        errorMsg += "Error in opening file: ";
        errorMsg.append(fileLocal);
        return std::string("");
    }

	// Append the source code
	while (std::getline(in, line))
		s += line + "\n";

    return s;
}


/**
 *	Read a shader file. Add the preprocessor definitions at
 *	the beginning of the file before the compilation.
 */
int ShaderEngine::getSourceFileTimeStamp(const char *filename)
{
    std::string dummy;
    return getSourceFileTimeStamp(filename, dummy);
}

/**
 *	Read a shader file. Add the preprocessor definitions at
 *	the beginning of the file before the compilation.
 */
int ShaderEngine::getSourceFileTimeStamp(const char *filename, std::string& errorMsg)
{
    struct stat filestat = { 0 };
#ifdef WIN32
    //assuming everything is done using the bad backslashes... so we convert all forward slashes to those
    const char * fileLocal = XipReplaceChar(filename, '/', '\\').getString();
#else //UNIX
    //assuming the other way around since we need forward slashes now...
    const char * fileLocal = XipReplaceChar(filename, '\\', '/').getString();
#endif //WIN32
    int returncode = stat(fileLocal, &filestat);
    if (returncode != 0)
    {
        errorMsg += "Error in retrieving timestamp for file: ";
        errorMsg.append(fileLocal);
    }
    return (returncode == 0) ? filestat.st_mtime : 0;
}


/**
 *	Read a shader file. Add the preprocessor definitions at
 *	the beginning of the file before the compilation.
 */	
void ShaderEngine::setShaderSource(GLuint handle, std::string source)
{
	GLchar *programString = (GLchar *)source.c_str();
	glShaderSource(handle, 1, (const GLchar**) &programString, NULL);
}

/**
 *	Compile a GLSL shader program
 */	
GLuint ShaderEngine::compileShader(const char * source,
								   GLenum       type)
{
    std::string dummy;
    return (source) ? ShaderEngine::compileShader(std::string(source), type, dummy) : 0;
}



/**
 *	Compile a GLSL shader program
 */	
GLuint ShaderEngine::compileShader(const std::string& source,
								   GLenum       type,
                                   std::string& errorMsg)
{
	GLint status = 0;
    GLuint handle = 0;

    if (!source.empty())
    {
        handle = glCreateShader(type);
        ShaderEngine::setShaderSource(handle, source);

        if (glIsShader(handle))
        {
	        glCompileShader(handle);
	        glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
        }

        // Check the compilation status
	    if (!status)
	    {
		    ShaderEngine::printShaderLog(handle, errorMsg);
            if (glIsShader(handle))
		        glDeleteShader(handle);
		    return 0;
	    }
    }

	return handle;
}

/**
 *	Links GLSL shader programs
 */	
GLuint ShaderEngine::linkShaders(GLuint &vpHandle,
                                 GLuint &gpHandle,
                                 GLuint &fpHandle)
{
    std::string dummy;
	int dummy_param = 0; 
    return ShaderEngine::linkShaders(vpHandle, gpHandle, fpHandle, dummy_param, dummy_param, dummy_param, dummy);
}

/**
 *	Links GLSL shader programs
 */	
GLuint ShaderEngine::linkShaders(GLuint &vpHandle,
                                 GLuint &gpHandle,
                                 GLuint &fpHandle,
                                 std::string& errorMsg)
{
	int dummy_param = 0; 
    return ShaderEngine::linkShaders(vpHandle, gpHandle, fpHandle, dummy_param, dummy_param, dummy_param, errorMsg);
}

/**
 *	Links GLSL shader programs
 */	
GLuint ShaderEngine::linkShaders(GLuint &vpHandle,
                                 GLuint &gpHandle,
                                 GLuint &fpHandle,
								 int gpVerticesOut,
                                 int gpTypeIn,
                                 int gpTypeOut,
                                 std::string& errorMsg)
{
	GLint isLinked = 0;
    GLuint handle = glCreateProgram();

	// Attach the vertex and fragment shaders to the GLSL program
    if (glIsProgram(handle))
    {
	    if (glIsShader(vpHandle))
		    glAttachShader(handle, vpHandle);
	    if (glIsShader(fpHandle))
    		glAttachShader(handle, fpHandle);
	    if (glIsShader(gpHandle)){
		    glAttachShader(handle, gpHandle);
    
			//max number of emitted vertices is
			glProgramParameteriEXT(handle,GL_GEOMETRY_VERTICES_OUT_EXT,gpVerticesOut);
			//input geometry type
			glProgramParameteriEXT(handle,GL_GEOMETRY_INPUT_TYPE_EXT,gpTypeIn);
			//output geometry type
			glProgramParameteriEXT(handle,GL_GEOMETRY_OUTPUT_TYPE_EXT,gpTypeOut);
		}

    	// Link the shaders
	    glLinkProgram(handle);

	    // Check the link status
	    glGetProgramiv(handle, GL_LINK_STATUS, &isLinked);
    }

	if (!isLinked)
	{
		ShaderEngine::printProgramLog(handle, errorMsg);
		ShaderEngine::deleteProgram(handle);
        handle = 0;
        vpHandle = 0;
        gpHandle = 0;
        fpHandle = 0;
	}
	return handle;
}


/**
 *	Links GLSL shader programs
 */	
GLuint ShaderEngine::createProgramFromSources(const char * vpSource,
                                              const char * gpSource,
                                              const char * fpSource)
{
    GLuint vp = ShaderEngine::compileShader(vpSource, GL_VERTEX_SHADER);
    GLuint gp = ShaderEngine::compileShader(gpSource, GL_GEOMETRY_SHADER_EXT);
    GLuint fp = ShaderEngine::compileShader(fpSource, GL_FRAGMENT_SHADER);
    return ShaderEngine::linkShaders(vp, gp, fp);
}


/**
 *	Print a log when compiling a shader fails 
 */	
void ShaderEngine::printShaderLog(GLuint shader, std::string& errorMsg)
{
	GLint length = 0;
    if (glIsShader(shader))
	    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

	if (length > 0)
	{
		GLchar *tmp_info = new GLchar[length + 1];
		glGetShaderInfoLog(shader, length, NULL, tmp_info);
		errorMsg.append(tmp_info, length);
		
		delete[] tmp_info;
	}
}

/**
 *	Print a log when linking shaders fails 
 */	
void ShaderEngine::printProgramLog(GLuint program, std::string& errorMsg)
{
	GLint length = 0;
    if (glIsProgram(program))
	    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

	if (length > 0)
	{
        if (length > 100)
            length = 100;

        GLchar *info = new GLchar[length + 1];
        glGetProgramInfoLog(program, length, NULL, info);
        errorMsg.append(info, length);

        if (length == 100)
            errorMsg.append("...");
        delete[] info;
	}
}
