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
#include <xip/system/standard.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>

#ifdef WIN32
#ifdef _CRT_ALLOCATION_DEFINED 
	#include <xip/system/GL/gl.h>
	#include <xip/system/GL/glext.h>
#else //only for VC6 compilation
	#include <GL/gl.h>
	#include <GL/glext.h>
#endif
#endif // WIN32

#ifndef WIN32
#include <xip/system/GL/gl.h>
#include <xip/system/GL/glext.h>
#endif // WIN32

#ifndef DARWIN
static PFNGLACTIVETEXTUREARBPROC glActiveTextureARB = 0;
#endif // DARWIN
int SoXipMultiTextureElement::mMaxUnits = 0;

/*
#undef DEBUG

#ifdef DEBUG
#define FUNCID(...) SoDebugError::postInfo(__FUNCTION__, __VA_ARGS__);
#else
#define FUNCID(...)
#endif
*/

SO_ELEMENT_SOURCE(SoXipMultiTextureElement);

SoXipMultiTextureElement::~SoXipMultiTextureElement()
{
}

void SoXipMultiTextureElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipMultiTextureElement, SoElement);
}

SbBool SoXipMultiTextureElement::matches(const SoElement *element) const
{
    return false;
	//	return FALSE;
	//for(int i = NB_TEXTURE_MAX - 1; i >= 0; i--)
	//{
	//	if(((const SoXipMultiTextureElement *) element)->enabled[i] != this->enabled[i])
	//		return FALSE;
	//}
	//if (((const SoXipMultiTextureElement *) element)->last!=this->last)
	//	return FALSE;
	//return TRUE;
}

SoElement* SoXipMultiTextureElement::copyMatchInfo() const
{
	SoXipMultiTextureElement *element = (SoXipMultiTextureElement*)(getTypeId().createInstance());
	//for(int i = NB_TEXTURE_MAX - 1; i >= 0; i--)
	//	element->enabled[i]=this->enabled[i];
	//element->last = this->last;
	return (SoElement *)element;
}

void SoXipMultiTextureElement::init(SoState *state)
{
    if (dynamic_cast<SoGLRenderAction*>(state->getAction()))
    {
#ifndef DARWIN
	    if (!glActiveTextureARB)
            glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)xipGlGetProcAddress("glActiveTextureARB");
#endif // DARWIN

	    if (!mMaxUnits)
        {
	        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &mMaxUnits);
	//SoDebugError::postInfo(__FUNCTION__, "Max texture units: %d", numUnits);
	        if (mMaxUnits <= 0)
    		    mMaxUnits = 1;
    	    else if (mMaxUnits > 32)
		        mMaxUnits = 32;
        }
    }

	for (int i = 0; i < mMaxUnits; ++i)
		mTextures[i] = textureInfo(0, 0);
	
	mCurrentUnit = 0;
}

void SoXipMultiTextureElement::push(SoState *state)
{
	SoXipMultiTextureElement *prev = (SoXipMultiTextureElement*)(this->getNextInStack());
    if (!prev)
        return;

	for (int i = 0; i < mMaxUnits; ++i)
		mTextures[i] = prev->mTextures[i];
		//FUNCID("Initting with textures = %p", textures);

	mCurrentUnit = prev->mCurrentUnit;
	mUnitsChanged = 0;

	//prev->capture(state);
}

void SoXipMultiTextureElement::pop(SoState *state, const SoElement *prevTopElement)
{
	SoXipMultiTextureElement *prev = (SoXipMultiTextureElement*)prevTopElement;
    if (!prev)
        return;
	// only check for changed ones...
	for (int i = 0; i < mMaxUnits; ++i)
    {
		if (prev->mUnitsChanged & (1 << i))
        {
			setUnitGL(i);
			prev->unbindTextureGL(i);
			if (mTextures[i].target != 0)
				bindTextureGL(i);
		}
	}

	setUnitGL(mCurrentUnit);
}

void SoXipMultiTextureElement::setUnit(SoState *state, GLuint unit)
{
	SoXipMultiTextureElement *element = (SoXipMultiTextureElement*)getElement(state, classStackIndex);
	if (element)
		element->setUnitElt(unit);
}

void SoXipMultiTextureElement::setUnitElt(GLuint unit)
{
	mCurrentUnit = unit;
	setUnitGL(mCurrentUnit);
}

void SoXipMultiTextureElement::setUnitGL(GLuint unit)
{
    if (glActiveTextureARB)
        glActiveTextureARB((unsigned int) GL_TEXTURE0 + unit);
}

void SoXipMultiTextureElement::bindTexture(SoState *state, GLenum target, GLuint id)
{
	SoXipMultiTextureElement *element = (SoXipMultiTextureElement*)getElement(state, classStackIndex);
	if (element)
		element->bindTextureElt(target, id);
}

void SoXipMultiTextureElement::bindTextureCurrUnit(SoState *state)
{
    SoXipMultiTextureElement *element = (SoXipMultiTextureElement*)getElement(state, classStackIndex);
	if (element)
        element->bindTextureElt(element->mTextures[element->mCurrentUnit].target, 
                                element->mTextures[element->mCurrentUnit].id);
}

void SoXipMultiTextureElement::bindTextureElt(GLenum target, GLuint id)
{
    if (!target)
    {
        SoDebugError::post(__FUNCTION__, "target == 0, cannot bind texture!");
        return;
    }
	
	mTextures[mCurrentUnit].target = target;
	mTextures[mCurrentUnit].id = id;

	bindTextureGL(mCurrentUnit);

	mUnitsChanged |= 1 << mCurrentUnit;
}

void SoXipMultiTextureElement::bindTextureGL(GLuint unit)
{
	glBindTexture(mTextures[unit].target, mTextures[unit].id);
}

void SoXipMultiTextureElement::unbindTextureGL(GLuint unit)
{
	glBindTexture(mTextures[unit].target, 0);
}

GLuint SoXipMultiTextureElement::getFreeUnit(SoState *state)
{
	const SoXipMultiTextureElement *element = (const SoXipMultiTextureElement*)getConstElement(state, classStackIndex);

	if (element)
		return element->getFreeUnitElt();
	return 0;
}

GLuint SoXipMultiTextureElement::getFreeUnitElt() const
{
	for (int i = 0; i < mMaxUnits; i++)
    {
		if (mTextures[i].target == 0)
			return i;
	}

	SoDebugError::post(__FUNCTION__, "Cannot find unused texture unit (max %d units used), defaulting to unit 0.", mMaxUnits);
	return 0;
}

GLuint SoXipMultiTextureElement::getFreeUnits(SoState *state, unsigned int num, GLuint *units)
{
	const SoXipMultiTextureElement *element = (const SoXipMultiTextureElement*)getConstElement(state, classStackIndex);

	if (!element)
        return 0;

	return element->getFreeUnitsElt(num, units);
}

GLuint SoXipMultiTextureElement::getFreeUnitsElt(unsigned int num, GLuint *units) const
{
	GLuint res = 0;
    for (int i = 0; i < mMaxUnits && res < num; i++)
    {
		if (mTextures[i].target == 0)
        {
			units[res] = i;
            res++;
		}
	}
    if (res != num)
        SoDebugError::post(__FUNCTION__, "Requested %d free units, but could only find %d.", num, res);
	return res;
}

GLuint SoXipMultiTextureElement::getCurrentUnit(SoState *state)
{
	const SoXipMultiTextureElement *element = (const SoXipMultiTextureElement*)getConstElement(state, classStackIndex);

	if (element)
		return element->getCurrentUnitElt();
	return 0;
}

GLuint SoXipMultiTextureElement::getCurrentUnitElt() const
{
	return mCurrentUnit;
}

