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

#ifndef SHADER_ENGINE_H
#define SHADER_ENGINE_H


#include <xip/inventor/coregl/xipivcoregl.h>

#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <xip/system/standard.h>
#include <xip/system/GL/gl.h>
#include <string>

#include <xip/inventor/coregl/ShaderSourceComponent.h>


/**
 *  Component       : XIP
 *  Name            : ShaderEngine
 *  Author          : Lindholm S, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 26-Jun-2009
 *  Description     : Static class for common shader operations
                        such as compile/link/etc.
 *
 *  Copyright � Siemens AG 2006-2007. All Rights Reserved.
 */


class XIPIVCOREGL_API ShaderEngine
{
public:

    struct ShaderBatch
    {
        GLuint                  handle;
        __uint64                timestamp;
        bool                    dirtyTimestamp;
        ShaderSourceComponent   source;
        bool                    dirtySource;

        ShaderBatch() {clear();}

        void clear()
        {
            handle      = 0;
            timestamp   = 0;
            dirtyTimestamp = true;
            source.clear();
            dirtySource = true;
        }
    };

    struct ProgramBatch
    {
        SbString            tag;
        GLuint              handle;
        __uint64            timestamp;
        bool                dirtyTimestamp;
        ShaderBatch         vertShader;
        ShaderBatch         geomShader;
        ShaderBatch         fragShader;

		GLint				gsNumVertOut;
		GLint				gsPrimTypeIn;
		GLint				gsPrimTypeOut;


        ProgramBatch() {clear();}

        void clear()
        {
            tag       = "";
            handle    = 0;
            timestamp = 0;
            dirtyTimestamp = false;
            vertShader.clear();
            geomShader.clear();
            fragShader.clear();

			gsNumVertOut = 0;
			gsPrimTypeIn = 0;
			gsPrimTypeOut = 0;

        }
    };

public:

    static int            getSourceFileTimeStamp(const char *filename);
    static int            getSourceFileTimeStamp(const char *filename, std::string& errorMsg);
    static std::string    readShaderSourceFile(const char *filename);
    static std::string    readShaderSourceFile(const char *filename, std::string& errorMsg);
    static GLuint         compileShader(const char * source, GLenum type);
    static GLuint         compileShader(const std::string& source, GLenum type, std::string& errorMsg);
    static GLuint         linkShaders(GLuint& vpHandle, GLuint& gpHandle, GLuint& fpHandle);
    static GLuint         linkShaders(GLuint& vpHandle, GLuint& gpHandle, GLuint& fpHandle, std::string& errorMsg);
    static GLuint         linkShaders(GLuint& vpHandle, GLuint& gpHandle, GLuint& fpHandle, int gpVerticesOut, int gpTypeIn, int gpTypeOut, std::string& errorMsg);
    static GLuint         createProgramFromSources(const char * vpSource, const char * gpSource, const char * fpSource);
    static void           deleteProgram(GLuint& programHandle);
    static void           deleteShader(GLuint& shaderHandle);

private:

    static void setShaderSource(GLuint handle, std::string source);
    static void printShaderLog(GLuint shader, std::string& errorMsg);
    static void printProgramLog(GLuint program, std::string& errorMsg);
};

#endif // SHADER_PROGRAM_MANAGER_H
