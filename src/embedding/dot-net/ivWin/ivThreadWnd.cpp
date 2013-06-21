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
/*[ Compilation unit ----------------------------------------------------------

Component:
	prototype

Name:
	ivThreadWnd.cpp

Author:
	Babu Samuel; Siemens AG SCR IM
	Thomas Moeller; Siemens AG SCR IM

Language:
	C++

Creation Date:
	December 19, 2003

Description:
	Implementation of ivThreadWnd class.

Requirement Key:


Hazard Key:
	None

Include:
	

	Copyright (C) Siemens AG 2008-2008 All Rights Reserved

-----------------------------------------------------------------------------*/
/*] END */

#pragma unmanaged

#include "stdafx.h"

#include "ivThreadWnd.hpp"
#include <process.h>


// initialize static variable
const int CreateWindowTimeOut	= 10000;
const UINT32 WM_CREATEWND = WM_USER + 1000;
const UINT32 WM_DESTROYWND = WM_USER + 1001;


/*[ Method --------------------------------------------------------------------

Name:
	ivThreadWnd::ivThreadWnd

Description:
	Constructor.

Arguments:
  -	instance
	Window name.
  -	x, y, width, height
	Window placement.
  -	parent
	Parent window.
  -	winStyle
	Window style (see MSDN Library CreateWindow).
  -	exStyle
	Extended window style (see MSDN Library CreateWindowEx).
  -	classStyle
	Class style (see MSDN Library WNDCLASS).

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
ivThreadWnd::ivThreadWnd(const wchar_t *instance, int x, int y, int width, int height, HWND parent, UINT winStyle, UINT exStyle, UINT classStyle)
: ivWnd(instance, x, y, width, height, parent, winStyle, exStyle, classStyle)
/*] END Method */
{
	mhThread	= 0;
	mThreadId	= 0;
	mIsCreated  = FALSE;
}

/*[ Method --------------------------------------------------------------------

Name:
	ivThreadWnd::~ivThreadWnd

Description:
	Destructor.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
ivThreadWnd::~ivThreadWnd()
/*] END Method */
{
	// destroy the window if exist
	if (mThreadId)
	{
		this->destroyWindow();
	}
}


/*[ Method --------------------------------------------------------------------

Name:
	ivThreadWnd::createThread

Description:
	Creates a new thread for handling window's message.

Exceptions:
	Throws IvtException if thread cannot be created.
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
BOOL ivThreadWnd::createThread()
/*] END Method */
{
	if (mhThread) return TRUE;

	// set up main thread for processing
	THREAD_START(mhThread, ThreadWnd_ServiceThread, this);

	if(!mhThread)
	{
		// THREAD_START() failed.
		return FALSE;
	}

	// wait for thread to be started (reports the thread id)
	while (!mThreadId)
	{
		// TBD: add timeout
		::Sleep(100);
	}

	return TRUE;
}


/*[ Method --------------------------------------------------------------------

Name:
	ivThreadWnd::destroyThread

Description:
	Shuts the window thread down. This method is called only by destroyWindow()
	and is therfore always called from a different thread than mThreadId.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
void ivThreadWnd::destroyThread()
/*] END Method */
{
	if (!mhThread) return;

	// signal thread to exit message loop
	::PostThreadMessage(mThreadId, WM_QUIT, 0 , 0);

	THREAD_CLOSE(mhThread);
	mhThread = 0;
	mThreadId = 0;
}


/*[ Method --------------------------------------------------------------------

Name:
	ivThreadWnd::createWindow

Description:
	Creates a OpenGL window. Attributes must be passed to constructor.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
BOOL ivThreadWnd::createWindow()
/*] END Method */
{
	// destroy any existing window before attempting to create a new one
	this->destroyWindow();

	// need to create thread first
	this->createThread();

	// create window in dedicated thread
    ::PostThreadMessage(mThreadId, WM_CREATEWND, 0, 0);

	// wait for window to be created       
	MSG msg;
	int elapseTime = 0;
    while ( ((!this->getHwnd()) || (!mhRC)) && ((elapseTime < CreateWindowTimeOut)) ) 
    {
		if (mParentWnd)
		{
			while (::PeekMessage(&msg, mParentWnd, 0, 0, PM_NOREMOVE))
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}

		::Sleep(100);
		elapseTime += 100;
    }

	if (!this->getHwnd())
    {
        // Error creating window handle.
		return FALSE;
    }

	return TRUE;
}

/*[ Method --------------------------------------------------------------------

Name:
	ivThreadWnd::destroyWindow

Description:
	Destroys window.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
void ivThreadWnd::destroyWindow()
/*] END Method */
{
	// this method can only be called from a different thread than the one we created
	// to process this window's messages

	if (mThreadId)
	{
		// Post thread message to make sure the window is destroyed in the thread
		// that created it. Afterwards clear thread ID so we now the window along with
		// it's thread is being shut down.
		::PostThreadMessage(mThreadId, WM_DESTROYWND, 0, 0);

		// we need to wait here for the window being destroyed
		int elapseTime = 0;
		while ( (this->getHwnd()) && ((elapseTime < CreateWindowTimeOut)) )
		{
			::Sleep(100);
			elapseTime += 100;
		}

		this->destroyThread();
	}
}


/*[ Function -------------------------------------------------------------

Name:
ivThreadWnd::ThreadWnd_ServiceThread

Description:
Thread function for dispatching Windows messages.

Notes:
We want this thread to be the processing thread for the main window. Therefore
the windows must be created and deleted within this thread itself, not outside.

Arguments:
void *param - pointer to UINT32 variable that receives the thread's ID

Return:
none

API:
No

Exceptions:
none.  

Error Codes:
none

----------------------------------------------------------------------*/
THREAD_FUNC_TYPE ivThreadWnd::ThreadWnd_ServiceThread(void *param)
/*] END Method */
{
	MSG msg;
	ivThreadWnd *thisPtr = (ivThreadWnd*) param;

	// thread entry point
	thisPtr->mThreadId = ::GetCurrentThreadId();

	while(GetMessage(&msg, NULL, 0, 0))
	{
		::TranslateMessage(&msg);
		if (!msg.hwnd)
		{
			// thread message
			switch(msg.message)
			{
			case  WM_CREATEWND:
				{
					BOOL status = FALSE;
					try
					{
						status = thisPtr->ivWnd::createWindow();						
					}
					catch (...)
					{
						status = FALSE;
					}
					thisPtr->mIsCreated = status;
				} break;

			case WM_DESTROYWND:
				{
					thisPtr->ivWnd::destroyWindow();
				} break;
			
			default:
				{
					// by default redirect to registered window
					//msg.hwnd = thisPtr->getHwnd();
				} break;
			}
		}
		::DispatchMessage(&msg);
	}

	THREAD_RETURN;
}
