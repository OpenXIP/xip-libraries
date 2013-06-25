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
