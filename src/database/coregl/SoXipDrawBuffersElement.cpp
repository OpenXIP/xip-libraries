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
#include <xip/system/GL/gl.h>
#include <xip/inventor/coregl/SoXipDrawBuffersElement.h>

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/errors/SoDebugError.h>


#undef DEBUG

#ifdef DEBUG
#define FUNCID(...) SoDebugError::postInfo(__FUNCTION__, __VA_ARGS__);
#else
#define FUNCID(...)
#endif


SO_ELEMENT_SOURCE(SoXipDrawBuffersElement);

/**
 *  Class initiation.
 */
void SoXipDrawBuffersElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipDrawBuffersElement, SoReplacedElement);
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
}

/**
 *  Destructor.
 */
SoXipDrawBuffersElement::~SoXipDrawBuffersElement()
{
	FUNCID("");
}

/**
 *  Initiates first instance of element.
 */
void SoXipDrawBuffersElement::init(SoState *state)
{
	FUNCID("");
    int maxDrawBuffers = 0;
    int maxAttachments = 0;
    mMaxBuffers = 0;
    mNumBuffers = 0;

    // Get maximum number of buffers (should be defined in GLOW)
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &maxAttachments);
    glGetIntegerv(GL_MAX_DRAW_BUFFERS,      &maxDrawBuffers);
    mMaxBuffers = (maxAttachments < maxDrawBuffers) ? maxAttachments : maxDrawBuffers;

    // Extract current sub buffer setup
    int subBuffers = GL_NONE;
    for (int i = 0; i < mMaxBuffers; i++)
    {
        subBuffers = GL_NONE;
        glGetIntegerv(GL_DRAW_BUFFER0 + i, &subBuffers);
        mSubBuffers[i] = subBuffers;
        if (subBuffers)
            mNumBuffers++;
    }
    for (int i = mMaxBuffers; i < 16; i++)
        mSubBuffers[i] = GL_NONE;

    //mNumBuffers = 0;
}



/**
 *  Push functionality to support scene traversal.
 */
void SoXipDrawBuffersElement::push(SoState *state)
{
	FUNCID("push");

	// Propogate values from previous
	SoXipDrawBuffersElement *prev = (SoXipDrawBuffersElement*)(this->getNextInStack());
    mMaxBuffers = prev->mMaxBuffers;
    mNumBuffers = prev->mNumBuffers;
    for (int i = 0; i < 16; i++)
        mSubBuffers[i] = prev->mSubBuffers[i];
}

/**
 *  Pop functionality to support scene traversal.
 */
void SoXipDrawBuffersElement::pop(SoState *state, const SoElement *prevTopElement)
{
	FUNCID("pop");

	// Always rebind when pop (for now at least)
    drawBuffersGL();
}



#if 0
SbBool SoXipDrawBuffersElement::matches(const SoElement *elt) const {
	FUNCID("");
    return false;
}

SoElement* SoXipDrawBuffersElement::copyMatchInfo() const {
	FUNCID("");
    SoXipDrawBuffersElement *result = (SoXipDrawBuffersElement*)getTypeId().createInstance();

    return result;
}
#endif



/**
 *  Set function for setting current setup.
 *  Static version.
 *  @see setElt()
 */
void SoXipDrawBuffersElement::set(SoState *state, SoNode *node, int numBuffers)
{
	FUNCID("set");
    SoXipDrawBuffersElement *elt = (SoXipDrawBuffersElement*)getElement(state, classStackIndex, node);
	if (elt) {
		elt->setElt(numBuffers);
	}
}

/**
 *  Set function for setting current setup.
 *  @see set()
 */
void SoXipDrawBuffersElement::setElt(int numBuffers)
{
    if (numBuffers)
    {
        mNumBuffers = (numBuffers < mMaxBuffers) ? numBuffers : mMaxBuffers;
        for (int i = 0; i < mNumBuffers; i++)
            mSubBuffers[i] = GL_COLOR_ATTACHMENT0_EXT + i;
        for (int i = mNumBuffers; i < 16; i++)
            mSubBuffers[i] = GL_NONE;
    }

    drawBuffersGL();
}





/**
 *  Set function for setting current setup.
 *  Static version.
 *  @see setElt()
 */
void SoXipDrawBuffersElement::setBuffer(SoState *state, SoNode *node, int buffer)
{
	FUNCID("setBuffer");
    SoXipDrawBuffersElement *elt = (SoXipDrawBuffersElement*)getElement(state, classStackIndex, node);
	if (elt) {
		elt->setBufferElt(buffer);
	}
}

/**
 *  Set function for setting current setup.
 *  @see set()
 */
void SoXipDrawBuffersElement::setBufferElt(int buffer)
{
    mNumBuffers = 1;
    mSubBuffers[0] = buffer;
    for (int i = 1; i < 16; i++)
        mSubBuffers[i] = GL_NONE;

    drawBuffersGL();
}





/**
 *  Get function for extraction of current setup.
 *  Static version.
 *  @see getElt()
 */
int SoXipDrawBuffersElement::getNum(SoState *state, SoNode *node)
{
	FUNCID("get");
    SoXipDrawBuffersElement *elt = (SoXipDrawBuffersElement*)getElement(state, classStackIndex, node);
    return (elt) ? elt->getNumElt() : 0;
}

/**
 *  Non static Elt version.
 */
int SoXipDrawBuffersElement::getNumElt()
{
    return mNumBuffers;
}


/**
 *  Get function for extraction of current sub buffer setup.
 *  Static version.
 *  Use getNum in order to allocate enough memory before calling
 *  getSubBuffers since memory is assumed to be allocated.
 *  @see getElt()
 */
void SoXipDrawBuffersElement::getSubBuffers(SoState *state, SoNode *node, int num, GLenum * iBuffers)
{
	FUNCID("get");
    SoXipDrawBuffersElement *elt = (SoXipDrawBuffersElement*)getElement(state, classStackIndex, node);
    if (elt)
        elt->getSubBuffersElt(num, iBuffers);
}

/**
 *  Non static Elt version.
 */
void SoXipDrawBuffersElement::getSubBuffersElt(int num, GLenum * iBuffers)
{
    if (num < 16)
        for (int i = 0; i < num; i++)
            iBuffers[i] = mSubBuffers[i];
}


/**
 *  Internal, binds the active FBO.
 */
void SoXipDrawBuffersElement::drawBuffersGL()
{
	FUNCID("bind fb");

	if (mSubBuffers[0] == GL_BACK || mSubBuffers[0] == GL_FRONT || mSubBuffers[0] == GL_LEFT ||
		mSubBuffers[0] == GL_RIGHT || mSubBuffers[0] == GL_FRONT_LEFT || mSubBuffers[0] == GL_FRONT_RIGHT ||
		mSubBuffers[0] == GL_BACK_LEFT || mSubBuffers[0] == GL_BACK_RIGHT) 
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		glDrawBuffer(mSubBuffers[0]);
	}
    //else if (mNumBuffers == 1)
    //    glDrawBuffer(mSubBuffers[0]);
    else
        glDrawBuffers(mNumBuffers, mSubBuffers);
}


