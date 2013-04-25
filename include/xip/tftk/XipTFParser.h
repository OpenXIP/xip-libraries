// -*- Mode: c++; c-indentation-style: stroustrup; -*-

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

#ifndef  XIP_TF_PARSER_H
#define  XIP_TF_PARSER_H

#include <stdio.h>
#include <stdlib.h>

#ifndef XIP_INLINE
#define XIP_INLINE inline
#endif

#define XIP_THROW_EXCEPTION(f,l,m)

/*
  XIP Transfer Function Toolkit (XIP TFTK)

*/


/*
  ------------------------------------------------------------------------
    XipTFParser

    This TF Parser generates a parse tree that can be used by the
    TF Engine to create a XipTFDefinition object.

    It may also be used to generate update requests to an existing TF
    Definition.
    ------------------------------------------------------------------------
*/

class XipTFParser {
public:
    enum Flags {
	FLAG_CLEAR = 0x0001
    };

    enum Error {
	ERR_NONE = 0,
	ERR_UNEXPECTED_END_OF_FILE,
	ERR_INVALID_FIELD_NAME,
	ERR_MALLOC_FAILED,
	ERR_INVALID_ARRAY_SPEC,
	ERR_INVALID_COMPOUND_ARG,
	ERR_MISSING_ARRAY_OPEN_BRACE,
	ERR_MISSING_SEMICOLON,
	ERR_INVALID_CHARACTER,
	ERR_MEMORY_FAILURE,
	ERR_PARSER_ERROR_INVALID_STATE,
	ERR_TOO_MANY_CLOSING_BRACES,
    };

    /*
      Parse tree node class
    */
    class ParseNode {
    public:
	friend class XipTFParser;

	enum Type {
	    TYPE_SINGLE_FIELD,
	    TYPE_ARRAY_FIELD,
	    TYPE_COMPOUND_FIELD,
	};

	XIP_INLINE ParseNode(Type type, char * name = 0,
			     char * value = 0, char * arg = 0);
	XIP_INLINE ~ParseNode();

	XIP_INLINE Type		getType() const { return mType; }

	XIP_INLINE ParseNode *	getChild() const { return mChild; }
	XIP_INLINE ParseNode *	getNext() const { return mNext; }
	XIP_INLINE void		setChild(ParseNode * child);
	XIP_INLINE void		setNext(ParseNode * next);

	XIP_INLINE const char *	getName() const { return mName; }
	XIP_INLINE const char *	getValue() const { return mValue; }
	XIP_INLINE const char *	getArg() const { return mArg; }

	XIP_INLINE char *	transferName();
	XIP_INLINE char *	transferValue();
	XIP_INLINE char *	transferArg();

	XIP_INLINE int printTree(FILE * out, int indent) const;

    protected:
	Type		mType;
	char *		mName;
	char *		mValue;
	char *		mArg;		// Arrays and Compounds have args
	ParseNode *	mNext;
	ParseNode *	mChild;
    };

    XipTFParser();
    ~XipTFParser();

    /*
      Parse a complete source string.
      This is to parse a complete description (from file)
    */
    int parseComplete(const char * source, int length,
		      int * line, int * col);


    ParseNode * getParseTree() { return mParseTree; }

#if 0
    /*
      Update the active TF container (maybe not the best name)
      For parsing updates from client/server, canonical form
    */
    int parseUpdate(const char * source, int length,
		    int * line, int * col);
#endif

protected:
    enum ParseState {
	PS_INIT,
	PS_FIELD,
	PS_FIELD_VALUE,
	PS_ARRAY_FIELD,
	PS_COMPOUND_FIELD,
	PS_NUMBER_OF_STATES
    };

    enum LexicalToken {
	LT_NONE,
	LT_END_OF_INPUT,
	LT_FIELD_NAME,
	LT_OPEN_ARRAY_SPEC,
	LT_CLOSE_ARRAY_SPEC,
	LT_OPEN_COMPOUND_ARG,
	LT_CLOSE_COMPOUND_ARG,
	LT_OPEN_COMPOUND,
	LT_CLOSE_COMPOUND,
	LT_SINGLE_VALUE,
	LT_ARRAY_VALUE,
	LT_COMPOUND_VALUE,
	LT_SINGLE_FIELD,
	LT_FIELD_ARGUMENT,
	LT_NUMBER_OF_TOKENS
    };

    enum ParserAction {
	PA_NONE,
	PA_INVALID_TOKEN,
	PA_NUMBER_OF_ACTIONS
    };

    XIP_INLINE ParseNode ** & nodeRefTop();
    XIP_INLINE void nodeRefPush();
    XIP_INLINE void nodeRefPop();


    int lexicalField();
    int lexicalValue();
    int lexicalArrayField();
    int lexicalCompoundField();
    int lexicalSingleValue();
    int lexicalArrayValue();
    int lexicalFieldArgument();
    void lexicalWhiteSpace();

    void assignFieldName(char * name);
    void assignFieldValue(char * value);
    void assignFieldArg(char * arg);

    void addParseNode(ParseNode::Type type);

    ParseNode *		mParseTree;

    ParseNode ***	mStackRef;		// ParseNode Linkage reference stack
    int			mStackRefTop;		// Top Entry on stack
    int			mStackRefSize;		// Size of stack

#if 0
    int			mParseState;

    char *		mTokenBuf;
    int			mTokenLength;
    int			mTokenBufSize;
#endif
    char *	mFieldName;
    char *	mFieldValue;
    char *	mFieldArg;

    int			mLineCount;
    const char * 	mLineStart;

    const char *	mSource;
    int			mSourceLength;
    const char *	mPos;
    const char *	mEnd;

    int			mError;
};


XIP_INLINE XipTFParser::ParseNode ** &
XipTFParser::nodeRefTop()
{
    return mStackRef[mStackRefTop];
}

XIP_INLINE void
XipTFParser::nodeRefPush()
{
    // Need to grow?
    if (mStackRefTop + 1 >= mStackRefSize)
    {
	mStackRefSize *= 2;		// Grow policy...

	ParseNode *** newStack = new ParseNode **[mStackRefSize];

	XIP_THROW_EXCEPTION(__FILE__, __LINE__, "Memory allocation failed");

	for (int i = 0; i < mStackRefTop; i++)
	{
	    newStack[i] = mStackRef[i];
	}

	delete mStackRef;
	mStackRef = newStack;
    }

    mStackRefTop++;
}

XIP_INLINE void
XipTFParser::nodeRefPop()
{
    if (mStackRefTop > 0)
    {
	mStackRefTop--;
    }
}


XIP_INLINE
XipTFParser::ParseNode::ParseNode(Type type, char * name,
				  char * value, char * arg)
{
    mType = type;
    mName = name;
    mValue = value;
    mArg = arg;
    mNext = 0;
    mChild = 0;
}

XIP_INLINE
XipTFParser::ParseNode::~ParseNode()
{
    ParseNode * next = mNext;
    ParseNode * child = mChild;

    free(mName);
    free(mValue);
    free(mArg);

    mNext = 0;
    mChild = 0;

    delete child;
    delete next;
}

XIP_INLINE void
XipTFParser::ParseNode::setChild(ParseNode * child)
{
    delete mChild;
    mChild = child;
}

XIP_INLINE void
XipTFParser::ParseNode::setNext(ParseNode * next)
{
    delete mNext;
    mNext = next;
}

XIP_INLINE int
XipTFParser::ParseNode::printTree(FILE * out, int indent) const
{
    int printed = 1;

    switch (mType)
    {
    case TYPE_SINGLE_FIELD:
        fprintf(out, "");
	if (mValue) fprintf(out, "%*s%-24s%s;\n", indent, "", mName, mValue);
	else fprintf(out, "%*s%s;\n", indent, "", mName);
	break;

    case TYPE_ARRAY_FIELD:
        fprintf(out, "%*s%s", indent, "", mName);
	fprintf(out, "[%s]\n%*s{\n",
		mArg, indent, "");
	if (mValue) fprintf(out, "%*s%s\n", indent + 4, "", mValue);
	fprintf(out, "%*s};\n", indent, "");
	break;

    case TYPE_COMPOUND_FIELD:
        fprintf(out, "%*s%s", indent, "", mName);
	if (mArg) fprintf(out, "(%s)", mArg);
	fprintf(out, "\n%*s{\n", indent, "");

	if (mChild)
	{
	    printed += mChild->printTree(out, indent + 4);
	}
	fprintf(out, "%*s}\n", indent, "");
	break;

    default:
	fprintf(out, "--- invalid node type: %d ---\n", mType);
	break;
    }

    if (mNext)
    {
	printed += mNext->printTree(out, indent);
    }

    return 1;
}

#endif /* XIP_TF_PARSER_H */
