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
#ifndef XIPEXCEPTION_H
#define XIPEXCEPTION_H

#include <xip/common/XipCommon.h>

/**	\class XipException
 *	\brief Exception class that contains information about fatal errors.
 *
 *  Exceptions are used to indicate "broken contract" when calling the XIP framework.
 *  The exception maintains the following information:
 *  - Exception type,
 *  - Source file information (line and filename),
 *  - and an optional debug string.
 *
 *  \warning Do no use the <tt>throw;</tt> statement without any arguments outside of a <tt>catch()</tt>
 *           block. <tt>throw;</tt> may \e only be used to propagate an exception that was catched by
 *           a catch block (see example).
 *
 *	\b Example:
	\code
	 
	// Example for using exceptions.

    try
	{
	    // some i/o error
		throw XipException(__LINE__, __FILE__, XipException::IO_ERROR);

    }
	catch (XipException &e)
	{
		// let's output some information about the error
		wprintf(L"Exception of type %d occured at %hs(%d)\n", e.type, e.file, e.line);

		// propagate exception to upper layers
		throw;
	}

	\endcode
 *
 */
class XIPCOMMON_API XipException
{
public:
	/// Public field for cause of exception.
	enum XipExceptionType
	{
		INTERNAL_SYSTEM_ERROR = 1,	///< An internal error or invalid state caused aborting the normal program flow.
		COMM_ERROR,                 ///< Communication failure.
		IO_ERROR,                   ///< File I/O error. 
		MEMORY_HEAP_ERROR,          ///< A memory allocation from the heap memory failed.
		MEMORY_DISK_ERROR,          ///< Allocation of disk space failed.
		MEMORY_MAPPING_ERROR,       ///< Failed to allocate or map a file into virtual address space of a process.
		INVALID_PARAM_ERROR,        ///< Invalid parameters have been passed to a method of function.
		INVALID_STATE_ERROR,        ///< Object is in invalid state to perform requested operation.
		ABORT_EXECUTION,            ///< This exception type indicates that the user cancelled an operation.
		OPERATION_UNSUPPORTED       ///< Specified that requested operation or feature is unsupported by a given module/plugin.
	};


	/// Constructor used to generate an exception
	XipException(unsigned int _line, const char *_file, XipExceptionType _type, const wchar_t *_message = 0);

    /// Destructor, cleans up data as needed
    virtual ~XipException();

    /// Returns the line number where the exception is thrown
    unsigned int getLine();

    /// Returns the exception type
    XipExceptionType getType();

    /// Returns the file name pointer
    const char* getFile();

    /// Returns the message string pointer
    const wchar_t* getMessage();


protected:
    /// Source code line number where the exception occured.
    unsigned int mLine;

    /// Source code file where the exception occured. This is a multibyte string!
    const char *mFile;

    /// Optional additional information string (UNICODE).
    const wchar_t *mMessage;

    /// Type of exception
    XipExceptionType mType;
};

#endif // XIPEXCEPTION_H