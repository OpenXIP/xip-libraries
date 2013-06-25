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
#include <Inventor/actions/SoGLRenderAction.h>
#include <Inventor/errors/SoDebugError.h>
#include <xip/inventor/core/SoXipMultiTextureElement.h>

#ifndef WIN32
#ifndef linux
#ifndef DARWIN
static PFNGLACTIVETEXTUREARBPROC glActiveTextureARB = 0;
#endif // DARWIN
#endif // linux
#endif // WIN32
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
}

SoElement* SoXipMultiTextureElement::copyMatchInfo() const
{
	SoXipMultiTextureElement *element = (SoXipMultiTextureElement*)(getTypeId().createInstance());
	return (SoElement *)element;
}

void SoXipMultiTextureElement::init(SoState *state)
{
    if (dynamic_cast<SoGLRenderAction*>(state->getAction()))
    {
//#ifdef WIN32
//	    if (!glActiveTextureARB)
//            glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC)xipGlGetProcAddress("glActiveTextureARB");
//#endif // DARWIN

	    if (!mMaxUnits)
        {
	        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &mMaxUnits);

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

	mCurrentUnit = prev->mCurrentUnit;
	mUnitsChanged = 0;
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

