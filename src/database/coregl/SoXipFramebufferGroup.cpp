/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
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

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <xip/inventor/coregl/SoXipFramebufferElement.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>
#include "SoXipFramebufferGroup.h"

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
	glGetIntegerv(GL_TEXTURE_2D_BINDING_EXT, &prevTextureBinding);

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
