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
#ifndef SO_XIP_FRAMEBUFFER_GROUP_H
#define SO_XIP_FRAMEBUFFER_GROUP_H

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>

class SoXipFramebufferGroup : public SoGroup {
	SO_NODE_HEADER(SoXipFramebufferGroup);

public:
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
		ALPHA4 = GL_ALPHA4,
		ALPHA8 = GL_ALPHA8,
		ALPHA12 = GL_ALPHA12,
		ALPHA16 = GL_ALPHA16,
		ALPHA16F_ARB = GL_ALPHA16F_ARB,
		ALPHA32F_ARB = GL_ALPHA32F_ARB,
		LUMINANCE4 = GL_LUMINANCE4,
		LUMINANCE8 = GL_LUMINANCE8,
		LUMINANCE12 = GL_LUMINANCE12,
		LUMINANCE16 = GL_LUMINANCE16,
		LUMINANCE16F_ARB = GL_LUMINANCE16F_ARB,
		LUMINANCE32F_ARB = GL_LUMINANCE32F_ARB,
		LUMINANCE4_ALPHA4 = GL_LUMINANCE4_ALPHA4,
		LUMINANCE6_ALPHA2 = GL_LUMINANCE6_ALPHA2,
		LUMINANCE8_ALPHA8 = GL_LUMINANCE8_ALPHA8,
		LUMINANCE12_ALPHA4 = GL_LUMINANCE12_ALPHA4,
		LUMINANCE12_ALPHA12 = GL_LUMINANCE12_ALPHA12,
		LUMINANCE16_ALPHA16 = GL_LUMINANCE16_ALPHA16,
		LUMINANCE_ALPHA16F_ARB = GL_LUMINANCE_ALPHA16F_ARB,
		LUMINANCE_ALPHA32F_ARB = GL_LUMINANCE_ALPHA32F_ARB,
		INTENSITY4 = GL_INTENSITY4,
		INTENSITY8 = GL_INTENSITY8,
		INTENSITY12 = GL_INTENSITY12,
		INTENSITY16 = GL_INTENSITY16,
		INTENSITY16F_ARB = GL_INTENSITY16F_ARB,
		INTENSITY32F_ARB = GL_INTENSITY32F_ARB,
		R3_G3_B2 = GL_R3_G3_B2,
		RGB4 = GL_RGB4,
		RGB5 = GL_RGB5,
		RGB8 = GL_RGB8,
		RGB10 = GL_RGB10,
		RGB12 = GL_RGB12,
		RGB16 = GL_RGB16,
		RGB16F_ARB = GL_RGB16F_ARB,
		RGB32F_ARB = GL_RGB32F_ARB,
		RGBA2 = GL_RGBA2,
		RGBA4 = GL_RGBA4,
		RGB5_A1 = GL_RGB5_A1,
		RGBA8 = GL_RGBA8,
		RGB10_A2 = GL_RGB10_A2,
		RGBA12 = GL_RGBA12,
		RGBA16 = GL_RGBA16,
		RGBA16F_ARB = GL_RGBA16F_ARB,
		RGBA32F_ARB = GL_RGBA32F_ARB,
	};

	enum DepthInternalFormat {
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
		LINEAR = GL_LINEAR
	};

	SoXipFramebufferGroup();

	void GLRender(SoGLRenderAction* action);
	
	static void initClass();

protected:
	SoFieldSensor **mSensors;
	int mNumFields;

private:
	~SoXipFramebufferGroup();

	static void sensorCB(void *usr, SoSensor *sensor);

	void allocate();
	void deallocate();

	SoSFInt32 width;
	SoSFInt32 height;
	SoSFBool autoSize;
	SoSFEnum format;
	SoSFEnum internalFormat;
	SoSFEnum depthInternalFormat;
	SoSFEnum wrapS;
	SoSFEnum wrapT;
	SoSFEnum filter;
	SoSFVec4f borderColor;
	//SoSFInt32 numBuffers;
	SoSFBool needPingPong;
	SoSFBool sharedDepth;
	SoSFBool bindAllTextures;

	bool mNeedsUpdate;
	bool mIsAllocated;

	GLuint mFrameBuffer[2];
	GLuint mColorBufferTex[2];
	GLuint mDepthBuffer[2];
	int mNumFrameBuffers;
	int mNumDepthBuffers;

	int mWidth;
	int mHeight;
};


#endif // SO_XIP_FRAMEBUFFER_GROUP_H
