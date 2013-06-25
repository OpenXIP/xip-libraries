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

#include "SoXipClientElement.h"

SO_ELEMENT_SOURCE(SoXipClientElement);

// Initializes the SoXipClientElement class.

void SoXipClientElement::initClass()
{
  SO_ELEMENT_INIT_CLASS(SoXipClientElement, SoInt32Element);
}

// Destructor

SoXipClientElement::~SoXipClientElement()
{
}

// Initializes the first instance used in an action's state.

void SoXipClientElement::init(SoState *)
{
    data = getDefault();
}

// Sets the current changed vlaue in the state.

void SoXipClientElement::set(SoState *state, SoNode *node, bool hasChanged)
{
    int temp;
    SoInt32Element::set(classStackIndex, state, node, (int32_t)hasChanged);
    if ( !hasChanged )
    {
        temp = 0;
    }
}


bool SoXipClientElement::get(SoState *state)
{
    return SoInt32Element::get(classStackIndex, state) != 0;
}

bool SoXipClientElement::getDefault()
{
    return 0; 
}


