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

#include <xip/inventor/core/SoXipActiveViewportElement.h>


SO_ELEMENT_SOURCE(SoXipActiveViewportElement);

// Initializes the SoXipActiveViewportElement class.

void SoXipActiveViewportElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipActiveViewportElement, SoInt32Element);
}

// Destructor

SoXipActiveViewportElement::~SoXipActiveViewportElement()
{
}

// Initializes the first instance used in an action's state.

void SoXipActiveViewportElement::init(SoState *)
{
	data = getDefault();
}

// Sets the current temperature in the state.

void SoXipActiveViewportElement::set(SoState *state, SoNode *node, int32_t isActive)
{
	// Use the corresponding method on SoInt32Element to set the
	// value in the top instance in the state
	SoInt32Element::set(classStackIndex, state, node, isActive);
}

// Returns the current temperature from the state.

int32_t SoXipActiveViewportElement::get(SoState *state)
{
	// Use the corresponding method on SoInt32Element to get the
	// value from the top instance in the state
	return SoInt32Element::get(classStackIndex, state);
}
