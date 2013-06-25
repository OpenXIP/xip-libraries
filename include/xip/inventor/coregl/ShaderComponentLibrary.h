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

#ifndef SHADER_COMPONENT_LIBRARY_H
#define SHADER_COMPONENT_LIBRARY_H


#include <xip/inventor/coregl/ShaderSourceComponent.h>


#include <string>
#include <map>


#include <xip/inventor/coregl/xipivcoregl.h>


/**
 *  Component       : XIP
 *  Name            : ShaderComponentLibrary
 *  Author          : Lindholm S, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 2-Oct-2007
 *  Description     : Class Declaration/Definition.
 *                    Singleton class providing support
 *                    for a shader manager that handles
 *                    all compiled and linked shaders.
 *
 *  Copyright © Siemens AG 2006-2007. All Rights Reserved.
 */


class XIPIVCOREGL_API ShaderComponentLibrary;
class XIPIVCOREGL_API GLSLUniform;




class XIPIVCOREGL_API ShaderComponentLibrary
{
private:

    typedef std::map<std::string, ShaderSourceComponent> ComponentMap;
    typedef std::map<std::string, GLSLUniform>           GLSLUniformMap;
    typedef std::map<std::string, GLSLUniformMap>        ComponentUniformMap;

public:

    static void initClass();
    static ShaderComponentLibrary * getInstance();

    void  insertEntry(ShaderSourceComponent& c) {mMap[c.getName()] = c;}
    void  removeEntry(const char * name)        {mMap.erase(std::string(name));}

    void  insertUniform(const char * compName, const char * uniformName, int type, void * value);
    void  removeUniforms(const char * compName);
    int   getNumUniforms(const char * compName);
    const GLSLUniform * getUniform(const char * compName, int idx);
    const GLSLUniform * getUniform(const char * compName, const char * uniformName);

    const ShaderSourceComponent * getEntry(const char * str);

private:

    ShaderComponentLibrary();
    ~ShaderComponentLibrary();

    ComponentMap        mMap;
    ComponentUniformMap mUniformMap;

    static ShaderComponentLibrary * mInstance;    /**< Singleton object */
};













class XIPIVCOREGL_API GLSLUniform
{
public:

    enum UniformType
    {
        UNIFORM_INT   = 1,
        UNIFORM_VEC2S = 2,
        UNIFORM_VEC3S = 3,
        UNIFORM_VEC4S = 4,
        UNIFORM_FLOAT = 5,
        UNIFORM_VEC2F = 6,
        UNIFORM_VEC3F = 7,
        UNIFORM_VEC4F = 8,
        UNIFORM_MAT3  = 9,
        UNIFORM_MAT4  = 10,
    };

    GLSLUniform();
    GLSLUniform(const char * name, int type, void * values);
    ~GLSLUniform();

    void updateValues(void * values);

    const char *    getName() const      {return mName;}
    int             getType() const      {return mType;}
    bool            isFloat() const      {return mIsFloat;}
    int             getNumVals() const   {return mNumVals;}
    const int *     getIntVals() const   {return mIvals;}
    const float *   getFloatVals() const {return mFvals;}

private:

    char        mName[64];
    int         mType;
    bool        mIsFloat;

    int         mNumVals;
    int         mIvals[4];
    float       mFvals[16];
};




#endif // SHADER_PROGRAM_MANAGER_H


