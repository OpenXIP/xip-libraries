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
#ifndef XIPEXCEPTION_H
#define XIPEXCEPTION_H

#include <xip/common/XipCommon.h>

// forward declaration
struct XipExceptionData;

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
		UNKNOWN_ERROR = 0,			///< Undefined error type, usually indicated uninitialized type
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
	
	inline const wchar_t* ToString(XipExceptionType type) const;	

	/// Constructor used to generate an exception
	XipException();
//	XipException(unsigned int _line, const char *_file, const char *_function, XipExceptionType _type, const wchar_t *_message = 0);
	XipException(unsigned int _line, const char *_file, const char *_function, XipExceptionType _type, const wchar_t* _message = 0, ...);
	XipException(const XipException& e);

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

    /// Returns the function string pointer
    const char* getFunction();


protected:

	XipExceptionData* mData;
	XipExceptionType mType;
};

//----------------------------------------------------------------
//convenience macros:
//------------------------------------------------------------------

//check for a NULL pointer, and throw exception
#define XIP_CHK_PTR(ptr) if (!ptr) {throw XipException(__LINE__, __FILE__, XipException::MEMORY_HEAP_ERROR, L#ptr ## L" is NULL");}


#endif // XIPEXCEPTION_H