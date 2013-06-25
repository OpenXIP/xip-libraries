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

#ifndef SHADER_SOURCE_COMPONENT_H
#define SHADER_SOURCE_COMPONENT_H


#define VEC


/**
 *  Component       : 
 *  Name            : ShaderSourceComponent
 *  Author          : Lindholm S, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 25-Jun-2009
 *  Description     :   Standalone (no GL, no Inventor, noXip)
 *                      struct for framebuffer objact information.
 *                      intended to be used in instances of
 *                      ShaderSourceLibrary.
 *
 *  Copyright © Siemens AG 2006-2007. All Rights Reserved.
 */

// Used for insertion of defines in shader source
#include <string>
#include <vector>
#include <map>

// Used for timestamp lookup on shader source
#include <sys/stat.h>
#include <time.h>

#include <xip/inventor/coregl/xipivcoregl.h>



class XIPIVCOREGL_API ShaderSourceComponent
{
public:
    
    enum SourceMode
    {
        NONE            = 0,
        DEFINE          = 1,
        HEADER          = 2,
        GLOBAL          = 3,
        FUNCTION        = 4,
        FUNCTION_BODY   = 5,
    };

    struct StringBatch
    {
        std::string str;
        int numL; //Lines
        int numLoffset; //Line offset

        StringBatch()
        {
            clear();
        }
        StringBatch(std::string s, int n, int o)
        {
            str = s;
            numL = n;
            numLoffset = o;
        }
        void clear()
        {
            str = "";
            numL = 0;
            numLoffset = 0;
        }
    };

    struct LineEntry
    {
        int len;
        int off;
        std::string comp;
        std::string part;
        std::string orig;

        LineEntry()
        {
            len = 0;
            off = 0;
            comp = "";
            part = "";
            orig = "";
        }
        LineEntry(int length, int offset, std::string component, std::string cpart, std::string origin)
        {
            len = length;
            off = offset;
            comp = component;
            part = cpart;
            orig = origin;
        }
    };

    /*
        Definitions are NOT sorted
    */
    struct def_less : public std::binary_function<std::string, std::string, bool>
	{	// functor for operator<
	    bool operator()(const std::string& _Left, const std::string& _Right) const
		{
            return _Left < _Right;
		}
	};

    /*
        Function prototypes are compaired without the return type
        This way they will end up in alphabetical order in the resulting shader
    */
    struct func_less : public std::binary_function<std::string, std::string, bool>
	{	// functor for operator<
	    bool operator()(const std::string& _Left, const std::string& _Right) const
		{
            int s,t;
            s = _Left.find_first_of(" ");
            s = _Left.find_first_not_of(" ", s+1);
            t = _Right.find_first_of(" ");
            t = _Right.find_first_not_of(" ", t+1);
            return (_Left.substr(s) < _Right.substr(t));
            //return (_Left < _Right);
		}
	};
    typedef std::pair<std::string, StringBatch>                 DefinePair_t;
    typedef std::pair<std::string, LineEntry>                   DefineLinePair_t;
    typedef std::vector<DefinePair_t>                           DefineVec_t;
    typedef std::vector<DefineLinePair_t>                       DefineLineVec_t;
    typedef std::map<std::string, StringBatch, func_less>       FuncMap_t;
    typedef std::map<std::string, LineEntry, func_less>         FuncLineMap_t;

    typedef std::map<int, int>                                  IntMap_t;

public:

    ShaderSourceComponent();
    ShaderSourceComponent(const char * name, const int type);
    ~ShaderSourceComponent();

    void clear();
    void clearContent();

    bool                isNameEmpty() const         {return (mName.empty()) ? true : false;}
    bool                isOriginEmpty() const       {return (mOrigin.empty()) ? true : false;}
    const char *        getName() const             {return mName.c_str();}
    const char *        getOrigin() const           {return mOrigin.c_str();}
    int                 getType() const             {return mType;}
    int                 getTimeStamp() const        {return mTimeStamp;}
    int                 getSourceTimeStamp() const  {return mSourceTimeStamp;}
    bool                isDirty() const             {return mIsDirty;}
    bool                isEmpty() const;

    void setName(const char * str)                  {mName = std::string(str);}
    void setOrigin(const char * str)                {mOrigin = std::string(str);}
    void setType(const int type)                    {mType = type;}
    void setTimeStamp(const int time)               {mTimeStamp = time;}
    void setSourceTimeStamp(const int time)         {mSourceTimeStamp = time;}
    void setDirty(bool dirty)                       {mIsDirty = dirty;}

    const char * getSuppHeader() const              {return mSuppHeader.str.c_str();}
    const char * getHeader() const                  {return mHeader.str.c_str();}
    const char * getGlobal() const                  {return mGlobal.str.c_str();}
    const char * getDefineKey(int i) const;
    const char * getDefineValue(int i) const;
    const char * getFunctionSignature(int i) const;
    const char * getFunctionBody(int i) const;

    /**!
        This functions uses std::string as return type,
        use with caution if different DLL's are used.
    **/
    const std::string getFullComponent();       

    int getNumLinesInSuppHeader() const             {return mSuppHeader.numL;}
    int getNumLinesInHeader() const                 {return mHeader.numL;}
    int getNumLinesInGlobal() const                 {return mGlobal.numL;}
    int getNumLinesInDefine(int i) const            {return getDefine(i)->second.numL;}
    int getNumLinesInFunction(int i) const          {return getFunction(i)->second.numL;}

    int getLineOffsetInSuppHeader() const           {return mSuppHeader.numLoffset;}
    int getLineOffsetInHeader() const               {return mHeader.numLoffset;}
    int getLineOffsetInGlobal() const               {return mGlobal.numLoffset;}
    int getLineOffsetInDefine(int i) const          {return getDefine(i)->second.numLoffset;}
    int getLineOffsetInFunction(int i) const        {return getFunction(i)->second.numLoffset;}
    int getNumDefines() const {return mDefineVec.size();}
    int getNumFunctions() const {return mFuncMap.size();}
    int getNumParameters() const {return mParamMap.size();}

    void addToSuppHeader(const char * str);
    void addToHeader(const char * str);
    void addToGlobal(const char * str);
    int  setDefine(const char * key, const char * val, int numLineOffset = 0);
    int  setFunction(const char * key, const char * val, int numLineOffset = 0);

	bool getParamter(int key, int &value) const;
	int  numParameters() const;
    void getParameter(int i, int& key, int& val) const;
    void setParameter(const int key, const int val);

    int readSourceFile(const char * filename, std::string& errstr);

private:

    const DefineVec_t::const_iterator getDefine(int i) const;
    const FuncMap_t::const_iterator getFunction(int i) const;

    const std::string getDefines();
    const std::string getFunctionPrototypes();
    const std::string getFunctionDefinitions();

    int countBrackets(std::string &str, std::string type1, std::string type2);
    int countOccurence(const std::string &str, std::string token) const;
    int countLines(const std::string &str) const;

    int countBrackets(const std::string &str) const;
    int countParentheses(const std::string &str) const;

    void addTo(const char * s, std::string& tar, int& ntar);
    void updateLineNumbers();

    std::string  mHolder; //Temp storage for return thingys

    std::string  mName;            // Component library name
    std::string  mOrigin;          // Filename / C++ / Generated / etc.
    int          mType;            // Must be one of GL_VERTEX_SHADER / GL_GEOMETRY_SHADER_EXT / GL_FRAGMENT_SHADER
    int          mTimeStamp;       // Time of source creation (including #define's!!)
    int          mSourceTimeStamp; // Time stamp on disk

    StringBatch mSuppHeader;  // In case of user specified #defines etc.
    StringBatch mHeader;      // Contains: #defines and uniforms
    StringBatch mGlobal;      // Contains: global variables and function signatures
    DefineVec_t mDefineVec;   // Contains: #define statements (this allows redefinitions)
    FuncMap_t   mFuncMap;     // Contains: function bodies
    IntMap_t    mParamMap;    // Contains: necessary program parameters (eg, GL_GEOMETRY_OUTPUT_TYPE_EXT etc.)

    bool         mIsDirty;
};

#endif //SHADER_SOURCE_COMPONENT_H
