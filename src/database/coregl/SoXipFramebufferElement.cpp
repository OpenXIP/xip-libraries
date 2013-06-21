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
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <xip/inventor/coregl/SoXipFramebufferElement.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>

#undef DEBUG

#ifdef DEBUG
#define FUNCID(...) SoDebugError::postInfo(__FUNCTION__, __VA_ARGS__);
#else
#define FUNCID(...)
#endif

SO_ELEMENT_SOURCE(SoXipFramebufferElement);

void SoXipFramebufferElement::initClass() {
	SO_ELEMENT_INIT_CLASS(SoXipFramebufferElement, SoElement);

	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
	SO_ENABLE(SoGLRenderAction, SoXipMultiTextureElement);
}

SoXipFramebufferElement::~SoXipFramebufferElement() {
	FUNCID("");
}

void SoXipFramebufferElement::init(SoState *state) {
	FUNCID("");

	// Initialize to some default values
	mFrameBuffer[0] = 0;
	mFrameBuffer[1] = 0;
	mColorBufferTex[0] = 0;
	mColorBufferTex[1] = 0;
	mCurrentFramebuffer = 0;
	hasDualBuffers = false;
	mTextureUnit = 0;
}

void SoXipFramebufferElement::push(SoState *state) {
	FUNCID("");

	// Propogate values from previous

	SoXipFramebufferElement *prev = (SoXipFramebufferElement*)(this->getNextInStack());

	/*
		FIXUP: The default element assumes FBO 0 is bound, this might not be the case
		so one way of solving this is to check GL for the real FBO in use. This is
		probably only needed when the current framebuffer is 0.
	*/

	if (prev->mFrameBuffer[prev->mCurrentFramebuffer] == 0)
	{
		int currentFbo;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, &currentFbo);
		prev->mFrameBuffer[prev->mCurrentFramebuffer] = currentFbo;
	}

	mFrameBuffer[0] = prev->mFrameBuffer[0];
	mFrameBuffer[1] = prev->mFrameBuffer[1];
	mColorBufferTex[0] = prev->mColorBufferTex[0];
	mColorBufferTex[1] = prev->mColorBufferTex[1];
	mCurrentFramebuffer = prev->mCurrentFramebuffer;
	hasDualBuffers = prev->hasDualBuffers;
	mTextureUnit = prev->mTextureUnit;
}

void SoXipFramebufferElement::pop(SoState *state, const SoElement *prevTopElement) {
	FUNCID("");

	// If same FB, keep changes
	if (mFrameBuffer[0] == ((SoXipFramebufferElement*)prevTopElement)->mFrameBuffer[0] &&
		mFrameBuffer[1] == ((SoXipFramebufferElement*)prevTopElement)->mFrameBuffer[1]) {
			mCurrentFramebuffer = ((SoXipFramebufferElement*)prevTopElement)->mCurrentFramebuffer;
	}
	// otherwise restore OpenGL state
	else {
		bindFB();
	}

	//if (mFramebuffer) {
	//	delete mFramebuffer;
	//}
	//if (((SoXipFramebufferElement*)prevTopElement)->mDataFramebuffer)
	//	((SoXipFramebufferElement*)prevTopElement)->mDataFramebuffer->unref();
}

SbBool SoXipFramebufferElement::matches(const SoElement *elt) const {
	FUNCID("");
    return false;
}

SoElement* SoXipFramebufferElement::copyMatchInfo() const {
	FUNCID("");
    SoXipFramebufferElement *result = (SoXipFramebufferElement*)getTypeId().createInstance();

    return result;
}

void SoXipFramebufferElement::set(SoState *state, GLuint primaryFB, GLuint secondaryFB, GLuint primaryTex, GLuint secondaryTex) {
	FUNCID("set with fb = (%d, %d)", primaryFB, secondaryFB);
	SoXipFramebufferElement *elt = (SoXipFramebufferElement*)getElement(state, classStackIndex);

	if (elt) {
		elt->setElt(state, primaryFB, secondaryFB, primaryTex, secondaryTex);
	}
}

void SoXipFramebufferElement::setElt(SoState *state, GLuint primaryFB, GLuint secondaryFB, GLuint primaryTex, GLuint secondaryTex) {
	mFrameBuffer[0] = primaryFB;
	mFrameBuffer[1] = secondaryFB;
	mColorBufferTex[0] = primaryTex;
	mColorBufferTex[1] = secondaryTex;
	
	hasDualBuffers = secondaryFB != 0;

	bindFB();

	if (hasDualBuffers) {
		// Save current texture unit
		mTextureUnit = SoXipMultiTextureElement::getCurrentUnit(state);

		bindTex(state);
	}
}

void SoXipFramebufferElement::flip(SoState *state) {
	FUNCID("");
	SoXipFramebufferElement *elt = (SoXipFramebufferElement*)getElement(state, classStackIndex);

	if (elt) {
		elt->flipElt(state);
	}

	return;
}

void SoXipFramebufferElement::flipElt(SoState *state) {
	if (hasDualBuffers) {
		mCurrentFramebuffer = (mCurrentFramebuffer + 1) % 2;

		bindFB();

		// Change to FBO-reserved texture unit
		GLuint unit = SoXipMultiTextureElement::getCurrentUnit(state);
		if (unit != mTextureUnit) {
			glActiveTexture(GL_TEXTURE0 + mTextureUnit);
			bindTex(state);
			glActiveTexture(GL_TEXTURE0 + unit);
		}
		else {
			bindTex(state);
		}
	}
	else {
		SoDebugError::post(__FUNCTION__, "Cannot flip a single framebuffer");
	}
}

int SoXipFramebufferElement::getCurrent(SoState *state) {
	FUNCID("");
	const SoXipFramebufferElement *elt = (SoXipFramebufferElement*)getConstElement(state, classStackIndex);

	if (elt) {
		return elt->getCurrentElt();
	}

	return 0;
}

int SoXipFramebufferElement::getCurrentElt() const {
	return mCurrentFramebuffer;
}

void SoXipFramebufferElement::bindFB() {
	FUNCID("fb = %d", mFrameBuffer[mCurrentFramebuffer]);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mFrameBuffer[mCurrentFramebuffer]);
}

void SoXipFramebufferElement::bindTex(SoState *state) {
	FUNCID("tex = %d", mColorBufferTex[(mCurrentFramebuffer + 1) % 2]);

	// Do not use the element, since we want our binds from flips to be preserved across separators
	glBindTexture(GL_TEXTURE_2D, mColorBufferTex[(mCurrentFramebuffer + 1) % 2]);
}
