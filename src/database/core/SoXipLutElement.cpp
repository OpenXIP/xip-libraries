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
#include <xip/inventor/core/SoXipLutElement.h>


SO_ELEMENT_SOURCE(SoXipLutElement);

// Initializes the SoXipLutElement class.

void SoXipLutElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipLutElement, SoReplacedElement);
}

// Destructor

SoXipLutElement::~SoXipLutElement()
{
}

// Initializes the first instance used in an action's state.

void SoXipLutElement::init(SoState *)
{
	data = getDefault();
}

// Sets the current lut in the state.

void SoXipLutElement::set(SoState *state, SoNode *node, SoXipData *volume)
{
	SoXipLutElement *elt;

	// Get an instance we can change (pushing if necessary)
	elt = (SoXipLutElement *) getElement(state, classStackIndex, node);
	if (elt) 
	{
		elt->data = volume;
	}
}

// Returns the current temperature from the state.

SoXipData *SoXipLutElement::get(SoState *state)
{
	SoXipLutElement * elt = (SoXipLutElement*) getConstElement(state, classStackIndex);
	if (elt)
		return elt->data;
	else
		return 0;
}

SoXipData *SoXipLutElement::getDefault()
{
	return 0; 
}
