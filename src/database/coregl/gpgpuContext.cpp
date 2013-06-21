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

#include <xip/inventor/coregl/gpgpuContext.h>
#include <Inventor/errors/SoError.h>

bool WinGpgpuWindow::instanceFlag = false;
WinGpgpuWindow* WinGpgpuWindow::theWinGpgpuWindow = NULL;

#ifdef WIN32
	 HDC			WinGpgpuWindow::hDC=0;		
	 HGLRC		WinGpgpuWindow::hRC=0;	
	//TEXT macro casts char * to appropriate wtring format windows uses
	LRESULT WINAPI MsgProcGpgpu( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
	switch( msg )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
	}
	LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
#endif /* WIN32 */

#ifdef linux
	Window		WinGpgpuWindow::win=0;
	GLXContext	WinGpgpuWindow::cx=0;
	Display*	WinGpgpuWindow::dpy;
	int WinGpgpuWindow::dblBuf[] = {GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, GLX_DEPTH_SIZE, 12, GLX_DOUBLEBUFFER, GLX_USE_GL, 1, None};
	int WinGpgpuWindow::snglBuf[] = {GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, GLX_DEPTH_SIZE, 12, GLX_USE_GL, 1, None};   	
#endif /* linux */

#ifdef DARWIN
	AGLContext	WinGpgpuWindow::ctx=0;
	// FIXME: OpenGL context stuff
#endif /* DARWIN */


WinGpgpuWindow::WinGpgpuWindow(){
#ifdef WIN32
	HDC			hDC=NULL;		// Private GDI Device Context
	HGLRC		hRC=NULL;		// Permanent Rendering Context
	HWND		hWnd=NULL;		// Holds Our Window Handle
#endif /* WIN32 */
	
#ifdef linux
	Display		*dpy=0;			// Private X-server Connection
	GLXContext      cx=0;		//GLX Rendering Context
	Window		win=0;			//Private GLX Drawable
#endif /* linux */

#ifdef DARWIN
	ctx = 0;
	// FIXME: OpenGL context stuff
#endif /* DARWIN */	
}



//kills the window and returns an error if something goes wrong
int WinGpgpuWindow::KillGLWindow(void)								
{
#ifdef WIN32
	int error=0;
	if (hRC)											
	{
		if (!wglMakeCurrent(NULL,NULL))					
		{
			error= errorKill_MakeCurrent;
		}

		if (!wglDeleteContext(hRC))						
		{
			error= errorKill_NotAllowedToDelete;
		}
		hRC=NULL;										
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					
	{
		error=errorKill_NotAllowedToRelease;
		hDC=NULL;										
	}

	if (hWnd && !DestroyWindow(hWnd))					
	{
		error=errorKill_NotAllowedToDestroy;
		hWnd=NULL;										
	}

	if (!UnregisterClass(TEXT("gpgpu"),hInstance))			
	{
		error=errorKill_NotAllowedToUnregister;
		hInstance=NULL;									
	}
	return error;
#endif /* WIN32 */

#ifdef linux
	int error=0;
	if (cx)											
	{
		if (!glXMakeCurrent(dpy,0,NULL))					
		{
			error= errorKill_MakeCurrent;
		}

		glXDestroyContext(dpy,cx);
		cx=NULL;										
	}
	if(win)
	{
		XDestroyWindow(dpy, win);
		win=0;
	}
	if(dpy)
	{
		XCloseDisplay(dpy);
		dpy=0;
	}
	return error;
#endif /* linux */

#ifdef DARWIN
	// FIXME: OpenGL context stuff
#endif /* DARWIN */
}


/*
const static int WinGpgpuWindow::errorCreate_NoError=0;
const static int WinGpgpuWindow::errorCreate_Register=1;
const static int WinGpgpuWindow::errorCreate_Create=2;
const static int WinGpgpuWindow::errorCreate_DeviceContext=3;

const static int WinGpgpuWindow::errorCreate_PixelFormat=5;
const static int WinGpgpuWindow::errorCreate_SetPixelFormat=6;
const static int WinGpgpuWindow::errorCreate_CreateRenderingContext=7;
const static int WinGpgpuWindow::errorCreate_MakeCurrent=8;
*/
//creates the window, window does not show up, though
int WinGpgpuWindow::createWindow(){
#ifdef WIN32
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match

	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)1;//width=1		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)1;//height=1		// Set Bottom Value To Requested Height



	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		=MsgProcGpgpu;// (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// no Menu
	wc.lpszClassName	= TEXT("gpgpu");								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		return errorCreate_Register;
	}




	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style


	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
		TEXT("gpgpu"),							// Class Name
		TEXT("gpgpu"),								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right-WindowRect.left,	// Calculate Window Width
		WindowRect.bottom-WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		return errorCreate_Create;
	}



	///create handle for Opengl
	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		8,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		8,											//  alpha buffer: 8 bits
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		8,											// Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		return errorCreate_DeviceContext;
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		return errorCreate_PixelFormat;
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		return errorCreate_SetPixelFormat;
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		return errorCreate_CreateRenderingContext;
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		return errorCreate_MakeCurrent;
	}
	return errorCreate_NoError;
#endif /* WIN32 */

#ifdef linux
	XVisualInfo             *vi;				//Display structure that serves as the connection to the X server
	Colormap                cmap;
	XSetWindowAttributes    swa;
	Bool doubleBuffer = True;
	unsigned int width=1;
	unsigned int height=1;

	dpy = XOpenDisplay(NULL);				//Open Display connection to the X server
	if(dpy == NULL) {
		printf("\n\tcannot connect to X server\n\n");
		exit(0); }

	vi = glXChooseVisual(dpy, DefaultScreen(dpy),dblBuf); // Did Windows Find A Matching Pixel Format?
	if (vi == NULL) {
		vi = glXChooseVisual(dpy, DefaultScreen(dpy),snglBuf);
		if (vi == NULL) {
			KillGLWindow();				// Reset The Display
			return errorCreate_PixelFormat;
		}
		doubleBuffer = False;		}

	// Create an X colormap for use.
	cmap = XCreateColormap(dpy,RootWindow(dpy, vi->screen), vi->visual, AllocNone);	//Creates a colormap of the specified visual type
	swa.colormap = cmap;
	swa.border_pixel = 0;
	swa.event_mask = ExposureMask           |
					 VisibilityChangeMask   |
					 KeyPressMask           |
					 KeyReleaseMask         | 
					 ButtonPressMask        |
					 ButtonReleaseMask      |
					 PointerMotionMask      |
					 StructureNotifyMask    |
					 SubstructureNotifyMask |
					 FocusChangeMask;//ExposureMask | ButtonPressMask | StructureNotifyMask;

	win = XCreateWindow(dpy, RootWindow(dpy, vi->screen), 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
	if (!win) {
		KillGLWindow();								// Reset The Display
		return errorCreate_Create;			
	}

	//XMapWindow(dpy, win); ....................make window appear
	XStoreName(dpy, win, "gpgpu");

	cx = glXCreateContext(dpy, vi, None, True);					//Create a new GLX rendering	context
	if (cx == NULL) {
		KillGLWindow();								// Reset The Display
		return errorCreate_CreateRenderingContext;
	}

	
	// bind the rendering context to the window
	if(!glXMakeCurrent(dpy, win, cx))		
	{
		KillGLWindow();								// Reset The Display
		return errorCreate_MakeCurrent;
	}
	
	return errorCreate_NoError;
#endif /* linux */

#ifdef DARWIN
	// FIXME: OpenGL context stuff
#endif /* DARWIN */
}


//destroy the window at the end
void WinGpgpuWindow::destroyWindow(){
	//destroy
#ifdef WIN32
	UnregisterClass(TEXT("gpgpu"), m_wc.hInstance);
#endif /* WIN32 */

#ifdef linux
	XDestroyWindow(dpy, win);						//Destroys the specified window as well as all of its subwindows
#endif /* linux */

#ifdef DARWIN
	// FIXME: OpenGL context stuff
#endif /* DARWIN */
}

 WinGpgpuWindow* WinGpgpuWindow::Instance() 
{
#ifdef WIN32
	if(! instanceFlag)
	{	  
		HGLRC rc=0;
		SoSFInt32 *	globalCacheContextField = (SoSFInt32 *) SoDB::getGlobalField(SbName("SHARED_MASTER_CONTEXT"));
		if (globalCacheContextField){
			int val=globalCacheContextField->getValue();
			rc=  (HGLRC) (unsigned __int64)val;

		}
		HDC hdc=0;
		SoSFInt32 *	globalCacheDeviceContextField = (SoSFInt32 *) SoDB::getGlobalField(SbName("SHARED_MASTER_DEVICE_CONTEXT"));
		if (globalCacheDeviceContextField){
			int val=globalCacheDeviceContextField->getValue();
			hdc=  (HDC) (unsigned __int64)val;
#ifdef DARWIN
			PIXELFORMATDESCRIPTOR  pfd;
#endif // DARWIN
			int  iPixelFormat;

			// get the current pixel format index 
			iPixelFormat = GetPixelFormat(hdc); 

			/*// obtain a detailed description of that pixel format 
			DescribePixelFormat(hdc, iPixelFormat, 
			sizeof(PIXELFORMATDESCRIPTOR), &pfd); 
			int i=0;*/
		}	
		if (globalCacheContextField	&&globalCacheDeviceContextField){  
			hDC=hdc;
			hRC=rc ;
			instanceFlag=true;
			return theWinGpgpuWindow;
		}
	}
	if(! instanceFlag)
	{
		theWinGpgpuWindow = new WinGpgpuWindow();
		int error=theWinGpgpuWindow->createWindow();
		if(WinGpgpuWindow::errorCreate_NoError!= error)SoError::post("error creating gpgpu win\n");
		instanceFlag = true;
		return theWinGpgpuWindow;
	}
	else
	{
		return theWinGpgpuWindow;
	}
#endif /* WIN32 */

#ifdef linux
	if(! instanceFlag)
	{	  
		

		GLXContext	cxt=0;
		
		SoSFInt32 *	globalCacheContextField = (SoSFInt32 *) SoDB::getGlobalField(SbName("SHARED_MASTER_CONTEXT"));
		if (globalCacheContextField){
			int val=globalCacheContextField->getValue();
			cxt=  (GLXContext)val;
		}
		Window	wint=0;
		SoSFInt32 *	globalCacheDeviceContextField = (SoSFInt32 *) SoDB::getGlobalField(SbName("SHARED_MASTER_DEVICE_CONTEXT"));
		if (globalCacheDeviceContextField){
			int val=globalCacheDeviceContextField->getValue();
			wint=  (Window)val;

			 // construct an XVisualInfo that matches the default Visual:
			  XVisualInfo templt; int num;
			  XVisualInfo *xvisual;
			  templt.visualid = XVisualIDFromVisual(DefaultVisual(dpy, DefaultScreen(dpy)));
			  xvisual = XGetVisualInfo(dpy, VisualIDMask, &templt, &num);

		}	
		if (globalCacheContextField	&&globalCacheDeviceContextField){  
			cx=cxt;
			win=wint ;
			instanceFlag=true;
			return theWinGpgpuWindow;
		}
	}
	if(! instanceFlag)
	{
		theWinGpgpuWindow = new WinGpgpuWindow();
		int error=theWinGpgpuWindow->createWindow();
		if(WinGpgpuWindow::errorCreate_NoError!= error)SoError::post("error creating gpgpu win\n");
		instanceFlag = true;
		return theWinGpgpuWindow;
	}
	else
	{
		return theWinGpgpuWindow;
	}
#endif /* linux */

#ifdef DARWIN
	// FIXME: OpenGL context stuff
#endif /* DARWIN */
}



