/*[ Compilation unit -----------------------------------------------
Component       : RAD – Image Processing(IP)
Name            : ShaderComponentLibrary
Author          : Lindholm S, SCR, Princeton
Language        : C++ Source File
Creation Date   : 2-Oct-2007
ClearCaseInfo   : ClearCase $Version$ Tag
Test State      : %Q%
Description     : Class Declaration/Definition.
                  Singleton class providing support
                  for a shader manager that handles
                  all compiled and linked shaders.
Requirement Keys: 
Internals       : 
History         : 
Copyright © Siemens AG 2006-2007. All Rights Reserved.
-----------------------------------------------------------------*/


#include <xip/inventor/coregl/ShaderComponentLibrary.h>

#include <string.h>

/**
 * Definition of static instance variable.
 */
ShaderComponentLibrary * ShaderComponentLibrary::mInstance = 0;

/**
 * Class initiator.
 */
void ShaderComponentLibrary::initClass()
{
    // The skeleton exists due to Invetor methology
}

/**
 * Instance manager.
 */
ShaderComponentLibrary * ShaderComponentLibrary::getInstance()
{
    if (!mInstance)
        mInstance = new ShaderComponentLibrary;
    return mInstance;
}

/**
 * Constructor.
 */
ShaderComponentLibrary::ShaderComponentLibrary()
{
}

/**
 * Destructor.
 * Frees the singleton instance.
 */
ShaderComponentLibrary::~ShaderComponentLibrary()
{
    if (mInstance)
        delete mInstance;
}

const ShaderSourceComponent * ShaderComponentLibrary::getEntry(const char * str)
{
    ShaderSourceComponent * comp = 0;
    std::string key = str;

    if (mMap.find(key) != mMap.end())
        comp = &mMap[key];

    return comp;
}



void ShaderComponentLibrary::insertUniform(const char *compName, const char *uniformName, int type, void *value)
{
    if (!compName || !uniformName || !value)
        return;

    if (mUniformMap.find(compName) == mUniformMap.end())
        mUniformMap[compName] = GLSLUniformMap();

    GLSLUniform * uni = &mUniformMap[compName][uniformName];
    if (uni)
    {
        if (uni->getType() == type && strcmp(uni->getName(), uniformName) == 0)
            uni->updateValues(value);
        else
            mUniformMap[compName][uniformName] =
                GLSLUniform(uniformName, type, reinterpret_cast<void *>(value));
    }
}

void ShaderComponentLibrary::removeUniforms(const char *compName)
{
    mUniformMap.erase(compName);
}

int ShaderComponentLibrary::getNumUniforms(const char *compName)
{
    if (mUniformMap.find(compName) != mUniformMap.end())
        return mUniformMap[compName].size();
    else
        return 0;
}

const GLSLUniform * ShaderComponentLibrary::getUniform(const char *compName, int idx)
{
    if (mUniformMap.find(compName) != mUniformMap.end())
    {
        GLSLUniformMap::const_iterator it = mUniformMap[compName].begin();
        advance(it, idx);
        return &(it->second);
    }
    else
        return 0;
}

const GLSLUniform * ShaderComponentLibrary::getUniform(const char *compName, const char *uniformName)
{
    if (mUniformMap.find(compName) != mUniformMap.end())
        if (mUniformMap[compName].find(uniformName) != mUniformMap[compName].end())
            return &mUniformMap[compName][uniformName];

    return 0;
}



























GLSLUniform::GLSLUniform()
{
    //mName = new char[64];
    mName[0] = 0;
    mType = 0;
    mIsFloat = false;
    mNumVals = 0;
    //mIvals = new int[4];
    //mFvals = new float[16];
}

GLSLUniform::GLSLUniform(const char * name, int type, void * values)
{
    if (name && strlen(name) < 64)
        strcpy(mName, name);
    else
        mName[0] = 0;

    mType = type;

    mIsFloat = (type >= UNIFORM_FLOAT) ? true : false;

    switch (type)
    {
    case UNIFORM_INT:
    case UNIFORM_FLOAT:
        mNumVals = 1;
        break;
    case UNIFORM_VEC2S:
    case UNIFORM_VEC2F:
        mNumVals = 2;
        break;
    case UNIFORM_VEC3S:
    case UNIFORM_VEC3F:
        mNumVals = 3;
        break;
    case UNIFORM_VEC4S:
    case UNIFORM_VEC4F:
        mNumVals = 4;
        break;
    case UNIFORM_MAT3:
        mNumVals = 9;
        break;
    case UNIFORM_MAT4:
        mNumVals = 16;
        break;
    default:
        mNumVals = 0;
    }

    updateValues(values);
}

void GLSLUniform::updateValues(void * values)
{
    if (!mIsFloat)
    {
        const int * ip = reinterpret_cast<const int*>(values);
        for (int i = 0; i < mNumVals; i++)
            mIvals[i] = ip[i];
    }
    else
    {
        const float * fp = reinterpret_cast<const float*>(values);
        for (int i = 0; i < mNumVals; i++)
            mFvals[i] = fp[i];
    }
}

GLSLUniform::~GLSLUniform()
{
}




