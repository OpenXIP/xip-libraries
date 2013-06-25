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
#include <xip/inventor/coregl/SoXipBufferMaskElement.h>
#include <Inventor/errors/SoDebugError.h>

#undef DEBUG

#ifdef DEBUG
#define FUNCID(...) SoDebugError::postInfo(__FUNCTION__, __VA_ARGS__);
#else
#define FUNCID(...)
#endif

SO_ELEMENT_SOURCE(SoXipBufferMaskElement);

void SoXipBufferMaskElement::initClass() {
	SO_ELEMENT_INIT_CLASS(SoXipBufferMaskElement, SoElement);
}

SoXipBufferMaskElement::~SoXipBufferMaskElement() {
	FUNCID("");
}

void SoXipBufferMaskElement::init(SoState *state) {
	FUNCID("");

	glGetIntegerv(GL_COLOR_WRITEMASK, maskColor);
	glGetIntegerv(GL_DEPTH_WRITEMASK, &maskDepth);
}

void SoXipBufferMaskElement::push(SoState *state) {
	FUNCID("");
	SoXipBufferMaskElement *prev = (SoXipBufferMaskElement*)(this->getNextInStack());

	maskColor[0] = prev->maskColor[0];
	maskColor[1] = prev->maskColor[1];
	maskColor[2] = prev->maskColor[2];
	maskColor[3] = prev->maskColor[3];

	maskDepth = prev->maskDepth;
}

void SoXipBufferMaskElement::pop(SoState *state, const SoElement *prevTopElement) {
	FUNCID("");

	setColorMaskGL();
	setDepthMaskGL();
}

SbBool SoXipBufferMaskElement::matches(const SoElement *elt) const {
	FUNCID("");
    return false;
}

SoElement* SoXipBufferMaskElement::copyMatchInfo() const {
	FUNCID("");

	SoXipBufferMaskElement *result = (SoXipBufferMaskElement*)getTypeId().createInstance();

    return result;
}

void SoXipBufferMaskElement::setColorMask(SoState *state, GLboolean r, GLboolean g, GLboolean b, GLboolean a) {
	FUNCID("");

	SoXipBufferMaskElement *elt = (SoXipBufferMaskElement*)getElement(state, classStackIndex);

	if (elt) {
		elt->setColorMaskElt(r, g, b, a);
	}
}

void SoXipBufferMaskElement::setColorMaskElt(GLboolean r, GLboolean g, GLboolean b, GLboolean a) {
	maskColor[0] = r;
	maskColor[1] = g;
	maskColor[2] = b;
	maskColor[3] = a;

	setColorMaskGL();
}

void SoXipBufferMaskElement::setColorMaskGL() {
	glColorMask(maskColor[0], maskColor[1], maskColor[2], maskColor[3]);
}

void SoXipBufferMaskElement::setDepthMask(SoState *state, GLboolean d) {
	FUNCID("");

	SoXipBufferMaskElement *elt = (SoXipBufferMaskElement*)getElement(state, classStackIndex);

	if (elt) {
		elt->setDepthMaskElt(d);
	}
}

void SoXipBufferMaskElement::setDepthMaskElt(GLboolean d) {
	maskDepth = d;

	setDepthMaskGL();
}

void SoXipBufferMaskElement::setDepthMaskGL() {
	glDepthMask(maskDepth);
}

//const void* SoXipBufferMaskElement::get(SoState *state) {
//	FUNCID("");
//
//	const SoXipBufferMaskElement *elt = (SoXipBufferMaskElement*)getConstElement(state, classStackIndex);
//
//	return elt;
//}


