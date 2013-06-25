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
/**
 *	Element class for shaders
 */
#include <xip/system/standard.h>
#include <xip/inventor/coregl/SoXipShaderProgramElement.h>

SO_ELEMENT_SOURCE(SoXipShaderProgramElement);

/**
 *	Initializes the element class
 */
void SoXipShaderProgramElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipShaderProgramElement, SoInt32Element);
}

/**
 *	Destructor
 */
SoXipShaderProgramElement::~SoXipShaderProgramElement()
{
}

/**
 *	Initializes the first instance used in an action's state.
 */
void SoXipShaderProgramElement::init(SoState * state )
{
	parent::init(state);
	this->data = getDefault();
}


int SoXipShaderProgramElement::get(SoState *state)
{
	/** Use the corresponding method on SoInt32Element to get the
		value from the top instance in the state */
	return SoInt32Element::get(classStackIndex, state);
}


void SoXipShaderProgramElement::set(SoState * const state, SoNode * const node, const int tmp )
{
	SoInt32Element::set(classStackIndex, state, node, tmp);
}


void SoXipShaderProgramElement::set(SoState * const state, const int tmp)
{
	set(state, NULL, tmp);
}


