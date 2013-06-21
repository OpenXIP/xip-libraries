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
#include "SoXipDropShadowElement.h"

SO_ELEMENT_SOURCE( SoXipDropShadowElement );

SoXipDropShadowElement::~SoXipDropShadowElement()
{
}


void
SoXipDropShadowElement::initClass()
{
	SO_ELEMENT_INIT_CLASS( SoXipDropShadowElement, SoReplacedElement );
}

void
SoXipDropShadowElement::init( SoState* )
{
	mOn = FALSE;
	mColor = SbColor( 0, 0, 0 );
	mTransparency = 0;
	mPixelOffset = SbVec2s( 0, 0 );
}


void
SoXipDropShadowElement::set( SoState* state, SoNode* node,
							 SbBool on,
							 const SbColor& color,
							 float transparency,
							 const SbVec2s& pixelOffset )
{
    SoXipDropShadowElement* elt = (SoXipDropShadowElement *)
		getElement( state, classStackIndex, node );

    if( elt )
	{
		elt->mOn = on;
		elt->mColor = color;
		elt->mTransparency = transparency;
		elt->mPixelOffset = pixelOffset;
	}
}

SbBool
SoXipDropShadowElement::matches( const SoElement* elt ) const
{
	const SoXipDropShadowElement* dsElt = (const SoXipDropShadowElement *) elt;

	if( mOn == dsElt->mOn &&
		mColor == dsElt->mColor &&
		mTransparency == dsElt->mTransparency &&
		mPixelOffset == dsElt->mPixelOffset )
	{
		return TRUE;
	}

	return FALSE;
}

SoElement*
SoXipDropShadowElement::copyMatchInfo() const
{
    SoXipDropShadowElement* result = (SoXipDropShadowElement *) getTypeId().createInstance();

	if( result )
	{
		result->mOn = mOn;
		result->mColor = mColor;
		result->mTransparency = mTransparency;
		result->mPixelOffset = mPixelOffset;

		return result;
	}
	
	return NULL;
}

SbBool
SoXipDropShadowElement::isOn( SoState* state )
{
	const SoXipDropShadowElement* elt = (const SoXipDropShadowElement*)
		getConstElement( state, classStackIndex );
	
	return elt ? elt->mOn : FALSE;
}

SbColor
SoXipDropShadowElement::getColor( SoState* state )
{
	const SoXipDropShadowElement* elt = (const SoXipDropShadowElement*)
		getConstElement( state, classStackIndex );
	
	return elt ? elt->mColor : NULL;

}

float
SoXipDropShadowElement::getTransparency( SoState* state )
{
	const SoXipDropShadowElement* elt = (const SoXipDropShadowElement*)
		getConstElement( state, classStackIndex );
	
	return elt ? elt->mTransparency : 0;

}

SbVec2s
SoXipDropShadowElement::getPixelOffset( SoState* state )
{
	const SoXipDropShadowElement* elt = (const SoXipDropShadowElement*)
		getConstElement( state, classStackIndex );
	
	return elt ? elt->mPixelOffset : NULL;
}
