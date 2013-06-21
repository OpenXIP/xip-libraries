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
#ifndef SOXIPOFFSCREENRENDERER_H
#define SOXIPOFFSCREENRENDERER_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFInt32.h> 
#include <Inventor/fields/SoSFNode.h> 
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/fields/SoSFEnum.h> 
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/SbLinear.h>

#include <xip/system/standard.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <xip/inventor/coregl/gpgpuContext.h>


class SoXipDataImage;


class SoXipOffscreenRenderer : public SoEngine
{
	SO_ENGINE_HEADER(SoXipOffscreenRenderer);

public:
	SoXipOffscreenRenderer();
	static void initClass();

	SoSFNode	node;
	SoSFInt32	width;
	SoSFInt32	height;
	SoSFColor	background;
	SoSFTrigger	apply;
	SoSFBool	autoApply;

	SoEngineOutput image;

	
	SoEngineOutput depthImage;
	enum Formats
	{
		UBYTE=GL_UNSIGNED_BYTE,
		USHORT=GL_UNSIGNED_SHORT,
		SHORT=GL_SHORT,
		FLOAT32=GL_FLOAT
	};


	SoSFEnum depthFormat;

protected:
	virtual ~SoXipOffscreenRenderer();

	virtual void inputChanged(SoField *whichField);

	virtual void evaluate();
	virtual void createOfflineBuffer();
	virtual void deleteOfflineBuffer();
	virtual SbBool render();


	virtual void evaluateSW();
	virtual void createSWOfflineBuffer();
	virtual void deleteSWOfflineBuffer();
	virtual SbBool renderSWBuffer();



	virtual void evaluateFBO();
	virtual void createFBO();
	virtual void deleteFBO();
	virtual SbBool renderFBO();

	SoXipDataImage *mImageData;
	SoXipDataImage *mDepthImageData;
	SbBool mNeedUpdate;

#ifdef WIN32
	HDC mDC;
	HGLRC mRC;
	void *mPixelBuffer;
	HANDLE mBMP;
	HBITMAP mOldBMP;
#endif /* WIN32 */

#ifdef linux
	Display                 *mdpy;
	Window                  mwin;
	GLXContext              mcx;
	static Pixmap mXPix ;
	static GLXPixmap mGPix;
#endif /* linux */
	
#ifdef DARWIN
	// FIXME: OpenGL context stuff
	AGLContext	ctx;
#endif /* DARWIN */
	

	int mWidth;
	int mHeight;
	SbViewVolume mViewVolume;
	bool m_bUseFBO;
	bool m_bCreatedFBO;
	GLuint renderTex;

	GLuint fbo;
	GLuint depthbuffer;
	GLuint stencilbuffer;
	bool FboOkay();

	WinGpgpuWindow* win;
};

#endif // SoXipOffscreenRenderer_H





