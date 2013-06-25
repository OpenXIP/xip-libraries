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
#include <xip/inventor/core/XipStringUtils.h>
#include <xip/inventor/coregl/ShaderSourceComponent.h>
#include <fstream>


ShaderSourceComponent::ShaderSourceComponent()
{
    clear();
}

ShaderSourceComponent::ShaderSourceComponent(const char * name, const int type)
{
    clear();
    mName = std::string(name);
    mType = type;
}

ShaderSourceComponent::~ShaderSourceComponent()
{
}

void ShaderSourceComponent::clear()
{
    mName = "";
    mOrigin = "";
    mType = 0;
    mSourceTimeStamp = 0;

    clearContent();
}

void ShaderSourceComponent::clearContent()
{
    mTimeStamp = 0;
    mIsDirty = false;

    mSuppHeader.clear();
    mHeader.clear();
    mGlobal.clear();
    mDefineVec.clear();
    mFuncMap.clear();
    mParamMap.clear();
}

int ShaderSourceComponent::countBrackets(std::string &str, std::string type1, std::string type2)
{
    int pos = -1, count = 0;
    do
    {
        pos = str.find_first_of(type1, pos+1); 
        if (pos != std::string::npos)
            count++;
    }while( pos != std::string::npos );

    pos = -1;
    do
    {
        pos = str.find_first_of(type2, pos+1);
        if (pos != std::string::npos)
            count--;
    }while( pos != std::string::npos );
    return count;
}

int ShaderSourceComponent::countOccurence(const std::string &str, std::string token) const
{
    int pos = 0, count = 0;
    do
    {
        pos = str.find_first_of(token, pos);
        if (pos != std::string::npos)
        {
            count++;
            pos++;
        }
    } while (pos != std::string::npos);
    return count;
}

int ShaderSourceComponent::countLines(const std::string &str) const
{
    return (str.empty() || str == "")
        ? 0
        : countOccurence(str, "\n");
}

int ShaderSourceComponent::countBrackets(const std::string &str) const
{
    return (str.empty() || str == "")
        ? 0
        : countOccurence(str, "{") - countOccurence(str, "}");
}

int ShaderSourceComponent::countParentheses(const std::string &str) const
{
    return (str.empty() || str == "")
        ? 0
        : countOccurence(str, "(") - countOccurence(str, ")");
}

/**
 *	Read a shader file. Add the preprocessor definitions at
 *	the beginning of the file before the compilation.
 */	
int ShaderSourceComponent::readSourceFile(const char *filename, std::string& errstr)
{
	std::ifstream				in;
	std::string					s, line, func;
    int numL = 0;
    
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
        errstr.append("Failed to open file");
		return 0;
    }

    mOrigin = std::string(fileLocal);

    int mode=NONE, oldmode=NONE, numBrackets=0, numParanthesis=0;
	// Append the source code
	while (std::getline(in, line))
    {
        numL++;
        oldmode = mode;

        if (line.compare(0,14,"/***DEFINE***/") == 0)
        {
            mode = DEFINE;
        }
        else if (line.compare(0,14,"/***HEADER***/") == 0)
        {
            mode = HEADER;
            mHeader.numLoffset = numL;
        }
        else if (line.compare(0,14,"/***GLOBAL***/") == 0)
        {
            mode = GLOBAL;
            mGlobal.numLoffset = numL;
        }
        else if (line.compare(0,16,"/***FUNCTION***/") == 0)
        {
            mode = FUNCTION;
        }

        if (mode != oldmode)
            continue;

        switch (mode)
        {
        case NONE: //step to next line
            break;

        case DEFINE: //store defines
            if (line.compare(0,7,"#define") == 0)
            {
                int s,t;
                s = line.find_first_not_of(" ", 7);
                t = line.find_first_of(" ", s+1);
                std::string key = (t == std::string::npos) ? line.substr(s) : line.substr(s,t-s);
                std::string val = (t == std::string::npos) ? "" : line.substr(t+1);

                if (key.find_first_not_of(" \n\t") == std::string::npos)
                    throw;
                setDefine(key.c_str(), val.c_str());
            }
            break;

        case HEADER: //store header lines
            mHeader.str += line + "\n";
            break;

        case GLOBAL: //store global lines
            mGlobal.str += line + "\n";
            break;

        case FUNCTION: //store function signatures
            numBrackets = countBrackets(line, "{", "}");
            numParanthesis = countBrackets(line, "(", ")");
            if (numBrackets || numParanthesis)
            {
                errstr.append("Failed to parse file \""
                    + std::string(fileLocal)
                    + "\", function signatures need to be a single line without { !");
                return 0; //Having a bracket on the signature line is forbidden
            }
            func = line;
            mFuncMap[func].str = "";
            mFuncMap[func].numLoffset = numL;
            oldmode = mode = 5;
            break;

        case FUNCTION_BODY: //store func body
            numBrackets += countBrackets(line, "{", "}");
            mFuncMap[func].str += line + "\n";
            if (numBrackets <= 0)
                mode = NONE;
            break;

        default: //bad
            errstr.append("Unknown error when parsing file");
            return 0;
        }
    }

    this->updateLineNumbers();

    return 1;
}


void ShaderSourceComponent::updateLineNumbers()
{
    mSuppHeader.numL = countLines(mSuppHeader.str);
    mHeader.numL     = countLines(mHeader.str);
    mGlobal.numL     = countLines(mGlobal.str);

    FuncMap_t::iterator it;
    for (it = mFuncMap.begin(); it != mFuncMap.end(); it++)
        it->second.numL = countLines(it->second.str) + 1;
}





const char * ShaderSourceComponent::getDefineKey(int i) const
{
    return getDefine(i)->first.c_str();
}

const char * ShaderSourceComponent::getDefineValue(int i) const
{
    return getDefine(i)->second.str.c_str();
}

const char * ShaderSourceComponent::getFunctionSignature(int i) const
{
    return getFunction(i)->first.c_str();
}

const char * ShaderSourceComponent::getFunctionBody(int i) const
{
    return getFunction(i)->second.str.c_str();
}


void ShaderSourceComponent::getParameter(int i, int& key, int& val) const
{
    i = (i < 0) ? 0 : (i > int(mParamMap.size())) ? mParamMap.size()-1 : i;
    IntMap_t::const_iterator it = mParamMap.begin();
    advance(it, i);
    
    key = it->first;
    val = it->second;
}


bool  ShaderSourceComponent::getParamter(int key, int &value) const
{
    IntMap_t::const_iterator it = mParamMap.find(key);
    if(it == mParamMap.end())
	    return false;
 
    value = it->second;
    return true;
}
 
int  ShaderSourceComponent::numParameters() const
{
	if(mParamMap.empty())
		return 0;
	return mParamMap.size();
}








const std::string ShaderSourceComponent::getDefines()
{
    std::string str = "";
    DefineVec_t::const_iterator it;
    for (it = mDefineVec.begin(); it != mDefineVec.end(); it++)
        str += "#define " + it->first + " " + it->second.str + "\n";
    return str.c_str();
}

const std::string ShaderSourceComponent::getFunctionPrototypes()
{
    std::string str = "";
    FuncMap_t::const_iterator it;
    for (it = mFuncMap.begin(); it != mFuncMap.end(); it++)
        str += it->first + ";\n";
    return str.c_str();
}

const std::string ShaderSourceComponent::getFunctionDefinitions()
{
    std::string str = "";
    FuncMap_t::const_iterator it;
    for (it = mFuncMap.begin(); it != mFuncMap.end(); it++)
        str += it->first + "\n" + it->second.str + "\n";
    return str.c_str();
}

const std::string ShaderSourceComponent::getFullComponent()
{
    std::string str = "";

    if (getNumDefines())
        str += getDefines();
    if (getNumLinesInSuppHeader())
        str += mSuppHeader.str;
    if (getNumLinesInHeader())
        str += mHeader.str;
    if (getNumLinesInGlobal())
        str += mGlobal.str;
    if (getNumFunctions())
    {
        str += getFunctionPrototypes();
        str += std::string("\n");
        str += getFunctionDefinitions();
    }
    return str.c_str();
}

bool ShaderSourceComponent::isEmpty() const
{
    bool any =
        (this->getSuppHeader() != "") |
        (this->getNumDefines() != 0)  |
        (this->getHeader() != "")     |
        (this->getGlobal() != "")     |
        (this->getNumFunctions() != 0);
    return !any;
}






const ShaderSourceComponent::DefineVec_t::const_iterator ShaderSourceComponent::getDefine(int i) const
{
    i = (i < 0) ? 0 : (i > int(mDefineVec.size())) ? mDefineVec.size()-1 : i;
    DefineVec_t::const_iterator it = mDefineVec.begin();
    advance(it, i);
    return it;
}

const ShaderSourceComponent::FuncMap_t::const_iterator ShaderSourceComponent::getFunction(int i) const
{
    i = (i < 0) ? 0 : (i > int(mFuncMap.size())) ? mFuncMap.size()-1 : i;
    FuncMap_t::const_iterator it = mFuncMap.begin();
    advance(it, i);
    return it;
}









void ShaderSourceComponent::addTo(const char * s, std::string& tar, int& ntar)
{
    std::string str = s;
    if (!str.empty())
    {
        tar += str;
        if (tar.compare(tar.size()-1, 1, "\n") != 0)
            tar += "\n";
    }
    ntar = countLines(tar);
}

void ShaderSourceComponent::addToSuppHeader(const char * str)
{
    addTo(str, mSuppHeader.str, mSuppHeader.numL);
}

void ShaderSourceComponent::addToHeader(const char * str)
{
    addTo(str, mHeader.str, mHeader.numL);
}

void ShaderSourceComponent::addToGlobal(const char * str)
{
    addTo(str, mGlobal.str, mGlobal.numL);
}

int ShaderSourceComponent::setDefine(const char * key, const char * val, int numLineOffset)
{
    std::string signature = key;
    std::string body = val;
    int replace = 0;

    if (signature == "")
        throw;

    if (signature != "")
    {
        //Get rid of all trailing \n
        int t = body.find_last_not_of(" \n\t");
        if (t != std::string::npos)
            body = body.substr(0,t+1);
        DefineVec_t::iterator it;
        for (it = mDefineVec.begin(); it != mDefineVec.end(); it++)
        {
            if (it->first == key)
            {
                replace = 1;
                break;
            }
        }

        if (replace)
            mDefineVec.erase(it);
        mDefineVec.push_back(DefinePair_t(key, StringBatch(body, 1, numLineOffset)));
    }
    return replace;
}

int ShaderSourceComponent::setFunction(const char * key, const char * val, int numLineOffset)
{
    std::string signature = key;
    std::string body = val;
    int replace = 0;

    if (signature == "" || body == "")
        throw;

    if (signature != "")
    {
        //Make sure we have only a SINGLE \n at end of string
        int t = body.find_last_not_of(" \n\t");
        if (t != std::string::npos)
            body = body.substr(0,t+1);
        body += "\n";

        replace = (mFuncMap.find(signature) != mFuncMap.end()) ? 1 : 0;
        //mFuncMap[signature] = StringBatch(body, countLines(body)+1, 0);
        mFuncMap[signature] = StringBatch(body, countLines(body)+1, numLineOffset);
    }
    return replace;
}

void ShaderSourceComponent::setParameter(const int key, const int val)
{
    mParamMap[key] = val;
}

