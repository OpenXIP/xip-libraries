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
#include <xip/inventor/coregl/SoXipDepthTestElement.h>
#include <Inventor/errors/SoDebugError.h>

#undef DEBUG

#ifdef DEBUG
#define FUNCID(...) SoDebugError::postInfo(__FUNCTION__, __VA_ARGS__);
#else
#define FUNCID(...)
#endif

SO_ELEMENT_SOURCE(SoXipDepthTestElement);

void SoXipDepthTestElement::initClass() {
	SO_ELEMENT_INIT_CLASS(SoXipDepthTestElement, SoElement);
}

SoXipDepthTestElement::~SoXipDepthTestElement() {
	FUNCID("");
}

void SoXipDepthTestElement::init(SoState *state) {
	FUNCID("");

	testEnabled = glIsEnabled(GL_DEPTH_TEST);
	glGetIntegerv(GL_DEPTH_FUNC, &depthFunction);
}

void SoXipDepthTestElement::push(SoState *state) {
	FUNCID("");

	SoXipDepthTestElement *prev = (SoXipDepthTestElement*)(this->getNextInStack());

	testEnabled = prev->testEnabled;
	depthFunction = prev->depthFunction;
}

void SoXipDepthTestElement::pop(SoState *state, const SoElement *prevTopElement) {
	FUNCID("");

	setEnabledGL();
	setDepthFuncGL();
}

SbBool SoXipDepthTestElement::matches(const SoElement *elt) const {
	FUNCID("");
    return false;
}

SoElement* SoXipDepthTestElement::copyMatchInfo() const {
	FUNCID("");

	SoXipDepthTestElement *result = (SoXipDepthTestElement*)getTypeId().createInstance();

    return result;
}

void SoXipDepthTestElement::setEnabled(SoState *state, GLboolean enabled) {
	FUNCID("");

	SoXipDepthTestElement *elt = (SoXipDepthTestElement*)getElement(state, classStackIndex);

	if (elt) {
		elt->setEnabledElt(enabled);
	}
}

void SoXipDepthTestElement::setEnabledElt(GLboolean enabled) {
	testEnabled = enabled;

	setEnabledGL();
}

void SoXipDepthTestElement::setEnabledGL() {
	if (testEnabled) {
		glEnable(GL_DEPTH_TEST);
	}
	else {
		glDisable(GL_DEPTH_TEST);
	}
}

void SoXipDepthTestElement::setDepthFunc(SoState *state, GLenum function) {
	FUNCID("");

	SoXipDepthTestElement *elt = (SoXipDepthTestElement*)getElement(state, classStackIndex);

	if (elt) {
		elt->setDepthFuncElt(function);
	}
}

void SoXipDepthTestElement::setDepthFuncElt(GLenum function) {
	depthFunction = function;

	setDepthFuncGL();
}

void SoXipDepthTestElement::setDepthFuncGL() {
	glDepthFunc(depthFunction);
}

//const void* SoXipDepthTestElement::get(SoState *state) {
//	FUNCID("");
//
//	const SoXipDepthTestElement *elt = (SoXipDepthTestElement*)getConstElement(state, classStackIndex);
//
//	return elt;
//}


