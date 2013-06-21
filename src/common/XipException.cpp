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
