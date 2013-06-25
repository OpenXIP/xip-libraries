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
#include "SoXipMenuStyleElement.h"

SO_ELEMENT_SOURCE( SoXipMenuStyleElement );

SoXipMenuStyleElement::~SoXipMenuStyleElement()
{
}


void
SoXipMenuStyleElement::initClass()
{
	SO_ELEMENT_INIT_CLASS( SoXipMenuStyleElement, SoReplacedElement );
}

void
SoXipMenuStyleElement::init( SoState* )
{
	mMenuStyle = SbXipMenuStyle();
}


void
SoXipMenuStyleElement::set( SoState* state, SoNode* node, const SbXipMenuStyle& style )
{
    SoXipMenuStyleElement* elt = (SoXipMenuStyleElement *)
		getElement( state, classStackIndex, node );

    if( elt )
		elt->mMenuStyle = style;
}

SbBool
SoXipMenuStyleElement::matches( const SoElement* elt ) const
{
	return mMenuStyle == ((const SoXipMenuStyleElement *) elt)->mMenuStyle;
}

SoElement*
SoXipMenuStyleElement::copyMatchInfo() const
{
    SoXipMenuStyleElement* result = (SoXipMenuStyleElement *) getTypeId().createInstance();

	if( result )
	{
		result->mMenuStyle = mMenuStyle;
		return result;
	}

	return NULL;
}

SbXipMenuStyle
SoXipMenuStyleElement::get( SoState* state )
{
	const SoXipMenuStyleElement* elt = (const SoXipMenuStyleElement*)
		getConstElement( state, classStackIndex );
	
	return elt ? elt->mMenuStyle : SbXipMenuStyle();
}
