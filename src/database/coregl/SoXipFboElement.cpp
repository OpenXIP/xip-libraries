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


#include <xip/inventor/coregl/SoXipFboElement.h>

#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/elements/SoViewportRegionElement.h>
//#include <Inventor/SoViewportRegion.h>
#include <Inventor/errors/SoDebugError.h>
#include <xip/inventor/coregl/SoXipGLOWElement.h>
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
