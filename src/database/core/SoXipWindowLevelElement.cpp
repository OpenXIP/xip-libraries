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
#include <xip/inventor/core/SoXipWindowLevelElement.h>

SO_ELEMENT_SOURCE( SoXipWindowLevelElement );


SoXipWindowLevelElement::~SoXipWindowLevelElement()
{
}

void SoXipWindowLevelElement::initClass()
{
	SO_ELEMENT_INIT_CLASS( SoXipWindowLevelElement, SoReplacedElement );
}

void SoXipWindowLevelElement::init( SoState* )
{
	mWindow = -1.f;
	mLevel = -1.f;
}

void SoXipWindowLevelElement::setWindow( SoState* state, SoNode *node,float window )
{
    SoXipWindowLevelElement *elt  = NULL;
	 elt =(SoXipWindowLevelElement *) getElement(state, classStackIndex,node);
    if (elt)
	{
		elt->mWindow = window;
	}
}

void SoXipWindowLevelElement::setLevel(SoState* state, SoNode *node,float level)
{
	SoXipWindowLevelElement *elt = NULL;
	elt = (SoXipWindowLevelElement *) getElement(state, classStackIndex,node);
    if (elt)
	{
		elt->mLevel = level;
	}
}

float SoXipWindowLevelElement::getWindow( SoState* state )
{
	SoXipWindowLevelElement* elt = (SoXipWindowLevelElement *)
		getConstElement( state, classStackIndex );

	if (elt)
		return elt->mWindow;

	return (-1.f);
}

float SoXipWindowLevelElement::getLevel( SoState* state )
{
	SoXipWindowLevelElement* elt = (SoXipWindowLevelElement *)
		getConstElement( state, classStackIndex );

	if (elt)
		return elt->mLevel;

	return (-1.f);
}

