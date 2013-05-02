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
