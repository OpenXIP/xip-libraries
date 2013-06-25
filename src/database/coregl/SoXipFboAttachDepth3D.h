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

#ifndef SO_XIP_FBO_ATTACH_DEPTH_3D_H
#define SO_XIP_FBO_ATTACH_DEPTH_3D_H


/**
 *  Component       : XIP
 *  Name            : SoXipFboAttachDepth3D
 *  Author          : Jaume S, SCR, Princeton
 *  Language        : C++
 *  Creation Date   : 6-Jan-2008
 *  Description     :   Duplicates current FBO and attaches an
 *                      additional depth target. Any previously
 *                      existing depth target will be replaced.
 *
 *  Copyright © Siemens AG 2006-2007. All Rights Reserved.
 */


#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <xip/inventor/coregl/SoXipFramebufferElement.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <xip/inventor/coregl/FramebufferObject.h>



class SoXipFboAttachDepth3D : public SoNode
{
	SO_NODE_HEADER(SoXipFboAttachDepth3D);

public:

    enum BufferStorage {
		TEXTURE      = GL_TEXTURE_2D,
		RENDERBUFFER = GL_RENDERBUFFER_EXT,
	};

    enum Format {
		NONE = 0,
		ALPHA = GL_ALPHA,
		LUMINANCE = GL_LUMINANCE,
		LUMINANCE_ALPHA = GL_LUMINANCE_ALPHA,
		INTENSITY = GL_INTENSITY,
		RGB = GL_RGB,
		RGBA = GL_RGBA,
	};

	enum InternalFormat {
		DEPTH_COMPONENT16 = GL_DEPTH_COMPONENT16,
		DEPTH_COMPONENT24 = GL_DEPTH_COMPONENT24,
		DEPTH_COMPONENT32 = GL_DEPTH_COMPONENT32,
	};

	enum Wrap			// Texture wrap type
	{
		REPEAT			= GL_REPEAT,
		CLAMP			= GL_CLAMP,
		CLAMP_TO_EDGE	= GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER	= GL_CLAMP_TO_BORDER,
		MIRRORED_REPEAT	= GL_MIRRORED_REPEAT
	};

	enum Filter
	{
		NEAREST	= GL_NEAREST,
		LINEAR  = GL_LINEAR
	};

	SoXipFboAttachDepth3D();
	void            GLRender(SoGLRenderAction* action);
	static void     initClass();

    // "input" fields
    SoSFInt32       sizeX;
    SoSFInt32       sizeY;
    SoSFInt32       sizeZ;
	SoSFEnum        bufferStorage;
	SoSFEnum        internalFormat;
	SoSFEnum        wrap;
	SoSFEnum        filter;

    // "output" fields
	SoMFInt32       handleOutput;

protected:

    SoFieldSensor  *mSensorOut;
    int             mNumFields;
    int             mNumFieldsOut;

private:

	~SoXipFboAttachDepth3D();
    bool            checkFramebufferStatus();
    static void     sensorOutCB(void *usr, SoSensor *sensor);
	bool            mNeedsUpdate;

	void            allocate();
    void            deallocate();
    void            syncOutput();

    FboSetup        mFboIn;
    FboSetup        mFboOut;
    GLuint          mHandle;
    unsigned int    mNodeId;
    bool            mIsAllocated;
};


#endif // SO_XIP_FBO_ATTACH_DEPTH_3D_H
