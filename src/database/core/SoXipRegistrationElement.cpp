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
#include <xip/inventor/core/SoXipRegistrationElement.h>

SO_ELEMENT_SOURCE(SoXipRegistrationElement);

void
SoXipRegistrationElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipRegistrationElement, SoReplacedElement);
}

SoXipRegistrationElement::~SoXipRegistrationElement()
{

}

void
SoXipRegistrationElement::init(SoState *state)
{
	SoReplacedElement::init(state);

	mMatrix.makeIdentity();
}

void
SoXipRegistrationElement::set(SoState *state, SoNode *node, const SbMatrix &matrix)
{
	SoXipRegistrationElement *elt;
	elt = (SoXipRegistrationElement*)getElement(state, classStackIndex, node);

	if ( NULL!=elt )
	{
		elt->setElt(matrix);
	}
}

const SbMatrix&
SoXipRegistrationElement::get(SoState *state)
{
	const SoXipRegistrationElement *elt;
	elt = (const SoXipRegistrationElement*)getConstElement(state, classStackIndex);

	return elt->mMatrix;
}

void
SoXipRegistrationElement::print(FILE *fp) const
{
	SoReplacedElement::print(fp);
}

void
SoXipRegistrationElement::setElt(const SbMatrix &matrix)
{
	mMatrix = matrix;
}
