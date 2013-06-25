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

#include <xip/inventor/coregl/SoXipBlendFuncElement.h>
#include <Inventor/errors/SoDebugError.h>

#undef DEBUG

#ifdef DEBUG
#define FUNCID(...) SoDebugError::postInfo(__FUNCTION__, __VA_ARGS__);
#else
#define FUNCID(...)
#endif

SO_ELEMENT_SOURCE(SoXipBlendFuncElement);

void SoXipBlendFuncElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipBlendFuncElement, SoElement);
}

SoXipBlendFuncElement::~SoXipBlendFuncElement()
{
	FUNCID("");
}

void SoXipBlendFuncElement::init(SoState *state)
{
	FUNCID("");

	blendEnabled = glIsEnabled(GL_BLEND);
	glGetIntegerv(GL_BLEND_SRC, &srcBlendFunction);
	glGetIntegerv(GL_BLEND_DST, &dstBlendFunction);
}

void SoXipBlendFuncElement::push(SoState *state)
{
	FUNCID("");

	SoXipBlendFuncElement *prev = (SoXipBlendFuncElement*)(this->getNextInStack());

    if (prev)
    {
	    blendEnabled = prev->blendEnabled;
	    srcBlendFunction = prev->srcBlendFunction;
	    dstBlendFunction = prev->dstBlendFunction;
    }
}

void SoXipBlendFuncElement::pop(SoState *state, const SoElement *prevTopElement)
{
	FUNCID("");

	setEnabledGL();
	setBlendFuncGL();
}

SbBool SoXipBlendFuncElement::matches(const SoElement *elt) const
{
	FUNCID("");
    return false;
}

SoElement* SoXipBlendFuncElement::copyMatchInfo() const
{
	FUNCID("");

	SoXipBlendFuncElement *result = (SoXipBlendFuncElement*)getTypeId().createInstance();

    return result;
}

void SoXipBlendFuncElement::setEnabled(SoState *state, GLboolean enabled)
{
	FUNCID("");

	SoXipBlendFuncElement *elt = (SoXipBlendFuncElement*)getElement(state, classStackIndex);

	if (elt) {
		elt->setEnabledElt(enabled);
	}
}

void SoXipBlendFuncElement::setEnabledElt(GLboolean enabled)
{
	blendEnabled = enabled;

	setEnabledGL();
}

void SoXipBlendFuncElement::setEnabledGL()
{
	if (blendEnabled)
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);
}

void SoXipBlendFuncElement::setBlendFunc(SoState *state, GLenum srcFunc, GLenum dstFunc) {
	FUNCID("");

	SoXipBlendFuncElement *elt = (SoXipBlendFuncElement*)getElement(state, classStackIndex);

	if (elt) {
		elt->setBlendFuncElt(srcFunc, dstFunc);
	}
}

void SoXipBlendFuncElement::setBlendFuncElt(GLenum srcFunc, GLenum dstFunc)
{
	srcBlendFunction = srcFunc;
	dstBlendFunction = dstFunc;

	setBlendFuncGL();
}

void SoXipBlendFuncElement::setBlendFuncGL()
{
	glBlendFunc(srcBlendFunction, dstBlendFunction);
}

//const void* SoXipBlendFuncElement::get(SoState *state) {
//	FUNCID("");
//
//	const SoXipBlendFuncElement *elt = (SoXipBlendFuncElement*)getConstElement(state, classStackIndex);
//
//	return elt;
//}
