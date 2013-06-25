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

#include <xip/common/XipLog.h>
#include <xip/common/XipLogListener.h>
#include <xip/system/standard.h>
#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#if defined(WINDOWS) || defined(_WIN32)
#include <windows.h>
#include <sys/timeb.h>
#else //UNIX
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
//using namespace std //why only here?
#endif //WINDOWS || _WIN32



XipLogListener** XipLog::mListeners = 0;
unsigned int XipLog::mNumListeners = 0;
XipLogEntry XipLog::mLastEntry;
wchar_t XipLog::mLastTimestamp[32];
wchar_t XipLog::mProcessInfo[1024];

void *XipLog::mTimeZoneInfo =0;
int XipLog::mUTC_offset =0;

const int XIP_STRING_LEN = 500;
const int XIP_TIMESTAMP_LENGTH = 32;


/** \fn XipLogEntry::XipLogEntry()
 * Initializes internal variables
 * \return none
 */
XipLogEntry::XipLogEntry()
:shortMessage(0),
    longMessage(0),
    level(-1),
    flags(-1),
    file(0),
    timestamp(0),
    timestampLength(0),
    processInfo(0),
    processInfoLength(-1),
    classID(CID_XIP_LOG_ENTRY)
{
	shortMessage = new wchar_t[MAX_PATH];
	longMessage = new wchar_t[MAX_PATH];
	function = new char[MAX_PATH];
	file = new char[MAX_PATH];
	timestamp = new wchar_t[XIP_TIMESTAMP_LENGTH];
	processInfo = new wchar_t[MAX_PATH];
}


/** \fn XipLogEntry::const XipLogEntry& other)
 * Do a deep copy of all the newly created objects from this
 * \return none
 */
XipLogEntry::XipLogEntry(const XipLogEntry& other)
{
	int nLength = 0;
	if ( other.shortMessage != NULL )
	{
		nLength = wcsnlen(other.shortMessage,XIP_STRING_LEN );
		shortMessage = new wchar_t[nLength + 1];
		if ( other.shortMessage )
			wcscpy(shortMessage,other.shortMessage);
	}else
		shortMessage = NULL;

	if ( other.longMessage != NULL )
	{
		nLength = wcsnlen(other.longMessage,XIP_STRING_LEN );
		longMessage = new wchar_t[nLength + 1];
		if ( other.longMessage )
			wcscpy(longMessage,other.longMessage);
	}else
		longMessage = NULL;

	this->level = other.level;
	this->flags = other.flags;

	if ( other.file != NULL)
	{
		nLength = strlen(other.file);
		file = new char[nLength + 1];
		strcpy(this->file,other.file);
	}else
		file = NULL;

	if ( other.timestamp != NULL )
	{
		nLength = wcsnlen(other.timestamp,XIP_STRING_LEN );
		timestamp = new wchar_t[nLength + 1];
		if ( other.timestamp )
			wcscpy(timestamp,other.timestamp);
	}else
		timestamp = NULL;

	this->timestampLength = other.timestampLength;

	if ( other.processInfo != NULL )
	{
		nLength = wcsnlen(other.processInfo,XIP_STRING_LEN );
		processInfo = new wchar_t[nLength + 1];
		if ( other.processInfo )
			wcscpy(processInfo,other.processInfo);
	}else
		processInfo = NULL;

	this->processInfoLength = other.processInfoLength;
	this->classID = other.classID;

	if ( other.function != NULL )
	{
		nLength = strlen(other.function);
		function = new char[nLength + 1];
		strcpy(this->function,other.function);
	}else
		function = NULL;

	this->line = other.line;

}


XipLogEntry::~XipLogEntry()
{
	if ( shortMessage )
	{
		delete[] shortMessage;
		shortMessage = 0;
	}
	if ( longMessage ) 
	{
		delete[] longMessage;
		longMessage = 0;
	}
	if ( timestamp ) 
	{
		delete[] timestamp;
		timestamp = 0;
	}
	if ( processInfo ) 
	{
		delete[] processInfo;
		processInfo = 0;
	}
	if ( file ) 
	{
		delete[] file;
		file = 0;
	}
	if ( function )
	{
		delete[] function;
		function = 0;
	}
}

/*! \fn XipLogEntry::clone()
*   Implements the virtual clone method to make a clone of its own
*/
XipLogEntry* XipLogEntry::clone()const
{
	XipLogEntry *clone = new XipLogEntry(*this);
	if ( !clone )
		return 0;

	return clone;
}

/*! \fn XipLog::addListener(XipLogListener* newListener)
*  Adds a log listener instance implementing the actual log destination
*  \param newListener the listener handling instance to be used
*  \return true if addition was successful, false if it failed.
*/
bool XipLog::addListener(XipLogListener* newListener)
{
	bool success = false;
    int ptrSize = sizeof(void*);
    if (mNumListeners == 0)
    {
        if (void* arrayStart = malloc(ptrSize))
        {
            mListeners = static_cast<XipLogListener**>(arrayStart);
            mListeners[0] = newListener;
            mNumListeners++;
			success = true;
        }
    }
    else
    {
        //grow the array that contains the listener pointers
        void* orig = static_cast<void*>(mListeners);
        if (void* grown = realloc(orig, (mNumListeners+1)*ptrSize))
        {
            mListeners = static_cast<XipLogListener**>(grown);
            mListeners[mNumListeners] = newListener;
            mNumListeners++;
			success = true;
        }
    }
	return success;
}


/*! \fn XipLog::post(const wchar_t* shortMessage, const wchar_t* longMessage, int level, int flags, const char* function, int line, const char* file)
*
*  Common interface for log entry posting and classification
*
*  \param shortMessage - the short message for brief log description
*  \param longMessage - long message describing further details of log entry
*  \param level - the warning level
*  \param flags - any optional flags
*  \param function - function mname of source location
*  \param line - line number of source location
*  \param file - file name of source locaiton
*
*  \return void
*/
void XipLog::post(const wchar_t* shortMessage, const wchar_t* longMessage, int level, int flags, const char* function, int line, const char* file)
{
    updateTimestamp();
    mLastEntry.timestampLength  = 32;
    updateProcessInfo();
    mLastEntry.processInfoLength = 1024;

	const char tempStr[] = "";
	const wchar_t wTempStr[] = L"";
	int nLength = 0;

	if (shortMessage)
	{
		if ( wcsnlen(shortMessage,XIP_STRING_LEN ) >
			wcsnlen(mLastEntry.shortMessage,XIP_STRING_LEN ))
		{
			delete[] mLastEntry.shortMessage;
			nLength = wcsnlen(shortMessage,XIP_STRING_LEN );
			mLastEntry.shortMessage = new wchar_t[nLength + 1];			
		}
		wcscpy(mLastEntry.shortMessage,shortMessage);

	}
	else
	{
		wcscpy(mLastEntry.shortMessage,wTempStr);
	}

	if (longMessage)
	{
		if ( wcsnlen(longMessage,XIP_STRING_LEN ) >
			wcsnlen(mLastEntry.longMessage,XIP_STRING_LEN ))
		{
			delete[] mLastEntry.longMessage;
			nLength = wcsnlen(longMessage,XIP_STRING_LEN );
			mLastEntry.longMessage = new wchar_t[nLength + 1];			
		}
		wcscpy(mLastEntry.longMessage,longMessage);
	}
	else
	{
		wcscpy(mLastEntry.longMessage,wTempStr);
	}

	if (function)
	{
		if ( strlen(function ) >
			strlen(mLastEntry.function ))
		{
			delete[] mLastEntry.function;
			nLength = strlen(function);
			mLastEntry.function = new char[nLength + 1];			
		}
		strcpy(mLastEntry.function,function);
	}
	else
	{
		strcpy(mLastEntry.function,tempStr);
	}

	if (file)
	{
		if ( strlen(file ) >
			strlen(mLastEntry.file ))
		{
			delete[] mLastEntry.file;
			nLength = strlen(file);
			mLastEntry.file = new char[nLength + 1];			
		}
		strcpy(mLastEntry.file,file);
	}
	else
	{
		strcpy(mLastEntry.file,tempStr);
	}

	if (mLastTimestamp)
	{
		if ( wcsnlen(mLastTimestamp,XIP_STRING_LEN ) >
			wcsnlen(mLastEntry.timestamp,XIP_STRING_LEN ))
		{
			delete[] mLastEntry.timestamp;
			nLength = wcsnlen(mLastTimestamp,XIP_STRING_LEN );
			mLastEntry.timestamp = new wchar_t[nLength + 1];			
		}
		wcscpy(mLastEntry.timestamp,mLastTimestamp);
	}
	else
	{
		wcscpy(mLastEntry.timestamp,wTempStr);
	}

	if (mProcessInfo)
	{
		if ( wcsnlen(mProcessInfo,XIP_STRING_LEN ) >
			wcsnlen(mLastEntry.processInfo,XIP_STRING_LEN ))
		{
			delete[] mLastEntry.processInfo;
			nLength = wcsnlen(mProcessInfo,XIP_STRING_LEN );
			mLastEntry.processInfo = new wchar_t[nLength + 1];			
		}
		wcscpy(mLastEntry.processInfo,mProcessInfo);
	}
	else
	{
		wcscpy(mLastEntry.processInfo,wTempStr);
	}

    mLastEntry.level = level;
    mLastEntry.flags = flags;
    mLastEntry.line = line;
    for (unsigned int i=0; i < mNumListeners; i++)
    {
        mListeners[i]->handleError(mLastEntry);
    }
}




/*! \fn XipLog::set( int property, const wchar_t* value )
*  Sets the property and value to all listeners
*  \param property - a property type value
*  \param value - a string value description
*  \return void
*/
void XipLog::set( int property, const wchar_t* value )
{
    for (unsigned int i=0; i < mNumListeners; i++)
    {
        mListeners[i]->set(property, value);
    }
}


/*! \fn XipLog::updateTimestamp()
*  This method is used internally by the post method to obtain the latest UTC
*  timestamp in the mLastTimestamp member variable that can be used to output to the 
*  final log information.
*
*  \return void
*/
void XipLog::updateTimestamp()
{
#if defined(WINDOWS) || defined(_WIN32)
    SYSTEMTIME utcTime, localTime; 
    GetSystemTime(&utcTime); //retrieves UTC time
    // Get the timezone info. 
    if (!mTimeZoneInfo)
    {
        mTimeZoneInfo = new TIME_ZONE_INFORMATION;
        LPTIME_ZONE_INFORMATION tzi =  static_cast<LPTIME_ZONE_INFORMATION>(mTimeZoneInfo) ;

        GetTimeZoneInformation(tzi);
        SystemTimeToTzSpecificLocalTime(tzi, &utcTime, &localTime);

        //use variant time to calculate the difference
        //http://msdn.microsoft.com/en-us/library/ms221646.aspx
        double dUTC, dLocal;
        SystemTimeToVariantTime (&utcTime, &dUTC);
        SystemTimeToVariantTime (&localTime, &dLocal);

        double offset = dUTC - dLocal;
        double hours = offset * 24.0;

        // hours will hold a number with precision error in the last decimal places, 
        // so we have to round it to the next integer
        mUTC_offset = hours >= 0 ? (int)(hours + 0.5) : (int)(hours - 0.5);
    }

	// This is already utc time, so the UTC offset is always zero
    swprintf(mLastTimestamp, 32, L"%04d%02d%02d%02d%02d%02d.%03d UTC+0", utcTime.wYear, utcTime.wMonth, utcTime.wDay, utcTime.wHour,utcTime.wMinute,utcTime.wSecond, utcTime.wMilliseconds);		


#else

    time_t rawtime;
    tm * ptm;
    time ( &rawtime );
    ptm = gmtime ( &rawtime );
    
    //not sure when this was tested last time, but it doesn't work on the mac
    //swprintf(mLastTimestamp, 32, L"%04d%02d%02d02d%02d%02d,%03d UTC%01d", ptm->tm_year, ptm->tm_month, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, rawtimeaStartTime.wMilliseconds, mUTC_offset );
    
    //TODO: does rawtime really hold the milliseconds now ???
                                  // 4Y, 2M, 2D, 2H, 2M, 2S, 3M : e.g. 2011 01 31 18 29 59 123
    swprintf(mLastTimestamp, 32, L"%04d%02d%02d%02d%02d%02d.%03d UTC%01d", ptm->tm_year, ptm->tm_mon, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, rawtime, mUTC_offset );
#endif		
}


/*! \fn XipLog::updateProcessInfo()
*  Updates the process ID information in the member variable
*  mProcessInfo that can be used by the log postings
*  \return void
*/
void XipLog::updateProcessInfo()
{
#ifdef WIN32
    swprintf(mProcessInfo, 1024,L"ProcessID: %u, ThreadID %u",GetCurrentProcessId(),GetCurrentThreadId());
#else //UNIX
    swprintf(mProcessInfo, 1024, L"ProcessID: %u, ThreadID %u", getpid(), pthread_self());
#endif //WIN32
}


/*! \fn XipLog::removeListener( XipLogListener* )
*  Tries to remove a log listener instance 
*  \param listener - the listener to be removed
*  \return true if succeeded, false if listener could not be found
*/
bool XipLog::removeListener( XipLogListener* listener )
{
   unsigned int whichListener = 0; 
    bool found = false;
    for (unsigned int i =0; i < mNumListeners; i++)
    {
        if (mListeners[i] == listener)
        {
            found = true;
            whichListener = i;
        }
    }

    //remove that listener
    if (found)
    {
        if (mNumListeners = 1)
        {
            //if this is the only listener, just scrap the mListeners array
            free(mListeners);
            mListeners = 0;
            mNumListeners = 0;
        }
        else
        {
            //move up the other listeners (to retain order of listeners)
            for (unsigned int i = whichListener; i < mNumListeners-1; i++)
            {
                mListeners[i] = mListeners[i+1];
            }
            //shrink the array so that it contains one fewer pointer
            void* orig = static_cast<void*>(mListeners);
            int ptrSize = sizeof(void*);
            if (void* shrunk = realloc(orig, (mNumListeners-1)*ptrSize))
            {
                mListeners = static_cast<XipLogListener**>(shrunk);
                //should the realloc fail for some reason, still decrement the listener
                //count outside of this IF-statement
                //this way we have a dangling bogus pointer at the end of the array
                //that is not being accessed during post() anyway
            }
            mNumListeners--; 
        }
        return true;
    }
    else
    {
        return false;
    }
}

/** \fn XipLog::XipLog()
 * Constructor, initializes process info
 * \return none
 */
XipLog::XipLog()
{
    updateProcessInfo();

}


/** \fn XipLog::XipLog()
 * Destructor, frees internal data
 * \return none
 */
XipLog::~XipLog()
{
    free(mListeners);
    delete mTimeZoneInfo;
}


