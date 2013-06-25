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
#include <xip/inventor/core/SoXipPickRadiusElement.h>

SO_ELEMENT_SOURCE(SoXipPickRadiusElement);

////////////////////////////////////////////////////////////////////////

SoXipPickRadiusElement::~SoXipPickRadiusElement()
{
}

void
SoXipPickRadiusElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipPickRadiusElement, SoFloatElement);	
}

void
SoXipPickRadiusElement::init(SoState *)
{
	data = 0;
}

void
SoXipPickRadiusElement::set(SoState *state, float index)
{
	SoFloatElement::set(classStackIndex, state, index);
}

float SoXipPickRadiusElement::get(SoState *state)
{
	return SoFloatElement::get(classStackIndex, state);
}
