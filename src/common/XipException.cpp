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
#include <xip/common/XipException.h>
#include <string>
#include <stdio.h>
#include <stdarg.h>

#include <xip/system/standard.h>

struct XipExceptionData
{
	XipExceptionData()
		: line(0),
		  file(),
		  function(),
		  message()
	{}

    /// Source code line number where the exception occured.
    unsigned int line;

    /// Source code file where the exception occured. 
	std::string file;

    /// Source code function where the exeption occurred.    
	std::string function;

    /// Optional additional information string (UNICODE).
	std::wstring message;

};

/** \fn XipException::XipException()
 * Constructor used to generate an exception.
 *
 *  This constructor should be used in connection with a throw statement to abort the normal
 *  program flow due to a fatal error.  This class does not make copy of the input
 *  file or message strings.  It merely retains a pointer currently.  The user should
 *  take care that the pointer life cycle is valid when use.
 *
 *  \param line Specifies the line number, where the exception was generated. Applications should use the __LINE__ macro for this parameter.
 *  \param file Specifies the source file, where the exception was generated. Applications should use the __FILE__ macro for this parameter.
 *  \param type The cause of the fatal error is identified through this parameter (see RadExceptionType).
 *  \param message Optional string containing additional information about the error.
 *
 */

XipException::XipException()
: mData(0),
  mType(UNKNOWN_ERROR)
{
}
#if 0
XipException::XipException(unsigned int line, const char *file, const char* function,  XipExceptionType type, const wchar_t *message)
: mData(0),
  mType(type)
{
	mData = new XipExceptionData();
	if (!mData)
		return;
	
	mData->line = line;

	if (NULL != file)
		mData->file = file;

	if (NULL != function)
	    mData->function = function;

	if (NULL != message)
	    mData->message = message;
	
}
#endif

XipException::XipException(  unsigned int line, const char* file, const char* function,
						     XipExceptionType type, 
                             const wchar_t* message, ...) 
: mData(0),
  mType(type)
{
	mData = new XipExceptionData();
	if (!mData)
		return;

	mData->line = line;

    if( NULL != file )
		mData->file = file;

	if (NULL != function)
	    mData->function = function;

    if( NULL != message )
    {
        const int SIZE = 1024;

        wchar_t buf[SIZE];

        // Make sure that last bytes are terminated.
        memset(buf, 0, sizeof(buf));

        // Leave room for terminating 0.
        const int max = sizeof(buf) / sizeof(wchar_t) - sizeof(wchar_t);

        try
        {
            va_list args;
            va_start(args, message);
            _vsnwprintf(buf, max, message, args);
            va_end(args);

			mData->message = buf;
        }
        catch (...)
        {
            // May happen if formatter string is bogus.
            std::wstring temp(L"String formatter threw up. Formatter string: ");
            temp.append(message);
			mData->message = temp.c_str();
        }
    }
}

XipException::XipException(const XipException& e)
: mData(),
  mType(UNKNOWN_ERROR)
{
	mData = new XipExceptionData();
	if (!mData)
		return;

	*mData = *e.mData;

	mType = e.mType;
}

/** \fn XipException::~XipException()
 * Destructor to clean up any necessary data.
 *
 */
XipException::~XipException()
{
	delete mData;
	mData = 0;
};

static const wchar_t* const exceptionTypeName[] = {L"INTERNAL_SYSTEM_ERROR", L"COMM_ERROR", L"IO_ERROR", L"MEMORY_HEAP_ERROR", L"MEMORY_DISK_ERROR", L"MEMORY_MAPPING_ERROR", L"INVALID_PARAM_ERROR", L"INVALID_STATE_ERROR", L"ABORT_EXECUTION", L"OPERATION_UNSUPPORTED"};

//////////////////////////////////////////////////////////////////////////////////////////////////
//convert the exception type to a string name
//////////////////////////////////////////////////////////////////////////////////////////////////
inline const wchar_t* XipException::ToString(XipExceptionType type) const	{
	return exceptionTypeName[type-1]; 
}

/*! \fn XipException::getLine()
 * 
 * Returns the line number where the exception is thrown
 */
unsigned int XipException::getLine()
{
    return (mData->line);
}


/*! \fn XipException::getType()
 * 
 * Returns the exception type
 */
XipException::XipExceptionType XipException::getType()
{
    return (mType);
}


/*! \fn XipException::getFile()
 * 
 * Returns the file name pointer
 */
const char* XipException::getFile()
{
    return (mData->file.c_str());
}

/*! \fn XipException::getFile()
* 
* Returns the function name pointer
*/
const char* XipException::getFunction()
{
    return (mData->function.c_str());
}


/*! \fn XipException::getMessage()
 * 
 * Returns the message string pointer
 */
const wchar_t* XipException::getMessage()
{
    return (mData->message.c_str());
}
