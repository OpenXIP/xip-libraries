/*[ Compilation unit ----------------------------------------------------------

Component:
	prototype

Name:
	ivThreadWnd.hpp

Author:
	Babu Samuel; Siemens AG SCR IM
	Thomas Moeller; Siemens AG SCR IM

Language:
	C++

Creation Date:
	December 19, 2003

Description:
	Declaration of ivThreadWnd class.

Requirement Key:


Hazard Key:
	None

Include:
	

	Copyright (C) Siemens AG 2008-2008 All Rights Reserved

-----------------------------------------------------------------------------*/
/*] END */

#ifndef IVTHREADWND_HPP
#define IVTHREADWND_HPP

#include "ivWnd.hpp"

// threading helper macros
#define THREAD_HANDLE		HANDLE
#define THREAD_CLOSE(h)		{ Sleep(0); ::WaitForSingleObject(h, 100); ::CloseHandle(h); }
#define THREAD_RETURN		return ::GetCurrentThreadId()
#ifdef _MT
#define THREAD_FUNC_TYPE	unsigned int __stdcall
#define THREAD_START(h,f,p)	{ UINT32 dummy;	h = (HANDLE) ::_beginthreadex(NULL, 0, f, (void*) p, 0, &dummy); }
#else
#define THREAD_FUNC_TYPE	DWORD WINAPI
#define THREAD_START(h,f,p)	{ unsigned long dummy; h = ::CreateThread(NULL, 0, f, (LPVOID) p, 0, &dummy); }
#endif	// _MT


/*[ Class ---------------------------------------------------------------------

Name:
	ivThreadWnd - Utility class for the creation of Win32 OpenGL windows running in its own thread.

Description:
	Utility class for the creation of Win32 OpenGL windows. This class is inherited
	from ivWnd and adds the functionality of running in a separate thread.
	
Base Classes:
	ivWnd

Include:
	#include "ivThreadWnd.hpp"

Requirement Key:

  
Hazard Key:
	None

API:
	no

Derivable:
	yes

-----------------------------------------------------------------------------*/
class ivThreadWnd : public ivWnd
/*] END Class */
{
public:
	ivThreadWnd(const wchar_t *instance, int x, int y, int width, int height, HWND parent = NULL, UINT wStyle = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, UINT exStyle = 0, UINT cStyle = CS_OWNDC);
	virtual ~ivThreadWnd();

	virtual BOOL createWindow();
	virtual void destroyWindow();

protected:
	virtual BOOL createThread();
	virtual void destroyThread();

	static THREAD_FUNC_TYPE ThreadWnd_ServiceThread(void* param);

protected:
	void*				mhThread;				// Thread handle
	unsigned int		mThreadId;				// Thread Id
	BOOL				mIsCreated;
};

#endif
