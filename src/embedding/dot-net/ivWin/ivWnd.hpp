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
	ivWnd.hpp

Author:
	Thomas Moeller; Siemens AG SCR IM

Language:
	C++

Creation Date:
	December 27, 2002

Description:
	Declaration of ivWnd class.

Requirement Key:


Hazard Key:
	None

Include:
	

	Copyright (C) Siemens AG 2008-2008 All Rights Reserved

-----------------------------------------------------------------------------*/
/*] END */

#ifndef IVWND_HPP
#define IVWND_HPP

#include "ivWndArray.hpp"
#include <string>

class SoSceneManager;
class SoSeparator;
class SoSensor;
class SoError;


/*[ Class ---------------------------------------------------------------------

Name:
	ivWnd - Utility class for the creation of Win32 OpenGL windows.

Description:
	Utility class for the creation of Win32 OpenGL windows. This class provides
    a set of virtual convenience methods for basic windows message handling.
	
Base Classes:

Include:
	#include "ivWnd.hpp"

Requirement Key:

  
Hazard Key:
	None

API:
	no

Derivable:
	yes

-----------------------------------------------------------------------------*/
class ivWnd
/*] END Class */
{
public:
	// constructor / destructor
	ivWnd(const wchar_t *instance, int x, int y, int width, int height, HWND parent = NULL, UINT wStyle = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, UINT exStyle = 0, UINT cStyle = CS_OWNDC);
	virtual ~ivWnd();

	// operations
	virtual BOOL createWindow();
	virtual void destroyWindow();
	virtual BOOL postMessage(UINT Msg, WPARAM wParam, LPARAM lParam);
	virtual BOOL postQuitMessage(int exitCode = 0);
	virtual BOOL sendMessage(UINT Msg, WPARAM wParam, LPARAM lParam);
	virtual BOOL showWindow(int nCmdShow);
	virtual void invalidate();
	virtual void makeCurrent();
	virtual void swapBuffers();

	// attributes
	virtual HWND getHwnd() const;
	virtual int getHeight() const;
	virtual int getWidth() const;
	virtual const WCHAR* getInstance() const;
	virtual const WCHAR *getClassName() const;
	virtual SoSeparator *getRoot() const;

	// global message pump
	static int messageLoop();

protected:
	// event handlers
	virtual LONG windowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void onChar(unsigned int charCode, unsigned int keyData);
	virtual void onMouseWheel(unsigned int keys, int x, int y, int delta);
	virtual void onTimer(int id);
	virtual void onDraw();
	virtual void onEraseBackground();
	virtual void onCreate();
	virtual void onDestroy();
	virtual bool onClose();
	virtual void onInitialDisplay();

	virtual void renderSceneCB();


	// member variables
	static ivWndArray mWindows;
	std::wstring mInstance;
	HWND mhWnd;
	HGLRC mhRC;
	HWND mParentWnd;
	int mLeft;
	int mTop;
	int mWidth;
	int mHeight;
	UINT mClassStyle;
	UINT mWinStyle;
	UINT mExStyle;
	bool mIsInitialized;

	// inventor
	bool mIsSceneManagerActive;
	UINT mIdleTimer;

	SoSceneManager *mSceneManager;
	SoSeparator *mRoot;

friend
	static LONG WINAPI ivWnd_WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	static void renderSceneCBFunc(void *user, class SoSceneManager *);
	static void fieldSensorCBFunc(void *user, SoSensor *sensor);
	static void errorHandlerCBFunc(const SoError *error, void *data);
};



/*[ Class ---------------------------------------------------------------------

Name:
	ivMainWnd - Utility class for the creation of an application window.

Description:
	Utility class for the creation of Win32 OpenGL application window. This class
	overrides the ivWnd::onDestroy to post a quit message to the thread
	that created the window.
	
Base Classes:
	ivWnd

See also:
	ivWnd::messageLoop, ivWnd::postQuitMessage

Include:
	#include "ivWnd.hpp"

Requirement Key:

  
Hazard Key:
	None

API:
	no

Derivable:
	yes

-----------------------------------------------------------------------------*/
class ivMainWnd : public ivWnd
/*] END Class */
{
public:
	// constructor
	ivMainWnd(const wchar_t *instance, int x, int y, int width, int height, HWND parent = NULL, UINT wStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, UINT exStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, UINT cStyle = CS_OWNDC);

protected:
	virtual void onDestroy();
	virtual bool onClose();
};


#endif
