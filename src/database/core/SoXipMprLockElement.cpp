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

#include <xip/inventor/core/SoXipMprLockElement.h>

SO_ELEMENT_SOURCE(SoXipMprLockElement);

////////////////////////////////////////////////////////////////////////


void SoXipMprLockElement::initClass()
{
	SO_ELEMENT_INIT_CLASS(SoXipMprLockElement, SoInt32Element);	
}


void SoXipMprLockElement::init(SoState *)
{
	data = getDefault();
}


void SoXipMprLockElement::set(SoState *state, SoNode *node, const int32_t lockMask)
{
	SoInt32Element::set(classStackIndex, state, node, lockMask);
}


int32_t SoXipMprLockElement::get(SoState *state)
{
	return SoInt32Element::get(classStackIndex, state);
}
