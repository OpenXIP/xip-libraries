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
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#if defined(WINDOWS) || defined(_WIN32)
#include <windows.h>
#include <sys/timeb.h>
#endif


#define XIP_STRING_LEN 1000		//maximum wchar_t array length

// Static variables declared
XipLogListener		*XipLog::mLogListener = 0;
const char			*XipLog::mCallStack;
XipLogType			XipLog::logLevel = XIP_LOG;		//default record everything

//////////////////////////////////////////////////////////////////////////////////////////////////
//XipLog constructor
//
//just copy pointers from input, did not keep a local copy right now
//and generate timeStamp and ProcessID info
//////////////////////////////////////////////////////////////////////////////////////////////////
XipLog::XipLog(XipLogType type, const wchar_t *debugString, const wchar_t * module, const wchar_t *category):
	mLogType(type), mDebugString(debugString), mModule(module), mLogCategory(category)
{
	mTimeStamp = new wchar_t[XIP_STRING_LEN];
	
	mProcessInfo = new wchar_t[XIP_STRING_LEN];

	setProcessInfo();

	setTimeStamp();
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//XipLog destructor
//////////////////////////////////////////////////////////////////////////////////////////////////

XipLog::~XipLog()
{
	if(mTimeStamp)
		delete [] mTimeStamp;
	if(mProcessInfo)
		delete [] mProcessInfo;
			
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//set the static listener to process the XipLog events
//////////////////////////////////////////////////////////////////////////////////////////////////
void	XipLog::setListener(XipLogListener *listener) 
{ 	
	if (mLogListener) {
		delete mLogListener;
		
	}
	mLogListener = listener;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//check whether this belongs to a specific type
//////////////////////////////////////////////////////////////////////////////////////////////////
bool XipLog::isOfType(XipLogType type) const
{
	return (mLogType==type);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//whether this matches a specific category (subtype)
//////////////////////////////////////////////////////////////////////////////////////////////////
bool XipLog::isOfCategory(const wchar_t* category) const
{
	return (wcscmp(mLogCategory,category)==0);
}

static const wchar_t* const logTypeName[] = {L"ERROR", L"WARNING", L"DEBUG_INFO", L"LOG"};

//////////////////////////////////////////////////////////////////////////////////////////////////
//convert the error type to a string name
//////////////////////////////////////////////////////////////////////////////////////////////////
inline const wchar_t* XipLog::ToString() const	{
	return logTypeName[getLogType()]; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//set the time stamp, called in the XipLog constructor
//////////////////////////////////////////////////////////////////////////////////////////////////
void XipLog::setTimeStamp()
{
	if (getTimeStamp()!=NULL) 
	{		
		
		//use UTC timestamp, how to get the time zone or Greenwich time info?
		/*
		LPTIME_ZONE_INFORMATION lpTimeZoneInfo;
		GetTimeZoneInformation(lpTimeZoneInfo);
		lpTimeZoneInfo->Bias
		swprintf(mTimeStamp, XIP_STRING_LEN, L"%04d-%02d-%02dT02d:%02d:%02d.%03d", ft.dwHighDateTime, aStartTime.wYear, aStartTime.wMonth, aStartTime.wDay, aStartTime.wHour,aStartTime.wMinute,aStartTime.wSecond, aStartTime.wMilliseconds );
		*/
#if defined(WINDOWS) || defined(_WIN32)
		SYSTEMTIME aStartTime;
		GetLocalTime(&aStartTime);
		// Get the timezone info.
		TIME_ZONE_INFORMATION TimeZoneInfo;
		GetTimeZoneInformation( &TimeZoneInfo );

		// Convert local time to UTC.
		SYSTEMTIME GmtTime;
		TzSpecificLocalTimeToSystemTime( &TimeZoneInfo, &aStartTime, &GmtTime );

		//swprintf(mTimeStamp, XIP_STRING_LEN, L"%02d:%02d:%02d.%03d", aStartTime.wHour,aStartTime.wMinute,aStartTime.wSecond,aStartTime.wMilliseconds );
		swprintf(mTimeStamp, XIP_STRING_LEN, L"%04d-%02d-%02dT%02d:%02d:%02d.%03d UTC", GmtTime.wYear, GmtTime.wMonth, GmtTime.wDay, GmtTime.wHour,GmtTime.wMinute,GmtTime.wSecond, GmtTime.wMilliseconds );		
#else

		time_t rawtime;
		tm * ptm;
		time ( &rawtime );
		ptm = gmtime ( &rawtime );
		swprintf(mTimeStamp, XIP_STRING_LEN, L"%04d-%02d-%02dT02d:%02d:%02d.%03d", ptm->tm_year, ptm->tm_month, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, rawtimeaStartTime.wMilliseconds );		
#endif		

	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//set the process ID and thread ID
//////////////////////////////////////////////////////////////////////////////////////////////////
void XipLog::setProcessInfo()
{
	if(getProcessInfo()!=NULL)
	{		
		swprintf(mProcessInfo, XIP_STRING_LEN, L"%u/%u",GetCurrentProcessId(),GetCurrentThreadId());        
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//	XipLog::post
//	transfer the handling to mLogListener, pass XipLog class as parameters
//////////////////////////////////////////////////////////////////////////////////////////////////
void XipLog::post(XipLogType errortype, const wchar_t *message, const wchar_t *module, const wchar_t* category)
{
	if (mLogListener && errortype<=logLevel)
	{
		XipLog error(errortype, message, module, category);		//__FUNCTION__
		mLogListener->handleError(error);
	}
}

//errortype, __FUNCTION__, __LINE__,  __FILE__
void XipLog::post(XipLogType errortype, const char *function, int line, const char* file)
{
	if (mLogListener && errortype<=logLevel)
	{
		wchar_t lFile[XIP_STRING_LEN], module[XIP_STRING_LEN];

		int len = strlen(file)+1;
		mbstowcs(lFile, file, len*sizeof(wchar_t));
		swprintf(module, XIP_STRING_LEN, L"File: %s, Line: %d", lFile, line);

		wchar_t message[XIP_STRING_LEN];
		mbstowcs(message, function, len*sizeof(wchar_t));
		
		//if (errortype==XipLogType::XIP_LOG)
		//	XipLog error(errortype, message, module, L"TRACE");		//__FUNCTION__
		//else
		XipLog error(errortype, message, module, L"");		//__FUNCTION__
		mLogListener->handleError(error);
	}
}

/*
//variable input
void XipLog::post(WIDECHAR *formatString ...)
{
    //should use xml to parse the string later
    va_list	args;

    va_start(args, formatString);
    int nBuf;
    WIDECHAR szBuffer[10000];
    nBuf = _vsnwprintf(szBuffer, sizeof(szBuffer), formatString, args);
    va_end(args);
	//get system time

	XipLog error(errortype, message, module, category);

	WIDECHAR debugString[10000];
	wprintf(debugString, "XIP error: %s", szBuffer);
    error.setDebugString(debugString);
    mLogListener->handleError(error);
}*/



////////////////////////////////////////////////////////////////////////
//
// Description:
//    Calls appropriate handler for an error instance. 
//
////////////////////////////////////////////////////////////////////////
#ifndef WIN32

void QXipBuilderError::recordCallStack(void *exceptionInfo)
{
	mCallStack = "";
}

#else

#include <windows.h>
#include <Tlhelp32.h>
#include <windef.h>

static BOOL WINAPI Get_Module_By_Ret_Addr(PBYTE Ret_Addr, 
                PCHAR Module_Name, PBYTE & Module_Addr)
{
    MODULEENTRY32  M = {sizeof(M)};
    HANDLE  hSnapshot = NULL;

    Module_Name[0] = 0;

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
    
    if ((hSnapshot != INVALID_HANDLE_VALUE) &&
        Module32First(hSnapshot, &M))
    {
        do
        {
            if (DWORD(Ret_Addr - M.modBaseAddr) < M.modBaseSize)
            {
				_snprintf(Module_Name, MAX_PATH, "%S", M.szExePath);
                Module_Addr = M.modBaseAddr;
                break;
            }
        } while (Module32Next(hSnapshot, &M));
    }

    CloseHandle(hSnapshot);

    return !!Module_Name[0];
} //Get_Module_By_Ret_Addr


typedef struct STACK_FRAME
{
    STACK_FRAME *   Ebp;   //address of the calling function frame
    PBYTE   Ret_Addr;      //return address
    DWORD   Param[0];      //parameter list - could be empty
} STACK_FRAME, * PSTACK_FRAME;


//int WINAPI Get_Call_Stack(PEXCEPTION_POINTERS pException, PCHAR Str)
static const char* Get_Call_Stack(void *exceptionInfo)
{
	CHAR    This_Module_Name[MAX_PATH];
    CHAR    Module_Name[MAX_PATH];
    PBYTE   Module_Addr;
    PSTACK_FRAME  Ebp = 0;
	int top = 1;

	static CHAR dump[2048];
	static int dumpLen = 0;

	dumpLen = 0;
	dump[0] = 0;
	This_Module_Name[0] = 0;

	if (exceptionInfo)
	{
		PEXCEPTION_POINTERS pException = (PEXCEPTION_POINTERS) exceptionInfo;
		Ebp = (PSTACK_FRAME)pException->ContextRecord->Ebp;
	}
	else
	{
       // Frame address of Get_Call_Stack()
       Ebp = (PSTACK_FRAME) &exceptionInfo - 1;
	}

    for (int Ret_Addr_I = 0;
        (Ret_Addr_I < 20) && !IsBadReadPtr(Ebp, sizeof(PSTACK_FRAME)) && !IsBadCodePtr((FARPROC)(Ebp->Ret_Addr));
        Ret_Addr_I++, Ebp = Ebp->Ebp)
    {
        // Find the module by a return address inside that module
        if (Get_Module_By_Ret_Addr(Ebp->Ret_Addr, Module_Name, Module_Addr))
        {
			if (strlen(This_Module_Name) == 0)
			{
				// record module name of this application
				strcpy(This_Module_Name, Module_Name);
			}

			// skip everything xip builder at the top
			if (top && (strcmp(Module_Name, This_Module_Name) == 0))
			{
				continue;
			}
			top = 0;

			dumpLen += _snprintf(dump + dumpLen, 2048 - dumpLen, "%08X+%08X %s\n", Module_Addr, Ebp->Ret_Addr - Module_Addr, Module_Name);
        }
    }

	if (strlen(dump) > 0)
	{
		// truncate last new line
		dump[strlen(dump) - 1] = 0;
	}

	return dump;
} //Get_Call_Stack


void XipLog::recordCallStack(void *exceptionInfo)
{
	mCallStack = Get_Call_Stack(exceptionInfo);
}

#endif