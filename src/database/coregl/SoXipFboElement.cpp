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

#include <xip/inventor/coregl/SoXipFboElement.h>

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoViewportRegionElement.h>
//#include <Inventor/SoViewportRegion.h>
#include <Inventor/errors/SoDebugError.h>
#include <xip/inventor/coregl/SoXipGlowElement.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>

#undef DEBUG

#ifdef DEBUG
#define FUNCID(...) SoDebugError::postInfo(__FUNCTION__, __VA_ARGS__);
#else
#define FUNCID(...)
#endif


SO_ELEMENT_SOURCE(SoXipFboElement);

/**
 *  Class initiation.
 */
void SoXipFboElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipFboElement, SoReplacedElement);
	SO_ENABLE(SoGLRenderAction, SoXipGLOWElement);
    SO_ENABLE(SoGLRenderAction, SoXipMultiTextureElement);
}

/**
 *  Destructor.
 */
SoXipFboElement::~SoXipFboElement()
{
	FUNCID("");
}

/**
 *  Initiates first instance of element.
 */
void SoXipFboElement::init(SoState *state)
{
	FUNCID("");

	// Initialize to some default values
    mActiveFB.clear();
    mPassiveFB.clear();

    for (int i = 0; i < 16; i++)
        mPingPongUnits[i] = 0;

    mIsPingPong = false;

#if 0 // Store in Fbo by element
    SbVec2s vp = SoViewportRegionElement::get(state).getViewportSizePixels();
    mActiveFB.width = vp[0];
    mActiveFB.height = vp[1];
#endif

#if 0 // Store in Fbo by Action
    SoGLRenderAction * action = static_cast<SoGLRenderAction *>(state->getAction());
    SbVec2s acvp = action->getViewportRegion().getViewportSizePixels();
    mActiveFB.width = acvp[0];
    mActiveFB.height = acvp[1];
#endif

#if 1 // Store in member by Action
    //SoGLRenderAction * action2 = static_cast<SoGLRenderAction *>(state->getAction());
    //SbVec2s acvp2 = action2->getViewportRegion().getViewportSizePixels();
    SoGLRenderAction * action2 = dynamic_cast<SoGLRenderAction *>(state->getAction());
    SbVec2s acvp2;
    if (action2)
        acvp2 = action2->getViewportRegion().getViewportSizePixels();
    mPrevVp = acvp2;
#endif
}



/**
 *  Push functionality to support scene traversal.
 */
void SoXipFboElement::push(SoState *state)
{
	FUNCID("push");

	// Propogate values from previous
	SoXipFboElement *prev = (SoXipFboElement*)(this->getNextInStack());

	/*
		FIXUP: The default element assumes FBO 0 is bound, this might not be the case
		so one way of solving this is to check GL for the real FBO in use. This is
		probably only needed when the current framebuffer is 0.
	*/
	if (prev->mActiveFB.fboHandle == 0)
	{
		int currentFbo;
		glGetIntegerv(GL_FRAMEBUFFER_BINDING_EXT, &currentFbo);
        prev->mActiveFB.fboHandle = currentFbo;
	}

    mActiveFB = prev->mActiveFB;
    mPassiveFB = prev->mPassiveFB;

    for (int i = 0; i < 16; i++)
        mPingPongUnits[i] = prev->mPingPongUnits[i];

    mIsPingPong = prev->mIsPingPong;

#if 0 // Store in Member by Previous
    mPrevVp = prev->mPrevVp;
#endif

#if 1 // Store in member by Action
    SoGLRenderAction * action2 = static_cast<SoGLRenderAction *>(state->getAction());
    SbVec2s acvp2 = action2->getViewportRegion().getViewportSizePixels();
    mPrevVp = acvp2;
#endif
}



/**
 *  Pop functionality to support scene traversal.
 */
void SoXipFboElement::pop(SoState *state, const SoElement *prevTopElement)
{
	FUNCID("pop");

    const SoXipFboElement * prevTop = static_cast<const SoXipFboElement *>(prevTopElement);
	// Rebind if different 
    if (mActiveFB.fboHandle != prevTop->mActiveFB.fboHandle)
		bindActiveFB();

    SoGLRenderAction * action = static_cast<SoGLRenderAction *>(state->getAction());

#if 1 // Reset by member
    SbViewportRegion vp(prevTop->mPrevVp);
    action->setViewportRegion(vp);
#endif

#if 0 // Reset by element
    SbVec2s vp = SoViewportRegionElement::get(state).getViewportSizePixels();
    action->setViewportRegion(vp);
#endif

#if 0 // Reset by FBO
    SbViewportRegion vp(mActiveFB.width, mActiveFB.height);
    action->setViewportRegion(vp);
    //SoViewportRegionElement::set(action->getState(), vp);
#endif
}



/**
 *  Binds current Fbo.
 *  Static version.
 *  @see setElt()
 */
void SoXipFboElement::bind(SoState *state, SoNode *node)
{
	FUNCID("bind");

    SoXipFboElement *elt = (SoXipFboElement*)getElement(state, classStackIndex, node);
    if (elt) {
	    elt->bindElt(state);
    }
}

/**
 *  Binds current Fbo.
 *  @see set()
 */
void SoXipFboElement::bindElt(SoState * state)
{
    bindActiveFB();

    SoGLRenderAction * action = static_cast<SoGLRenderAction *>(state->getAction());

#if 0 // Save old vewport
    mPrevVp = action->getViewportRegion().getViewportSizePixels();
#endif
	
#if 1 // Set viewport to new fbo
    SbViewportRegion vp(mActiveFB.width, mActiveFB.height);
    action->setViewportRegion(vp);
    SoViewportRegionElement::set(action->getState(), vp);
#endif
}


/**
 *  Set function for setting current setup.
 *  Static version.
 *  @see setElt()
 */
void SoXipFboElement::set(SoState *state, SoNode *node, FboSetup &primaryFB)
{
	FUNCID("set");

    SoXipFboElement *elt = (SoXipFboElement*)getElement(state, classStackIndex, node);
    if (elt) {
	    elt->setElt(state, primaryFB);
    }
}

/**
 *  Set function for setting current setup.
 *  @see set()
 */
void SoXipFboElement::setElt(SoState * state, FboSetup &primaryFB)
{
    mActiveFB = primaryFB;
}


/**
 *  Set function for second buffer of pingpong setup.
 *  Static version.
 *  @see setElt()
 */
void SoXipFboElement::setPingPong(SoState *state, SoNode *node, FboSetup &secondaryFB, unsigned int * units)
{
	FUNCID("set");

    SoXipFboElement *elt = (SoXipFboElement*)getElement(state, classStackIndex, node);
    if (elt) {
	    elt->setPingPongElt(state, secondaryFB, units);
    }
}

/**
 *  Set function for second buffer of pingpong setup.
 *  @see set()
 */
void SoXipFboElement::setPingPongElt(SoState * state, FboSetup &secondaryFB, unsigned int * units)
{
    mPassiveFB = secondaryFB;

    for (unsigned int i = 0; i < mPassiveFB.numColorAttachments; i++)
        mPingPongUnits[i] = units[i];
    for (unsigned int i = mPassiveFB.numColorAttachments; i < 16; i++)
        mPingPongUnits[i] = 0;

    mIsPingPong = true;

    bindPassiveTextures(state);
}



/**
 *  Flip buffers in pingpong setup
 *  Static version.
 *  @see setElt()
 */
void SoXipFboElement::flip(SoState *state, SoNode *node)
{
	FUNCID("set");

    SoXipFboElement *elt = (SoXipFboElement*)getElement(state, classStackIndex, node);
    if (elt) {
	    elt->flipElt(state);
    }
}

/**
 *  Flip buffers in pingpong setup.
 *  @see set()
 */
void SoXipFboElement::flipElt(SoState * state)
{
    if (mIsPingPong)
    {
        FboSetup tmp = mActiveFB;
        mActiveFB = mPassiveFB;
        mPassiveFB = tmp;

        bindPassiveTextures(state);
        bindActiveFB();
    }
}



/**
 *  Get function for extraction of active setup.
 *  Static version.
 *  @see getElt()
 */
FboSetup* SoXipFboElement::getActive(SoState *state, SoNode *node)
{
	FUNCID("get");
    SoXipFboElement *elt = (SoXipFboElement*)getElement(state, classStackIndex, node);
    return (elt) ? elt->getActiveElt() : 0;
}

/**
 *  Get function for extraction of active setup.
 *  @see get()
 */
FboSetup* SoXipFboElement::getActiveElt()
{
    return &mActiveFB;
}


/**
 *  Get function for extraction of passive setup (back buffer in pingpong).
 *  Static version.
 *  @see getElt()
 */
FboSetup* SoXipFboElement::getPassive(SoState *state, SoNode *node)
{
	FUNCID("get");
    SoXipFboElement *elt = (SoXipFboElement*)getElement(state, classStackIndex, node);
    return (elt) ? elt->getPassiveElt() : 0;
}

/**
 *  Get function for extraction of passive setup (back buffer in pingpong).
 *  @see get()
 */
FboSetup* SoXipFboElement::getPassiveElt()
{
    return &mPassiveFB;
}


/**
 *  Get function for extraction of passive setup (back buffer in pingpong).
 *  Static version.
 *  @see getElt()
 */
bool SoXipFboElement::isPingPong(SoState *state, SoNode *node)
{
	FUNCID("get");
    SoXipFboElement *elt = (SoXipFboElement*)getElement(state, classStackIndex, node);
    return (elt) ? elt->isPingPongElt() : 0;
}

/**
 *  Get function for extraction of passive setup (back buffer in pingpong).
 *  @see get()
 */
bool SoXipFboElement::isPingPongElt()
{
    return mIsPingPong;
}


#if 0
SbBool SoXipFboElement::matches(const SoElement *elt) const {
	FUNCID("");
#if 0
    return (mActiveFB == elt->mActiveFB) ? true : false;
#else
    return false;
#endif
}

SoElement* SoXipFboElement::copyMatchInfo() const {
	FUNCID("");
    SoXipFboElement *result = (SoXipFboElement*)getTypeId().createInstance();
#if 0
    mActiveFB = prev->mActiveFB;
#else
    return result;
#endif
}
#endif



/**
 *  Internal, binds the active FBO.
 */
void SoXipFboElement::bindActiveFB()
{
	FUNCID("");

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mActiveFB.fboHandle);
}


/**
 *  Internal, binds the default FBO.
 */
void SoXipFboElement::bindDefaultFB()
{
	FUNCID("");

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}


/**
 *  Internal, binds the attachments of the passive FBO as textures.
 */
void SoXipFboElement::bindPassiveTextures(SoState * state)
{
	FUNCID("");
    if (mIsPingPong && mPassiveFB.colorStorage == GL_TEXTURE_2D)
    {
        unsigned int unit = 0;
        int handles[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

        // Store handles
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mPassiveFB.fboHandle);
        for (unsigned int i = 0; i < mPassiveFB.numColorAttachments; i++)
            glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT,
                                                     GL_COLOR_ATTACHMENT0_EXT + i,
                                                     GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT,
                                                     handles + i);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mActiveFB.fboHandle);

        for (unsigned int i = 0; i < mPassiveFB.numColorAttachments; i++)
        {
            unit = mPingPongUnits[i];
            SoXipMultiTextureElement::setUnit(state, unit);
            SoXipMultiTextureElement::bindTexture(state, GL_TEXTURE_2D, handles[i]);
        }
    }
	else if (mIsPingPong && mPassiveFB.colorStorage == GL_TEXTURE_3D)
    {
        unsigned int unit = 0;
        int handles[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

        // Store handles
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mPassiveFB.fboHandle);
        for (unsigned int i = 0; i < mPassiveFB.numColorAttachments; i++)
            glGetFramebufferAttachmentParameterivEXT(GL_FRAMEBUFFER_EXT,
                                                     GL_COLOR_ATTACHMENT0_EXT + i,
                                                     GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT,
                                                     handles + i);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, mActiveFB.fboHandle);

        for (unsigned int i = 0; i < mPassiveFB.numColorAttachments; i++)
        {
            unit = mPingPongUnits[i];
            SoXipMultiTextureElement::setUnit(state, unit);
            SoXipMultiTextureElement::bindTexture(state, GL_TEXTURE_3D, handles[i]);
        }
    }
}

/**
* Get the ping pong texture units
*/
unsigned int* SoXipFboElement::getUnits(SoState * state, SoNode *node)
{
	FUNCID("set");

    SoXipFboElement *elt = (SoXipFboElement*)getElement(state, classStackIndex, node);

	if (elt) {
		return elt->getUnitsElt();
    }

	return 0;
}

/**
* Get the ping pong texture units
*/
unsigned int* SoXipFboElement::getUnitsElt()
{
	return mPingPongUnits;
}

/**
* render to slice
*/
void SoXipFboElement::renderToSlice(SoState *state, SoNode *node, int layer)
{
	FUNCID("");

    SoXipFboElement *elt = (SoXipFboElement*)getElement(state, classStackIndex, node);

	if (elt) {
		elt->renderToSliceElt(layer);
    }
}


/**
* render to slice
*/
void SoXipFboElement::renderToSliceElt(int layer)
{
	if (mActiveFB.colorStorage == GL_TEXTURE_3D)
    {
        for (unsigned int i = 0; i < mActiveFB.numColorAttachments; i++)
		{
            glFramebufferTexture3DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT+i,
				GL_TEXTURE_3D, mActiveFB.colorHandles[i], 0, layer);
			//SoDebugError::postInfo("SoXipFboElement", "mActiveFB.colorHandle %i bound as layer %i", mActiveFB.colorHandles[i], layer);
		}
	}
	else
	{
		SoDebugError::postInfo("SoXipFboElement", "mActiveFB.colorStorage != GL_TEXTURE_3D");
	}

	if (mActiveFB.depthStorage == GL_TEXTURE_3D)
		glFramebufferTexture3DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,
			GL_TEXTURE_3D, mActiveFB.depthHandle, 0, layer);
}

/**
* reattach as 3d
*/
void SoXipFboElement::reattachAs3D(SoState *state, SoNode *node)
{
	FUNCID("");

    SoXipFboElement *elt = (SoXipFboElement*)getElement(state, classStackIndex, node);

	if (elt) {
		elt->reattachAs3DElt();
    }
}


/**
* reattach as 3d
*/
void SoXipFboElement::reattachAs3DElt()
{
	if (mActiveFB.colorStorage == GL_TEXTURE_3D)
    {
        for (unsigned int i = 0; i < mActiveFB.numColorAttachments; i++)
		{
            glFramebufferTextureEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT+i, mActiveFB.colorHandles[i], 0);
			//SoDebugError::postInfo("SoXipFboElement", "mActiveFB.colorHandle %i bound as 3D", mActiveFB.colorHandles[i]);
		}
	}
	else
	{
		SoDebugError::postInfo("SoXipFboElement", "mActiveFB.colorStorage != GL_TEXTURE_3D");
	}

	if (mActiveFB.depthStorage == GL_TEXTURE_3D)
		glFramebufferTexture3DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_3D, mActiveFB.depthHandle, 0, 0);
}
