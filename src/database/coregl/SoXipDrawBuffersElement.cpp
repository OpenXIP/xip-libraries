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

    if (mSubBuffers[0] == GL_BACK)
        glDrawBuffer(mSubBuffers[0]);
    else
        glDrawBuffers(mNumBuffers, mSubBuffers);
}
