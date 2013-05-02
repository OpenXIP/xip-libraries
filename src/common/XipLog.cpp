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
#include <xip/common/XipLog.h>
#include <xip/common/XipLogListener.h>
//#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#if defined(WINDOWS) || defined(_WIN32)
#include <windows.h>
#include <sys/timeb.h>
#endif



XipLogListener** XipLog::mListeners = 0;
unsigned int XipLog::numListeners = 0;
XipLogEntry XipLog::mLastEntry;
wchar_t XipLog::mLastTimestamp[32];
wchar_t XipLog::mProcessInfo[1024];

void *XipLog::mTimeZoneInfo =0;
int XipLog::mUTC_offset =0;




XipLogEntry::XipLogEntry()
{
    shortMessage = 0;
    longMessage = 0;
    level = -1;
    flags = -1;
    file = 0;
    timestamp = 0;
    timestampLength = 0;
    processInfo = 0;
    processInfoLength = -1;
    classID = CID_XIP_LOG_ENTRY;
}


void XipLog::addListener(XipLogListener* newListener)
{
    int ptrSize = sizeof(void*);
    if (numListeners == 0)
    {
        if (void* arrayStart = malloc(ptrSize))
        {
            mListeners = static_cast<XipLogListener**>(arrayStart);
            mListeners[0] = newListener;
            numListeners++;
        }
    }
    else
    {
        //grow the array that contains the listener pointers
        void* orig = static_cast<void*>(mListeners);
        if (void* grown = realloc(orig, (numListeners+1)*ptrSize))
        {
            mListeners = static_cast<XipLogListener**>(grown);
            mListeners[numListeners] = newListener;
            numListeners++;
        }
    }
}


void XipLog::post(const wchar_t* shortMessage, const wchar_t* longMessage, int level, int flags, const char* function, int line, const char* file)
{
    updateTimestamp();
    mLastEntry.timestamp = mLastTimestamp;
    mLastEntry.timestampLength  = 32;
    updateProcessInfo();
    mLastEntry.processInfo = mProcessInfo;
    mLastEntry.processInfoLength = 1024;

    mLastEntry.shortMessage = shortMessage;
    mLastEntry.longMessage = longMessage;
    mLastEntry.level = level;
    mLastEntry.flags = flags;
    mLastEntry.function = function;
    mLastEntry.line = line;
    mLastEntry.file = file;
    for (unsigned int i=0; i < numListeners; i++)
    {
        mListeners[i]->handleError(&mLastEntry);
    }
}


void XipLog::set( int property, const wchar_t* value )
{
    for (unsigned int i=0; i < numListeners; i++)
    {
        mListeners[i]->set(property, value);
    }
}

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

    //swprintf(mTimeStamp, XIP_STRING_LEN, L"%02d:%02d:%02d.%03d", aStartTime.wHour,aStartTime.wMinute,aStartTime.wSecond,aStartTime.wMilliseconds );
    if (mUTC_offset > 0)
    {
        swprintf(mLastTimestamp, 32, L"%04d%02d%02d%02d%02d%02d,%03d UTC-%01d", utcTime.wYear, utcTime.wMonth, utcTime.wDay, utcTime.wHour,utcTime.wMinute,utcTime.wSecond, utcTime.wMilliseconds,  mUTC_offset);		
    }
    else if (mUTC_offset < 0 )
    {
        swprintf(mLastTimestamp, 32, L"%04d%02d%02d%02d%02d%02d,%03d UTC+%01d", utcTime.wYear, utcTime.wMonth, utcTime.wDay, utcTime.wHour,utcTime.wMinute,utcTime.wSecond, utcTime.wMilliseconds,  -mUTC_offset);		
    }
    else
    {
        swprintf(mLastTimestamp, 32, L"%04d%02d%02d%02d%02d%02d,%03d UTC", utcTime.wYear, utcTime.wMonth, utcTime.wDay, utcTime.wHour,utcTime.wMinute,utcTime.wSecond, utcTime.wMilliseconds);		
    }
#else

    time_t rawtime;
    tm * ptm;
    time ( &rawtime );
    ptm = gmtime ( &rawtime );
    swprintf(mLastTimestamp, 32, L"%04d%02d%02d02d%02d%02d,%03d UTC%01d", ptm->tm_year, ptm->tm_month, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, rawtimeaStartTime.wMilliseconds, mUTC_offset );		
#endif		
}


void XipLog::updateProcessInfo()
{
    swprintf(mProcessInfo, 1024,L"ProcessID: %u, ThreadID %u",GetCurrentProcessId(),GetCurrentThreadId());
}

void XipLog::removeListener( XipLogListener* listener )
{
    //TODO TH
}

XipLog::XipLog()
{

}




//#include <lm.h>
//int test()
//{
//LPTIME_OF_DAY_INFO pBuf = NULL;
//NET_API_STATUS nStatus;
//LPTSTR pszServerName = NULL;
//
////
//// Call the NetRemoteTOD function.
////
//nStatus = NetRemoteTOD((LPCWSTR) pszServerName,
//                       (LPBYTE *)&pBuf);
////
//// If the function succeeds, display the current date and time.
////
//if (nStatus == NERR_Success)
//{
//    if (pBuf != NULL)
//    {
//        fprintf(stderr, "\nThe current date is: %d/%d/%d\n",
//            pBuf->tod_month, pBuf->tod_day, pBuf->tod_year);
//        fprintf(stderr, "The current time is: %d:%d:%d\n",
//            pBuf->tod_hours, pBuf->tod_mins, pBuf->tod_secs);
//    }
//}
////
//// Otherwise, display a system error.
//else
//fprintf(stderr, "A system error has occurred: %d\n", nStatus);
////
//// Free the allocated buffer.
////
//if (pBuf != NULL)
//NetApiBufferFree(pBuf);
//
//return 0;
//}