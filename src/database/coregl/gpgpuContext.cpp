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

			PIXELFORMATDESCRIPTOR  pfd;
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

