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

#include <xip/system/standard.h>
#include <xip/inventor/coregl/SoXipOffscreenRenderer.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/errors/SoError.h>
#include <xip/system/GL/gl.h>
#include <xip/system/GL/glu.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>

#define FUNCID(...) //SoError::post(__FUNCTION__,"");

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifdef linux
Pixmap SoXipOffscreenRenderer::mXPix =0;
GLXPixmap SoXipOffscreenRenderer::mGPix = 0;
#endif /* linux */

SO_ENGINE_SOURCE(SoXipOffscreenRenderer);


static inline void CheckGLError(const char * module)
{

	GLenum err = glGetError(); 

	if (err != GL_NO_ERROR)
	{ 
		SoError::post(module, (char*)gluErrorString(err));
	}

}
SoXipOffscreenRenderer::SoXipOffscreenRenderer()
{
	mImageData = 0;
	mDepthImageData = 0;
	mNeedUpdate = 0;
#ifdef WIN32
	mDC = 0;
	mRC = 0;
	mPixelBuffer = 0;
	mBMP = 0;
	mOldBMP = 0;
#endif /* WN32 */

#ifdef linux
	mImageData = 0;
	mNeedUpdate = 0;

	mwin = 0;
	mcx = 0;
	mdpy = 0;
	mXPix=0 ;
	mGPix=0;
#endif /* linux */
	
#ifdef DARWIN
	ctx = 0;
	// TODO: FIXME: OpenGL context stuff
#endif /* DARWIN */
	
	mWidth = 0;
	mHeight = 0;

	SO_ENGINE_CONSTRUCTOR(SoXipOffscreenRenderer);
	SO_ENGINE_DEFINE_ENUM_VALUE( Formats, UBYTE );
	SO_ENGINE_DEFINE_ENUM_VALUE( Formats, USHORT );
	SO_ENGINE_DEFINE_ENUM_VALUE( Formats, SHORT );
	SO_ENGINE_DEFINE_ENUM_VALUE( Formats, FLOAT32 );
	SO_ENGINE_SET_SF_ENUM_TYPE( depthFormat, Formats );
	SO_ENGINE_ADD_INPUT( depthFormat, (UBYTE) );

	SO_ENGINE_ADD_INPUT(node, (0));
	SO_ENGINE_ADD_INPUT(width, (512));
	SO_ENGINE_ADD_INPUT(height, (512));
	SO_ENGINE_ADD_INPUT(background, (0, 0, 0));
	SO_ENGINE_ADD_INPUT(apply, ());
	SO_ENGINE_ADD_INPUT(autoApply, (FALSE));



	SO_ENGINE_ADD_OUTPUT(image, SoXipSFDataImage);
	SO_ENGINE_ADD_OUTPUT(depthImage, SoXipSFDataImage);
	m_bUseFBO=false;
	m_bCreatedFBO=false;
	win=NULL;
}


SoXipOffscreenRenderer::~SoXipOffscreenRenderer()
{


	deleteOfflineBuffer();

	if (mImageData)
	{
		mImageData->unref();
		mImageData = 0;
	}
}


void SoXipOffscreenRenderer::initClass()
{
	SO_ENGINE_INIT_CLASS(SoXipOffscreenRenderer, SoEngine, "Engine");
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
}


void SoXipOffscreenRenderer::inputChanged(SoField *whichField)
{
	if (autoApply.getValue() || (whichField == &apply))
		mNeedUpdate = TRUE;

	SoEngine::inputChanged(whichField);
}

void SoXipOffscreenRenderer::evaluateSW(){


	if (mNeedUpdate)
	{
		if (mImageData)
		{
			mImageData->unref();
			mImageData = 0;
		}

		createOfflineBuffer();
		if (render())
		{
			
			SbMatrix modelMatrix;
			modelMatrix.setScale(SbVec3f(mWidth, mHeight, 1));

			SbXipImage *img = new SbXipImage(
				SbXipImageDimensions(mWidth, mHeight),
				SbXipImage::UNSIGNED_BYTE, 8, 3, SbXipImage::INTERLEAVED, SbXipImage::RGB, modelMatrix);
#if !defined(DARWIN)
			unsigned char* buffer = (unsigned char *) img->refBufferPtr();
#endif // DARWIN
#ifdef WIN32
			unsigned char *src = (unsigned char *) mPixelBuffer;

			for (int y = mHeight - 1; y >= 0; y--)
			{
				
				unsigned char *src = (unsigned char *) mPixelBuffer;

					src += y * (mWidth * 4);
				for (int x = 0; x < mWidth; x++)
				{
					buffer[0] = src[2];
					buffer[1] = src[1];
					buffer[2] = src[0];

					buffer += 3;
					src += 4;
				}
			}
#endif /* WIN32 */

#ifdef linux
			if(glXMakeCurrent(mdpy, mGPix, mcx))
			{
			
				glReadPixels( 	0,
						0,
						mWidth,
						mHeight,
						GL_BITMAP,
						GL_RGB,
						buffer);
				glXMakeCurrent(mdpy,0,NULL);
			}									
#endif /* linux */
			
#ifdef DARWIN
			// FIXME: OpenGL context stuff
#endif /* DARWIN */

			img->unrefBufferPtr();
			mImageData = new SoXipDataImage;
			mImageData->ref();
			mImageData->set(img);
		}
		
	}

	// update output
	SO_ENGINE_OUTPUT(image, SoXipSFDataImage, setValue(mImageData));

	mNeedUpdate = FALSE;
}


void SoXipOffscreenRenderer::evaluate()
{
#ifdef WIN32
	HGLRC    prev_hglrc=wglGetCurrentContext();
	HDC		prev_hdc=wglGetCurrentDC();

	win=WinGpgpuWindow::Instance();
	win->makeCurrent();
 	SoXipGLOW::init();
	
 	if(!GLOW_EXT_framebuffer_object)m_bUseFBO=false;
	else m_bUseFBO=true;
 
	if(m_bUseFBO){
 		evaluateFBO();
 	}
 	else{
 		evaluateSW();
 	};
 	
 	if(prev_hdc!=NULL && prev_hglrc!=NULL)  wglMakeCurrent(prev_hdc, prev_hglrc );
#endif /* WIN32 */

#ifdef linux
 	GLXContext	prev_cx= glXGetCurrentContext();
 	Window		prev_win= glXGetCurrentDrawable();
 
 	win=WinGpgpuWindow::Instance();
 	 /*   if(win==NULL) 
 		{
 			win=new WinGpgpuWindow;
 		int error=win->createWindow();
 			if(WinGpgpuWindow::errorCreate_NoError!= error)SoError::post("error creating gpgpu win\n");
  
 		}*/
	win->makeCurrent();	
  	SoXipGLOW::init();

	if(!GLOW_EXT_framebuffer_object)m_bUseFBO=false;
	else m_bUseFBO=true;
 
	if(m_bUseFBO){
		evaluateFBO();
  	}
  	else{
  		evaluateSW();
  	};
  	if(prev_win!=NULL && prev_cx!=NULL)  glXMakeCurrent(mdpy,prev_win,prev_cx);
#endif /* LINUX */

#ifdef DARWIN
	// FIXME: OpenGL context stuff
#endif /* DARWIN */
}

void SoXipOffscreenRenderer::createSWOfflineBuffer(){
#ifdef WIN32
	if ((width.getValue() == mWidth) && (height.getValue() == mHeight))
		return;

	deleteOfflineBuffer();

	if ((width.getValue() <= 0) || (height.getValue() <= 0))
		return;

	BITMAPINFOHEADER bih;
	memset(&bih, 0, sizeof(bih));
	bih.biSize = sizeof(bih);
	bih.biWidth = ((((int) width.getValue() * 8) + 31) & ~31) >> 3;
	bih.biHeight = height.getValue();
	bih.biPlanes = 1;
	bih.biBitCount = 32;
	bih.biCompression = BI_RGB;

	mDC = CreateCompatibleDC(NULL);
	mBMP = CreateDIBSection(mDC, (BITMAPINFO*) &bih, DIB_PAL_COLORS, &mPixelBuffer, NULL, 0);
	mOldBMP = (HBITMAP) SelectObject(mDC, mBMP);

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_BITMAP | PFD_SUPPORT_OPENGL;// | PFD_SUPPORT_GDI;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cAlphaBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int PixelFormat = ChoosePixelFormat(mDC, &pfd);
	SetPixelFormat(mDC, PixelFormat, &pfd);


	mRC = wglCreateContext(mDC);
	unsigned int cacheId = (unsigned __int64) mRC;


	if (mRC)
	{
		mWidth = width.getValue();
		mHeight = height.getValue();
	}
	else
	{
		SoError::post("SoXipOffscreenRenderer::createOfflineBuffer", "OpenGL error: %d", glGetError());
	}
#endif /* WIN32 */

#ifdef linux
	if ((width.getValue() == mWidth) && (height.getValue() == mHeight))
		return;

	deleteOfflineBuffer();

	if ((width.getValue() <= 0) || (height.getValue() <= 0))
		return;

	mdpy = XOpenDisplay(NULL);
	if(mdpy == NULL) {
		printf("\n\tcannot connect to X server\n\n");
		exit(0); 
	}
	XVisualInfo    *Visp;
	int attrList[10], n=0;
	int dblBuf[] = {GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, GLX_DEPTH_SIZE, 12, GLX_DOUBLEBUFFER, GLX_USE_GL, 1, None};
	int snglBuf[] = {GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, GLX_DEPTH_SIZE, 12, GLX_USE_GL, 1, None};  

	Visp = glXChooseVisual(mdpy, DefaultScreen(mdpy),dblBuf); // Did Windows Find A Matching Pixel Format?

		if (Visp == NULL) {
			Visp = glXChooseVisual(mdpy, DefaultScreen(mdpy),snglBuf);
			if (Visp == NULL) {
				exit(-1);
			}			}

	unsigned int WIDTH=((((int) width.getValue() * 8) + 31) & ~31) >> 3;
	unsigned int HEIGHT=height.getValue();

	//printf("Visp = %p, depth = %d\n", Visp, Visp->depth);

	mXPix = XCreatePixmap(mdpy, RootWindow(mdpy, Visp->screen), WIDTH, HEIGHT, Visp->depth);

	//printf("XPix = %p\n", mXPix);

	mGPix = glXCreateGLXPixmap(mdpy, Visp, mXPix); //The glXCreateGLXPixmap subroutine creates an off-screen rendering area and returns its XID

	mcx = glXCreateContext(mdpy, Visp, None, True);					//Create a new GLX rendering	context
	if (mcx) {
		
		mWidth = width.getValue();
		mHeight = height.getValue();
	}
#endif /* linux */

#ifdef DARWIN
	// FIXME: OpenGL context stuff
#endif /* DARWIN */
}

void SoXipOffscreenRenderer::createOfflineBuffer()
{

	if(m_bUseFBO){

		createFBO();
	}
	else{
		createSWOfflineBuffer();
	};

}

void SoXipOffscreenRenderer::deleteSWOfflineBuffer(){

#ifdef WIN32
	mWidth = mHeight = 0;
	mPixelBuffer = 0;

	if (mRC)
	{
		wglMakeCurrent(0, 0);
		wglDeleteContext(mRC);
		mRC = 0;
	}

	if (mBMP)
	{
		SelectObject(mDC, mOldBMP);
		DeleteObject(mBMP);
		mBMP = 0;
		mOldBMP = 0;
	}

	if (mDC)
	{
		DeleteDC(mDC);
		mDC = 0;
	}
#endif /* WIN32 */

#ifdef linux
	mWidth = mHeight = 0;
	mXPix = 0;
	mGPix = 0;
	if (mcx)											
	{
		glXMakeCurrent(mdpy,0,NULL);					
		glXDestroyContext(mdpy,mcx);
		mcx=NULL;										
	}
	if(mwin)
	{
		XDestroyWindow(mdpy, mwin);
		mwin=0;
	}
	if(mdpy)
	{
		XCloseDisplay(mdpy);
		mdpy=0;
	}
#endif /* linux */

#ifdef DARWIN
	// FIXME: OpenGL context stuff
#endif /* DARWIN */
}

void SoXipOffscreenRenderer::deleteOfflineBuffer()
{


	if(m_bUseFBO){

		deleteFBO();
	}
	else{
		deleteSWOfflineBuffer();
	};


}

SbBool SoXipOffscreenRenderer::renderSWBuffer(){

	if ((mWidth <= 0) || (mHeight <= 0) || !node.getValue()) 
		return FALSE;

	// note that context sharing and hardware acceleration are not available for
	// PFD_DRAW_TO_BITMAP context
	SoGLRenderAction *renderAction = new SoGLRenderAction(SbViewportRegion(mWidth, mHeight));
	if (!renderAction)
		return FALSE;


	#ifdef WIN32
	HDC hDC = ::wglGetCurrentDC();
	HGLRC hRC = ::wglGetCurrentContext();

	renderAction->setCacheContext((unsigned int) mRC);
	renderAction->setTransparencyType(SoGLRenderAction::BLEND);
	wglMakeCurrent(mDC, mRC);
	#elif defined(linux) && !(defined(__x86_64) || defined(__x86_64__) || defined(__ia64)) //64 bit version did not work
 	GLXContext cx = glXGetCurrentContext();
 	Window win= glXGetCurrentDrawable();
 	renderAction->setCacheContext((unsigned int) mcx);
 	renderAction->setTransparencyType(SoGLRenderAction::BLEND);
 	glXMakeCurrent(mdpy, mwin, mcx); 	
 	#endif
#ifdef DARWIN
	// FIXME: OpenGL context stuff
#endif /* DARWIN */
	SbColor c = background.getValue();
	glClearColor(c[0], c[1], c[2], 0 );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	renderAction->apply(node.getValue());
	mViewVolume = SoViewVolumeElement::get(renderAction->getState());

	delete renderAction;

 	#ifdef WIN32	
	 	wglMakeCurrent(hDC, hRC);
 	#elif defined(linux) && !defined(__x86_64__)
 		glXMakeCurrent(mdpy, win, cx);
 	#endif
#ifdef DARWIN
	// FIXME: OpenGL context stuff
#endif /* DARWIN */

	return TRUE;
}
SbBool SoXipOffscreenRenderer::render()
{

	bool ret = false;
	if (m_bUseFBO) {

		ret = renderFBO() == TRUE;
	}
	else {
		ret = renderSWBuffer() == TRUE;
	}
	return ret;

}
void SoXipOffscreenRenderer::evaluateFBO(){


	if (mNeedUpdate)
	{
		if (mImageData)
		{
			mImageData->unref();
			mImageData = 0;
		}

		createOfflineBuffer();

		//	bool ret=render();

		if (render())
		{

			SbMatrix modelMatrix;
			modelMatrix.setScale(SbVec3f(mWidth, mHeight, 1));

			SbXipImage *img = new SbXipImage(
				SbXipImageDimensions(mWidth, mHeight),
				SbXipImage::UNSIGNED_BYTE, 8, 4, SbXipImage::INTERLEAVED, SbXipImage::RGBA, modelMatrix);

			unsigned char* buffer = (unsigned char *) img->refBufferPtr();

			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
			glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
			glReadPixels(0, 0, mWidth, mHeight, GL_RGBA, GL_UNSIGNED_BYTE, buffer); 


			//SbXipImage::DataType type=SbXipImage::UNSIGNED_BYTE;
			//if(depthFormat.getValue()==GL_UNSIGNED_SHORT)type=SbXipImage::UNSIGNED_SHORT;
			//else if(depthFormat.getValue()==GL_SHORT)type=SbXipImage::SHORT;
			//else if(depthFormat.getValue()==GL_FLOAT)type=SbXipImage::FLOAT;
			//SbXipImage *depthimg = new SbXipImage(
			//	SbXipImageDimensions(mWidth, mHeight),
			//	type, 8, 1, SbXipImage::SEPARATE, SbXipImage::LUMINANCE, modelMatrix);



			//void* dbuffer =  depthimg->refBufferPtr();

			//glReadPixels(0, 0, mWidth, mHeight, GL_DEPTH_COMPONENT, depthFormat.getValue(), dbuffer);

			//depthimg->unrefBufferPtr();

			//mDepthImageData = new SoXipDataImage;
			//mDepthImageData->ref();
			//mDepthImageData->set(depthimg);

			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);


			img->unrefBufferPtr();

			mImageData = new SoXipDataImage;
			mImageData->ref();
			mImageData->set(img);
		}

	}

	// update output
	SO_ENGINE_OUTPUT(image, SoXipSFDataImage, setValue(mImageData));
	SO_ENGINE_OUTPUT(depthImage, SoXipSFDataImage, setValue(mDepthImageData));
	mNeedUpdate = FALSE;


}
void SoXipOffscreenRenderer::createFBO(){





	if ((width.getValue() == mWidth) && (height.getValue() == mHeight))
		return;

	deleteFBO();

	if ((width.getValue() <= 0) || (height.getValue() <= 0))
		return;

	mWidth = width.getValue();
	mHeight = height.getValue();
	//create FBO
	glGenFramebuffersEXT(1, &fbo);


	m_bCreatedFBO=true;
	// bind offscreen buffer 
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);

	// create rendertexture 

	glGenTextures (1, &renderTex);
	glBindTexture(GL_TEXTURE_2D,renderTex);
	// turn off filtering and set proper wrap mode 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	;
	// and allocate graphics memory
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 
		mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	//attach texture to FBO

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, 
		GL_TEXTURE_2D, renderTex, 0);








	glGenRenderbuffersEXT(1, &depthbuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthbuffer);

	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT,GL_DEPTH_COMPONENT24, mWidth, mHeight);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,
		GL_DEPTH_ATTACHMENT_EXT,
		GL_RENDERBUFFER_EXT, depthbuffer);
	////
	/*
	// initialize packed depth-stencil renderbuffer
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, packed_rb);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_STENCIL_EXT, 512, 512);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, packed_rb);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, packed_rb);*/
	/////////////
	
	/*
	//does not seem to be supported with teh current generation of GPUs/drivers
	glGenRenderbuffersEXT(1, &stencilbuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, stencilbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_STENCIL_INDEX, mWidth, mHeight);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT,GL_RENDERBUFFER_EXT, stencilbuffer);
	*/

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	//FboOkay();

}

bool SoXipOffscreenRenderer::FboOkay(){

	bool isOK = false;

	GLenum status;                                            
	status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	switch(status) {                                          
  case GL_FRAMEBUFFER_COMPLETE_EXT: // Everything's OK
	  isOK = true;
	  break;
  case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
	  SoError::post("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT\n");
	  isOK = false;
	  break;
  case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:

	  SoError::post("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT\n");
	  isOK = false;
	  break;
  case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:

	  SoError::post("GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT\n");
	  isOK = false;
	  break;
  case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:

	  SoError::post("GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT\n");
	  isOK = false;
	  break;
  case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:

	  SoError::post("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT\n");
	  isOK = false;
	  break;
  case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:

	  SoError::post( "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT\n");
	  isOK = false;
	  break;
  case GL_FRAMEBUFFER_UNSUPPORTED_EXT:

	  SoError::post( "GL_FRAMEBUFFER_UNSUPPORTED_EXT\n");
	  isOK = false;
	  break;
  default:

	  SoError::post( "Unknown ERROR\n");
	  isOK = false;
	}

	return isOK;
}


void SoXipOffscreenRenderer::deleteFBO(){

	if(m_bCreatedFBO){

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, 0, 0);



		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		if(stencilbuffer!=0)glDeleteRenderbuffersEXT(1, &stencilbuffer);
		if(depthbuffer!=0)glDeleteRenderbuffersEXT(1, &depthbuffer);
		if(fbo!=0)glDeleteFramebuffersEXT (1,&fbo);

		if(renderTex!=0)glDeleteTextures(1,&renderTex);

		m_bCreatedFBO=false;
	}

}

SbBool SoXipOffscreenRenderer::renderFBO(){

	int vp[4];
	GLint currentDrawbuf;
	glGetIntegerv(GL_DRAW_BUFFER, &currentDrawbuf); // Save the current Draw buffer
	glGetIntegerv(GL_VIEWPORT, vp);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();




	if ((mWidth <= 0) || (mHeight <= 0) ) 

		return FALSE;




	if (!node.getValue()) 

		return FALSE;


	SoGLRenderAction *renderAction = new SoGLRenderAction(SbViewportRegion(mWidth, mHeight));
#if (_MIPS_SZPTR == 64 || __ia64 || __x86_64 || __x86_64__)
    renderAction->setCacheContext((unsigned int)((unsigned long) win->getGLContext()));
#else
	renderAction->setCacheContext((unsigned int) win->getGLContext());
#endif
	if (!renderAction)
		return FALSE;


	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	SbColor c = background.getValue();
	glClearColor(c[0], c[1], c[2], 0 );
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	GLfloat params[16]={0.0,0.0,0.0,0.0,
		0.0,0.0,0.0,0.0,
		0.0,0.0,0.0,0.0,
		0.0,0.0,0.0,0.0};


	glGetFloatv(GL_MODELVIEW_MATRIX,params);
	glGetFloatv(GL_PROJECTION_MATRIX,params);




	renderAction->apply(node.getValue());

	//mViewVolume = SoViewVolumeElement::get(renderAction->getState());


	delete renderAction;


	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glDrawBuffer(currentDrawbuf);
	glViewport(vp[0],vp[1],vp[2],vp[3]);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	return TRUE;
}


