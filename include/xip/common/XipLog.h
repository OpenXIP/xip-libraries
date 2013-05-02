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
#ifndef _XIP_LOG_H
#define _XIP_LOG_H

#include <xip/common/XipCommon.h>
#include <xip/common/XipException.h>

class XipLogListener;

//typedef wchar_t      WIDECHAR;

/*
Fileds: 

type:			log type
message:		specific log message
module:			file, class or function name
category:		detailed log types
timeStamp:		time stamp
processInfo:	process ID and thread ID

to use:

first register a listener using

XipLog::setListener(listener);

use static XipLog::post(type, message, module, category) or MACROs XIP_POST_ERROR, XIP_POST_WARNING,
XIP_POST_DEBUG, XIP_POST_LOG to post an error or log message,
and it is subsequently processed by listener.handleError(log)

post is supposed to both record the log, and error handling
so use XipLog::post to throw an error handled by listener as well

#include <xip/common/XipLog.h>
#include "XipDefaultLogListener.h"

MainApp::MainApp(int argc, char *argv[])
{

	...
	//add log files
	if(!XipLog::getListener()) {
		listener = new XipDefaultLogListener(L"MainApp_log_attr.xml");
		//listener = new XipDefaultLogListener(L"MainApp_log_attr.txt");
		XipLog::setLogLevel(XIP_LOG);
		XipLog::setListener(listener);
	}
	...
}

SomeFunctionToTrace()
{
	XIP_POST_LOG0;		//give function name, line and file using MACROS
}

SomeFunctionProneToError()
{
	try{
		...		
	}
	catch(...)
	{
		XIP_POST_ERROR("ERROR loading SomeFunctionProneToError()", L"MainAPP", L"EXCEPTION"); 
	}
}

MainApp::~MainApp()
{
	...
	//clean up listener
	if(listener) {
		XipLog::setListener(NULL);
	}
}

*/


/*
XipLogType defines different types of errors or logs, thus different level of logs
*/
enum XipLogType
{
	//XIP_INVENTOR_ERROR,				// Inventor Error
	XIP_ERROR,					// Exception 
	XIP_WARNING,					// Warning  
	XIP_DEBUG_INFO,					// Debug Info	
	//XIP_TRACE,						// Trace Info
	XIP_LOG,						// LOG Info
	//XIP_USER_ERROR,					// USER Error
	//XIP_USER_EVENT					// record USER events
};

class XIPCOMMON_API XipLog
{
public:
	/// Constructor used to generate an exception or a log message
	XipLog(XipLogType type, const wchar_t *message, const wchar_t *module = 0, const wchar_t* category = 0);
    
	/// Destructor, cleans up data as needed
    virtual ~XipLog();   

	//set the current log level, above which log will be ignored
	static void setLogLevel(XipLogType level) {logLevel = level;};
	
	// Sets Listener function for XipLog class
    static void	setListener(XipLogListener *listener);

    
	static XipLogListener *getListener()	{ return mLogListener; };

    // Returns type identifier for XipLog class
	const XipLogType	getLogType() const	{ return mLogType; };

	const wchar_t*	getLogCategory() const	{ return mLogCategory; };  

	const wchar_t*	getModule()		 const	{ return mModule; };  

	const wchar_t*	getProcessInfo() const	{ return mProcessInfo; };  

	const wchar_t *getTimeStamp()	 const	{ return mTimeStamp; };

	const wchar_t *getDebugString()  const	{ return mDebugString; };

	//convert the error type to a string name
	inline const wchar_t* ToString() const;	

	// Returns TRUE if instance is of given type or is derived from it
	bool isOfType(XipLogType type) const;

	bool isOfCategory(const wchar_t *subType) const;

	void setTimeStamp();

	void setProcessInfo();

    // Posts an error. The debugString will be created from the given
    // arguments, which are in printf() format
	static void		post(XipLogType errortype, const wchar_t *message, const wchar_t *module, const wchar_t* category);

	static void		post(XipLogType errortype, const char *function, int line, const char* file);
	
	void recordCallStack(void *exceptionInfo);

	static const char *mCallStack;		//trace stack 

	static XipLogListener		*mLogListener;	// Static Listener for XipLog class
	
	//the log type, log types above which will be ignored in post
	static XipLogType logLevel;


protected:    
    /// Type of exception
    const XipLogType	mLogType;

	const wchar_t		*mLogCategory;	// Detailed error message string	

    const wchar_t		*mDebugString;	// Detailed error message msg

	const wchar_t		*mModule;		//which file  or line, may use __LINE__, __FILE__

	wchar_t				*mTimeStamp;	// time stamp

	wchar_t				*mProcessInfo;
	
};

//use MACRO to save time


//levels higher than logLevel will not be processed
#define XIP_POST(level, msg, module, category) \
	if (level > XipLog::logLevel) ; \
	else XipLog::post(level, msg, module, category)

//tricky to deal with variable inputs now
//use XipLog::post_error(msg) instead
#define XIP_POST_ERROR0							XIP_POST(XIP_ERROR, __FUNCTION__, __LINE__, __FILE__); 
#define XIP_POST_ERROR1(msg)					XIP_POST(XIP_ERROR, msg, L"", L""); 
#define XIP_POST_ERROR2(msg, module)			XIP_POST(XIP_ERROR, msg, module, L""); 
#define XIP_POST_ERROR(msg, module, category)	XIP_POST(XIP_ERROR, msg, module, category); 

#define XIP_POST_WARNING0						XIP_POST(XIP_WARNING, __FUNCTION__, __LINE__, __FILE__); 
#define XIP_POST_WARNING1(msg)					XIP_POST(XIP_WARNING, msg, L"", L""); 
#define XIP_POST_WARNING2(msg, module)			XIP_POST(XIP_WARNING, msg, module, , L""); 
#define XIP_POST_WARNING(msg, module, category)	XIP_POST(XIP_WARNING, msg, module, category); 

#define XIP_POST_DEBUG0							XIP_POST(XIP_DEBUG_INFO, __FUNCTION__, __LINE__, __FILE__); 
#define XIP_POST_DEBUG1(msg)					XIP_POST(XIP_DEBUG_INFO, msg, L"", L""); 
#define XIP_POST_DEBUG2(msg, module)			XIP_POST(XIP_DEBUG_INFO, msg, module, L""); 
#define XIP_POST_DEBUG(msg, module, category)	XIP_POST(XIP_DEBUG_INFO, msg, module, category); 

//use overloading functions
#define XIP_POST_LOG0							XIP_POST(XIP_LOG, __FUNCTION__, __LINE__, __FILE__); 
#define XIP_POST_LOG1(msg)						XIP_POST(XIP_LOG, msg, L"", L""); 
#define XIP_POST_LOG2(msg, module)				XIP_POST(XIP_LOG, msg, module, L""); 
#define XIP_POST_LOG(msg, module, category)		XIP_POST(XIP_LOG, msg, module, category); 

#endif // _XIP_LOG_H
