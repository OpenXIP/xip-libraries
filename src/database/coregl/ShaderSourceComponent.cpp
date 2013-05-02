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

	// Open the shader file
	in.open(filename);
	if (in.fail())
    {
        errstr.append("Failed to open file");
		return 0;
    }

    mOrigin = std::string(filename);

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
                    + std::string(filename)
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

