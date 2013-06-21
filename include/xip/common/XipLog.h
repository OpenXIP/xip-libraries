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

#ifndef XIPLOG_H
#define XIPLOG_H

#include <xip/common/XipCommon.h>
#include <xip/common/XipException.h>

#define CID_XIP_LOG_ENTRY 0

/*
* XipLogLevel defines different levels of logs
*/
enum XipLogLevel
{
    XIPLOG_FATAL,
    XIPLOG_ERROR,
    XIPLOG_WARN, 
    XIPLOG_INFO,
    XIPLOG_DEBUG,
    XIPLOG_TRACE,
    XIPLOG_CUSTOM_LEVEL
};


enum XipLogFlags
{
    XipLog_None = 0x00000000,
    XipLog_TypeSession = 0x00000001,
    XipLog_TypeMeasurement = 0x00000002,
    XipLog_BlockingError = 0x00000004,
    XipLog_UserError = 0x00000008
};

/*! \class XipLogClone
 * \brief An abstract base class to enforce the implemntation of clone method
 *       this clone method must be overweritten in every subclass and return deep copy of its own.
 */
struct XIPCOMMON_API XipLogClone
{
	XipLogClone(){};
	virtual ~XipLogClone(){};
	virtual XipLogClone* clone()const = 0;
};


/*! \class XipLogEntry
 * \brief A public class describing the content of a single log entry
 *
 */
class XIPCOMMON_API XipLogEntry  : public XipLogClone
{
public:
    XipLogEntry();
	XipLogEntry(const XipLogEntry& other);
	virtual ~XipLogEntry();
	virtual XipLogEntry* clone() const;

    wchar_t* shortMessage;
    wchar_t* longMessage; 
    int level; 
    int flags; 
    char* function; 
    int line;
    char* file;
    wchar_t* timestamp;
    int timestampLength;
    wchar_t* processInfo;
    int processInfoLength;
    int classID;
};


class XipLogListener;



/*! \class XipLog
 * \brief A base log handling implementation 
 *
 * This class provides a basic implementation of handling a base listener and provides the
 * common post interface for use by applications.  This class and the associated log
 * listener class are meant to be derived by application specific log destination and handling
 * derived classes. 
 *
 */
class XIPCOMMON_API XipLog
{
public:

    static void post(const wchar_t* shortMessage, const wchar_t* longMessage, int level, int flags, const char* function, int line, const char* file);
    static void set(int property, const wchar_t* value);

    static bool addListener(XipLogListener* listener);
    static bool removeListener(XipLogListener* listener);
    static bool hasListeners(){return mNumListeners>0;}

protected:

    explicit XipLog(); //no one should be able to create an instance of this class
    virtual ~XipLog();

    static XipLogListener** mListeners;
    static unsigned int mNumListeners;
    static XipLogEntry mLastEntry;

    static void updateTimestamp();
    static void updateProcessInfo();

    static wchar_t mLastTimestamp[32];
    static wchar_t mProcessInfo[1024];

    static void* mTimeZoneInfo;
    static int mUTC_offset;

};



#define XIP_LOG(shortmessage, longmessage, level, flags) XipLog::post((shortmessage), (longmessage), (level), (flags), (0), (-1), (0))
#define XIP_LOG_FLF(shortmessage, longmessage, level, flags, function, line, file)   XipLog::post((shortmessage), (longmessage), (level), (flags), (function), (line), (file))
#define XIP_LOG_AUTOFLF(shortmessage, longmessage, level, flags) XipLog::post((shortmessage), (longmessage), (level), (flags), (__FUNCTION__), (__LINE__), (__FILE__))

#define XIP_LOG_FATAL(shortmessage, longmessage, flags) XIP_LOG((shortmessage), (longmessage), (XIPLOG_FATAL), (flags))
#define XIP_LOG_FATAL0(shortmessage, longmessage) XIP_LOG((shortmessage), (longmessage), (XIPLOG_FATAL), (0))
#define XIP_LOG_FATAL_FLF(shortmessage, longmessage, flags, function, line, file) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_FATAL), (flags), function, line, file)
#define XIP_LOG_FATAL_FLF0(shortmessage, longmessage, function, line, file) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_FATAL), (0), function, line, file)
#define XIP_LOG_FATAL_AUTOFLF(shortmessage, longmessage, flags) XIP_LOG_AUTOFLF((shortmessage), (longmessage), (XIPLOG_FATAL), (flags))
#define XIP_LOG_FATAL_AUTOFLF0(shortmessage, longmessage) XIP_LOG_AUTOFLF((shortmessage), (longmessage), (XIPLOG_FATAL), (0))

#define XIP_LOG_ERROR(shortmessage, longmessage, flags) XIP_LOG((shortmessage), (longmessage), (XIPLOG_ERROR), (flags))
#define XIP_LOG_ERROR0(shortmessage, longmessage) XIP_LOG((shortmessage), (longmessage), (XIPLOG_ERROR), (0))
#define XIP_LOG_ERROR_FLF(shortmessage, longmessage, flags, function, line, file) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_ERROR), (flags), function, line, file)
#define XIP_LOG_ERROR_FLF0(shortmessage, longmessage, function, line, file) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_ERROR), (0), function, line, file)
#define XIP_LOG_ERROR_AUTOFLF(shortmessage, longmessage, flags) XIP_LOG_AUTOFLF((shortmessage), (longmessage), (XIPLOG_ERROR), (flags))
#define XIP_LOG_ERROR_AUTOFLF0(shortmessage, longmessage) XIP_LOG_AUTOFLF((shortmessage), (longmessage), (XIPLOG_ERROR), (0))

#define XIP_LOG_WARN(shortmessage, longmessage, flags) XIP_LOG((shortmessage), (longmessage), (XIPLOG_WARN), (flags))
#define XIP_LOG_WARN0(shortmessage, longmessage) XIP_LOG((shortmessage), (longmessage), (XIPLOG_WARN), (0))
#define XIP_LOG_WARN_FLF(shortmessage, longmessage, flags, function, line, file) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_WARN), (flags), function, line, file)
#define XIP_LOG_WARN_FLF0(shortmessage, longmessage, function, line, file) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_WARN), (0), function, line, file)
#define XIP_LOG_WARN_AUTOFLF(shortmessage, longmessage, flags) XIP_LOG_AUTOFLF((shortmessage), (longmessage), (XIPLOG_WARN), (flags))
#define XIP_LOG_WARN_AUTOFLF0(shortmessage, longmessage) XIP_LOG_AUTOFLF((shortmessage), (longmessage), (XIPLOG_WARN), (0))

#define XIP_LOG_INFO(shortmessage, longmessage, flags) XIP_LOG((shortmessage), (longmessage), (XIPLOG_INFO), (flags))
#define XIP_LOG_INFO0(shortmessage, longmessage) XIP_LOG((shortmessage), (longmessage), (XIPLOG_INFO), (0))
#define XIP_LOG_INFO_FLF(shortmessage, longmessage, flags, function, line, file) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_INFO), (flags), function, line, file)
#define XIP_LOG_INFO_FLF0(shortmessage, longmessage, function, line, file) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_INFO), (0), function, line, file)
#define XIP_LOG_INFO_AUTOFLF(shortmessage, longmessage, flags) XIP_LOG_AUTOFLF((shortmessage), (longmessage), (XIPLOG_INFO), (flags))
#define XIP_LOG_INFO_AUTOFLF0(shortmessage, longmessage) XIP_LOG_AUTOFLF((shortmessage), (longmessage), (XIPLOG_INFO), (0))

#define XIP_LOG_DEBUG(shortmessage, longmessage, flags) XIP_LOG((shortmessage), (longmessage), (XIPLOG_DEBUG), (flags))
#define XIP_LOG_DEBUG0(shortmessage, longmessage) XIP_LOG((shortmessage), (longmessage), (XIPLOG_DEBUG), (0))
#define XIP_LOG_DEBUG_FLF(shortmessage, longmessage, flags, function, line, file) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_DEBUG), (flags), function, line, file)
#define XIP_LOG_DEBUG_FLF0(shortmessage, longmessage, function, line, file) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_DEBUG), (0), function, line, file)
#define XIP_LOG_DEBUG_AUTOFLF(shortmessage, longmessage, flags) XIP_LOG_AUTOFLF((shortmessage), (longmessage), (XIPLOG_DEBUG), (flags))
#define XIP_LOG_DEBUG_AUTOFLF0(shortmessage, longmessage) XIP_LOG_AUTOFLF((shortmessage), (longmessage), (XIPLOG_DEBUG), (0))

#define XIP_LOG_TRACE(shortmessage, longmessage, flags) XIP_LOG((shortmessage), (longmessage), (XIPLOG_TRACE), (flags))
#define XIP_LOG_TRACE0(shortmessage, longmessage) XIP_LOG((shortmessage), (longmessage), (XIPLOG_TRACE), (0))
#define XIP_LOG_TRACE_FLF(shortmessage, longmessage, flags, function, line, file) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_TRACE), (flags), function, line, file)
#define XIP_LOG_TRACE_FLF0(shortmessage, longmessage, function, line, file) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_TRACE), (0), function, line, file)
#define XIP_LOG_TRACE_AUTOFLF(shortmessage, longmessage, flags) XIP_LOG_AUTOFLF((shortmessage), (longmessage), (XIPLOG_TRACE), (flags))
#define XIP_LOG_TRACE_AUTOFLF0(shortmessage, longmessage) XIP_LOG_AUTOFLF((shortmessage), (longmessage), (XIPLOG_TRACE), (0))


#define XIP_LOG_SET(property, value)  XipLog::set(property, value)


//
//
//#define XIP_LOG_ERROR(shortmessage, longmessage, flags, function, line, file) XIP_LOG((shortmessage), (longmessage), (XIPLOG_ERROR), (flags), function, line, file)
//#define XIP_LOG_ERROR0(shortmessage, longmessage, function, line, file) XIP_LOG((shortmessage), (longmessage), (XIPLOG_ERROR), (0), function, line, file)
//#define XIP_LOG_ERROR_FLF(shortmessage, longmessage, flags) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_ERROR), (flags))
//#define XIP_LOG_ERROR_FLF0(shortmessage, longmessage) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_ERROR), (0))
//
//#define XIP_LOG_WARN(shortmessage, longmessage, flags, function, line, file) XIP_LOG((shortmessage), (longmessage), (XIPLOG_WARN), (flags), function, line, file)
//#define XIP_LOG_WARN0(shortmessage, longmessage, function, line, file) XIP_LOG((shortmessage), (longmessage), (XIPLOG_WARN), (0), function, line, file)
//#define XIP_LOG_WARN_FLF(shortmessage, longmessage, flags) XIP_LOG_FLF((shortmessage), (longmessage),  (XIPLOG_WARN), (flags))
//#define XIP_LOG_WARN_FLF0(shortmessage, longmessage) XIP_LOG_FLF((shortmessage), (longmessage),  (XIPLOG_WARN), (0))
//
//#define XIP_LOG_INFO(shortmessage, longmessage, flags, function, line, file) XIP_LOG((shortmessage), (longmessage), (XIPLOG_INFO), (flags), function, line, file)
//#define XIP_LOG_INFO0(shortmessage, longmessage, function, line, file) XIP_LOG((shortmessage), (longmessage), (XIPLOG_INFO), (0), function, line, file)
//#define XIP_LOG_INFO_FLF(shortmessage, longmessage, flags) XIP_LOG_FLF((shortmessage), (longmessage),  (XIPLOG_INFO), (flags))
//#define XIP_LOG_INFO_FLF0(shortmessage, longmessage) XIP_LOG_FLF((shortmessage), (longmessage),  (XIPLOG_INFO), (0))
//
//#define XIP_LOG_DEBUG(shortmessage, longmessage, flags, function, line, file) XIP_LOG((shortmessage), (longmessage), (XIPLOG_DEBUG), (flags), function, line, file)
//#define XIP_LOG_DEBUG0(shortmessage, longmessage, function, line, file) XIP_LOG((shortmessage), (longmessage), (XIPLOG_DEBUG), (0), function, line, file)
//#define XIP_LOG_DEBUG_FLF(shortmessage, longmessage, flags) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_DEBUG), (flags))
//#define XIP_LOG_DEBUG_FLF0(shortmessage, longmessage) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_DEBUG), (0))
//
//#define XIP_LOG_TRACE(shortmessage, longmessage, flags, function, line, file) XIP_LOG((shortmessage), (longmessage), (XIPLOG_TRACE), (flags), function, line, file)
//#define XIP_LOG_TRACE0(shortmessage, longmessage, function, line, file) XIP_LOG((shortmessage), (longmessage), (XIPLOG_TRACE), (0), function, line, file)
//#define XIP_LOG_TRACE_FLF(shortmessage, longmessage, flags) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_TRACE), (flags))
//#define XIP_LOG_TRACE_FLF0(shortmessage, longmessage) XIP_LOG_FLF((shortmessage), (longmessage), (XIPLOG_TRACE), (0))
//

#endif
