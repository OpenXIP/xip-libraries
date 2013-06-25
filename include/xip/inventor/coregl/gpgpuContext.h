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
*/#ifndef __WIN32_GPGPU_WINDOW_H__
#define __WIN32_GPGPU_WINDOW_H__

#include <xip/system/standard.h>
#include <xip/system/GL/gl.h>
#include <xip/system/GL/glu.h>
#include <xip/system/GL/xipglwindow.h>

#ifdef linux
#include<stdlib.h>
#include<iostream>
#include<X11/Xlib.h>
#endif

#ifdef linux

  #include<stdlib.h>
  #include<iostream>
  #include<X11/Xlib.h>
  #include<GL/glx.h>
  #include<GL/glu.h>

#endif // linux

#include <Inventor/errors/SoError.h>
#include <Inventor/fields/SoSFInt32.h>
/*
* This class creates a context for GPGPU computations with OpenGL.
* When using engines, there is not necessarily an OpenGL context available,
* in this case, a context is created.
* For now, only Windows is supported, different architectures coule be added, though.


*/

class WinGpgpuWindow{

private:
#ifdef WIN32
		HWND                    m_hWnd;
		WNDCLASSEX              m_wc;
		static HDC		hDC;		// private GDI Device Context
		static HGLRC		hRC;		// Rendering Context
		HWND			hWnd;		// handle to window
		HINSTANCE		hInstance;	//application instance
#endif // WIN32 
#ifdef linux
		static Display                 * dpy;
		static Window                  win;
		static GLXContext              cx;

		static int dblBuf[];
		static int snglBuf[];
#endif //linux
#ifdef DARWIN
	static AGLContext  ctx;
	// FIXME: OpenGL context stuff
#endif // DARWIN
	static bool instanceFlag;
    	static WinGpgpuWindow *theWinGpgpuWindow;

	WinGpgpuWindow();
	//kills the window and returns an error if something goes wrong
	int KillGLWindow(void);
	//creates the window, window does not show up, though
	int createWindow();
	//destroy the window at the end
	void destroyWindow();
public:
	//error codes for KillGlWindow
	const static int errorKill_NoError=0;
	const static int errorKill_MakeCurrent=1;
	const static int errorKill_NotAllowedToDelete=2;
	const static int errorKill_NotAllowedToRelease=3;
	const static int errorKill_NotAllowedToDestroy=4;
	const static int errorKill_NotAllowedToUnregister=5;


public:

	static WinGpgpuWindow* Instance();
#ifdef WIN32
		HGLRC		getGLContext()
		{
			return hRC;
		}
		HDC			getDeviceContext()
		{
			return hDC;
		}
		void makeCurrent()
		{
			wglMakeCurrent(hDC,hRC);
		}
#endif // WIN32 
#ifdef linux
		GLXContext		getGLContext()
		{
			return cx;
		}
		Display*		getDeviceDisplay()
		{
			return dpy;
		}
		Window		getWindow()
		{
			return win;
		}
		void makeCurrent()
		{
			glXMakeCurrent(dpy, win, cx);
		}

#endif //linux
		
#ifdef DARWIN
	// FIXME: OpenGL context stuff
	AGLContext	getGLContext()
	{
		return ctx;
	}
	void makeCurrent()
	{
		aglSetCurrentContext(ctx);
	}	
#endif // DARWIN
	const static int errorCreate_NoError=0;
	const static int errorCreate_Register=1;
	const static int errorCreate_Create=2;
	const static int errorCreate_DeviceContext=3;

	const static int errorCreate_PixelFormat=5;
	const static int errorCreate_SetPixelFormat=6;
	const static int errorCreate_CreateRenderingContext=7;
	const static int errorCreate_MakeCurrent=8;
};

#endif // __WIN32_GPGPU_WINDOW_H__




