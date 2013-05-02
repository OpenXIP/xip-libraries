/*[ Compilation unit ----------------------------------------------------------

Component:
	prototype

Name:
	ivWnd.cpp

Author:
	Thomas Moeller; Siemens AG SCR IM

Language:
	C++

Creation Date:
	December 27, 2002

Description:
	Implementation of ivWnd class.

Requirement Key:


Hazard Key:
	None

Include:
	

	Copyright (C) Siemens AG 2008-2008 All Rights Reserved

-----------------------------------------------------------------------------*/
/*] END */

#pragma unmanaged

#include "stdafx.h"

// WM_MOUSEWHEEL
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#include <windows.h>

#include "ivWnd.hpp"
#include <windowsx.h>	// GET_Y_LPARAM etc.

#include <Inventor/SoInteraction.h>
#include <Inventor/SoSceneManager.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/actions/SoActions.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <Inventor/events/SoLocation2Event.h>


// static member
ivWndArray ivWnd::mWindows;



/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::ivWnd

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
ivWnd::ivWnd(const wchar_t *instance, int x, int y, int width, int height, HWND parent, UINT winStyle, UINT exStyle, UINT classStyle)
/*] END Method */
{
	mhWnd = NULL;
	mhRC = NULL;
	mInstance = instance;
	mLeft = x;
	mTop = y;
	mWidth = width;
	mHeight = height;
	mParentWnd = parent;
	mWinStyle = winStyle;
	mExStyle = exStyle;
	mClassStyle = classStyle;
	mIsInitialized = FALSE;

	mIdleTimer = 0;
	mSceneManager = 0;
	mRoot = 0;
	mIsSceneManagerActive = false;
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::~ivWnd

Description:
	Destructor.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
ivWnd::~ivWnd()
/*] END Method */
{
	if (mhWnd)
	{
		this->destroyWindow();

		while(::IsWindow(mhWnd))
		{
			::Sleep(10);
		}
	}
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::createWindow

Description:
	Creates a OpenGL window. Attributes must be passed to constructor.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
BOOL ivWnd::createWindow()
/*] END Method */
{
	int pf;
	HDC hDC;
	WNDCLASS wc;
	PIXELFORMATDESCRIPTOR pfd;
	HINSTANCE hInstance = 0;

	// do nothing if a window has been created
	if (mhWnd != NULL)
	{
		return TRUE;
	}

	// only register the window class if it is the first window
	if (mWindows.isEmpty())
	{
		hInstance        = GetModuleHandle(NULL);
		wc.style         = mClassStyle;
		wc.lpfnWndProc   = (WNDPROC) ivWnd_WindowProc;
		wc.cbClsExtra    = 0;
		wc.cbWndExtra    = 0;
		wc.hInstance     = hInstance;
		wc.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
		wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName  = NULL;
		wc.lpszClassName = this->getClassName();

		if (!RegisterClass(&wc))
		{
			// RegisterClass() failed.
			return FALSE;
		}
	}

	// adjust window's client rect size
	RECT r;
	r.top = mTop;
	r.left = mLeft;
	r.bottom = mTop + mHeight;
	r.right = mLeft + mWidth;

	::AdjustWindowRectEx(&r, mWinStyle, FALSE, mExStyle);

	mhWnd = ::CreateWindowEx(mExStyle, this->getClassName(), mInstance.c_str(), mWinStyle,
				r.left, r.top, r.right - r.left, r.bottom - r.top, mParentWnd, NULL, hInstance, NULL);

	if (mhWnd == NULL) 
	{
		// CreateWindowEx() failed.
		return FALSE;
	}

	if (mParentWnd)
	{
		HWND result = SetParent(mhWnd, mParentWnd);
	}

	if (!mWindows.add(mhWnd, this))
	{
		// Adding window to global list failed.
		return FALSE;
	}

	hDC = GetDC(mhWnd);

	// set pixel format descriptor
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cStencilBits = 8;
	pfd.cColorBits = 32;

	pf = ChoosePixelFormat(hDC, &pfd);
	if (pf == 0) 
	{
		// ChoosePixelFormat() failed.
		return FALSE;
	} 

	if (!SetPixelFormat(hDC, pf, &pfd)) 
	{
		// SetPixelFormat() failed.
		return FALSE;
	} 

	DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	if ((pfd.cStencilBits == 0) || (pfd.cColorBits < 24))
	{
		ReleaseDC(mhWnd, hDC);
		// Pixel format unsupported.
		return FALSE;
	}

	mhRC = wglCreateContext(hDC);

	if (!SoDB::isInitialized())
	{
		SoDB::init();
		SoInteraction::init();
	}

	mSceneManager = new SoSceneManager;
	mSceneManager->setWindowSize(SbVec2s(mWidth, mHeight));
	mSceneManager->setSize(SbVec2s(mWidth, mHeight));
	mSceneManager->setViewportRegion(SbViewportRegion(mWidth, mHeight));
	mSceneManager->setRenderCallback(renderSceneCBFunc, this);
	mSceneManager->getGLRenderAction()->setTransparencyType(SoGLRenderAction::BLEND);
	mSceneManager->setBackgroundColor(SbColor(0.0, 0.0, 0.0));

	// the first instance will create or set a global field to its RC for all others to share
	unsigned int cacheId = (unsigned int) (unsigned __int64) mhRC;
	SoSFInt32 *globalCacheContextField = (SoSFInt32 *) SoDB::getGlobalField(SbName("RAD_SHARED_CACHE_CONTEXT"));
	if (globalCacheContextField)
	{
		if (globalCacheContextField->getValue())
		{
			cacheId = globalCacheContextField->getValue();
			::wglShareLists((HGLRC) cacheId, mhRC);
		}
		else
		{
			globalCacheContextField->setValue(cacheId);
		}
	}
	else
	{
		globalCacheContextField = (SoSFInt32 *) SoDB::createGlobalField(SbName("RAD_SHARED_CACHE_CONTEXT"), SoSFInt32::getClassTypeId());
		if (globalCacheContextField)
			globalCacheContextField->setValue(cacheId);
	}

	mSceneManager->getGLRenderAction()->setCacheContext(cacheId);
	mSceneManager->activate();
	mIsSceneManagerActive = true;

	ReleaseDC(mhWnd, hDC);

//	if (mRequiresIdleProcessing)
//	{
		mIdleTimer = ::SetTimer(mhWnd, 1, 10, NULL);
//	}

//	RECT rect;
//	::GetClientRect(hWnd, &rect);
//	this->onSize(hWnd, SIZE_RESTORED, rect.right - rect.left, rect.bottom - rect.top);

	mRoot = new SoSeparator;
	mRoot->ref();
	mSceneManager->setSceneGraph(mRoot);

//	mRoot->addChild(new SoDirectionalLight);

//	SoOrthographicCamera *cam = new SoOrthographicCamera;
//	cam->set("position 0 0 5");
//	mRoot->addChild(cam);
//	mRoot->addChild(new SoCone);

	return TRUE;
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::destroyWindow

Description:
	Destroys a previously created window.

See also:
	ivWnd::createWindow

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
void ivWnd::destroyWindow()
/*] END Method */
{
	try
	{
		if (mSceneManager)
		{
			if (mIdleTimer)
			{
				::KillTimer(mhWnd, mIdleTimer);
				mIdleTimer = 0;
			}

		//	deleteFieldSensors();

			this->makeCurrent();
			mRoot->removeAllChildren();
			mSceneManager->render(FALSE, FALSE);

			mSceneManager->deactivate();
			mIsSceneManagerActive = false;

			delete mSceneManager;
			mSceneManager = 0;

			mRoot->unref();
			mRoot = 0;

			// check if this was the global shared context
			SoSFInt32 *globalCacheContextField = (SoSFInt32 *) SoDB::getGlobalField(SbName("RAD_SHARED_CACHE_CONTEXT"));
			if (globalCacheContextField)
			{
				if (mhRC == (HGLRC) globalCacheContextField->getValue())
				{
					globalCacheContextField->setValue(0);
				}
			}
		}

		// send WM_DESTROY message
		if (mhWnd)
		{
			if (mhRC)
			{
				// make the rendering context not current
				::wglMakeCurrent(NULL, NULL);

				// delete the rendering context
				wglDeleteContext(mhRC);
				mhRC = 0;
			}

			if (!::DestroyWindow(mhWnd))
			{
				// if ERROR_INVALID_WINDOW_HANDLE the parent window destroyed this
				// window as well, all other errors are a problem
				if (::GetLastError() != ERROR_INVALID_WINDOW_HANDLE)
				{
					// DestroyWindow() failed.
				}
			}

			// remove window from global list
			mWindows.remove(mhWnd);

			mhWnd = NULL;
			mIsInitialized = FALSE;

			// unregister window class
			if (mWindows.isEmpty())
			{
				if (!::UnregisterClass(this->getClassName(), GetModuleHandle(NULL)))
				{
					int e = ::GetLastError();

					// UnregisterClass() failed.
				}
			}
		}
	}
	catch(...)
	{
		// Ignore errors: This method is called also by the destructor and
		//                should never generate exceptions
	}
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::windowProc

Description:
	Window message method that receives messages sent to a window. This method maps
	certain messages to dedicated methods of the ivWnd class.
  
Arguments:
  -	uMsg
	Specifies the message.
  -	wParam
	Specifies additional message information. The contents of this parameter depend
	on the value of the uMsg parameter.
  -	lParam
	Specifies additional message information. The contents of this parameter depend
	on the value of the uMsg parameter.

See also:
	onDraw, onTimer, onMouseMove, onMouseWheel, onMouseDown, onMouseUp, onMouseDblClick,
	onChar

Return:
	The return value is the result of the message processing and depends on the
	message sent.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
LONG ivWnd::windowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
/*] END Method */
{
	if (uMsg != WM_TIMER)
	{
		wchar_t tmp[100];
		wsprintf(tmp, L"msg: %X\n", uMsg);
		//::OutputDebugStr(tmp);
	}

	switch (uMsg)
	{
	case WM_SHOWWINDOW:
		{
			int s = 1;
		} break;
	case WM_ERASEBKGND:
		{
			//this->onEraseBackground();
			return 1;
		} break;

	case WM_PAINT:
		{
			try
			{
				if (!mIsInitialized)
				{
					// first paint message
					mIsInitialized = TRUE;
					this->onInitialDisplay();
				}
				//this->onDraw();
				this->renderSceneCB();
			}
			catch (...)
			{
				// make sure we always tell the OS that the window has been painted
			}

			PAINTSTRUCT ps;
			HDC hdc; 
 			hdc = BeginPaint(mhWnd, &ps);
			EndPaint(mhWnd, &ps);

		} break;

	case WM_TIMER:
		{
			this->onTimer(wParam);
		} break;

	case WM_MOUSEMOVE:
		if (mSceneManager) 
		{
			SbTime time;
			time.setToTimeOfDay();
			SoLocation2Event event;
			event.setTime(time);
			if (wParam & MK_SHIFT) event.setShiftDown(TRUE);
			if (wParam & MK_CONTROL) event.setCtrlDown(TRUE);
			event.setPosition(SbVec2s(GET_X_LPARAM(lParam), mHeight - GET_Y_LPARAM(lParam)));
			if (mSceneManager->processEvent(&event))
			{
				SoDB::getSensorManager()->processDelayQueue(FALSE);
			}
			else
			{
				::SetCursor(::LoadCursor(NULL, IDC_ARROW));
			}
		} break;
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		::SetCapture(mhWnd);	// no break, continue to next case
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
		if (mSceneManager) 
		{
			SbTime time;
			time.setToTimeOfDay();
			SoMouseButtonEvent event;
			event.setTime(time);
			switch (uMsg)
			{
			default:
			case WM_LBUTTONDBLCLK: event.setButton(SoMouseButtonEvent::BUTTON1); break;
			case WM_LBUTTONDOWN: event.setButton(SoMouseButtonEvent::BUTTON1); break;
			case WM_MBUTTONDOWN: event.setButton(SoMouseButtonEvent::BUTTON2); break;
			case WM_RBUTTONDBLCLK: event.setButton(SoMouseButtonEvent::BUTTON3); break;
			case WM_RBUTTONDOWN: event.setButton(SoMouseButtonEvent::BUTTON3); break;
			}
			if (wParam & MK_SHIFT) event.setShiftDown(TRUE);
			if (wParam & MK_CONTROL) event.setCtrlDown(TRUE);
			event.setState(SoButtonEvent::DOWN);
			event.setPosition(SbVec2s(SbVec2s(GET_X_LPARAM(lParam), mHeight - GET_Y_LPARAM(lParam))));

			if ((uMsg == WM_LBUTTONDBLCLK) || (uMsg == WM_RBUTTONDBLCLK))
			{
				if (mSceneManager->processEvent(&event)) 
					SoDB::getSensorManager()->processDelayQueue(FALSE);
				event.setState(SoButtonEvent::UP);
			}
			if (mSceneManager->processEvent(&event))
				SoDB::getSensorManager()->processDelayQueue(FALSE);
		} break;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		::ReleaseCapture();
		if (mSceneManager) 
		{

			SbTime time;
			time.setToTimeOfDay();
			SoMouseButtonEvent event;
			event.setTime(time);
			switch (uMsg)
			{
			default:
			case WM_LBUTTONUP: event.setButton(SoMouseButtonEvent::BUTTON1); break;
			case WM_MBUTTONUP: event.setButton(SoMouseButtonEvent::BUTTON2); break;
			case WM_RBUTTONUP: event.setButton(SoMouseButtonEvent::BUTTON3); break;
			}
			if (wParam & MK_SHIFT) event.setShiftDown(TRUE);
			if (wParam & MK_CONTROL) event.setCtrlDown(TRUE);
			event.setState(SoButtonEvent::UP);
			event.setPosition(SbVec2s(SbVec2s(GET_X_LPARAM(lParam), mHeight - GET_Y_LPARAM(lParam))));
			if (mSceneManager->processEvent(&event))
				SoDB::getSensorManager()->processDelayQueue(FALSE);
		} break;

/*	case WM_MOUSEWHEEL:
		{
			this->onMouseWheel(LOWORD(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), ((short) HIWORD(wParam)) / WHEEL_DELTA);
		} break;

	case WM_CHAR:
		{
			this->onChar(wParam, lParam);
		} break;
*/
	case WM_CREATE:
		this->onCreate();
		break;

	case WM_DESTROY:
		this->onDestroy();
		break;

	case WM_CLOSE:
		if (!this->onClose())
		{
			// do not close window
			return 0;
		}
		break;

	case WM_SIZE:
		{
			//this->invalidate();
			mWidth = LOWORD(lParam);
			mHeight = HIWORD(lParam);

			if (mSceneManager)
			{
				mSceneManager->setWindowSize(SbVec2s(mWidth, mHeight));
				mSceneManager->setSize(SbVec2s(mWidth, mHeight));
				mSceneManager->setViewportRegion(SbViewportRegion(mWidth, mHeight));
				mSceneManager->scheduleRedraw();
			}
		} break;

	}
	
	return ::DefWindowProc(mhWnd, uMsg, wParam, lParam);
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::postMessage

Description:
	Window message method that post a new window message.
  
Arguments:
  -	Msg
	Specifies the message to be posted. 
  -	wParam
	Specifies additional message information.
  -	lParam
	Specifies additional message information.

Return:
	The return value is TRUE if the method succeeds.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
BOOL ivWnd::postMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
/*] END Method */
{
	return ::PostMessage(mhWnd, Msg, wParam, lParam);
}

/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::sendMessage

Description:
	Window message method that send a new window message.
  
Arguments:
  -	Msg
	Specifies the message to be sent. 
  -	wParam
	Specifies additional message information.
  -	lParam
	Specifies additional message information.

Return:
	The return value is TRUE if the method succeeds.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
BOOL ivWnd::sendMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
/*] END Method */
{
	return ::SendMessage(mhWnd, Msg, wParam, lParam);
}

/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::postQuitMessage

Description:
	Posts a quit message to the thread that created the window. This method can
	be called to exit the messageLoop method.

Arguments:
  -	exitCode
	Exit code for messageLoop. 

See also:
	ivWnd::messageLoop

Return:
	The return value is TRUE if the method succeeds.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
BOOL ivWnd::postQuitMessage(int exitCode)
/*] END Method */
{
	return ::PostMessage(mhWnd, WM_QUIT, exitCode, 0);
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::showWindow

Description:
	The ShowWindow function sets the specified window's show state.
  
Arguments:
  -	nCmdShow
	Specifies how the window is to be shown (see MSDN ShowWindow).

Return:
    The return value is TRUE if the method succeeds.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
BOOL ivWnd::showWindow(int nCmdShow)
/*] END Method */
{
	return ::ShowWindow(mhWnd, nCmdShow);
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::invalidate

Description:
	Triggers a new message that calls ivWnd::onDraw to refresh the window.

See also:
	ivWnd::onDraw
  
Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
void ivWnd::invalidate()
/*] END Method */
{
	this->postMessage(WM_PAINT, 0, 0);
}



/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::makeCurrent

Description:
	Makes the rendering context of this window current.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
void ivWnd::makeCurrent()
/*] END Method */
{
	if (::wglGetCurrentContext() != mhRC)
	{
		HDC hDC = ::GetDC(mhWnd);
		::wglMakeCurrent(hDC, mhRC);
		::ReleaseDC(mhWnd, hDC);
	}
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::swapBuffers

Description:
	Exchanges the front and back buffers.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
void ivWnd::swapBuffers()
/*] END Method */
{
	if (mhRC)
	{
		HDC hDC = ::GetDC(mhWnd);
		::SwapBuffers(hDC);
 		::ReleaseDC(mhWnd, hDC);
	}
}

#include <GL/gl.h>

/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::onDraw

Description:
	Called whenever a window needs to be rerendered.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
void ivWnd::onDraw()
/*] END Method */
{
	this->makeCurrent();
	glClear(GL_COLOR_BUFFER_BIT);
	this->swapBuffers();
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::onEraseBackground

Description:
	Called whenever a window needs to erase it's background.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
void ivWnd::onEraseBackground()
/*] END Method */
{

}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::onTimer

Description:
	Called when the window receives a timer message.

Arguments:
  -	id
    Timer identifier.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
void ivWnd::onTimer(int id)
/*] END Method */
{
	if (id == 1)
	{
		// monitor parent window size and adjust if necessary
		RECT parentRect, thisRect;
		::GetClientRect(mParentWnd, &parentRect);
		::GetClientRect(mhWnd, &thisRect);

		if ((parentRect.right != thisRect.right) || (parentRect.bottom != thisRect.bottom))
		{
			::MoveWindow(mhWnd, 0, 0, parentRect.right, parentRect.bottom, FALSE);
		}

		// process timer and delay queue
		SoDB::getSensorManager()->processDelayQueue(TRUE);
		SoDB::getSensorManager()->processTimerQueue();
	}
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::onCreate

Description:
	Called when the window receives a create message. The window procedure of
	the new window receives this message after the window is created, but before
	the window becomes visible.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
void ivWnd::onCreate()
/*] END Method */
{
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::onInitialDisplay

Description:
	Called when the window is displayed for the first time.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
void ivWnd::onInitialDisplay()
/*] END Method */
{
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::onDestroy

Description:
	Called when the window receives a destroy message.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
void ivWnd::onDestroy()
/*] END Method */
{
	if (mhRC)
	{
		// make the rendering context not current
		::wglMakeCurrent(NULL, NULL);

		// delete the rendering context
		wglDeleteContext(mhRC);
		mhRC = 0;
	}

}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::onClose

Description:
	Called when the window receives a WM_CLOSE message.

Return:
	If TRUE is returned the default window message handler is called, which will
	send a WM_DESTROY message to the window. If FALSE is returned, the message is
	ignored.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
bool ivWnd::onClose()
/*] END Method */
{
	return FALSE;
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::onMouseWheel

Description:
	Called when a mouse wheel is rotated.

Arguments:
  -	keys
	Indicates whether various virtual keys are down:
	MK_CONTROL - Set if the ctrl key is down. 
	MK_LBUTTON - Set if the left mouse button is down. 
	MK_MBUTTON - Set if the middle mouse button is down. 
	MK_RBUTTON - Set if the right mouse button is down. 
	MK_SHIFT   - Set if the shift key is down. 
  -	x, y
	Mouse position.
  -	delta
	Indicates distance rotated.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
void ivWnd::onMouseWheel(unsigned int keys, int x, int y, int delta)
/*] END Method */
{

}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::onChar

Description:
	Called when a character key is pressed.

Arguments:
  -	charCode
	Character code.
  -	keyData
	Specifies the repeat count, scan code, extended-key flag, context code,
	previous key-state flag, and transition-state flag, as shown in the following table:
	0 -15 - Specifies the repeat count for the current message.
	16-23 - Specifies the scan code.
	24    - The value is 1 if it is an extended key; otherwise, it is 0. 
	29    - The value is 1 if the alt key is held down while the key is pressed.
	30    - The value is 1 if the key is down before the message is sent., or it is 0 if the key is up.
	31    - The value is 1 if the key is being released, or it is 0 if the key is being pressed. 

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
void ivWnd::onChar(unsigned int charCode, unsigned int keyData)
/*] END Method */
{

}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::getWidth

Description:
	Returns the width of the window.

Return:
	Window width.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
int ivWnd::getWidth() const
/*] END Method */
{
	RECT r;
	::GetClientRect(mhWnd, &r);
	
	return r.right;
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::getHeight

Description:
	Returns the height of the window.

Return:
	Window height.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
int ivWnd::getHeight() const
/*] END Method */
{
	RECT r;
	::GetClientRect(mhWnd, &r);
	
	return r.bottom;
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::getHwnd

Description:
	Returns the window handle.

Return:
	Window handle.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
HWND ivWnd::getHwnd() const
/*] END Method */
{
	return mhWnd;
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::getClassName

Description:
	Returns the window class name.

Return:
	Window class name.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
const wchar_t* ivWnd::getClassName() const
/*] END Method */
{
	return L"ivWnd";
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::getInstance

Description:
	Returns the instance/window name passed to the constructor.

Return:
	Instance name.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
const wchar_t* ivWnd::getInstance() const
/*] END Method */
{
	return mInstance.c_str();
}


/*[ Method --------------------------------------------------------------------

Name:
	ivWnd::messageLoop

Description:
	Global (static) method that runs the Windows message loop.

Return:
	wParam of last processed message (WM_QUIT).

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
int ivWnd::messageLoop()
/*] END Method */
{
	MSG msg;

	while(GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		if (!msg.hwnd)
		{
			// thread message, redirect to default window
			::PostMessage(mWindows.getDefaultWnd(), msg.message, msg.wParam, msg.lParam);
			continue;
		}
		::DispatchMessage(&msg);
	}

	return msg.wParam;
}


/*[ Function ------------------------------------------------------------------

Name:
	ivWnd_WindowProc

Description:
	Window message function that receives messages sent to a window. All messages
    are redirected to the associated ivWnd::windowProc method.

Arguments:
  -	hWnd
	Handle to the window.
  -	uMsg
	Specifies the message.
  -	wParam
	Specifies additional message information. The contents of this parameter depend
	on the value of the uMsg parameter.
  -	lParam
	Specifies additional message information. The contents of this parameter depend
	on the value of the uMsg parameter.

Return:
	The return value is the result of the message processing and depends on the
	message sent.

See also:
	ivWnd::windowProc

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
static LONG WINAPI ivWnd_WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
/*] END Function */
{
    // get class that is associated with this window handle
	void *ptr = ivWnd::mWindows.getPtr(hWnd);

	if (ptr)
	{
        // forward the message
		return ((ivWnd*) ptr)->windowProc(uMsg, wParam, lParam);
	}

	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}


/*[ Method --------------------------------------------------------------------

Name:
	ivMainWnd::ivMainWnd

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
ivMainWnd::ivMainWnd(const wchar_t *instance, int x, int y, int width, int height, HWND parent, UINT wStyle, UINT exStyle, UINT cStyle)
	: ivWnd(instance, x, y, width, height, parent, wStyle, exStyle, cStyle)
/*] END Method */
{
}


/*[ Method --------------------------------------------------------------------

Name:
	ivMainWnd::onDestroy

Description:
	Called when the window receives a destroy message. Posts a quit message to
	the thread that created the window.

See also:
	ivWnd::postQuitMessage

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
void ivMainWnd::onDestroy()
/*] END Method */
{
	this->postQuitMessage();
}


/*[ Method --------------------------------------------------------------------

Name:
	ivMainWnd::onClose

Description:
	Called when the window receives a WM_CLOSE message.

Return:
	If TRUE is returned the default window message handler is called, which will
	send a WM_DESTROY message to the window. If FALSE is returned, the message is
	ignored.

Exceptions:
	N/A
	
Hazard Key:
	None

API:
	no

-----------------------------------------------------------------------------*/
bool ivMainWnd::onClose()
/*] END Method */
{
	return TRUE;
}


void ivWnd::renderSceneCBFunc(void *user, class SoSceneManager *)
{
	if (user)
	{
		((ivWnd*) user)->renderSceneCB();
	}
}

void ivWnd::fieldSensorCBFunc(void *user, SoSensor *sensor)
{
}

void ivWnd::errorHandlerCBFunc(const SoError *error, void *data)
{
}


void ivWnd::renderSceneCB()
{
	if (mhWnd && mSceneManager)
	{
		// get DC and make rendering context current if necessary
		//HDC hDC = ::GetDC(mhWnd);
		//HGLRC prevRC = wglGetCurrentContext();
		//if (prevRC != mhRC) wglMakeCurrent(hDC, mhRC);

		this->makeCurrent();

		// render and swap front/back buffers
		glEnable(GL_DEPTH_TEST);

		mSceneManager->render();
		//::SwapBuffers(hDC);
		this->swapBuffers();

		// restore prev. rendering context and release DC
		//if (prevRC != mhRC) wglMakeCurrent(hDC, prevRC);
		//::ReleaseDC(mhWnd, hDC);
	}
}

SoSeparator *ivWnd::getRoot() const
{
	return mRoot;
}
