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
#include <xip/inventor/core/SoXipRenderModeElement.h>


SO_ELEMENT_SOURCE(SoXipRenderModeElement);

// Initializes the SoRadRenderModeElement class.

void SoXipRenderModeElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipRenderModeElement, SoInt32Element);
}

// Destructor

SoXipRenderModeElement::~SoXipRenderModeElement()
{
}

// Initializes the first instance used in an action's state.

void SoXipRenderModeElement::init(SoState *)
{
	data = getDefault();
}

// Sets the current temperature in the state.

void SoXipRenderModeElement::set(SoState *state, SoNode *node, RenderModes mode)
{
	// Use the corresponding method on SoInt32Element to set the
	// value in the top instance in the state
	SoInt32Element::set(classStackIndex, state, node, (int32_t) mode);
}

// Returns the current temperature from the state.

SoXipRenderModeElement::RenderModes SoXipRenderModeElement::get(SoState *state)
{
	// Use the corresponding method on SoInt32Element to get the
	// value from the top instance in the state
	return (RenderModes) SoInt32Element::get(classStackIndex, state);
}
