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
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <xip/inventor/coregl/SoXipFramebufferElement.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>
#include "SoXipFramebufferGroup.h"

#include <xip/system/GL/gl.h>

SO_NODE_SOURCE(SoXipFramebufferGroup);

SoXipFramebufferGroup::SoXipFramebufferGroup() {
	SO_NODE_CONSTRUCTOR(SoXipFramebufferGroup);

	SO_NODE_ADD_FIELD(width, (0));
	SO_NODE_ADD_FIELD(height, (0));
	SO_NODE_ADD_FIELD(autoSize, (false));
	SO_NODE_ADD_FIELD(format, (RGBA));
	SO_NODE_ADD_FIELD(internalFormat, (RGBA8));
	SO_NODE_ADD_FIELD(depthInternalFormat, (DEPTH_COMPONENT24));
	SO_NODE_ADD_FIELD(wrapS, (CLAMP_TO_BORDER));
	SO_NODE_ADD_FIELD(wrapT, (CLAMP_TO_BORDER));
	SO_NODE_ADD_FIELD(borderColor, (SbVec4f(0, 0, 0, 0)));
	SO_NODE_ADD_FIELD(filter, (NEAREST));
	//SO_NODE_ADD_FIELD(numBuffers, (1));
	SO_NODE_ADD_FIELD(needPingPong, (false));
	SO_NODE_ADD_FIELD(sharedDepth, (false));
	SO_NODE_ADD_FIELD(bindAllTextures, (false));

	SO_NODE_DEFINE_ENUM_VALUE(Format, ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(Format, LUMINANCE);
	SO_NODE_DEFINE_ENUM_VALUE(Format, LUMINANCE_ALPHA);
	SO_NODE_DEFINE_ENUM_VALUE(Format, INTENSITY);
	SO_NODE_DEFINE_ENUM_VALUE(Format, RGB);
	SO_NODE_DEFINE_ENUM_VALUE(Format, RGBA);
	SO_NODE_SET_SF_ENUM_TYPE(format, Format);

	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, ALPHA32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE4_ALPHA4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE6_ALPHA2);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE8_ALPHA8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE12_ALPHA4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE12_ALPHA12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE16_ALPHA16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE_ALPHA16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, LUMINANCE_ALPHA32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, INTENSITY32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, R3_G3_B2);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB5);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB10);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB32F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA2);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA4);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB5_A1);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA8);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGB10_A2);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA12);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA16);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA16F_ARB);
	SO_NODE_DEFINE_ENUM_VALUE(InternalFormat, RGBA32F_ARB);
	SO_NODE_SET_SF_ENUM_TYPE(internalFormat, InternalFormat);

	SO_NODE_DEFINE_ENUM_VALUE(DepthInternalFormat, NONE);
	SO_NODE_DEFINE_ENUM_VALUE(DepthInternalFormat, DEPTH_COMPONENT16);
	SO_NODE_DEFINE_ENUM_VALUE(DepthInternalFormat, DEPTH_COMPONENT24);
	SO_NODE_DEFINE_ENUM_VALUE(DepthInternalFormat, DEPTH_COMPONENT32);
	SO_NODE_SET_SF_ENUM_TYPE(depthInternalFormat, DepthInternalFormat);

	SO_NODE_DEFINE_ENUM_VALUE(Wrap,	 REPEAT);
	SO_NODE_DEFINE_ENUM_VALUE(Wrap,  CLAMP);
	SO_NODE_DEFINE_ENUM_VALUE(Wrap,	 CLAMP_TO_BORDER);
	SO_NODE_DEFINE_ENUM_VALUE(Wrap,  CLAMP_TO_EDGE);
	SO_NODE_DEFINE_ENUM_VALUE(Wrap,	 MIRRORED_REPEAT);
	SO_NODE_SET_SF_ENUM_TYPE(wrapS, Wrap);
	SO_NODE_SET_SF_ENUM_TYPE(wrapT, Wrap);

	SO_NODE_DEFINE_ENUM_VALUE(Filter, NEAREST);
	SO_NODE_DEFINE_ENUM_VALUE(Filter, LINEAR);
	SO_NODE_SET_SF_ENUM_TYPE(filter, Filter);

	SoField* fields[] = { &format, &internalFormat, &depthInternalFormat, &wrapS, &wrapT, &filter, &borderColor, &needPingPong, &sharedDepth };

	mNumFields = sizeof(fields) / sizeof(fields[0]);

	mSensors = new SoFieldSensor*[mNumFields];

	for (int i = 0; i < mNumFields; i++) {
		mSensors[i] = new SoFieldSensor(sensorCB, this);
		mSensors[i]->attach(fields[i]);
	}

	mNeedsUpdate = true;
	mIsAllocated = false;

	mWidth = 0;
	mHeight = 0;
}

SoXipFramebufferGroup::~SoXipFramebufferGroup() {
	for (int i = 0; i < mNumFields; i++) {
		delete mSensors[i];
	}
	delete [] mSensors;

	if (mIsAllocated) {
		deallocate();
	}
}

void SoXipFramebufferGroup::initClass() {
	SO_NODE_INIT_CLASS(SoXipFramebufferGroup, SoGroup, "SoGroup");

	SO_ENABLE(SoGLRenderAction, SoXipFramebufferElement);
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
	SO_ENABLE(SoGLRenderAction, SoXipMultiTextureElement);
}

void SoXipFramebufferGroup::GLRender(SoGLRenderAction* action) {
	if (autoSize.getValue()) {
		const SbVec2s &viewportSize = action->getViewportRegion().getViewportSizePixels();
		if (viewportSize != SbVec2s(width.getValue(), height.getValue())) {
			SoDebugError::postInfo(__FUNCTION__, "Autosetting FBO size to (%d, %d)", viewportSize[0], viewportSize[1]);
			width.setValue(viewportSize[0]);
			height.setValue(viewportSize[1]);
			mNeedsUpdate = true;
		}
	}

	// Can't use sensors if fields are changed while traversing tree, such as by parent size changing
	if (width.getValue() != mWidth  || height.getValue() != mHeight)
		mNeedsUpdate = true;

	if (mNeedsUpdate) {
		if (mIsAllocated)
			deallocate();

		allocate();

		mNeedsUpdate = false;
	}

	if (mIsAllocated) {
		// Bind a null texture on the current unit, since this will be our result unit
		SoXipMultiTextureElement::bindTexture(action->getState(), GL_TEXTURE_2D, 0);

		// Save state
		action->getState()->push();

		// Set viewport to FBO size
		SbViewportRegion viewport(mWidth, mHeight);
		action->setViewportRegion(viewport);
		SoViewportRegionElement::set(action->getState(), viewport);

		// Set up FBO element
		SoXipFramebufferElement::set(action->getState(), mFrameBuffer[0], mFrameBuffer[1], mColorBufferTex[0], mColorBufferTex[1]);

		// Render children
		SoGroup::GLRender(action);

		// Get current framebuffer (which may have changed by flipping)
		int lastFramebuffer = SoXipFramebufferElement::getCurrent(action->getState());

		// Restore state
		action->getState()->pop();

		// Restore viewport
		action->setViewportRegion(SoViewportRegionElement::get(action->getState()));

		// Bind result texture(s)
		if (needPingPong.getValue() && bindAllTextures.getValue()) {
			SoXipMultiTextureElement::bindTexture(action->getState(), GL_TEXTURE_2D, mColorBufferTex[0]);
			SoXipMultiTextureElement::setUnit(action->getState(), SoXipMultiTextureElement::getCurrentUnit(action->getState()) + 1);
			SoXipMultiTextureElement::bindTexture(action->getState(), GL_TEXTURE_2D, mColorBufferTex[1]);
		}
		else {
			SoXipMultiTextureElement::bindTexture(action->getState(), GL_TEXTURE_2D, mColorBufferTex[lastFramebuffer]);
		}
		
		SoGLTextureEnabledElement::set(action->getState(), TRUE);
	}
}

void SoXipFramebufferGroup::allocate() {
	// Check for size 0 framebuffer
	if (width.getValue() * height.getValue() == 0) {
		SoDebugError::post(__FUNCTION__, "Tried to initialize a framebuffer of size 0");
		return;
	}

	// Check for necessary GLOW extension
	if (!GLOW_EXT_framebuffer_object) {
		SoDebugError::post(__FUNCTION__, "Driver does not support necessary extensions\n");
		return;
	}

	mWidth = width.getValue();
	mHeight = height.getValue();

	// Calculate number of framebuffers and depth buffers
	mNumFrameBuffers = needPingPong.getValue() ? 2 : 1;
	mNumDepthBuffers = depthInternalFormat.getValue() != 0 ? !sharedDepth.getValue() ? mNumFrameBuffers : 1 : 0;

	//SoDebugError::post(__FUNCTION__, "Using %d color buffers and %d depth buffers", mNumFrameBuffers, mNumDepthBuffers);

	// Allocate depth buffer IDs
	if (mNumDepthBuffers > 0) {
		glGenRenderbuffersEXT(mNumDepthBuffers, mDepthBuffer);
	}
	else {
		mDepthBuffer[0] = 0;
	}

	// Use same depth buffer for both framebuffers if only 1 is allocated (shared)
	if (mNumDepthBuffers < 2)
		mDepthBuffer[1] = mDepthBuffer[0];

	int prevRenderBinding;
	glGetIntegerv(GL_RENDERBUFFER_BINDING_EXT, &prevRenderBinding);

	// Allocate depth buffers
	for (int i = 0; i < mNumDepthBuffers; i++) {
		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, mDepthBuffer[i]);
		glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, depthInternalFormat.getValue(), mWidth, mHeight);
	}

	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, prevRenderBinding);

	// Allocate texture IDs
	glGenTextures(mNumFrameBuffers, mColorBufferTex);

	int prevTextureBinding;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &prevTextureBinding);

	// Allocate color buffers
	for (int i = 0; i < mNumFrameBuffers; i++) {
		glBindTexture(GL_TEXTURE_2D, mColorBufferTex[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS.getValue());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT.getValue());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter.getValue());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter.getValue());
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor.getValue().getValue());
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat.getValue(), mWidth, mHeight, 0, format.getValue(), GL_UNSIGNED_BYTE, NULL);
	}

	// Maybe should save previous bound texture?
	glBindTexture(GL_TEXTURE_2D, prevTextureBinding);

	// Allocate framebuffer IDs
	glGenFramebuffersEXT(mNumFrameBuffers, mFrameBuffer);
	if (mNumFrameBuffers < 2)
		mFrameBuffer[1] = 0;

	int prevFboBinding;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, &prevFboBinding);

	// Allocate framebuffers
	for (int i = 0; i < mNumFrameBuffers; i++) {
		//SoDebugError::postInfo(__FUNCTION__, "Framebuffer %d: (%d, %d)", mFrameBuffer[i], mColorBufferTex[i], mDepthBuffer[i]);

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFrameBuffer[i]);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, mColorBufferTex[i], 0);
		if (mDepthBuffer[i] != 0)
			glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, mDepthBuffer[i]);

		GLenum status;
		status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
		if (status != GL_FRAMEBUFFER_COMPLETE_EXT)
			SoDebugError::post(__FUNCTION__, "Framebuffer %d not complete (%p)", i, status);
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, prevFboBinding);

	mIsAllocated = true;

	//SoDebugError::postInfo(__FUNCTION__, "Allocated resources");
}

void SoXipFramebufferGroup::deallocate() {
	glDeleteFramebuffersEXT(mNumFrameBuffers, mFrameBuffer);
	glDeleteTextures(mNumFrameBuffers, mColorBufferTex);
	if (mNumDepthBuffers > 0)
		glDeleteRenderbuffersEXT(mNumDepthBuffers, mDepthBuffer);

	for (int i = 0; i < mNumFrameBuffers; i++) {
		mFrameBuffer[i] = 0;
		mColorBufferTex[i] = 0;
		mDepthBuffer[i] = 0;
	}

	mIsAllocated = false;

	//SoDebugError::postInfo(__FUNCTION__, "Released resources");
}

void SoXipFramebufferGroup::sensorCB(void *usr, SoSensor *sensor) {
	((SoXipFramebufferGroup*)usr)->mNeedsUpdate = true;
}
